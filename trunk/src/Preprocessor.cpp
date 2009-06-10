/// @file
/// @brief Definition of Preprocessor class

#include "Preprocessor.hpp"
#include "Pattern.hpp"
#include "NessieException.hpp"
#include <boost/timer.hpp>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>



Preprocessor::Preprocessor (const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width)
:	clip_(0),
	clipHeight_(height),
	clipWidth_(width),
	statistics_(),
	regions_(0),
	delimiters_(0),
	inlineRegions_(),
	patterns_(0),
	averageCharacterHeight_(0.0),
	averageCharacterWidth_(0.0),
	averageSpaceBetweenCharacters_(0.0)
{
	if ( (height == 0) && (width == 0) )
		throw NessieException ("Preprocessor::Preprocessor() : Constructor has 0 size.");

	if ( width > page.columns() )
		throw NessieException ("Preprocessor::Preprocessor() : The press clip's width cannot be wider than the underlying page's.");

	if ( height > page.rows() )
		throw NessieException ("Preprocessor::Preprocessor() : The press clip's height cannot be higher than the underlying page's.");

	if ( x >= page.rows() || y >= page.columns() )
		throw NessieException ("Preprocessor::Preprocessor() : The press clip's top leftmost pixel falls outside the page.");

	if( (x + height) > page.rows() || (y + width) > page.columns() )
		throw NessieException ("Preprocessor::Preprocessor() : The clip does not fall completely within the underlying page.");

	// Create a view over the input image
	Magick::Pixels imageView(const_cast<Magick::Image&>(page));
	Magick::PixelPacket *pixels = imageView.get(x, y, clipWidth_, clipHeight_);

	// Traverse the view to get the pixel values
	Magick::ColorGray grayLevel;
	for ( unsigned int i = 0; i < clipHeight_; ++i )
	{
		for ( unsigned int j = 0; j < clipWidth_; ++j )
		{
			grayLevel = *pixels++;
			clip_.push_back( static_cast<unsigned char>(round(grayLevel.shade() * 255.0)) );
		}
	}

	statistics_.clipSize(clip_.size());
}


void Preprocessor::removeNoiseByLinearFiltering ()
{
	boost::timer timer;
	timer.restart();

	// Create the filtering mask
	int maskSize = 3;
	std::vector<double> mask(maskSize * maskSize);

	mask.at(0 * maskSize + 0) = 1.0;
	mask.at(0 * maskSize + 1) = 2.0;
	mask.at(0 * maskSize + 2) = 1.0;
	mask.at(1 * maskSize + 0) = 2.0;
	mask.at(1 * maskSize + 1) = 4.0;
	mask.at(1 * maskSize + 2) = 2.0;
	mask.at(2 * maskSize + 0) = 1.0;
	mask.at(2 * maskSize + 1) = 2.0;
	mask.at(2 * maskSize + 2) = 1.0;

	double grayLevel;
	for ( int i = 1; i < static_cast<int>(clipHeight_)-1; ++i )
	{
		for ( int j = 1; j < static_cast<int>(clipWidth_)-1; ++j )
		{
			grayLevel = 0.0;

			// Compute the averaged gray level of the actual pixel
			for ( int filterI = 0; filterI < maskSize; ++filterI )
			{
				for ( int filterJ = 0; filterJ < maskSize; ++filterJ )
				{
					if ((i+filterI-1) >= 0 && (i+filterI-1) < static_cast<int>(clipHeight_) && (j+filterJ-1) >= 0 && (j+filterJ-1) < static_cast<int>(clipWidth_))
						grayLevel += mask.at(filterI * maskSize + filterJ) * static_cast<double>(clip_.at((i+filterI-1) * clipWidth_ + (j+filterJ-1)));
				}
			}

			// Apply a specific filter when dealing with clip borders
			if ( i == 0 || i == (static_cast<int>(clipHeight_)-1) || j == 0 || j == (static_cast<int>(clipWidth_)-1) )
				grayLevel = grayLevel * 0.083333333;
			else
				grayLevel = grayLevel * 0.0625;

			// Truncate unexpected gray level values
			if ( grayLevel > 255.0 )
				grayLevel = 255.0;

			if ( grayLevel < 0.0 )
				grayLevel = 0.0;

			// Update actual pixel's gray level
			clip_.at(i * clipWidth_ + j) = static_cast<unsigned char>(round(grayLevel));
		}
	}

	statistics_.averagingFilteringTime(timer.elapsed());
}


/// @brief		Computes the optimal threshold value in a press clip following the Otsu's algorithm.
///
/// @details	The strategy proposed by N. Otsu in "A Threshold Selection Method from Gray-Level Histograms" (1979) maximises the likelihood that the
/// threshold is chosen so as to split the image between and object and its background. An optimal threshold is selected by the discriminant
/// criterion, namely, so as to maximize the separability of the resultant classes in gray levels. The procedure is very simple, utilizing only the
/// zeroth- and the first-order cumulative moments of the gray-level histogram.
///
/// @param		clip	The input press clip.
///	@param		height	Clip height in pixels.
///	@param		width	Clip width in pixels.
///
///	@return		A unsigned char with the optimal threshold value in a scale of [0,255].
unsigned char computeOtsuOptimalThreshold (const std::vector<unsigned char>& clip, const unsigned int& height, const unsigned int& width)
{
	// Compute the normalized clip histogram
	std::vector<double> histogram(256, 0.0);

	for ( unsigned int i = 0; i < height; ++i )
	{
		for ( unsigned int j = 0; j < width; ++j )
		{
			unsigned int grayLevel = static_cast<unsigned int>(clip.at(i * width + j));

			histogram.at(grayLevel) += 1.0;
		}
	}
	std::transform (histogram.begin(), histogram.end(), histogram.begin(), std::bind2nd(std::divides<double>(), clip.size()) );

	// Compute the total mean gray level of the clip
	double totalMeanGrayLevel = 0.0;
	for ( unsigned int i = 1; i <= histogram.size(); ++i )
		totalMeanGrayLevel += histogram.at(i-1) * static_cast<double>(i);

	// Compute the zeroth- and first-order cumulative moments, i.e. the probabilities of class occurrence and the
	// class mean levels up to level i-th.
	std::vector<double> zerothOrderMoment(256, 0.0);
	std::vector<double> firstOrderMoment(256, 0.0);
	for ( unsigned int i = 0; i < histogram.size(); ++i )
	{
		for ( unsigned int j = 0; j < i; ++j )
		{
			zerothOrderMoment.at(i)	+= histogram.at(j);
			firstOrderMoment.at(i)	+= static_cast<double>(j+1) * histogram.at(j);
		}
	}

	// Compute the between-class variance, according to the criterion measurements used in the discriminant analysis
	std::vector<double> betweenClassVariance(256, 0.0);
	for ( unsigned int i = 0; i < histogram.size(); ++i )
	{
		double numerator = pow(totalMeanGrayLevel * zerothOrderMoment.at(i) - firstOrderMoment.at(i), 2);
		double denominator = zerothOrderMoment.at(i) * (1 - zerothOrderMoment.at(i));

		if ( std::isnan(numerator / denominator) )
			betweenClassVariance.at(i) = 0.0;
		else
			betweenClassVariance.at(i) = numerator / denominator;
	}

	// Find the gray level that maximizes the between-class variance
	std::vector<double>::iterator maximumVariance = std::max_element(betweenClassVariance.begin(), betweenClassVariance.end());
	std::vector<double>::iterator i = betweenClassVariance.begin();
	unsigned char optimalThreshold = 0;

	while ( i != maximumVariance )
	{
		++i;
		++optimalThreshold;
	}

	return optimalThreshold;
}


void Preprocessor::applyGlobalThresholding ()
{
	boost::timer timer;
	timer.restart();

	// Get the optimal threshold
	unsigned char threshold = computeOtsuOptimalThreshold(clip_, clipHeight_, clipWidth_);

	// Compute the background gray level and its complementary gray level for the ink
	unsigned int backgroundAverageGrayLevel = 0;
	backgroundAverageGrayLevel += clip_.at(0 * clipWidth_ + 0);
	backgroundAverageGrayLevel += clip_.at(0 * clipWidth_ + clipWidth_);
	backgroundAverageGrayLevel += clip_.at((clipHeight_-1) * clipWidth_ + 0);
	backgroundAverageGrayLevel += clip_.at((clipHeight_-1) * clipWidth_ + (clipWidth_-1));
	backgroundAverageGrayLevel = backgroundAverageGrayLevel / 4;

	unsigned char ink, background;
	if ( backgroundAverageGrayLevel <= threshold )
	{
		ink = 0;
		background = 1;
	}
	else
	{
		ink = 1;
		background = 0;
	}

	// Binarize image
	std::replace_if (clip_.begin(), clip_.end(), std::bind2nd(std::less_equal<unsigned char>(), threshold), ink);
	std::replace_if (clip_.begin(), clip_.end(), std::bind2nd(std::greater<unsigned char>(), threshold), background);

	statistics_.optimalThreshold(threshold);
	statistics_.globalThresholdingTime(timer.elapsed());
}


void Preprocessor::removeNoiseByTemplateMatching ()
{
	boost::timer timer;
	timer.restart();

	unsigned int equalPixels;

	// Apply first filter mask, checking neighbour pixels above the target pixel
	int upperRow;
	for ( int i = clipHeight_-1; i >= 0; --i )
	{
		for ( int j = clipWidth_-1; j >= 0; --j )
		{
			upperRow = i-1;

			if ( upperRow >= 0 )
			{
				equalPixels = 1;

				if ( j > 0 )
				{
					if ( clip_.at(upperRow * clipWidth_ + j) == clip_.at(upperRow * clipWidth_ + j-1) && clip_.at(upperRow * clipWidth_ + j-1) == clip_.at(i * clipWidth_ + j-1) )
						equalPixels += 2;
				}

				if ( j < static_cast<int>(clipWidth_)-1 )
				{
					if ( clip_.at(upperRow * clipWidth_ + j) == clip_.at(upperRow * clipWidth_ + j+1) && clip_.at(upperRow * clipWidth_ + j+1) == clip_.at(i * clipWidth_ + j+1) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_.at(i * clipWidth_ + j) = clip_.at(upperRow * clipWidth_ + j);
			}
		}
	}

	// Apply second filter mask, checking neighbour pixels below the target pixel
	int lowerRow;
	for ( int i = clipHeight_-1; i >= 0; --i )
	{
		for ( int j = clipWidth_-1; j >= 0; --j )
		{
			lowerRow = i+1;

			if ( lowerRow < static_cast<int>(clipHeight_) )
			{
				equalPixels = 1;

				if ( j > 0 )
				{
					if ( clip_.at(lowerRow * clipWidth_ + j) == clip_.at(lowerRow * clipWidth_ + j-1) && clip_.at(lowerRow * clipWidth_ + j-1) == clip_.at(i * clipWidth_ + j-1) )
						equalPixels += 2;
				}

				if ( j < static_cast<int>(clipWidth_)-1 )
				{
					if ( clip_.at(lowerRow * clipWidth_ + j) == clip_.at(lowerRow * clipWidth_ + j+1) && clip_.at(lowerRow * clipWidth_ + j+1) == clip_.at(i * clipWidth_ + j+1) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_.at(i * clipWidth_ + j) =  clip_.at(lowerRow * clipWidth_ + j);
			}
		}
	}

	// Apply third filter mask, checking neighbour pixels on the left of target pixel
	int leftColumn;
	for ( int i = clipHeight_-1; i >= 0; --i )
	{
		for ( int j = clipWidth_-1; j >= 0; --j )
		{
			leftColumn = j-1;

			if ( leftColumn >= 0 )
			{
				equalPixels = 1;

				if ( i > 0 )
				{
					if ( clip_.at(i * clipWidth_ + leftColumn) == clip_.at((i-1) * clipWidth_ + leftColumn) && clip_.at((i-1) * clipWidth_ + leftColumn) == clip_.at((i-1) * clipWidth_ + j) )
						equalPixels += 2;
				}

				if ( i < static_cast<int>(clipHeight_)-1 )
				{
					if ( clip_.at(i * clipWidth_ + leftColumn) == clip_.at((i+1) * clipWidth_ + leftColumn) && clip_.at((i+1) * clipWidth_ + leftColumn) == clip_.at((i+1) * clipWidth_ + j) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_.at(i * clipWidth_ + j) =  clip_.at(i * clipWidth_ + leftColumn);
			}
		}
	}

	// Apply fourth filter mask, checking neighbour pixels on the right of target pixel
	int rightColumn;
	for ( int i = clipHeight_-1; i >= 0; --i )
	{
		for ( int j = clipWidth_-1; j >= 0; --j )
		{
			rightColumn = j+1;

			if ( rightColumn < static_cast<int>(clipWidth_) )
			{
				equalPixels = 1;

				if ( i > 0 )
				{
					if ( clip_.at(i * clipWidth_ + rightColumn) == clip_.at((i-1) * clipWidth_ + rightColumn) && clip_.at((i-1) * clipWidth_ + rightColumn) == clip_.at((i-1) * clipWidth_ + j) )
						equalPixels += 2;
				}

				if ( i < static_cast<int>(clipHeight_)-1 )
				{
					if ( clip_.at(i * clipWidth_ + rightColumn) == clip_.at((i+1) * clipWidth_ + rightColumn) && clip_.at((i+1) * clipWidth_ + rightColumn) == clip_.at((i+1) * clipWidth_ + j) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_.at(i * clipWidth_ + j) =  clip_.at(i * clipWidth_ + rightColumn);
			}
		}
	}

	statistics_.templateFilteringTime(timer.elapsed());
}


/// @brief	Auxiliary function object to use in accumulate algorithm inside isolateRegions().
///
/// @param	x		Value to update.
/// @param	region	Reference value to use in update
///
/// @return The accumulated height of input string 'region'.
struct accumulateHeightIncrement : std::binary_function <double,Region,double>
{
	double operator() (const double& x, const Region& region) const
	{
		return (x + region.height());
	}
};


/// @brief	Auxiliary function object to use in accumulate algorithm inside isolateRegions().
///
/// @param	x		Value to update.
/// @param	region	Reference value to use in update
///
/// @return The accumulated width of input string 'region'.
struct accumulateWidthIncrement : std::binary_function <double,Region,double>
{
	double operator() (const double& x, const Region& region) const
	{
		return (x + region.width());
	}
};


std::vector<unsigned int> Preprocessor::isolateRegions ()
{
	boost::timer timer;
	timer.restart();

	// Traverse the press clip searching the ink pixels where the flooding process will start from
	std::vector<PixelCoordinates> seeds(0);
	seeds.reserve(clip_.size());
	for ( unsigned int i = 0; i < clipHeight_; ++i )
	{
		for ( unsigned int j = 0; j < clipWidth_; ++j )
		{
			if ( clip_.at(i * clipWidth_ + j) == 1 )
				seeds.push_back( PixelCoordinates(i,j) );
		}
	}

	// Build the initial list of regions by applying the flooding algorithm
	regions_.clear();
	std::deque<bool> visited(clip_.size(), false);
	for ( std::vector<PixelCoordinates>::iterator s = seeds.begin(); s != seeds.end(); ++s )
	{
		int row		= s->first;
		int column	= s->second;

		if ( not visited.at(row * clipWidth_ + column) )
		{
			visited.at(row * clipWidth_ + column) = true;

			// This seed begins a new region
			Region region;
			region.addCoordinates( PixelCoordinates(row, column) );

			// Explore the immediate neighbourhood
			for ( int i = row-1; (i <= row+1) && (i < static_cast<int>(clipHeight_)); ++i )
			{
				for ( int j = column-1; (j <= column+1) && (j < static_cast<int>(clipWidth_)); ++j )
				{
					if ( i >= 0 && j >= 0 )
					{
						if ( clip_.at(i * clipWidth_ + j) == 1 && not visited.at(i * clipWidth_ + j) )
						{
							visited.at(i * clipWidth_ + j) = true;
							region.addCoordinates( PixelCoordinates(i,j) );
						}
					}
				}
			}

			// Explore the neighbours of the neighbours
			unsigned int k = 1;
			while ( region.size() > k )
			{
				PixelCoordinates coordinates( region.at(k) );

				for ( int i = coordinates.first-1; (i <= static_cast<int>(coordinates.first+1)) && (i < static_cast<int>(clipHeight_)); ++i )
				{
					for ( int j = coordinates.second-1; (j <= static_cast<int>(coordinates.second+1)) && (j < static_cast<int>(clipWidth_)); ++j )
					{
						if ( i >= 0 && j >= 0 )
						{
							if ( clip_.at(i * clipWidth_ + j) == 1 && not visited.at(i * clipWidth_ + j) )
							{
								visited.at(i * clipWidth_ + j) = true;
								region.addCoordinates( PixelCoordinates(i, j) );
							}
						}
					}
				}
				++k;
			}

			regions_.push_back(region);
		}
	}

	findLineDelimiters(visited);
	organizeRegionsIntoLines();

	mergeVerticallyOverlappedRegions();

	averageCharacterHeight_ = std::accumulate (regions_.begin(), regions_.end(), 0.0, accumulateHeightIncrement()) / regions_.size();
	averageCharacterWidth_ = std::accumulate (regions_.begin(), regions_.end(), 0.0, accumulateWidthIncrement()) / regions_.size();

	for( RegionLines::iterator i = inlineRegions_.begin(); i != inlineRegions_.end(); ++i )
		sortRegions(i->second);

	std::vector<unsigned int> spaceLocations = findSpacesBetweenWords();
	statistics_.nRegions(regions_.size());
	statistics_.nLines(delimiters_.size());
	statistics_.averageCharacterHeight(averageCharacterHeight_);
	statistics_.averageCharacterWidth(averageCharacterWidth_);
	statistics_.segmentationTime(timer.elapsed());

	return spaceLocations;
}


void Preprocessor::findLineDelimiters (const std::deque<bool>& visited)
{
	delimiters_.clear();

	// Traverse each row searching non-visited pixels
	unsigned int topRowOfTextLine = 0;
	bool rowHasInk = false, previousRowHasInk;

	for ( unsigned int i = 0; i < clipHeight_; ++i )
	{
		previousRowHasInk	= rowHasInk;
		rowHasInk			= false;

		for ( unsigned int j = 0; j < clipWidth_; ++j )
		{
			if ( visited.at(i * clipWidth_ + j) )
			{
				rowHasInk = true;
				break;
			}
		}

		if (not rowHasInk )
		{
			if ( previousRowHasInk )
				delimiters_.push_back( LineDelimiter(topRowOfTextLine, i-1) );
			else
				topRowOfTextLine = i;
		}
		else
		{
			if ( not previousRowHasInk )
				topRowOfTextLine = i;
		}
	}

	// Make sure the last text line joins with the clip border
	if ( rowHasInk )
		delimiters_.push_back( LineDelimiter(topRowOfTextLine, clipHeight_-1) );

	LineDelimiterIterator previousLineDelimiterIterator = delimiters_.begin();
	LineDelimiterIterator currentLineDelimiterIterator	= delimiters_.begin();
	advance( currentLineDelimiterIterator, 1 );

	// Search lines that are too close to each other, probably because there are accents belonging to characters on a single line
	while ( currentLineDelimiterIterator != delimiters_.end() )
	{
		unsigned int currentLineHeight	= currentLineDelimiterIterator->second - currentLineDelimiterIterator->first + 1;
		unsigned int previousLineHeight	= previousLineDelimiterIterator->second - previousLineDelimiterIterator->first + 1;

		if ( previousLineHeight > (currentLineHeight / 2) )
		{
			advance( currentLineDelimiterIterator, 1 );
			advance( previousLineDelimiterIterator, 1 );
		}
		else
		{
			// A new line delimiter is inserted by joining the two line delimiters explored.
			delimiters_.insert( previousLineDelimiterIterator, LineDelimiter(previousLineDelimiterIterator->first, currentLineDelimiterIterator->second) );

			LineDelimiterIterator newLineDelimiterIterator = previousLineDelimiterIterator;
			advance ( newLineDelimiterIterator, -1 );

			// The two old line delimiters are removed from the list
			delimiters_.erase( previousLineDelimiterIterator );
			previousLineDelimiterIterator = currentLineDelimiterIterator;

			advance( currentLineDelimiterIterator, 1 );
			delimiters_.erase( previousLineDelimiterIterator );

			previousLineDelimiterIterator = newLineDelimiterIterator;
		}
	}
}


/// @brief	Auxiliary function object to use in find_if algorithm inside organizeRegionsIntoLines method.
///
/// @param	delimiters	Pair of x-axis coordinates that delimits a line of characters.
/// @param	row			X-axis coordinate of a row.
///
/// @return True if the row falls within the limits imposed by the delimiters. False otherwise.
struct rowWithinLimits : std::binary_function <std::pair<unsigned int, unsigned int>, unsigned int, bool>
{
	bool operator() (const std::pair<unsigned int, unsigned int>& delimiter, const unsigned int& row) const
	{
		if ( row >= delimiter.first && row <= delimiter.second )
			return true;
		else
			return false;
	}
};


void Preprocessor::organizeRegionsIntoLines()
{
	inlineRegions_.clear();

	unsigned int centerRow;
	for ( RegionIterator i = regions_.begin(); i != regions_.end(); ++i  )
	{
		// Find the delimiters where the actual region falls.
		centerRow = (i->bottomBorderRow() + i->topBorderRow()) / 2;
		LineDelimiterIterator j = std::find_if(delimiters_.begin(), delimiters_.end(), std::bind2nd(rowWithinLimits(), centerRow));

		// Update the list of iterators to regions
		unsigned int index = std::distance(delimiters_.begin(), j);
		if ( inlineRegions_.count(index) == 0 )
			inlineRegions_.insert( std::pair<unsigned int, std::list<RegionIterator> >(index, std::list<RegionIterator>(1,i)) );
		else
			inlineRegions_[index].push_back(i);
	}
}


void Preprocessor::mergeVerticallyOverlappedRegions ()
{
	// Traverse each line of regions searching for pairs of overlapped elements.
	for( RegionLines::iterator i = inlineRegions_.begin(); i != inlineRegions_.end(); ++i )
	{
		std::list<RegionIterator>::iterator j(i->second.begin());

		while ( j != i->second.end() )
		{
			std::list<RegionIterator>::iterator k = j;
			advance(k,1);

			// Search a region within the line overlapped with the actual one
			while ( k != i->second.end() )
			{
				unsigned int centroidJcolumn = ((*j)->leftBorderColumn() + (*j)->rightBorderColumn()) / 2;
				unsigned int centroidKcolumn = ((*k)->leftBorderColumn() + (*k)->rightBorderColumn()) / 2;

				if ( (centroidKcolumn > (*j)->leftBorderColumn() && centroidKcolumn < (*j)->rightBorderColumn()) || (centroidJcolumn > (*k)->leftBorderColumn() && centroidJcolumn < (*k)->rightBorderColumn()) )
					break;
				else
					advance(k, 1);
			}

			// Merge both regions in a new region if they are overlapped. The old regions are erased from the list of regions
			// and the list of iterator to the regions.
			if ( k != i->second.end() && j != k )
			{
				// Create a new region by merging and append it to the list of iterators
				i->second.push_back( regions_.insert(regions_.end(), *(*j) + *(*k)) );

				// Erase the second region and its iterator
				regions_.erase(*k);
				i->second.erase(k);

				// Erase the first region and its iterator
				regions_.erase(*j);
				std::list<RegionIterator>::iterator tmp(j);
				advance(tmp, 1);
				i->second.erase(j);

				// Point the iterator to the next element
				j = tmp;
			}
			else
				advance(j, 1);
		}
	}
}


void Preprocessor::sortRegions (std::list<RegionIterator>& regions)
{
	for ( std::list<RegionIterator>::iterator i = regions.begin(); i != regions.end(); ++i )
	{
		if ( i == regions.begin() )
			continue;

		// Get current element
		RegionIterator value = *i;

		// Get previous element
		std::list<RegionIterator>::reverse_iterator j = regions.rbegin();
		advance(j, distance(i, regions.end()));

		// Shift elements until finding final position
		while ( j != regions.rend() && *value < *(*j) )
		{
			std::list<RegionIterator>::reverse_iterator k = j;
			--k;
			*k = *j;

			++j;
		}

		// Insert current element into its final position
		std::list<RegionIterator>::reverse_iterator k = j;
		--k;
		*k = value;
	}
};


std::vector<unsigned int> Preprocessor::findSpacesBetweenWords ()
{
	averageSpaceBetweenCharacters_ = 0.0;

	// Compute the average space between characters
	for( RegionLines::iterator k = inlineRegions_.begin(); k != inlineRegions_.end(); ++k )
	{
		std::list<RegionIterator> line(k->second);
		std::list<RegionIterator>::iterator i(line.begin());
		std::list<RegionIterator>::iterator j(i);
		advance(j, 1);

		while ( j != line.end() )
		{
			averageSpaceBetweenCharacters_ += static_cast<int>((*j)->leftBorderColumn()) - static_cast<int>((*i)->rightBorderColumn()) + 1;

			advance (i, 1);
			advance (j, 1);
		}
	}
	averageSpaceBetweenCharacters_ = averageSpaceBetweenCharacters_ / regions_.size();

	std::vector<unsigned int> spaces(0);
	unsigned int spaceLocation = 1;

	// Traverse the lines of regions detecting a space between two regions greater than the average space.
	for( RegionLines::iterator k = inlineRegions_.begin(); k != inlineRegions_.end(); ++k )
	{
		std::list<RegionIterator> line(k->second);
		std::list<RegionIterator>::iterator i(line.begin());
		std::list<RegionIterator>::iterator j(i);
		advance(j, 1);

		while ( j != line.end() )
		{
			int distanceBetweenRegions = static_cast<int>((*j)->leftBorderColumn()) - static_cast<int>((*i)->rightBorderColumn()) + 1;

			if ( distanceBetweenRegions > (averageSpaceBetweenCharacters_ / 0.5) )
				spaces.push_back(spaceLocation);

			++spaceLocation;
			advance (i, 1);
			advance (j, 1);
		}

		spaces.push_back(spaceLocation);
		++spaceLocation;
	}

	statistics_.averageSpaceBetweenCharacters( averageSpaceBetweenCharacters_ );
	return spaces;
}


void Preprocessor::buildPatterns ()
{
	boost::timer timer;
	timer.restart();

	patterns_.clear();
	patterns_.reserve(regions_.size());
	Pattern pattern;

	// Traverse the list of iterators to regions creating a Pattern object for each region
	for( RegionLines::iterator k = inlineRegions_.begin(); k != inlineRegions_.end(); ++k )
	{
		std::list<RegionIterator> line(k->second);

		for( std::list<RegionIterator>::iterator i = line.begin(); i != line.end(); ++i )
		{
			(*i)->normalizeCoordinates();

			// Normalize region using Magick++ facilities
			Magick::Image image( Magick::Geometry((*i)->width(), (*i)->height()), Magick::ColorGray(1.0) );
			image.type( Magick::BilevelType );

			Magick::Pixels view(image);
			Magick::PixelPacket *originPixel = view.get(0, 0, (*i)->width(), (*i)->height());
			Magick::PixelPacket *pixel;

			for ( unsigned int j = 0; j < (*i)->size(); ++j )
			{
				pixel	= originPixel + ((*i)->at(j).first * view.columns() + (*i)->at(j).second);
				*pixel	= Magick::ColorGray (0.0);
			}
			view.sync();
			image.syncPixels();
			image.sample( Magick::Geometry(Pattern::planeSize(), Pattern::planeSize()) );

			// Preprocess the normalized region
			Preprocessor temporalPreprocessor (image, 0, 0, image.rows(), image.columns());
			temporalPreprocessor.applyGlobalThresholding();
			temporalPreprocessor.isolateRegions();

			Region normalizedRegion;

			// Merge subregions if preprocessing splitted the original region
			if ( temporalPreprocessor.regions_.size() > 1 )
			{
				for ( RegionIterator j = temporalPreprocessor.regions_.begin(); j != temporalPreprocessor.regions_.end(); ++j )
					normalizedRegion = normalizedRegion + *j;

				temporalPreprocessor.regions_.clear();
				temporalPreprocessor.regions_.push_back(normalizedRegion);
			}
			else
				normalizedRegion = temporalPreprocessor.regions_.front();

			// Build the pattern
			pattern.clean();
			for ( unsigned int i = 0; i < normalizedRegion.size(); ++i )
				pattern.at(normalizedRegion.at(i).first, normalizedRegion.at(i).second) = 1;

			// Correct shifting
			if ( image.rows() < Pattern::planeSize() )	// Shift rows from top to the center
			{
				unsigned int offset = (Pattern::planeSize() - image.rows()) / 2;

				while ( offset != 0 )
				{
					for ( int i = Pattern::planeSize()-2; i >= 0; --i )
					{
						for ( unsigned int j = 0; j < Pattern::planeSize(); ++j )
							pattern.at(i+1, j) = pattern.at(i, j);
					}
					for ( unsigned int j = 0; j < Pattern::planeSize(); ++j )
						pattern.at(0, j) = 0;

					--offset;
				}
			}

			if ( image.columns() < Pattern::planeSize() )	// Shift columns from left to center
			{
				unsigned int offset = (Pattern::planeSize() - image.columns()) / 2;

				while ( offset != 0 )
				{
					for ( unsigned int i = 0; i < Pattern::planeSize(); ++i )
					{
						for ( int j = Pattern::planeSize()-2; j >= 0; --j )
							pattern.at(i, j+1) = pattern.at(i, j);
					}
					for ( unsigned int i = 0; i < Pattern::planeSize(); ++i )
						pattern.at(i, 0) = 0;

					--offset;
				}
			}

			patterns_.push_back( pattern );
		}
	}

	statistics_.patternsBuildingTime(timer.elapsed());
}


void Preprocessor::skeletonizePatterns()
{
	boost::timer timer;
	timer.restart();

	for ( std::vector<Pattern>::iterator p = patterns_.begin(); p != patterns_.end(); ++p )
	{
		bool pixelsHaveBeenRemoved = true;
		while ( pixelsHaveBeenRemoved )
		{
			pixelsHaveBeenRemoved = false;

			// Step 1 of Zhang-Suen algorithm
			std::deque<bool> removablePixels(p->size(), false);
			for ( int i = 0; i < static_cast<int>(p->height()); ++i )
			{
				for ( int j = 0; j < static_cast<int>(p->width()); ++j )
				{
					if ( p->at(i,j) == 0 )	// Skip background pixels
						continue;

					unsigned int p2 = ( i-1 > 0 ) ? p->at(i-1,j) : 0;
					unsigned int p9 = ( i-1 > 0 && j-1 > 0 ) ? p->at(i-1,j-1) : 0;
					unsigned int p3 = ( i-1 > 0 && j+1 < static_cast<int>(p->width()) ) ? p->at(i-1,j+1) : 0;

					unsigned int p6 = ( i+1 < static_cast<int>(p->height()) ) ? p->at(i+1,j) : 0;
					unsigned int p7 = ( i+1 < static_cast<int>(p->height()) && j-1 > 0 ) ? p->at(i+1,j-1) : 0;
					unsigned int p5 = ( i+1 < static_cast<int>(p->height()) && j+1 < static_cast<int>(p->width()) ) ? p->at(i+1,j+1) : 0;

					unsigned int p8 = ( j-1 > 0 ) ? p->at(i,j-1) : 0;
					unsigned int p4 = ( j+1 < static_cast<int>(p->width()) ) ? p->at(i,j+1) : 0;
					unsigned int nonBackgroundNeighbours = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;

					unsigned int zeroToOneTransitions = 0;
					zeroToOneTransitions += (p2 == 0 && p3 == 1)?1:0;
					zeroToOneTransitions += (p3 == 0 && p4 == 1)?1:0;
					zeroToOneTransitions += (p4 == 0 && p5 == 1)?1:0;
					zeroToOneTransitions += (p5 == 0 && p6 == 1)?1:0;
					zeroToOneTransitions += (p6 == 0 && p7 == 1)?1:0;
					zeroToOneTransitions += (p7 == 0 && p8 == 1)?1:0;
					zeroToOneTransitions += (p8 == 0 && p9 == 1)?1:0;
					zeroToOneTransitions += (p9 == 0 && p2 == 1)?1:0;

					bool isRemovable = true;
					if ( !(2 <= nonBackgroundNeighbours && nonBackgroundNeighbours <= 6) )
						isRemovable = false;

					if ( zeroToOneTransitions != 1 )
						isRemovable = false;

					if ( p2*p4*p6 != 0 )
						isRemovable = false;

					if ( p4*p6*p8 != 0 )
						isRemovable = false;

					removablePixels.at(i * p->width() + j) = isRemovable;
				}
			}

			for ( unsigned int i = 0; i < p->height(); ++i )
			{
				for ( unsigned int j = 0; j < p->width(); ++j )
				{
					if ( removablePixels.at(i * p->width() + j) )
					{
						p->at(i,j) = 0;
						pixelsHaveBeenRemoved = true;
					}
				}
			}

			// Step 2
			removablePixels.assign(p->size(), false);
			for ( int i = 0; i < static_cast<int>(p->height()); ++i )
			{
				for ( int j = 0; j < static_cast<int>(p->width()); ++j )
				{
					if ( p->at(i,j) == 0 )	// Skip background pixels
						continue;

					unsigned int p2 = ( i-1 > 0 ) ? p->at(i-1,j) : 0;
					unsigned int p9 = ( i-1 > 0 && j-1 > 0 ) ? p->at(i-1,j-1) : 0;
					unsigned int p3 = ( i-1 > 0 && j+1 < static_cast<int>(p->width()) ) ? p->at(i-1,j+1) : 0;

					unsigned int p6 = ( i+1 < static_cast<int>(p->height()) ) ? p->at(i+1,j) : 0;
					unsigned int p7 = ( i+1 < static_cast<int>(p->height()) && j-1 > 0 ) ? p->at(i+1,j-1) : 0;
					unsigned int p5 = ( i+1 < static_cast<int>(p->height()) && j+1 < static_cast<int>(p->width()) ) ? p->at(i+1,j+1) : 0;

					unsigned int p8 = ( j-1 > 0 ) ? p->at(i,j-1) : 0;
					unsigned int p4 = ( j+1 < static_cast<int>(p->width()) ) ? p->at(i,j+1) : 0;
					unsigned int nonBackgroundNeighbours = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;

					unsigned int zeroToOneTransitions = 0;
					zeroToOneTransitions += (p2 == 0 && p3 == 1)?1:0;
					zeroToOneTransitions += (p3 == 0 && p4 == 1)?1:0;
					zeroToOneTransitions += (p4 == 0 && p5 == 1)?1:0;
					zeroToOneTransitions += (p5 == 0 && p6 == 1)?1:0;
					zeroToOneTransitions += (p6 == 0 && p7 == 1)?1:0;
					zeroToOneTransitions += (p7 == 0 && p8 == 1)?1:0;
					zeroToOneTransitions += (p8 == 0 && p9 == 1)?1:0;
					zeroToOneTransitions += (p9 == 0 && p2 == 1)?1:0;

					bool isRemovable = true;
					if ( !(2 <= nonBackgroundNeighbours && nonBackgroundNeighbours <= 6) )
						isRemovable = false;

					if ( zeroToOneTransitions != 1 )
						isRemovable = false;

					if ( p2*p4*p8 != 0 )
						isRemovable = false;

					if ( p2*p6*p8 != 0 )
						isRemovable = false;

					removablePixels.at(i * p->width() + j) = isRemovable;
				}
			}

			for ( unsigned int i = 0; i < p->height(); ++i )
			{
				for ( unsigned int j = 0; j < p->width(); ++j )
				{
					if ( removablePixels.at(i * p->width() + j) )
					{
						p->at(i,j) = 0;
						pixelsHaveBeenRemoved = true;
					}
				}
			}
		}
	}

	statistics_.skeletonizationTime(timer.elapsed());
}



#include <iostream>
void Preprocessor::correctSlanting ()
{
	boost::timer timer;
	timer.restart();

	const double PI = 3.1415926535;

	for ( std::vector<Pattern>::iterator i = patterns_.begin(); i != patterns_.end(); ++i )
	{
	    const unsigned int rotationLimit = 20;
		double shearingFactor;;

	    // This vector stores the greatest number of ink pixels counted in any column of a rotated pattern.
		std::vector<unsigned int> columnPixelMaximalCounts(rotationLimit);

		// Rotate the pattern and count the number of ink pixels per column
		for ( double angle = 0; angle < rotationLimit; ++angle )
		{
			std::map<unsigned int, std::set<unsigned int> > pixelsPerColumn;
			shearingFactor = tan(-angle * PI / 180.0);

			// Store the columns of rotated pixels
			for ( unsigned int j = 0; j < i->height(); ++j )
			{
				for ( unsigned int k = 0; k < i->width(); ++k )
				{
					if ( i->at(j,k) == 1 )  // Ink pixel
					{
						double jp = j;
						double kp = k;
						kp = round(kp - jp * shearingFactor);

						if ( kp < i->width() && kp > 0 )
							pixelsPerColumn[kp].insert(j);
					}
				}
			}

			unsigned int columnPixelMaximalCount = 0;
			for ( std::map<unsigned int, std::set<unsigned int> >::iterator row = pixelsPerColumn.begin(); row != pixelsPerColumn.end(); ++row )
			{
				if ( row->second.size() > columnPixelMaximalCount )
					columnPixelMaximalCount = row->second.size();
			}
			
			columnPixelMaximalCounts.at(angle) = columnPixelMaximalCount;
		}

		// Get the angle to rotate selecting the rotation that generates the maximal number of pixels in a column
		double targetAngle = distance( columnPixelMaximalCounts.begin(), std::max_element(columnPixelMaximalCounts.begin(), columnPixelMaximalCounts.end()) );
		shearingFactor = tan(-targetAngle * PI / 180.0);

		// Correct slanting of the actual pattern
		if ( targetAngle != 0 )
		{
			Pattern rotatedPattern;
			rotatedPattern.clean();

			for ( unsigned int j = 0; j < i->height(); ++j )
			{
				for ( unsigned int k = 0; k < i->width(); ++k )
				{
					if ( i->at(j,k) == 1 )
					{
						double jp = j;
						double kp = k;
						kp = round(kp - jp * shearingFactor);

						if ( kp < i->width() && kp > 0 )
							rotatedPattern.at(jp, kp) = 1;
					}
				}
			}
			*i = rotatedPattern;
		}
	}

	statistics_.slantingCorrectionTime(timer.elapsed());;
}


void Preprocessor::writeClipToOutputImage (const std::string& outputFile, const double& scalingFactor) const
{
	// Create a new Image object
	Magick::Image outputImage = Magick::Image(Magick::Geometry(clipWidth_, clipHeight_), Magick::ColorGray(1.0));
	outputImage.type( Magick::GrayscaleType );

	// Create a view over the image
	Magick::Pixels imageView(outputImage);
	Magick::PixelPacket *originPixel = imageView.get(0, 0, clipWidth_, clipHeight_);
	Magick::PixelPacket *pixel;

	// Assign values to the image pixels
	for ( unsigned int i = 0; i < imageView.rows(); ++i )
	{
		for ( unsigned int j = 0; j < imageView.columns(); ++j )
		{
			pixel = originPixel + (i * imageView.columns()) + j;

			*pixel = Magick::ColorGray ( static_cast<double>(clip_.at(i * clipWidth_ + j)) / scalingFactor );
		}
	}

	// Synchronize and write changes to disc
	imageView.sync();
	outputImage.syncPixels();
	outputImage.write(outputFile);
}


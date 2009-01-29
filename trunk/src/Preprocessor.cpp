/// @file
/// @brief Definition of Preprocessor class

#include "Preprocessor.hpp"
#include <boost/timer.hpp>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

Preprocessor::Preprocessor (const Clip& pressClip)
:	clip_(pressClip),
	statistics_(PreprocessorStatistics()),
	regions_(std::list<Region>(0))
{
	statistics_.clipSize(pressClip.size());
};


/// @details The algorithm uses the Otsu's method to find automatically the optimal threshold for the press clip. Then, it compares each pixel
/// gray level with that threshold and transforms the source clip into a binary image. As a result, the final histogram is bimodal. The algorithm
/// also assumes that gray levels in the press clip above the threshold belong to the background, while gray levels below belong to the ink.
/// 
/// @todo Avoid the assumption made about background's gray level. Sometimes a press clip background comes in dark gray levels and the ink in light
/// ones. Some function should be developed to automatically make the right decision.
void Preprocessor::applyGlobalThresholding ()
{
	boost::timer timer;
	timer.restart();

	unsigned char threshold = computeOtsuOptimalThreshold();
	statistics_.optimalThreshold(threshold);

	for ( unsigned int i = 0; i < clip_.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip_.width(); ++j )
		{
			if ( clip_(i,j) < threshold)
				clip_(i,j) = 1;	// ink
			else
				clip_(i,j) = 0;	// background
		}
	}

	statistics_.globalThresholdingTime(timer.elapsed());
};


/// @details The strategy proposed by N. Otsu in "A Threshold Selection Method from Gray-Level Histograms" (1979) maximises the likelihood that the
/// threshold is chosen so as to split the image between and object and its background. An optimal threshold is selected by the discriminant
/// criterion, namely, so as to maximize the separability of the resultant classes in gray levels. The procedure is very simple, utilizing only the
/// zeroth- and the first-order cumulative moments of the gray-level histogram.
unsigned char Preprocessor::computeOtsuOptimalThreshold () const
{
	// Compute the normalized clip histogram 
	std::vector<double> histogram(256, 0.0);

	for ( unsigned int i = 0; i < clip_.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip_.width(); ++j )
		{
			unsigned int grayLevel = static_cast<unsigned int>(clip_(i,j));

			histogram.at(grayLevel) += 1.0;
		}
	}
	std::transform (histogram.begin(), histogram.end(), histogram.begin(), std::bind2nd(std::divides<double>(), clip_.size()) );


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

	while ( i not_eq maximumVariance )
	{
		++i;
		++optimalThreshold;
	}

	return optimalThreshold;
};


/// @details The strategy proposed by M. Sonka, V. Hlavac and R. Boyle in "Image Processing, Analysis and Machine Vision" (2008) is to find a mean
/// value between the mean value of background's gray level and the mean value of objects' gray level, starting from an initial threshold that is
/// computed from the four corners of the press clip. 
unsigned char Preprocessor::computeSonkaOptimalThreshold () const
{
	// Start with an initial threshold
	unsigned char optimalThreshold = (clip_(0,0) + clip_(0, clip_.width()-1) + clip_(0, clip_.height()-1) + clip_(clip_.height()-1,clip_.width()-1)) / 4;
	unsigned char currentThreshold = ~optimalThreshold;

	// Loop as many times as needed to find the optimal threshold by averaging the pixel gray levels
	while (currentThreshold not_eq optimalThreshold)
	{
		double backgroundMeanValue = 0.0, objectsMeanValue = 0.0;
		unsigned int nSamples = 0;

		// Count the pixels that belong to objects and the pixels that belong to background
		for ( unsigned int i = 0; i < clip_.height(); ++i )
		{
			for ( unsigned int j = 0; j < clip_.width(); ++j )
			{
				unsigned char grayLevel = clip_(i, j);

				if ( grayLevel >= optimalThreshold )
				{
					backgroundMeanValue += static_cast<double>(grayLevel);
					nSamples++;
				}
				else
					objectsMeanValue += static_cast<double>(grayLevel);
			}
		}
		backgroundMeanValue = round(backgroundMeanValue / static_cast<double>(nSamples));
		objectsMeanValue = round(objectsMeanValue / static_cast<double>(clip_.size() - nSamples));

		// Update the optimal threshold keeping the last one
		currentThreshold = optimalThreshold;
		optimalThreshold = static_cast<unsigned char>( round((objectsMeanValue + backgroundMeanValue) / 2.0) );
	}

	return optimalThreshold;
};


void Preprocessor::applyTemplateFilters ()
{
	boost::timer timer;
	timer.restart();

	// Apply first filter mask, checking neighbour pixels above the target pixel
	for ( int i = clip_.height()-1; i >= 0; --i )
	{
		for ( int j = clip_.width()-1; j >= 0; --j )
		{
			int upperRow = i-1;

			if ( upperRow >= 0 )
			{
				unsigned int equalPixels = 1;

				if ( j > 0 )
				{
					if ( clip_(upperRow,j) == clip_(upperRow,j-1) and clip_(upperRow,j-1) == clip_(i,j-1) )
						equalPixels += 2;
				}

				if ( j < static_cast<int>(clip_.width())-1 )
				{
					if ( clip_(upperRow,j) == clip_(upperRow,j+1) and clip_(upperRow,j+1) == clip_(i,j+1) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_(i,j) =  clip_(upperRow,j);
			}
		}
	}

	// Apply second filter mask, checking neighbour pixels below the target pixel
	for ( int i = clip_.height()-1; i >= 0; --i )
	{
		for ( int j = clip_.width()-1; j >= 0; --j )
		{
			int lowerRow = i+1;

			if ( lowerRow < static_cast<int>(clip_.height()) )
			{
				unsigned int equalPixels = 1;

				if ( j > 0 )
				{
					if ( clip_(lowerRow,j) == clip_(lowerRow,j-1) and clip_(lowerRow,j-1) == clip_(i,j-1) )
						equalPixels += 2;
				}

				if ( j < static_cast<int>(clip_.width())-1 )
				{
					if ( clip_(lowerRow,j) == clip_(lowerRow,j+1) and clip_(lowerRow,j+1) == clip_(i,j+1) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_(i,j) =  clip_(lowerRow,j);
			}
		}
	}

	// Apply third filter mask, checking neighbour pixels on the left of target pixel
	for ( int i = clip_.height()-1; i >= 0; --i )
	{
		for ( int j = clip_.width()-1; j >= 0; --j )
		{
			int leftColumn = j-1;

			if ( leftColumn >= 0 )
			{
				unsigned int equalPixels = 1;

				if ( i > 0 )
				{
					if ( clip_(i,leftColumn) == clip_(i-1,leftColumn) and clip_(i-1,leftColumn) == clip_(i-1,j) )
						equalPixels += 2;
				}

				if ( i < static_cast<int>(clip_.height())-1 )
				{
					if ( clip_(i,leftColumn) == clip_(i+1,leftColumn) and clip_(i+1,leftColumn) == clip_(i+1,j) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_(i,j) =  clip_(i,leftColumn);
			}
		}
	}

	// Apply fourth filter mask, checking neighbour pixels on the right of target pixel
	for ( int i = clip_.height()-1; i >= 0; --i )
	{
		for ( int j = clip_.width()-1; j >= 0; --j )
		{
			int rightColumn = j+1;

			if ( rightColumn < static_cast<int>(clip_.width()) )
			{
				unsigned int equalPixels = 1;

				if ( i > 0 )
				{
					if ( clip_(i,rightColumn) == clip_(i-1,rightColumn) and clip_(i-1,rightColumn) == clip_(i-1,j) )
						equalPixels += 2;
				}

				if ( i < static_cast<int>(clip_.height())-1 )
				{
					if ( clip_(i,rightColumn) == clip_(i+1,rightColumn) and clip_(i+1,rightColumn) == clip_(i+1,j) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_(i,j) =  clip_(i,rightColumn);
			}
		}
	}

	statistics_.templateFilteringTime(timer.elapsed());
};


void Preprocessor::applyAveragingFilters ()
{
	boost::timer timer;
	timer.restart();

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

	int clipHeight	= clip_.height();
	int clipWidth	= clip_.width();

	for ( int i = 0; i < clipHeight; ++i )
	{
		for ( int j = 0; j < clipWidth; ++j )
		{
			double grayLevel = 0.0;

			for ( int filterI = 0; filterI < maskSize; ++filterI )
			{
				for ( int filterJ = 0; filterJ < maskSize; ++filterJ )
				{
					int imageI = (i + filterI - 1);
					int imageJ = (j + filterJ - 1);

					// Check borders
					if (imageI >= 0 and imageI < clipHeight and imageJ >= 0 and imageJ < clipWidth)
					{
						grayLevel += mask.at(filterI * maskSize + filterJ) * static_cast<double>(clip_(imageI,imageJ));
					}
				}
			}

			grayLevel = grayLevel * 1/16;

			if ( grayLevel > 255.0 )
				grayLevel = 255.0;

			if ( grayLevel < 0.0 )
				grayLevel = 0.0;

			clip_(i,j) = static_cast<unsigned char>(round(grayLevel));
		}
	}

	statistics_.averagingFilteringTime(timer.elapsed());
};


/// @details This method isolates every region of ink pixels in a press clip following a region flooding algorithm. Starting from an arbitrary pixel of ink,
///	it connects its neighbouring ink pixels and builds a set of regions. This set is then post-processed to join accents and other punctuation signs to their
/// final region. A final list is generated by sorting the set of regions by lines and columns, so that traversing the list forward is equivalent to reading
/// the text from left to right and from up to down.
void Preprocessor::extractRegions ()
{
	boost::timer timer;
	timer.restart();

	// Traverse the press clip searching the ink pixels where the flooding process will start from
	std::vector<PixelCoordinates> seeds(0);
	seeds.reserve(clip_.size());
	for ( unsigned int i = 0; i < clip_.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip_.width(); ++j )
		{
			if ( clip_(i, j) == 1 )
				seeds.push_back( PixelCoordinates(i,j) );
		}
	}

	// Build the initial list of regions by applying the flooding algorithm
	std::vector<bool> visited(clip_.size(), false);
	for ( std::vector<PixelCoordinates>::iterator s = seeds.begin(); s not_eq seeds.end(); ++s )
	{
		int row		= (*s).first;
		int column	= (*s).second;

		if ( not visited.at(row * clip_.width() + column) )
		{
			visited.at(row * clip_.width() + column) = true;

			// This seed begins a new region
			Region region;
			region.addCoordinates( PixelCoordinates(row, column) );

			// Explore the immediate neighbourhood
			for ( int i = row-1; (i <= row+1) and (i < static_cast<int>(clip_.height())); ++i )
			{
				for ( int j = column-1; (j <= column+1) and (j < static_cast<int>(clip_.width())); ++j )
				{
					if ( i >= 0 and j >= 0 )
					{
						if ( clip_(i,j) == 1 and not visited.at(i * clip_.width() + j) )
						{
							visited.at(i * clip_.width() + j) = true;
							region.addCoordinates( PixelCoordinates(i,j) );
						}
					}
				}
			}

			// Explore the neighbours of the neighbours
			unsigned int k = 1;
			while ( region.size() > k )
			{
				PixelCoordinates coordinates( region(k) );

				for ( int i = coordinates.first-1; (i <= static_cast<int>(coordinates.first+1)) and (i < static_cast<int>(clip_.height())); ++i )
				{
					for ( int j = coordinates.second-1; (j <= static_cast<int>(coordinates.second+1)) and (j < static_cast<int>(clip_.width())); ++j )
					{
						if ( i >= 0 and j >= 0 )
						{
							if ( clip_(i,j) == 1 and not visited.at(i * clip_.width() + j) )
							{
								visited.at(i * clip_.width() + j) = true;
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
	statistics_.nRegionsBeforeMerging(regions_.size());

	// Find the rows that delimits the regions as if they were characters in a text
	std::list<LineDelimiter> delimiters(0);
	findLineDelimiters(visited, delimiters);
	statistics_.nLineDelimiters(delimiters.size());

	// Merge every pair of regions that are supposed to be accents isolated from their vocals in a text line.
	mergeVerticallyOverlappedRegions (delimiters);
	statistics_.nRegionsAfterMerging(regions_.size());

	// Sort the regions by lines and columns
	regions_.sort();

	statistics_.regionsExtractionTime(timer.elapsed());
};


void Preprocessor::findLineDelimiters (const std::vector<bool>& visited, std::list<LineDelimiter>& delimiters) const
{
	// Traverse each row searching non-visited pixels
	unsigned int topRowOfTextLine = 0;
	bool rowHasInk = false, previousRowHasInk;

	for ( unsigned int i = 0; i < clip_.height(); ++i )
	{
		previousRowHasInk	= rowHasInk;
		rowHasInk			= false;

		for ( unsigned int j = 0; j < clip_.width(); ++j )
		{
			if ( visited.at(i * clip_.width() + j) )
			{
				rowHasInk = true;
				break;
			}
		}

		if (not rowHasInk )
		{
			if ( previousRowHasInk )
				delimiters.push_back( LineDelimiter(topRowOfTextLine, i-1) );
			else
				topRowOfTextLine = i;
		}
		else	// row has ink
		{
			if ( not previousRowHasInk )
				topRowOfTextLine = i;
		}
	}

	// Make sure the last text line joins with the clip border
	if ( rowHasInk )
		delimiters.push_back( LineDelimiter(topRowOfTextLine, clip_.height()-1) );


	// Search for lines that are too close to each other, probably because there are accents belonging to characters on a single line
	std::list<LineDelimiter>::iterator previousLineDelimiterIterator = delimiters.begin();
	std::list<LineDelimiter>::iterator currentLineDelimiterIterator	= delimiters.begin();
	advance( currentLineDelimiterIterator, 1 );

	while ( currentLineDelimiterIterator not_eq delimiters.end() )
	{
		if ( ((*currentLineDelimiterIterator).first - (*previousLineDelimiterIterator).second + 1) > 2 )
		{
			advance( currentLineDelimiterIterator, 1 );
			advance( previousLineDelimiterIterator, 1 );
		}
		else
		{
			// A new line delimiter is inserted by joining the two line delimiters explored.
			delimiters.insert( previousLineDelimiterIterator, LineDelimiter((*previousLineDelimiterIterator).first, (*currentLineDelimiterIterator).second) );

			std::list<LineDelimiter>::iterator newLineDelimiterIterator = previousLineDelimiterIterator;
			advance ( newLineDelimiterIterator, -1 );

			// The two old line delimiters are removed from the list
			delimiters.erase( previousLineDelimiterIterator );
			previousLineDelimiterIterator = currentLineDelimiterIterator;

			advance( currentLineDelimiterIterator, 1 );
			delimiters.erase( previousLineDelimiterIterator );

			previousLineDelimiterIterator = newLineDelimiterIterator;
		}
	}
};


void Preprocessor::mergeVerticallyOverlappedRegions (const std::list<LineDelimiter>& delimiters)
{
	for ( std::list<LineDelimiter>::const_iterator delimitersIterator = delimiters.begin(); delimitersIterator not_eq delimiters.end(); ++delimitersIterator  )
	{
		unsigned int lineTopBorder		= (*delimitersIterator).first;
		unsigned int lineBottomBorder	= (*delimitersIterator).second;

		// Traverse the list of regions searching a pair of regions vertically overlapped.
		std::list<Region>::iterator i = regions_.begin();

		while ( i not_eq regions_.end() )
		{
			bool regionIsAboveLine = (*i)(0).first < lineTopBorder;
			bool regionIsBelowLine = (*i)(0).first > lineBottomBorder;

			if ( regionIsAboveLine or regionIsBelowLine )
				advance (i, 1);
			else
			{
				// Find a region vertically overlapped with the current one.
				std::list<Region>::iterator j; // parametro de entrada == i

				for ( j = regions_.begin(); j not_eq regions_.end(); ++j )
				{
					if ( i == j )
						continue;

					bool candidateRegionIsAboveLine = (*j)(0).first < lineTopBorder;
					bool candidateRegionIsBelowLine = (*j)(0).first > lineBottomBorder;

					if ( candidateRegionIsAboveLine or candidateRegionIsBelowLine )
						continue;

					// Count the overlapped pixels of both regions by computing the intersection of column coordinates.
					std::set<unsigned int> regionI;
					std::set<unsigned int> regionJ;

					for ( unsigned int k = 0; k < (*i).size(); ++k )
						regionI.insert((*i)(k).second);

					for ( unsigned int k = 0; k < (*j).size(); ++k )
						regionJ.insert((*j)(k).second);

					std::vector<int> intersection( std::max(regionI.size(), regionJ.size()), -1 );
					std::vector<int>::iterator k = std::set_intersection(regionI.begin(), regionI.end(), regionJ.begin(), regionJ.end(), intersection.begin());

					if ( std::count_if(intersection.begin(), intersection.end(), std::bind2nd(std::not_equal_to<int>(), -1) )> round((*i).width() / 2) )
						break;
				}

				if ( j not_eq regions_.end() and i not_eq j )	// Merge this regions
				{
					regions_.push_back(*i + *j);
					regions_.erase(j);

					j = i ;
					advance(j, 1);
					regions_.erase(i);
					i = j;
				}
				else
					advance(i, 1);
			}
		}
	}
};


void Preprocessor::correctSlanting ()
{
	boost::timer timer;
	timer.restart();

	std::vector<unsigned int> angleEstimations(0);

	for ( std::list<Region>::iterator i = regions_.begin(); i not_eq regions_.end(); ++i )
	{
		const unsigned int rotationLimit = 46;

		// Detect the optimal angle for slanting correction
		Region rotatingRegion((*i));
		std::vector<unsigned int> maximumPixelsPerColumn(rotationLimit);

		for ( unsigned int j = 0; j < rotationLimit; ++j )
		{
			for ( unsigned int k = 0; k < rotatingRegion.size(); ++k )
			{
				double x = static_cast<double>(rotatingRegion(k).first);
				double y = static_cast<double>(rotatingRegion(k).second);

				rotatingRegion(k).first	= static_cast<unsigned int>(round(x - y * tan(j)));
			}

			std::vector<unsigned int> pixelsPerColumn((*i).width(), 0);
			for ( unsigned int k = 0; k < rotatingRegion.size(); ++k )
				pixelsPerColumn.at(rotatingRegion(k).second - rotatingRegion.topLeftmostPixelCoordinates().second) += 1;

			std::sort(pixelsPerColumn.begin(), pixelsPerColumn.end());
			maximumPixelsPerColumn.at(j) = pixelsPerColumn.back();
		}

		std::vector<unsigned int>::iterator maxOfMaximumPixelsPerColumn = std::max_element(maximumPixelsPerColumn.begin(), maximumPixelsPerColumn.end());
		unsigned int slantAngle = 0;
		for ( std::vector<unsigned int>::iterator j = maximumPixelsPerColumn.begin(); j not_eq maxOfMaximumPixelsPerColumn; ++j )
			slantAngle += 1;

		angleEstimations.push_back(slantAngle);

		// Correct slanting
		if ( slantAngle not_eq 0 )
		{
			for ( unsigned int j = 0; j < (*i).size(); ++j )
			{
				double x = static_cast<double>((*i)(j).first);
				double y = static_cast<double>((*i)(j).second);

				(*i)(j).first	= static_cast<unsigned int>(round(x - y * tan(slantAngle)));
			}
		}
	}
	statistics_.slantingCorrectionTime(timer.elapsed());;

	unsigned int meanSlantAngle = 0.0;
	std::accumulate(angleEstimations.begin(), angleEstimations.end(), meanSlantAngle);
	meanSlantAngle = meanSlantAngle / static_cast<double>(regions_.size());
	statistics_.slantAngleEstimation(meanSlantAngle);
};


std::vector<unsigned int> Preprocessor::findSpacesBetweenWords ()
{
	boost::timer timer;
	timer.restart();

	// Compute the mean inter-character space
	std::list<Region>::const_iterator i = regions_.begin();
	advance (i, 1);
	std::list<Region>::const_iterator j = regions_.begin();

	double meanInterRegionSpace = 0.0;
	while ( i not_eq regions_.end() )
	{
		if ( (*i).leftBorderColumn() >=  (*j).rightBorderColumn() )
			meanInterRegionSpace += (*i).leftBorderColumn() - (*j).rightBorderColumn() + 1;

		advance (i, 1);
		advance (j, 1);
	}
	meanInterRegionSpace = meanInterRegionSpace / regions_.size();
	statistics_.meanInterRegionSpace( meanInterRegionSpace );

	// Traverse the list of regions detecting a space between two regions greater than the mean space.
	i = regions_.begin();
	advance (i,1);
	j = regions_.begin();

	std::vector<unsigned int> spaces(0);
	unsigned int spaceLocation = 1;

	while ( i not_eq regions_.end() )
	{
		if ( (*i).leftBorderColumn() < (*j).rightBorderColumn() )
			spaces.push_back(spaceLocation);
		else
		{
			unsigned int distanceBetweenRegions = (*i).leftBorderColumn() - (*j).rightBorderColumn() + 1;

			if ( distanceBetweenRegions > meanInterRegionSpace )
				spaces.push_back(spaceLocation);
		}

		advance (i, 1);
		advance (j, 1);
		++spaceLocation;
	}

	statistics_.spacesBetweenWords(spaces.size());
	statistics_.spacesLocationFindingTime(timer.elapsed());
	return spaces;
};


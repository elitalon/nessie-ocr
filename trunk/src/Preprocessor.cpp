/// @file
/// @brief Definition of Preprocessor class

#include "Preprocessor.hpp"
#include "Pattern.hpp"
#include <Magick++.h>
#include <boost/timer.hpp>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>


/// @brief		Computes the optimal threshold value in a press clip following the Sonka's algorithm.
/// @details	The strategy proposed by M. Sonka, V. Hlavac and R. Boyle in "Image Processing, Analysis and Machine Vision" (2008) is to find a mean
/// value between the mean value of background's gray level and the mean value of objects' gray level, starting from an initial threshold that is
/// computed from the four corners of the press clip.

///
/// @return		A unsigned char with the optimal threshold value in a scale of [0,255].
/// @param		clip	The input press clip.
unsigned char computeSonkaOptimalThreshold (const Clip& clip);


/// @brief		Computes the optimal threshold value in a press clip following the Otsu's algorithm.
/// @details	The strategy proposed by N. Otsu in "A Threshold Selection Method from Gray-Level Histograms" (1979) maximises the likelihood that the
/// threshold is chosen so as to split the image between and object and its background. An optimal threshold is selected by the discriminant
/// criterion, namely, so as to maximize the separability of the resultant classes in gray levels. The procedure is very simple, utilizing only the
/// zeroth- and the first-order cumulative moments of the gray-level histogram.
///
///	@return		A unsigned char with the optimal threshold value in a scale of [0,255].
/// @param		clip	The input press clip.
unsigned char computeOtsuOptimalThreshold (const Clip& clip);


Preprocessor::Preprocessor (const Clip& pressClip)
:	clip_(pressClip),
	statistics_(),
	regions_(0),
	patterns_(0),
	averageCharacterHeight_(0.0)
{
	try
	{
		statistics_.clipSize(pressClip.size());
	}
	catch(...) {}
};


void Preprocessor::applyGlobalThresholding ()
{
	boost::timer timer;
	timer.restart();

	unsigned char threshold = computeOtsuOptimalThreshold(clip_);
	try
	{
		statistics_.optimalThreshold(threshold);
	}
	catch(...) {}

	// Find background's average gray level
	unsigned int backgroundAverageGrayLevel = 0, nPixels = 0;
	for( unsigned int i = 0; (i < 3) && (i < clip_.height()); ++i )
	{
		for( unsigned int j = 0; (j < 3) && (j < clip_.width()); ++j )
		{
			backgroundAverageGrayLevel += clip_(i,j);
			++nPixels;
		}

		for( unsigned int j = clip_.width()-1; (j > clip_.width()-4) && (j > 0); --j )
		{
			backgroundAverageGrayLevel += clip_(i,j);
			++nPixels;
		}
	}

	for( unsigned int i = clip_.height()-1; (i > clip_.height()-4) && (i > 0); --i )
	{
		for( unsigned int j = 0; (j < 3) && (j < clip_.width()); ++j )
		{
			backgroundAverageGrayLevel += clip_(i,j);
			++nPixels;
		}

		for( unsigned int j = clip_.width()-1; (j > clip_.width()-4) && (j > 0); --j )
		{
			backgroundAverageGrayLevel += clip_(i,j);
			++nPixels;
		}
	}
	backgroundAverageGrayLevel = backgroundAverageGrayLevel / nPixels;
	
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

	// Apply threshold
	for ( unsigned int i = 0; i < clip_.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip_.width(); ++j )
		{
			if ( clip_(i,j) <= threshold)
				clip_(i,j) = ink;
			else
				clip_(i,j) = background;
		}
	}

	try
	{
		statistics_.globalThresholdingTime(timer.elapsed());
	}
	catch(...) {}
};


void Preprocessor::removeNoiseByTemplateMatching ()
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
					if ( clip_(upperRow,j) == clip_(upperRow,j-1) && clip_(upperRow,j-1) == clip_(i,j-1) )
						equalPixels += 2;
				}

				if ( j < static_cast<int>(clip_.width())-1 )
				{
					if ( clip_(upperRow,j) == clip_(upperRow,j+1) && clip_(upperRow,j+1) == clip_(i,j+1) )
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
					if ( clip_(lowerRow,j) == clip_(lowerRow,j-1) && clip_(lowerRow,j-1) == clip_(i,j-1) )
						equalPixels += 2;
				}

				if ( j < static_cast<int>(clip_.width())-1 )
				{
					if ( clip_(lowerRow,j) == clip_(lowerRow,j+1) && clip_(lowerRow,j+1) == clip_(i,j+1) )
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
					if ( clip_(i,leftColumn) == clip_(i-1,leftColumn) && clip_(i-1,leftColumn) == clip_(i-1,j) )
						equalPixels += 2;
				}

				if ( i < static_cast<int>(clip_.height())-1 )
				{
					if ( clip_(i,leftColumn) == clip_(i+1,leftColumn) && clip_(i+1,leftColumn) == clip_(i+1,j) )
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
					if ( clip_(i,rightColumn) == clip_(i-1,rightColumn) && clip_(i-1,rightColumn) == clip_(i-1,j) )
						equalPixels += 2;
				}

				if ( i < static_cast<int>(clip_.height())-1 )
				{
					if ( clip_(i,rightColumn) == clip_(i+1,rightColumn) && clip_(i+1,rightColumn) == clip_(i+1,j) )
						equalPixels += 2;
				}

				if ( equalPixels == 5 )
					clip_(i,j) =  clip_(i,rightColumn);
			}
		}
	}

	try
	{
		statistics_.templateFilteringTime(timer.elapsed());
	}
	catch(...) {}
};


void Preprocessor::removeNoiseByLinearFiltering ()
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

	for ( int i = 1; i < clipHeight-1; ++i )
	{
		for ( int j = 1; j < clipWidth-1; ++j )
		{
			double grayLevel = 0.0;

			for ( int filterI = 0; filterI < maskSize; ++filterI )
			{
				for ( int filterJ = 0; filterJ < maskSize; ++filterJ )
				{
					int imageI = (i + filterI - 1);
					int imageJ = (j + filterJ - 1);

					if (imageI >= 0 && imageI < clipHeight && imageJ >= 0 && imageJ < clipWidth)
						grayLevel += mask.at(filterI * maskSize + filterJ) * static_cast<double>(clip_(imageI,imageJ));
				}
			}

			if ( i == 0 || i == (clipHeight-1) || j == 0 || j == (clipWidth-1) )
				grayLevel = grayLevel * (1.0/12.0);
			else
				grayLevel = grayLevel * (1.0/16.0);

			if ( grayLevel > 255.0 )
				grayLevel = 255.0;

			if ( grayLevel < 0.0 )
				grayLevel = 0.0;

			clip_(i,j) = static_cast<unsigned char>(round(grayLevel));
		}
	}

	try
	{
		statistics_.averagingFilteringTime(timer.elapsed());
	}
	catch(...) {}
};


/// @brief	Auxiliary function to use in accumulate algorithm.
/// 
/// @param	x		Value to update.
/// @param	region	Reference value to use in update
/// 
/// @return The size of input string 'region'.
double autoHeightIncrement (const double& x, const Region& region)
{
	return (x + region.height());
}


std::vector<unsigned int> Preprocessor::isolateRegions ()
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
	regions_.clear();
	std::deque<bool> visited(clip_.size(), false);
	for ( std::vector<PixelCoordinates>::iterator s = seeds.begin(); s != seeds.end(); ++s )
	{
		int row		= s->first;
		int column	= s->second;

		if ( not visited.at(row * clip_.width() + column) )
		{
			visited.at(row * clip_.width() + column) = true;

			// This seed begins a new region
			Region region;
			region.addCoordinates( PixelCoordinates(row, column) );

			// Explore the immediate neighbourhood
			for ( int i = row-1; (i <= row+1) && (i < static_cast<int>(clip_.height())); ++i )
			{
				for ( int j = column-1; (j <= column+1) && (j < static_cast<int>(clip_.width())); ++j )
				{
					if ( i >= 0 && j >= 0 )
					{
						if ( clip_(i,j) == 1 && not visited.at(i * clip_.width() + j) )
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
				PixelCoordinates coordinates( region.at(k) );

				for ( int i = coordinates.first-1; (i <= static_cast<int>(coordinates.first+1)) && (i < static_cast<int>(clip_.height())); ++i )
				{
					for ( int j = coordinates.second-1; (j <= static_cast<int>(coordinates.second+1)) && (j < static_cast<int>(clip_.width())); ++j )
					{
						if ( i >= 0 && j >= 0 )
						{
							if ( clip_(i,j) == 1 && not visited.at(i * clip_.width() + j) )
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

	std::list<LineDelimiter> delimiters(0);
	
	findLineDelimiters(visited, delimiters);
	mergeVerticallyOverlappedRegions (delimiters);

	averageCharacterHeight_ = std::accumulate (regions_.begin(), regions_.end(), 0.0, autoHeightIncrement) / regions_.size();
	
	regions_.sort();
	std::vector<unsigned int> spaceLocations = findSpacesBetweenWords(delimiters);
	try
	{
		statistics_.nRegions(regions_.size());
		statistics_.nLines(delimiters.size());
		statistics_.averageCharacterHeight(averageCharacterHeight_);
		statistics_.segmentationTime(timer.elapsed());
	}
	catch(...) {}
	
	return spaceLocations;
};


void Preprocessor::findLineDelimiters (const std::deque<bool>& visited, std::list<LineDelimiter>& delimiters) const
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
		else
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

	while ( currentLineDelimiterIterator != delimiters.end() )
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
			delimiters.insert( previousLineDelimiterIterator, LineDelimiter(previousLineDelimiterIterator->first, currentLineDelimiterIterator->second) );

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
	for ( std::list<LineDelimiter>::const_iterator delimitersIterator = delimiters.begin(); delimitersIterator != delimiters.end(); ++delimitersIterator  )
	{
		unsigned int lineTopBorder		= delimitersIterator->first;
		unsigned int lineBottomBorder	= delimitersIterator->second;

		// Traverse the list of regions searching a pair of regions vertically overlapped.
		std::list<Region>::iterator i = regions_.begin();

		while ( i != regions_.end() )
		{
			bool regionIsAboveLine = i->at(0).first < lineTopBorder;
			bool regionIsBelowLine = i->at(0).first > lineBottomBorder;

			if ( regionIsAboveLine || regionIsBelowLine )
				advance (i, 1);
			else
			{
				// Find a region vertically overlapped with the current one.
				std::list<Region>::iterator j;

				for ( j = regions_.begin(); j != regions_.end(); ++j )
				{
					if ( i == j )
						continue;

					bool candidateRegionIsAboveLine = j->at(0).first < lineTopBorder;
					bool candidateRegionIsBelowLine = j->at(0).first > lineBottomBorder;

					if ( candidateRegionIsAboveLine || candidateRegionIsBelowLine )
						continue;

					// Count the overlapped pixels of both regions by computing the intersection of column coordinates.
					std::set<unsigned int> regionI;
					std::set<unsigned int> regionJ;

					for ( unsigned int k = 0; k < (*i).size(); ++k )
						regionI.insert(i->at(k).second);

					for ( unsigned int k = 0; k < (*j).size(); ++k )
						regionJ.insert(j->at(k).second);

					std::vector<int> intersection( std::max(regionI.size(), regionJ.size()), -1 );
					std::vector<int>::iterator k = std::set_intersection(regionI.begin(), regionI.end(), regionJ.begin(), regionJ.end(), intersection.begin());

					if ( std::count_if(intersection.begin(), intersection.end(), std::bind2nd(std::not_equal_to<int>(), -1) )> round(i->width() / 2) )
						break;
				}

				if ( j != regions_.end() && i != j )	// Merge this regions
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

	for ( std::list<Region>::iterator i = regions_.begin(); i != regions_.end(); ++i )
	{
		const unsigned int rotationLimit = 46;

		// Detect the optimal angle for slanting correction
		Region rotatingRegion(*i);
		std::vector<unsigned int> maximumPixelsPerColumn(rotationLimit);

		for ( unsigned int j = 0; j < rotationLimit; ++j )
		{
			for ( unsigned int k = 0; k < rotatingRegion.size(); ++k )
			{
				double x = static_cast<double>(rotatingRegion.at(k).first);
				double y = static_cast<double>(rotatingRegion.at(k).second);

				rotatingRegion.at(k).first	= static_cast<unsigned int>(round(x - y * tan(j)));
			}

			std::vector<unsigned int> pixelsPerColumn((*i).width(), 0);
			for ( unsigned int k = 0; k < rotatingRegion.size(); ++k )
				pixelsPerColumn.at(rotatingRegion.at(k).second - rotatingRegion.topLeftmostPixelCoordinates().second) += 1;

			std::sort(pixelsPerColumn.begin(), pixelsPerColumn.end());
			maximumPixelsPerColumn.at(j) = pixelsPerColumn.back();
		}

		std::vector<unsigned int>::iterator maxOfMaximumPixelsPerColumn = std::max_element(maximumPixelsPerColumn.begin(), maximumPixelsPerColumn.end());
		unsigned int slantAngle = 0;
		for ( std::vector<unsigned int>::iterator j = maximumPixelsPerColumn.begin(); j != maxOfMaximumPixelsPerColumn; ++j )
			slantAngle += 1;

		angleEstimations.push_back(slantAngle);

		// Correct slanting
		if ( slantAngle != 0 )
		{
			for ( unsigned int j = 0; j < (*i).size(); ++j )
			{
				double x = static_cast<double>(i->at(j).first);
				double y = static_cast<double>(i->at(j).second);

				i->at(j).first	= static_cast<unsigned int>(round(x - y * tan(slantAngle)));
			}
		}
	}

	unsigned int meanSlantAngle = 0.0;
	std::accumulate(angleEstimations.begin(), angleEstimations.end(), meanSlantAngle);
	meanSlantAngle = meanSlantAngle / static_cast<double>(regions_.size());
	try
	{
		statistics_.slantAngle(meanSlantAngle);
		statistics_.slantingCorrectionTime(timer.elapsed());;
	}
	catch(...) {}
};


void Preprocessor::buildPatterns ()
{
	boost::timer timer;
	timer.restart();

	// Make a backup of critical data
	PreprocessorStatistics backupStatistics(statistics_);
	Clip backupClip(clip_);
	std::list<Region> backupRegions(regions_);
	double backupAverageCharacterHeight = averageCharacterHeight_;
	double backupAverageInterRegionSpace = averageInterRegionSpace_;

	patterns_.clear();
	patterns_.reserve(regions_.size());

	for ( std::list<Region>::iterator i = backupRegions.begin(); i != backupRegions.end(); ++i )
	{
		Pattern pattern;
		try
		{
			i->normalizeCoordinates();

			// Normalize region using a Magick++ object
			Magick::Image regionImage(Magick::Geometry(i->width(), i->height()), Magick::ColorGray(1.0));
			regionImage.type( Magick::BilevelType );

			Magick::Pixels view(regionImage);
			Magick::PixelPacket *originPixel = view.get(0, 0, i->width(), i->height());
			Magick::PixelPacket *pixel;

			for ( unsigned int j = 0; j < i->size(); ++j )
			{
				pixel	= originPixel + (i->at(j).first * view.columns() + i->at(j).second);
				*pixel	= Magick::ColorGray (0.0);
			}
			view.sync();
			regionImage.syncPixels();
			regionImage.sample( Magick::Geometry(Pattern::planeSize(), Pattern::planeSize()) );

			// Preprocess the normalized region
			clip_ = Clip(regionImage, 0, 0, regionImage.rows(), regionImage.columns());
			this->applyGlobalThresholding();
			this->isolateRegions();

			if ( regions_.size() > 1 )	// Merge subregions if preprocessing splitted the original region
			{
				Region tmp;

				for ( std::list<Region>::iterator i = regions_.begin(); i != regions_.end(); ++i )
					tmp = tmp + *i;

				regions_.clear();
				regions_.push_back(tmp);
			}

			// Build the pattern
			Region normalizedRegion(regions_.front());
			for ( unsigned int i = 0; i < normalizedRegion.size(); ++i )
				pattern.at(normalizedRegion.at(i).first, normalizedRegion.at(i).second) = 1;

			if ( regionImage.rows() < Pattern::planeSize() )	// Shift rows from top to the center
			{
				unsigned int offset = (Pattern::planeSize() - regionImage.rows()) / 2;

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

			if ( regionImage.columns() < Pattern::planeSize() )	// Shift columns from left to center
			{
				unsigned int offset = (Pattern::planeSize() - regionImage.columns()) / 2;

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
		}
		catch (...) {}	// Ignore the exception, a blank pattern will be created.

		patterns_.push_back( pattern );
	}

	try
	{
		statistics_ = backupStatistics;
		
		clip_ = backupClip;
		regions_ = backupRegions;
		averageCharacterHeight_ = backupAverageCharacterHeight;
		averageInterRegionSpace_ = backupAverageInterRegionSpace;
		
		statistics_.patternsBuildingTime(timer.elapsed());
	}
	catch(...) {}
};

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

			// Step 1
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

	try
	{
		statistics_.skeletonizationTime(timer.elapsed());
	}
	catch (...) {}
};


std::vector<unsigned int> Preprocessor::findSpacesBetweenWords (const std::list<LineDelimiter>& delimiters)
{
	averageInterRegionSpace_ = 0.0;

	std::list<Region>::const_iterator i = regions_.begin();
	std::list<Region>::const_iterator j = regions_.begin();
	advance (j, 1);
	while ( j != regions_.end() )
	{
		bool lineBreak = false;
		for ( std::list<LineDelimiter>::const_iterator k = delimiters.begin(); k != delimiters.end(); ++k )
		{
			if ( i->topBorderRow() >= k->first && i->bottomBorderRow() <= k->second )	// line found
			{
				if ( !(j->topBorderRow() >= k->first && j->bottomBorderRow() <= k->second) )	// the second region is in another line
					lineBreak = true;
			}
		}

		if ( !lineBreak && (j->leftBorderColumn() >= i->rightBorderColumn()) )
			averageInterRegionSpace_ += static_cast<int>(j->leftBorderColumn()) - static_cast<int>(i->rightBorderColumn()) + 1;
		
		advance (i, 1);
		advance (j, 1);
	}
	averageInterRegionSpace_ = averageInterRegionSpace_ / regions_.size();
	try
	{
		statistics_.averageInterCharacterSpace( averageInterRegionSpace_ );
	}
	catch(...) {}


	// Traverse the list of regions detecting a space between two regions greater than the mean space.
	i = regions_.begin();
	advance (i,1);
	j = regions_.begin();

	std::vector<unsigned int> spaces(0);
	unsigned int spaceLocation = 1;

	while ( i != regions_.end() )
	{
		bool lineBreak = false;
		for ( std::list<LineDelimiter>::const_iterator k = delimiters.begin(); k != delimiters.end(); ++k )
		{
			if ( i->topBorderRow() >= k->first && i->bottomBorderRow() <= k->second )	// line found
			{
				if ( !(j->topBorderRow() >= k->first && j->bottomBorderRow() <= k->second) )	// the second region is in another line
					lineBreak = true;
			}
		}

		if ( lineBreak )
			spaces.push_back(spaceLocation);
		else
		{
			int distanceBetweenRegions = static_cast<int>(i->leftBorderColumn()) - static_cast<int>(j->rightBorderColumn()) + 1;

			if ( distanceBetweenRegions > (averageInterRegionSpace_ / 0.7) )
				spaces.push_back(spaceLocation);
		}

		advance (i, 1);
		advance (j, 1);
		++spaceLocation;
	}

	return spaces;
};


unsigned char computeOtsuOptimalThreshold (const Clip& clip)
{
	// Compute the normalized clip histogram
	std::vector<double> histogram(256, 0.0);

	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			unsigned int grayLevel = static_cast<unsigned int>(clip(i,j));

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
};


unsigned char computeSonkaOptimalThreshold (const Clip& clip)
{
	// Start with an initial threshold
	unsigned char optimalThreshold = (clip(0,0) + clip(0, clip.width()-1) + clip(0, clip.height()-1) + clip(clip.height()-1,clip.width()-1)) / 4;
	unsigned char currentThreshold = ~optimalThreshold;

	// Loop as many times as needed to find the optimal threshold by averaging the pixel gray levels
	while (currentThreshold != optimalThreshold)
	{
		double backgroundMeanValue = 0.0, objectsMeanValue = 0.0;
		unsigned int nSamples = 0;

		// Count the pixels that belong to objects and the pixels that belong to background
		for ( unsigned int i = 0; i < clip.height(); ++i )
		{
			for ( unsigned int j = 0; j < clip.width(); ++j )
			{
				unsigned char grayLevel = clip(i, j);

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
		objectsMeanValue = round(objectsMeanValue / static_cast<double>(clip.size() - nSamples));

		// Update the optimal threshold keeping the last one
		currentThreshold = optimalThreshold;
		optimalThreshold = static_cast<unsigned char>( round((objectsMeanValue + backgroundMeanValue) / 2.0) );
	}

	return optimalThreshold;
};


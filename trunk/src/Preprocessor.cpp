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
#include <iostream>


/// @brief	Computes the optimal threshold value in a press clip following the Sonka's algorithm.
/// @return	A unsigned char with the optimal threshold value in a scale of [0,255].
/// @param	clip	The input press clip.
unsigned char computeSonkaOptimalThreshold (const Clip& clip);


/// @brief	Computes the optimal threshold value in a press clip following the Otsu's algorithm.
///	@return	A unsigned char with the optimal threshold value in a scale of [0,255].
/// @param	clip	The input press clip.
unsigned char computeOtsuOptimalThreshold (const Clip& clip);


Preprocessor::Preprocessor (const Clip& pressClip)
:	clip_(pressClip),
	statistics_(),
	regions_(0)
{
	try
	{
		statistics_.clipSize(pressClip.size());
	}
	catch(...) {}	
};


/// @details	The algorithm uses the Otsu's method to find automatically the optimal threshold for the press clip. Then, it compares each pixel
/// gray level with that threshold and transforms the source clip into a binary image. As a result, the final histogram is bimodal. The algorithm
/// also assumes that gray levels in the press clip above the threshold belong to the background, while gray levels below belong to the ink.
///
/// @todo		Avoid the assumption made about background's gray level. Sometimes a press clip background comes in dark gray levels and the ink in light
/// ones. Some function should be developed to automatically make the right decision.
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

	for ( unsigned int i = 0; i < clip_.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip_.width(); ++j )
		{
			if ( clip_(i,j) <= threshold)
				clip_(i,j) = 1;	// ink
			else
				clip_(i,j) = 0;	// background
		}
	}

	try
	{
		statistics_.globalThresholdingTime(timer.elapsed());
	}
	catch(...) {}	
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


/// @details This method peels off every region of pixel following the Hilditch's thinning algorithm. It consists in multiple passes on the press clip, where on
///	each pass the algorithm checks all the pixels and decides to change a pixel from black to white if it satisfies four conditions. The algorithm stops when there
///	are no changes in the press clip.
void Preprocessor::applyThinning ()
{
	boost::timer timer;
	timer.restart();

	bool clipHasChanged = true;
	while ( clipHasChanged )
	{
		clipHasChanged = false;

		for( int i = 0; i < static_cast<int>(clip_.height()); ++i)
		{
			for( int j = 0; j < static_cast<int>(clip_.width()); ++j)
			{
				if ( clip_(i,j) == 0 )
					continue;

				std::vector<unsigned int> p1Neighbours(8,0);	// p1 is the central pixel
				unsigned int z = 0;
				for ( int m = i-1; m < i+2; ++m )
				{
					for ( int n = j-1; n < j+2; ++n )
					{
						if ( not (m == i && n == j) )
						{
							if ( m >= 0 && m < static_cast<int>(clip_.height()) && n >= 0 && n< static_cast<int>(clip_.width()) )
								p1Neighbours.at(z) = clip_(m,n);

							++z;
						}
					}
				}
				std::rotate (p1Neighbours.begin(), p1Neighbours.begin()+1, p1Neighbours.end());
				std::swap ( *(p1Neighbours.begin()+4), *(p1Neighbours.begin()+5) );
				std::swap ( *(p1Neighbours.begin()+2), *(p1Neighbours.begin()+3) );
				std::swap ( *(p1Neighbours.begin()+3), *(p1Neighbours.begin()+6) ) ;

				// Compute additional pixels
				unsigned int p10 = 0, p11 = 0, p12 = 0, p14 = 0, p15 = 0, p16 = 0;
				if( i-2 >= 0 && j-1 >= 0 )
					p10 = clip_(i-2,j-1);

				if( i-2 >= 0 )
					p11 = clip_(i-2,j);

				if( i-2 >= 0 && j+1 < static_cast<int>(clip_.width()) )
					p12 = clip_(i-2,j+1);

				if( i-1 >= 0 && j+2 < static_cast<int>(clip_.width()) )
					p14 = clip_(i-1,j+2);

				if( j+2 < static_cast<int>(clip_.width()) )
					p15 = clip_(i,j+2);

				if( i+1 < static_cast<int>(clip_.height()) && j+2 < static_cast<int>(clip_.width()) )
					p16 = clip_(i+1,j+2);

				std::vector<unsigned int> p2Neighbours(8);
				p2Neighbours.at(0) = p11;
				p2Neighbours.at(1) = p12;
				p2Neighbours.at(2) = p1Neighbours.at(1); // p3
				p2Neighbours.at(3) = p1Neighbours.at(2); // p4
				p2Neighbours.at(4) = clip_(i,j);
				p2Neighbours.at(5) = p1Neighbours.at(6); // p8
				p2Neighbours.at(6) = p1Neighbours.at(7); // p9
				p2Neighbours.at(7) = p10;

				std::vector<unsigned int> p4Neighbours(8);
				p4Neighbours.at(0) = p1Neighbours.at(1); // p3
				p4Neighbours.at(1) = p14;
				p4Neighbours.at(2) = p15;
				p4Neighbours.at(3) = p16;
				p4Neighbours.at(4) = p1Neighbours.at(3); // p5
				p4Neighbours.at(5) = p1Neighbours.at(4); // p6
				p4Neighbours.at(6) = clip_(i,j);
				p4Neighbours.at(7) = p1Neighbours.at(0); // p2

				// Discriminant function A(p1)
				unsigned int a_p1 = 0;
				std::vector<unsigned int>::iterator k = p1Neighbours.begin();
				std::vector<unsigned int>::iterator l = p1Neighbours.begin();
				advance (l,1);
				while ( l != p1Neighbours.end() )
				{
					if ( (*k) == 0 && (*l) == 1 )
						++a_p1;

					advance (k,1);
					advance (l,1);
				}
				if ( p1Neighbours.at(7) == 0 && p1Neighbours.at(0) == 1 )
					++a_p1;

				// Discriminant function B(p1)
				unsigned int b_p1 = 0;
				for( unsigned int k = 0; k < 8; ++k )
					b_p1 += p1Neighbours.at(k);

				// Discriminant function A(p2)
				unsigned int a_p2 = 0;
				k = p2Neighbours.begin();
				l = p2Neighbours.begin();
				advance (l,1);
				while ( l != p2Neighbours.end() )
				{
					if ( (*k) == 0 && (*l) == 1 )
						++a_p2;

					advance (k,1);
					advance (l,1);
				}
				if ( p2Neighbours.at(7) == 0 && p2Neighbours.at(0) == 1 )
					++a_p2;

				// Discriminant function A(p4)
				unsigned int a_p4 = 0;
				k = p4Neighbours.begin();
				l = p4Neighbours.begin();
				advance (l,1);
				while ( l != p4Neighbours.end() )
				{
					if ( (*k) == 0 && (*l) == 1 )
						++a_p4;

					advance (k,1);
					advance (l,1);
				}
				if ( p4Neighbours.at(7) == 0 && p4Neighbours.at(0) == 1 )
					++a_p4;

				// Decide whether to peel of the pixel or not
				bool firstCondition		= (2 <= b_p1) && (b_p1 <= 6);
				bool secondCondition	= (a_p1 == 1);
				bool thirdCondition		= ((p1Neighbours.at(0) * p1Neighbours.at(2) * p1Neighbours.at(6)) == 0) || (a_p2 != 1);
				bool fourthCondition	= ((p1Neighbours.at(0) * p1Neighbours.at(2) * p1Neighbours.at(4)) == 0) || (a_p4 != 1);

				if ( firstCondition && secondCondition && thirdCondition && fourthCondition )
				{
					clip_(i,j) = 0;
					clipHasChanged = true;
				}
			}
		}
	}

	try
	{
		statistics_.thinningTime(timer.elapsed());
	}
	catch(...) {}	
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
	for ( std::vector<PixelCoordinates>::iterator s = seeds.begin(); s != seeds.end(); ++s )
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
				PixelCoordinates coordinates( region(k) );

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
	try
	{
		statistics_.nRegionsBeforeMerging(regions_.size());
	}
	catch(...) {}	

	std::list<LineDelimiter> delimiters(0);
	findLineDelimiters(visited, delimiters);
	try
	{
		statistics_.nLineDelimiters(delimiters.size());
	}
	catch(...) {}	

	mergeVerticallyOverlappedRegions (delimiters);
	try
	{
		statistics_.nRegionsAfterMerging(regions_.size());
	}
	catch(...) {}	

	regions_.sort();

	try
	{
		statistics_.regionsExtractionTime(timer.elapsed());
	}
	catch(...) {}	
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
		unsigned int currentLineHeight	= (*currentLineDelimiterIterator).second - (*currentLineDelimiterIterator).first + 1;
		unsigned int previousLineHeight	= (*previousLineDelimiterIterator).second - (*previousLineDelimiterIterator).first + 1;

		if ( previousLineHeight > (currentLineHeight / 2) )
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
	for ( std::list<LineDelimiter>::const_iterator delimitersIterator = delimiters.begin(); delimitersIterator != delimiters.end(); ++delimitersIterator  )
	{
		unsigned int lineTopBorder		= (*delimitersIterator).first;
		unsigned int lineBottomBorder	= (*delimitersIterator).second;

		// Traverse the list of regions searching a pair of regions vertically overlapped.
		std::list<Region>::iterator i = regions_.begin();

		while ( i != regions_.end() )
		{
			bool regionIsAboveLine = (*i)(0).first < lineTopBorder;
			bool regionIsBelowLine = (*i)(0).first > lineBottomBorder;

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

					bool candidateRegionIsAboveLine = (*j)(0).first < lineTopBorder;
					bool candidateRegionIsBelowLine = (*j)(0).first > lineBottomBorder;

					if ( candidateRegionIsAboveLine || candidateRegionIsBelowLine )
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
		for ( std::vector<unsigned int>::iterator j = maximumPixelsPerColumn.begin(); j != maxOfMaximumPixelsPerColumn; ++j )
			slantAngle += 1;

		angleEstimations.push_back(slantAngle);

		// Correct slanting
		if ( slantAngle != 0 )
		{
			for ( unsigned int j = 0; j < (*i).size(); ++j )
			{
				double x = static_cast<double>((*i)(j).first);
				double y = static_cast<double>((*i)(j).second);

				(*i)(j).first	= static_cast<unsigned int>(round(x - y * tan(slantAngle)));
			}
		}
	}
	try
	{
		statistics_.slantingCorrectionTime(timer.elapsed());;
	}
	catch(...) {}	

	unsigned int meanSlantAngle = 0.0;
	std::accumulate(angleEstimations.begin(), angleEstimations.end(), meanSlantAngle);
	meanSlantAngle = meanSlantAngle / static_cast<double>(regions_.size());
	try
	{
		statistics_.slantAngleEstimation(meanSlantAngle);
	}
	catch(...) {}	
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
	while ( i != regions_.end() )
	{
		if ( (*i).leftBorderColumn() >=  (*j).rightBorderColumn() )
			meanInterRegionSpace += (*i).leftBorderColumn() - (*j).rightBorderColumn() + 1;

		advance (i, 1);
		advance (j, 1);
	}
	meanInterRegionSpace = meanInterRegionSpace / regions_.size();
	try
	{
		statistics_.meanInterRegionSpace( meanInterRegionSpace );
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

	try
	{
		statistics_.spacesBetweenWords(spaces.size());
		statistics_.spacesLocationFindingTime(timer.elapsed());
	}
	catch(...) {}	
	
	return spaces;
};


/// @details The strategy proposed by N. Otsu in "A Threshold Selection Method from Gray-Level Histograms" (1979) maximises the likelihood that the
/// threshold is chosen so as to split the image between and object and its background. An optimal threshold is selected by the discriminant
/// criterion, namely, so as to maximize the separability of the resultant classes in gray levels. The procedure is very simple, utilizing only the
/// zeroth- and the first-order cumulative moments of the gray-level histogram.
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


/// @details The strategy proposed by M. Sonka, V. Hlavac and R. Boyle in "Image Processing, Analysis and Machine Vision" (2008) is to find a mean
/// value between the mean value of background's gray level and the mean value of objects' gray level, starting from an initial threshold that is
/// computed from the four corners of the press clip.
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


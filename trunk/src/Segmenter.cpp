///
/// @file
/// @brief Definition of Segmenter class
///

#include "Segmenter.hpp"

#include "Clip.hpp"
#include "boost/timer.hpp"

#include <cmath>



Segmenter::Segmenter ()
	:	inkValue_(0),
		seeds_(std::deque<Pixel>(0)),
		visited_(std::deque<bool>(0)),
		shapes_(std::list<Shape>(0)),
		lineMarkers_(std::list<LineMarker>(0)),
		thresholdingTime_(0.0),
		shapesFindingTime_(0.0)
{
	
};



///
/// @details This method implements a simple thresholding algorithm that compares each pixel's gray level with a threshold value. The background
/// reference gray level is taken into account to decide the final gray level that is applied to the pixel, so that the ink value is assumed as the
/// very opposite gray level of background reference.
///
void Segmenter::applyThreshold (Clip& clip, const unsigned char& threshold, const unsigned char& backgroundReference)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	// Threshold every pixel
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			if ( (backgroundReference >= threshold) and (clip(i, j) >= threshold) )	// The background is near white
				clip(i, j) = 255;
			else
			{
				if ( (backgroundReference >= threshold) and (clip(i, j) < threshold) )
					clip(i, j) = 0;
				else
				{
					if ( (backgroundReference < threshold) and (clip(i, j) < threshold) )	// The background is near black
						clip(i, j) = 0;
					else
						clip(i, j) = 255;
				}
			}	
		}
	}
	
	
	// Stablish the value of the ink pixels
	if ( backgroundReference >= threshold )
		inkValue_ = 0;
	else
		inkValue_ = 255;
	
	// Gather elapsed time
	thresholdingTime_ = timer.elapsed();
};



///
/// @details This method isolates every shape in a press clip by connecting pixels of ink that are located together in a 3x3 neighbourhood. The shapes
/// may contain a subset of shapes, since further processing is applied to join accents and other punctuation signs to their characters. The final list
/// of shapes is sorted by lines and columns, so that traversing the list is equivalent to read the text from left to right and from up to down.
/// 
void Segmenter::findShapes (const Clip& clip)
{
	// Start timing
	boost::timer timer;
	timer.restart();

	
	// Find the seeds where the flooding process will start from
	findSeeds(clip);

	
	// Obtain the initial shapes	
	growSeedsIntoInitialShapes(clip);

	
	// Find the markers that delimit the lines
	findLineMarkers(clip);


	// Join accents to their vocals in a line of characters
	for ( std::list<LineMarker>::iterator i = lineMarkers_.begin(); i not_eq lineMarkers_.end(); ++i )
	{
		unsigned int lineTop	= (*i).first;
		unsigned int lineBottom	= (*i).second;
		
		// Iterator to the list of shapes
		ShapeIterator iShape = shapes_.begin();

		// Traverse the list of shapes,. For each shape it is searched another shape that is vertically overlapped
		while ( iShape not_eq shapes_.end() )
		{
			bool shapeIsAboveTheLine = ((*iShape).topPixel().first < lineTop) and ((*iShape).bottomPixel().first < lineTop);
			bool shapeIsBelowTheLine = ((*iShape).topPixel().first > lineBottom) and ((*iShape).bottomPixel().first > lineBottom);

			// Avoid processing a shape that is outside the line borders
			if ( shapeIsAboveTheLine or shapeIsBelowTheLine )
				advance (iShape, 1);
			else
			{
				ShapeIterator jShape = findVerticallyOverlappedShape(lineTop, lineBottom, iShape);
				
				if ( jShape not_eq iShape )
					joinVerticallyOverlappedShapes( iShape, jShape );
				else
					advance(iShape, 1);
			}
		}
	}
	

	// Sort the shapes by lines and columns
	shapes_.sort();
	
	
	// Gather elapsed time
	shapesFindingTime_ = timer.elapsed();
};



///
/// @details A seed is a pixel that has a gray level equal to the gray level of characters in the clip. Thus, the seeds founded by this method
/// are actually all the pixels that do not belong to the background in the clip.
///
void Segmenter::findSeeds (const Clip& clip)
{
	// Traverse the clip searching the seeds
	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			if ( clip(i, j) == inkValue_ )
				seeds_.push_back( Pixel(i,j) );
		}
	}
};



///
/// @details The initial shapes are a set of shapes that are inconsistent with the real characters in the press clip. That is because
/// a further processing is necessary to join accents to vocals, split shapes that represents two characters joined, etc.
/// 
/// This method follows a strategy similar to the 'flood fill' algorithm. The main target is to isolate every shape in a clip that represents
/// a character. Every shape is built starting from an ink pixel (a seed) and exploring its neighbourhood looking for connected pixels. The process
/// ends when there are not more seeds to explore and the shapes are completely isolated.
///
void Segmenter::growSeedsIntoInitialShapes (const Clip& clip)
{
	// Initialize the visited_ deque
	visited_ = std::deque<bool>(clip.size(), false);
	
	// Explore the neighbourhood of each seed. For each pixel explored, the vector above tells if it has already been explored
	for ( std::deque<Pixel>::iterator seedsIterator = seeds_.begin(); seedsIterator not_eq seeds_.end(); ++seedsIterator )
	{
		unsigned int row	= (*seedsIterator).first;
		unsigned int column	= (*seedsIterator).second;
	
		if ( not visited_.at(row * clip.width() + column) )	// This seed has not already been visited
		{
			visited_.at(row * clip.width() + column) = true;
		
			// This seed begins a new shape
			shapes_.push_back(Shape());
			shapes_.back().addPixel( Pixel(row, column) );
		
		
			// Explore the seed's neighbourhood
			for ( unsigned int i = row-1; (i <= row+1) and (i < clip.height()); ++i )
			{
				for ( unsigned int j = column-1; (j <= column+1) and (j < clip.width()); ++j )
				{
					// Test clip borders are not passed
					if ( i >= 0 and j >= 0 )
					{
						// Add this neighbour if has ink and has already not been visited
						if ( clip(i,j) == inkValue_ and not visited_.at(i * clip.width() + j) )
						{
							visited_.at(i * clip.width() + j) = true;
							shapes_.back().addPixel( Pixel(i, j) );
						}
					}
				}
			}
		
		
			// Explore the neighbours of the neighbours of the seed.
			unsigned int lastPixelPosition = 1;
			while ( shapes_.back().size() > lastPixelPosition )
			{
				Pixel pixel( shapes_.back()(lastPixelPosition) );
			
				// Explore the neighbour's neighbourhood
				for ( unsigned int i = pixel.first-1; (i <= pixel.first+1) and (i < clip.height()); ++i )
				{
					for ( unsigned int j = pixel.second-1; (j <= pixel.second+1) and (j < clip.width()); ++j )
					{
						// Test clip borders are not passed
						if ( i >= 0 and j >= 0 )
						{
							// Add this neighbour if has ink and has already not been visited
							if ( clip(i,j) == inkValue_ and not visited_.at(i * clip.width() + j) )
							{
								visited_.at(i * clip.width() + j) = true;
								shapes_.back().addPixel( Pixel(i, j) );
							}
						}
					}
				}
				
				// Update the pixel's counter
				lastPixelPosition++;
			}
		}
	}	
};



///
/// @details Each row is isolated by searching horizontal blank lines between characters. Every time a row with no pixels of ink is found following
/// a row with some pixels of ink a top marker is set. Then, the following rows are explored until a new blank line is found. The line before
/// that last blank line is set as the bottom marker of the line.
///
void Segmenter::findLineMarkers (const Clip& clip)
{
	unsigned int topRow = 0;
	bool rowHasInk = false, previousRowHasInk;
	
	// Traverse the clip searching non-visited pixels
	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		previousRowHasInk	= rowHasInk;
		rowHasInk			= false;
		
		unsigned int nVisitedPixels = 0;
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			if ( visited_.at(i * clip.width() + j) )
				nVisitedPixels++;
		}
		
		// A line with less than two pixels of ink is assumed as a blank line
		if ( nVisitedPixels > 1 )
			rowHasInk = true;
		
		// Check if a new line border has been found
		if ( rowHasInk )
		{
			if ( not previousRowHasInk )
				topRow = i;
		}
		else
		{
			if ( previousRowHasInk )
				lineMarkers_.push_back( LineMarker(topRow, i-1) );
			else
				topRow = i;
		}
	}
	
	
	// Compute the mean shape height
	float meanShapeHeight = 0.0;
	
	for ( ShapeIterator iShape = shapes_.begin(); iShape not_eq shapes_.end(); ++iShape )
		meanShapeHeight += (*iShape).height();
	
	meanShapeHeight = meanShapeHeight / static_cast<float>(shapes_.size());
	
	
	// Point iterators to the first two elements
	std::list<LineMarker>::iterator previousLineMarkerIterator	= lineMarkers_.begin();
	std::list<LineMarker>::iterator currentLineMarkerIterator	= lineMarkers_.begin();
	advance( currentLineMarkerIterator, 1 );
	
	// Search for lines that are too close to each other, probably because there are characters with accents in a single line
	while ( currentLineMarkerIterator not_eq lineMarkers_.end() )
	{
		// An accent is as much as three times smaller than the mean shape height
		if ( ((*previousLineMarkerIterator).second - (*previousLineMarkerIterator).first + 1) >= round(meanShapeHeight / 4.0) )
		{
			// This is not an accent
			advance( currentLineMarkerIterator, 1 );
			advance( previousLineMarkerIterator, 1 );
		}
		else
		{
			// A new line marker representing the union of the two line markers that are being handled is inserted
			// and the two old line markers are removed from the list
			
			lineMarkers_.insert( previousLineMarkerIterator, LineMarker((*previousLineMarkerIterator).first, (*currentLineMarkerIterator).second) );
			
			std::list<LineMarker>::iterator newLineMarkerIterator = previousLineMarkerIterator;
			advance ( newLineMarkerIterator, -1 );
			
			// Delete the first line marker
			lineMarkers_.erase( previousLineMarkerIterator );

			// Delete the second line marker
			previousLineMarkerIterator = currentLineMarkerIterator;
			advance( currentLineMarkerIterator, 1 );
			lineMarkers_.erase( previousLineMarkerIterator );
			
			// Point to the new element inserted
			previousLineMarkerIterator = newLineMarkerIterator;
		}
	}
};



void Segmenter::joinVerticallyOverlappedShapes (ShapeIterator& s1, ShapeIterator& s2)
{
	// Join shapes into a new one and insert it before the current shape
	shapes_.push_back(*s1 + *s2);
	
	// Delete the second shape
	shapes_.erase(s2);
	
	// Update iterators
	s2 = s1;
	advance(s2, 1);
	
	// Delete the first shape
	shapes_.erase(s1);
	s1 = s2;
};



///
/// @details The list of shapes is traversed in order to find a shape that is vertically overlapped with the shape passed. A shape is considered
/// as overlapped when at least one pixel is overlapped with the shape of interest. This minimum criteria is necessary because of characters that
/// are too small.
///
ShapeIterator Segmenter::findVerticallyOverlappedShape (const unsigned int& lineTop, const unsigned int& lineBottom, const ShapeIterator& shape)
{
	for ( ShapeIterator i = shapes_.begin(); i not_eq shapes_.end(); ++i )
	{
		// Avoid processing a shape against itself
		if ( shape == i )
			continue;
		
		bool candidateShapeIsAboveShapeOfInterest = ((*i).topPixel().first < lineTop) and ((*i).bottomPixel().first < lineTop);
		bool candidateShapeIsBelowShapeOfInterest = ((*i).topPixel().first > lineBottom) and ((*i).bottomPixel().first > lineBottom);

		// Avoid processing a shape that is outside the line borders
		if ( candidateShapeIsAboveShapeOfInterest or candidateShapeIsBelowShapeOfInterest )
			continue;
		
		unsigned int overlappedPixels	= 0;
		
		// Count the overlapped pixels that the shape has with the shape of interest
		for ( unsigned int j = 0; j < (*i).size(); ++j )
		{
			if ( ((*i)(j).second > (*shape).leftPixel().second) and ((*i)(j).second < (*shape).rightPixel().second) )
				overlappedPixels++;
		}
		
		// Check if the shape is overlapped with the shape of interest
		if ( overlappedPixels >= 1)
			return i;
	}
	return shape;
};




// void Segmenter::applyAdaptiveThreshold (Clip& clip, const std::vector<unsigned char>& thresholds, const unsigned char& backgroundReference, const unsigned int& subclipSide)
// {
// 	// Explore subimages
// 	for ( unsigned int row = 0; row < ceil(static_cast<double>(clip.height()) / static_cast<double>(subclipSide)) ; ++row )
// 	{
// 		for ( unsigned int column = 0; column < ceil(static_cast<double>(clip.width()) / static_cast<double>(subclipSide)) ; ++column )
// 		{
// 			for ( unsigned int i = row * subclipSide; (i < ((row * subclipSide) + subclipSide)) and (i < clip.height()); ++i )
// 			{
// 				for ( unsigned int j = column * subclipSide; (j < ((column * subclipSide) + subclipSide)) and (j < clip.width()); ++j )
// 				{
// 					unsigned char grayLevel = clip.getPixelGrayLevel(i, j);
// 					unsigned char threshold = thresholds[row*column];
// 
// 					if ( (backgroundReference > threshold) and (grayLevel >= threshold) )	// The background is near white
// 						clip.setPixelGrayLevel(i, j, 255);
// 					else
// 					{
// 						if ( (backgroundReference > threshold) and (grayLevel < threshold) )
// 							clip.setPixelGrayLevel(i,j, 0);
// 						else
// 						{
// 							if ( (backgroundReference < threshold) and (grayLevel < threshold) )	// The background is near black
// 								clip.setPixelGrayLevel(i,j, 0);
// 							else
// 								clip.setPixelGrayLevel(i,j, 255);
// 						}
// 					}	
// 				}
// 			}
// 		}
// 	}
// };

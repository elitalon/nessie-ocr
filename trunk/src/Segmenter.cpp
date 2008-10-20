///
/// @file
/// @brief Definition of the class Segmenter
///

#include "Segmenter.hpp"

#include "boost/timer.hpp"

#include <algorithm>
#include <iostream>



///
/// @details Initializes a Segmenter object
///
Segmenter::Segmenter ()
	:	inkValue_(0),
		shapes_(std::vector<Shape>(0)),
		thresholdingTime_(0.0),
		floodFillingTime_(0.0),
		seeds_(std::list<Pixel>(0))
{
	
};



///
/// @details Simple thresholding that compares each pixel's gray level with a threshold value. The background reference gray level is taken
/// into account to decide the final gray level that must be applied to the pixel.
///
void Segmenter::applyThreshold (Clip &clip, const unsigned char &threshold, const unsigned char &backgroundReference)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	// Threshold every pixel
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			unsigned char grayLevel = clip(i, j);
			
			if ( (backgroundReference >= threshold) and (grayLevel >= threshold) )	// The background is near white
				clip(i, j) = 255;
			else
			{
				if ( (backgroundReference >= threshold) and (grayLevel < threshold) )
					clip(i, j) = 0;
				else
				{
					if ( (backgroundReference < threshold) and (grayLevel < threshold) )	// The background is near black
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
/// @details The 'flood fill' algorithm is a segmentation technique that isolates every shape in a clip that represents a character.
/// Every shape is built starting from a seed, i.e. an ink pixel, exploring its neighbourhood and adding every ink pixel that is
/// connected to the seed. The process ends when there are not more seeds to explore and the shapes are completely isolated.
/// 
void Segmenter::applyFloodFill (const Clip &clip)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	// Find the seeds where the flooding process will start from
	findSeeds(clip);
	
	// Explore the neighbourhood of each seed. Since a subset of seeds are removed for each shape, the
	// 'while' style avoids to make an error by modifying a list that is being reading
	while ( seeds_.size() > 0 )
	{
		shapes_.push_back(Shape());
		exploreSeedNeighbourhood(*(seeds_.begin()), clip);
	}
	
	///
	/// 3. Sort shapes according to their position within the clip
	///

	
	// Gather elapsed time
	floodFillingTime_ = timer.elapsed();
};



///
/// @details All the pixels of the clip are explored, adding to the vector of #seeds_ those whose gray level is equal to the ink's gray level
/// stablished in #inkValue_ member.
///
void Segmenter::findSeeds (const Clip &clip)
{
	// Explore the whole clip adding the ink pixels
	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			if ( clip(i, j) == inkValue_ )
				seeds_.push_back(Pixel(i, j));
		}
	}
};



///
/// @details
///
bool Segmenter::isSeed (const Pixel& pixel) const
{
	if( static_cast<int>(std::count(seeds_.begin(), seeds_.end(), pixel)) > 0 )
		return true;
	else
		return false;
};



///
/// @details
///
void Segmenter::exploreSeedNeighbourhood (const Pixel &seed, const Clip &clip)
{
	// Check that seed's coordinates fall inside the clip
	if ( (seed.first < 0) or (seed.first >= clip.height()) )
		return;
	
	if ( (seed.second < 0) or (seed.second >= clip.width()) )
		return;


	// Test this pixel has a gray level equal to the character's ink value
	if ( clip(seed.first, seed.second) not_eq inkValue_ )
		return;
		
	// Test this pixel has already been explored
	if ( not isSeed(seed) )
		return;
	
	
	// Save the coordinates and remove this seed from the list
	unsigned int x = seed.first, y = seed.second;
	seeds_.remove(seed);


	// Recursive calls
	exploreSeedNeighbourhood( Pixel(x, y+1), clip );	// East
	exploreSeedNeighbourhood( Pixel(x, y-1), clip );	// West
	exploreSeedNeighbourhood( Pixel(x+1, y), clip );	// South
	exploreSeedNeighbourhood( Pixel(x-1, y), clip );	// North
	exploreSeedNeighbourhood( Pixel(x+1, y+1), clip );	// South-East
	exploreSeedNeighbourhood( Pixel(x+1, y-1), clip );	// South-West
	exploreSeedNeighbourhood( Pixel(x-1, y+1), clip );	// North-East
	exploreSeedNeighbourhood( Pixel(x-1, y-1), clip );	// North-West
};



// void Segmenter::applyAdaptiveThreshold (Clip &clip, const std::vector<unsigned char> &thresholds, const unsigned char &backgroundReference, const unsigned int &subclipSide)
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

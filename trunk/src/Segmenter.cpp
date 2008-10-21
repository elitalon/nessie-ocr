///
/// @file
/// @brief Definition of the class Segmenter
///

#include "Segmenter.hpp"

#include "Clip.hpp"
#include "Pixel.hpp"
#include "boost/timer.hpp"

#include <list>
#include <algorithm>
#include <iostream>



///
/// @details Initializes a Segmenter object
///
Segmenter::Segmenter ()
	:	inkValue_(0),
		shapes_(std::vector<Shape>(0)),
		thresholdingTime_(0.0),
		shapesFindingTime_(0.0)
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
/// @details This method follows a strategy similar to the 'flood fill' algorithm. The main target is to isolate every shape in a clip that represents
/// a character. Every shape is built starting from an ink pixel (a seed) and exploring its neighbourhood looking for connected pixels. The process
/// ends when there are not more seeds to explore and the shapes are completely isolated.
/// 
void Segmenter::findShapes (const Clip &clip)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	// Find the seeds where the flooding process will start from
	std::list<Pixel> seeds;
	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			if ( clip(i, j) == inkValue_ )
				seeds.push_back(Pixel(i, j));
		}
	}
	
	
	// A vector of "visited/non visited" status for the pixels in the clip
	std::vector<bool> visited(clip.size(), false);
	
	
	// Explore the neighbourhood of each seed. For each pixel explored, the vector above tells if it has already been explored
	std::list<Pixel>::iterator seedsIterator;
	for (  seedsIterator = seeds.begin(); seedsIterator not_eq seeds.end(); ++seedsIterator )
	{
		unsigned int row	= (*seedsIterator).first;
		unsigned int column	= (*seedsIterator).second;
		
		if ( not visited.at(row * clip.width() + column) )	// This seed has not already been visited
		{
			visited.at(row * clip.width() + column) = true;
			
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
						if ( clip(i,j) == inkValue_ and not visited.at(i * clip.width() + j) )
						{
							visited.at(i * clip.width() + j) = true;
							shapes_.back().addPixel( Pixel(i, j) );
						}
					}
				}
			}
			
			
			// Explore the neighbours of the neighbours of the seed.
			unsigned int index = 1;
			while ( shapes_.back().size() > index )
			{
				Pixel pixel( shapes_.back()(index) );
				
				// Explore the neighbour's neighbourhood
				for ( unsigned int i = pixel.first-1; (i <= pixel.first+1) and (i < clip.height()); ++i )
				{
					for ( unsigned int j = pixel.second-1; (j <= pixel.second+1) and (j < clip.width()); ++j )
					{
						// Test clip borders are not passed
						if ( i >= 0 and j >= 0 )
						{
							// Add this neighbour if has ink and has already not been visited
							if ( clip(i,j) == inkValue_ and not visited.at(i * clip.width() + j) )
							{
								visited.at(i * clip.width() + j) = true;
								shapes_.back().addPixel( Pixel(i, j) );
							}
						}
					}
				}
				index++;
			}
		}
	}


	// Gather elapsed time
	shapesFindingTime_ = timer.elapsed();
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

///
/// @file
/// @brief Definition of the class Segmenter
///

#include "Segmenter.hpp"

#include "Clip.hpp"
#include "boost/timer.hpp"

#include <iostream>

///
/// @details Initializes a Segmenter object
///
Segmenter::Segmenter ()
	:	shapes_(std::vector<Shape>(0)), thresholdingTime_(0.0), floodFillingTime_(0.0)
{
	
};


///
/// @details Simple thresholding by comparing every pixel gray level with a threshold value
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
			unsigned char grayLevel = clip.getPixelGrayLevel(i, j);
		
			if ( grayLevel > threshold )
				clip.setPixelGrayLevel(i, j, 255);
			else
				clip.setPixelGrayLevel(i, j, 0);
			// if ( (backgroundReference > threshold) and (grayLevel >= threshold) )	// The background is near white
			// 				clip.setPixelGrayLevel(i, j, 255);
			// 			else
			// 			{
			// 				if ( (backgroundReference > threshold) and (grayLevel < threshold) )
			// 					clip.setPixelGrayLevel(i,j, 0);
			// 				else
			// 				{
			// 					if ( (backgroundReference < threshold) and (grayLevel >= threshold) )	// The background is near black
			// 						clip.setPixelGrayLevel(i,j, 255);
			// 					else
			// 						clip.setPixelGrayLevel(i,j, 0);
			// 				}
			// 			}	
		}
	}
	
	
	// Gather elapsed time
	thresholdingTime_ = timer.elapsed();
};


///
/// @details
/// 
void Segmenter::applyFloodFill (const Clip &clip)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	
	// Gather elapsed time
	floodFillingTime_ = timer.elapsed();
};

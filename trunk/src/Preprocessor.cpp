///
/// @file
/// @brief Implementation of the class Preprocessor
///

#include "Preprocessor.hpp"

#include <cmath>
#include <vector>
#include <algorithm>

#include "Clip.hpp"
#include "boost/timer.hpp"



///
/// @details Initializes a Preprocessor object
/// 
Preprocessor::Preprocessor ()
	: optimalThreshold_(0), backgroundReferenceGrayLevel_(255),
	noiseRemovalTime_(0.0), optimalThresholdComputingTime_(0.0), backgroundReferenceGrayLevelFindingTime_(0.0)
{

};


///
/// @details To compute the optimal threshold we follow the strategy proposed by Sonka M., Hlavac V. and Boyle R. in
/// "Image Processing, Analysis and Machine Vision" (Thomson Learning, 2008). The target is to find a mean value between
/// the mean value of background's gray level and the mean value of objects' gray level, starting from an initial threshold value.
/// 
unsigned char Preprocessor::computeOptimalThreshold (const Clip &clip)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	// Get the pixels of the clip (this is faster than calling clip.getPixelGrayLevel() each time)
	std::vector<unsigned char> pixels = clip.pixels();
	
	
	// Start with an initial threshold
	optimalThreshold_ = backgroundReferenceGrayLevel_;
	unsigned char currentThreshold = not optimalThreshold_;	// Enforces current threshold to be different so the firts loop is always made
	
	
	// Loop as many times as needed to find the optimal threshold by averaging the pixel gray levels
	while (currentThreshold not_eq optimalThreshold_)
	{
		unsigned int backgroundMeanValue = 0, objectsMeanValue = 0;
		unsigned int nSamples = 0;
		
		std::vector<unsigned char>::iterator pixelsIterator;
		
		// Compute the background and objects mean values
		for ( pixelsIterator = pixels.begin(); pixelsIterator not_eq pixels.end(); ++pixelsIterator )
		{
			unsigned char grayLevel = *pixelsIterator;
			
			if ( grayLevel >= optimalThreshold_ )
			{
				backgroundMeanValue += grayLevel;
				nSamples++;
			}
			else
				objectsMeanValue += grayLevel;
		}
		backgroundMeanValue = round(backgroundMeanValue / nSamples);
		objectsMeanValue = round(objectsMeanValue / (clip.nPixels() - nSamples));


		// Update the optimal threshold keeping the last one
		currentThreshold = optimalThreshold_;
		optimalThreshold_ = static_cast<unsigned char>( round((objectsMeanValue + backgroundMeanValue) / 2) );
	}
	
	// Gather elapsed time
	optimalThresholdComputingTime_ = timer.elapsed();
	
	return optimalThreshold_;
};


///
/// @details To find the reference gray level of the background it is assumed that there are more pixels belonging to the
/// background than belonging to the foreground. Then, we search the more frequent gray level and its neighbours. Finally, we compute
/// a gray level weighted mean using all those values.
/// 
unsigned char Preprocessor::findBackgroundReferenceGrayLevel (const Clip &clip, const unsigned int &referenceGrayLevelNeighbours)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	// Get the pixels of the clip (this is faster than calling clip.getPixelGrayLevel() each time)
	std::vector<unsigned char> pixels = clip.pixels();
	
	
	// Compute clip histogram
	std::vector<unsigned int> histogram(256, 0);
	std::vector<unsigned char>::iterator pixelsIterator;
	
	for ( pixelsIterator = pixels.begin(); pixelsIterator not_eq pixels.end(); ++pixelsIterator )
		histogram[*pixelsIterator] += 1;
	
		
	// Search the more frequent level of gray
	std::vector<unsigned int>::iterator histogramIterator;
	unsigned char moreFrequentGrayLevel = 0, levelCounter = 0;

	for (histogramIterator = histogram.begin(); histogramIterator not_eq histogram.end(); ++histogramIterator, ++levelCounter)
	{
		if ( *histogramIterator > histogram[moreFrequentGrayLevel] )
			moreFrequentGrayLevel = levelCounter;
	}
	unsigned int referenceGrayLevel = moreFrequentGrayLevel * histogram[moreFrequentGrayLevel];


	// Search the neighbours of the more frequent level of gray
	std::vector<unsigned int>::reverse_iterator histogramReverseIterator( std::find (histogram.rbegin(), histogram.rend(), histogram[moreFrequentGrayLevel])++ );
	histogramIterator = histogramReverseIterator.base()++;
	unsigned int nFrequencies = histogram[moreFrequentGrayLevel];

	for ( unsigned int i = 1; i <= referenceGrayLevelNeighbours; ++i )
	{
		// Search forwards
		if ( histogramIterator not_eq histogram.end() )
		{
			referenceGrayLevel	+= (moreFrequentGrayLevel + i) * histogram[moreFrequentGrayLevel + i];
			nFrequencies		+= histogram[moreFrequentGrayLevel + i];

			++histogramIterator;
		}

		// Search backwards
		if ( histogramReverseIterator not_eq histogram.rend() )
		{
			referenceGrayLevel	+= (moreFrequentGrayLevel - i) * histogram[moreFrequentGrayLevel - i];
			nFrequencies		+= histogram[moreFrequentGrayLevel - i];

			++histogramReverseIterator;
		}
	}

	// Set the background reference gray level found
	backgroundReferenceGrayLevel_ = static_cast<unsigned char>( round(referenceGrayLevel / nFrequencies) );
	
	// Gather elapsed time
	backgroundReferenceGrayLevelFindingTime_ = timer.elapsed();
	
	return backgroundReferenceGrayLevel_;
};


///
/// @details The 'isolated noise removal' algorithm tries to eliminate isolated noisy pixels from an clip.
/// The isolationCoefficient parameter defines how much isolated should be a noisy pixel to be removed. That means
/// a noisy pixel will be removed whenever it has as much neighbours whose gray level is over a threshold value as isolationCoefficient.
/// 
void Preprocessor::removeIsolatedNoise (Clip &clip, const unsigned int &isolationCoefficient)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	// Loop over the clip to remove every noisy isolated pixel
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			unsigned char pixelGrayLevel = clip.getPixelGrayLevel(i, j);
			
			// Comparison values to avoid pixels that clearly belong to the background
			bool backgroundPixelOnWhite = (backgroundReferenceGrayLevel_ > optimalThreshold_) and (pixelGrayLevel > backgroundReferenceGrayLevel_);
			bool backgroundPixelOnBlack = (backgroundReferenceGrayLevel_ < optimalThreshold_) and (pixelGrayLevel < backgroundReferenceGrayLevel_);
			
			if ( not backgroundPixelOnBlack and not backgroundPixelOnWhite )
			{
				unsigned int nBackgroundPixels = 0, nPixels = 0;

				// Explore the pixel neighbourhood
				for(int p = i-1; p < static_cast<int>(i+2); p++)
				{
					for(int q = j-1; q < static_cast<int>(j+2); q++)
					{
						// Comparison values to avoid step outside the image and the central pixel
						bool heightOverflow	= (p < 0) or (p >= static_cast<int>(clip.height()));
						bool widthOverflow	= (q < 0) or (q >= static_cast<int>(clip.width()));
						bool isCentralPixel = (p == static_cast<int>(i)) and (q == static_cast<int>(j));
						
						if ( not heightOverflow and not widthOverflow and not isCentralPixel )
						{
							// Update pixels counter
							nPixels++;

							// Get neighbour pixel gray level
							unsigned char neighbourPixelGrayLevel = clip.getPixelGrayLevel(p, q);

							// When background gray level is close to white but not the pixel, update the noisy neighbours counter
							if ( (backgroundReferenceGrayLevel_ > optimalThreshold_) and (neighbourPixelGrayLevel > optimalThreshold_) )
								nBackgroundPixels++;
							else
							{
								// When background gray level is close to black but not the pixel, update the noisy neighbours counter
								if ( (backgroundReferenceGrayLevel_ < optimalThreshold_) and (neighbourPixelGrayLevel < optimalThreshold_) )
									nBackgroundPixels++;
							}
						}
					}
				}

				// Clear the noisy pixel if it is isolated
				if (nBackgroundPixels >= (nPixels - isolationCoefficient))
					clip.setPixelGrayLevel(i, j, backgroundReferenceGrayLevel_);
			}
		}
	}
	
	// Gather elapsed time
	noiseRemovalTime_ = timer.elapsed();
};

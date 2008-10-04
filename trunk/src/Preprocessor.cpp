///
/// @file
/// @brief Implementation of class Preprocessor
///

#include "Preprocessor.h"
#include "Clip.h"

#include <cmath>
#include <vector>



///
/// @details Initializes a Preprocessor object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
Preprocessor::Preprocessor ()
	: optimalThreshold_(0.0), backgroundReferenceGrayLevel_(1.0),
	noiseRemovalTime_(0.0), optimalThresholdComputingTime_(0.0), backgroundReferenceGrayLevelFindingTime_(0.0)
{
	
};


///
/// @details Destroys a Preprocessor object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
Preprocessor::~Preprocessor ()
{
	
};


///
/// @return Current optimal threshold computed from the last clip used
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
double Preprocessor::optimalThreshold () const
{
	return optimalThreshold_;
};


///
/// @param threshold A value between 0.0 and 1.0 that stablishes the optimal threshold of a clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
void Preprocessor::optimalThreshold (const double &threshold)
{
	if ( threshold < 0.0 )
		optimalThreshold_ = 0.0;
	else
	{
		if ( threshold > 1.0 )
			optimalThreshold_ = 1.0;
		else
			optimalThreshold_ = threshold;
	}
};


///
/// @return Reference vackground gray level in the last clip used
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
double Preprocessor::backgroundReferenceGrayLevel () const
{
	return backgroundReferenceGrayLevel_;
};


///
/// @param grayLevel Background reference gray level to use in algorithms
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
void Preprocessor::backgroundReferenceGrayLevel (const double &grayLevel)
{
	if ( grayLevel < 0.0 )
		backgroundReferenceGrayLevel_ = 0.0;
	else
	{
		if ( grayLevel > 1.0 )
			backgroundReferenceGrayLevel_ = 1.0;
		else
			backgroundReferenceGrayLevel_ = grayLevel;
	}
};


///
/// @return Elapsed time when applying the 'isolated noise removal' algorithm
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
double Preprocessor::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};


///
/// @return Elapsed time while computing the background reference gray level
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
double Preprocessor::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


///
/// @return Elapsed time while founding the optimal threshold within the clip
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
double Preprocessor::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


///
/// @details Algorithm explanation
/// 
/// @param[in,out] clip The clip where applying the algorithm over
/// 
/// @return The optimal threshold of the clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
double Preprocessor::computeOptimalThreshold (const Clip &clip)
{
	return 0.0;
};


///
/// @details To find the reference gray level of the background it is assumed that there are more pixels belonging to the
/// background than beloging to the foreground. Then, we search the more frequent gray level and its neighbours. Finally, we compute
/// a gray level weighted mean using all those values.
/// 
/// @param[in,out]	clip							The clip where applying the algorithm over
/// @param			referenceGrayLevelNeighbours	Number of the more frequent gray level neighbours to explore on each direction
/// 
/// @return The reference gray level of the background
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
double Preprocessor::findBackgroundReferenceGrayLevel (const Clip &clip, const unsigned int &referenceGrayLevelNeighbours)
{
	// Compute image histogram
	std::vector<unsigned int> histogram(256, 0);
	
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			// Get gray level of this pixel
			double grayLevel = clip.getPixel(i,j).grayLevel();
			
			// Update histogram
			histogram[std::floor(grayLevel * 255.0)] += 1;
		}
	}
	
	
	// Search the more frequent level of gray
	std::vector<unsigned int>::iterator histogramIterator;
	unsigned int moreFrequentGrayLevel = 0, levelCounter = 0;
	
	for (histogramIterator = histogram.begin(); histogramIterator not_eq histogram.end(); ++histogramIterator, ++levelCounter)
	{
		if ( *histogramIterator > histogram[moreFrequentGrayLevel] )
			moreFrequentGrayLevel = levelCounter;
	}
	backgroundReferenceGrayLevel_ = moreFrequentGrayLevel * histogram[moreFrequentGrayLevel];
	
	
	// Search the neighbours of the more frequent level of gray
	std::vector<unsigned int>::reverse_iterator histogramReverseIterator( find (histogram.rbegin(), histogram.rend(), histogram[moreFrequentGrayLevel])++ );
	histogramIterator = histogramReverseIterator.base()++;
	double nFrequencies = histogram[moreFrequentGrayLevel];
	
	for ( unsigned int i = 1; i <= referenceGrayLevelNeighbours; ++i )
	{
		// Search forwards
		if ( histogramIterator not_eq histogram.end() )
		{
			backgroundReferenceGrayLevel_ += (moreFrequentGrayLevel + i) * histogram[moreFrequentGrayLevel + i];
			++histogramIterator;
			nFrequencies += histogram[moreFrequentGrayLevel + i];
		}
		
		// Search backwards
		if ( histogramReverseIterator not_eq histogram.rend() )
		{
			backgroundReferenceGrayLevel_ += (moreFrequentGrayLevel - i) * histogram[moreFrequentGrayLevel - i];
			++histogramReverseIterator;
			nFrequencies += histogram[moreFrequentGrayLevel - i];
		}
	}
	
	
	// Set the background reference gray level found
	backgroundReferenceGrayLevel_ = (backgroundReferenceGrayLevel_ / nFrequencies) / 255.0;
	return backgroundReferenceGrayLevel_;
};


///
/// @details The 'isolated noise removal' algorithm tries to eliminate isolated noisy pixels from an clip.
/// The isolationCoefficient parameter defines how much isolated should be a noisy pixel to be removed. That means
/// a noisy pixel will be removed whenever it has up to isolationCoefficient neighbours whose gray level is over a threshold value,
/// which is controlled by the optimalThreshold attribute.
/// 
/// @remarks You MUST call Preprocessor::computeOptimalThreshold method before calling this, since the optimalThreshold attribute
/// is used internally to know whether a pixel is noisy or not.
/// 
/// @param[in,out]	clip					The clip where applying the algorithm over
/// @param			isolationCoefficient	The maximum noisy neighbours for a pixel to consider it as isolated
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Preprocessor::removeIsolatedNoise (Clip &clip, const unsigned int &isolationCoefficient)
{
	// Find background reference gray level
	findBackgroundReferenceGrayLevel(clip);
	
	
	// Loop over the clip to remove every noisy isolated pixel
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			unsigned int nBackgroundPixels = 0, nPixels = 0;

			// Explore the pixel neighbourhood
			for(int p = i-1; p < (signed int)i+2; p++)
			{
				for(int q = j-1; q < (signed int)j+2; q++)
				{
					// Check clip borders
					if ( (p < 0) or (p >= (signed int)clip.height()) )
						continue;
					
					if ( (q < 0) or (q >= (signed int)clip.width()) )
						continue;
					
					nPixels++;
					
					// Get neighbour pixel gray level
					Pixel neighbourPixel = clip.getPixel(p, q);
					
					// When background gray level is close to white but not the pixel, update the noisy neighbours counter
					if ( (backgroundReferenceGrayLevel_ > optimalThreshold_) and (neighbourPixel.grayLevel() > optimalThreshold_) )
						nBackgroundPixels++;
					else
					{
						// When background gray level is close to black but not the pixel, update the noisy neighbours counter
						if ( (backgroundReferenceGrayLevel_ < optimalThreshold_) and (neighbourPixel.grayLevel() < optimalThreshold_) )
							nBackgroundPixels++;
					}
				}
			}
			
			// Adjust the isolated coefficient influence according to the number of neighbours found
			unsigned int realIsolationCoefficient = nPixels - 8 + (8 - isolationCoefficient);

			// Delete the noisy pixel if it is isolated
			if (nBackgroundPixels >= realIsolationCoefficient)
				clip.setPixel(i, j, backgroundReferenceGrayLevel_);
		}
	}
};

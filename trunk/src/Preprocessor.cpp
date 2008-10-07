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
/// @return Reference background gray level in the last clip used
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
/// @details To compute the optimal threshold we follow the strategy proposed by Sonka M., Hlavac V. and Boyle R. in
/// "Image Processing, Analysis and Machine Vision" (Thomson Learning, 2008). The target is to find a mean value between
/// the mean value of background's gray level and the mean value of objects' gray level, assuming we have an initial threshold value.
/// That initial threshold is in fact provided by the Preprocessor::findBackgroundReferenceGrayLevel method.
/// 
/// @param[in] clip The clip where applying the algorithm over
/// 
/// @return The optimal threshold of the clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-06
///
double Preprocessor::computeOptimalThreshold (const Clip &clip)
{
	// Find background reference gray level
	findBackgroundReferenceGrayLevel(clip);
	optimalThreshold_ = backgroundReferenceGrayLevel_;
	double temporaryThreshold;
	
	do
	{
		// Compute the background and objects mean values
		double backgroundMeanValue = 0.0, objectsMeanValue = 0.0;
		unsigned int nSamples = 0;
		
		for (unsigned int i=0; i < clip.height(); ++i)
		{
			for (unsigned int j=0; j < clip.width(); ++j)
			{
				// Get gray level of this pixel
				double grayLevel = clip.getPixelGrayLevel(i,j);
				
				// Assume light gray values as the background
				if ( grayLevel >= optimalThreshold_ )
				{
					backgroundMeanValue += grayLevel;
					nSamples++;
				}
				else
					objectsMeanValue += grayLevel;
			}
		}
		backgroundMeanValue = backgroundMeanValue / static_cast<double>(nSamples);
		objectsMeanValue = objectsMeanValue / static_cast<double>(clip.nPixels() - nSamples);
				
		// Update the optimal threshold keeping the last one
		temporaryThreshold = optimalThreshold_;
		optimalThreshold_ = (objectsMeanValue + backgroundMeanValue) / 2.0;
	}
	while (temporaryThreshold != optimalThreshold_);

	return optimalThreshold_;
};


///
/// @details To find the reference gray level of the background it is assumed that there are more pixels belonging to the
/// background than belonging to the foreground. Then, we search the more frequent gray level and its neighbours. Finally, we compute
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
			double grayLevel = clip.getPixelGrayLevel(i,j);
			
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
					double neighbourPixelGrayLevel = clip.getPixelGrayLevel(p, q);
					
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
			
			// Adjust the isolated coefficient influence according to the number of neighbours found
			unsigned int realIsolationCoefficient = nPixels - 8 + (8 - isolationCoefficient);

			// Delete the noisy pixel if it is isolated
			if (nBackgroundPixels >= realIsolationCoefficient)
				clip.setPixel(i, j, backgroundReferenceGrayLevel_);
		}
	}
};



//
// Otsu's algorithm for computing optimal threshold
//

// // Compute image histogram
// std::vector<double> histogram(256, 0.0);
// for (unsigned int i=0; i < clip.height(); ++i)
// {
// 	for (unsigned int j=0; j < clip.width(); ++j)
// 	{
// 		// Get gray level of this pixel
// 		double grayLevel = clip.getPixel(i,j).grayLevel();
// 		
// 		// Update histogram
// 		histogram[std::floor(grayLevel * 255.0)] += 1.0;
// 	}
// }
// 
// // Normalise histogram
// std::transform( histogram.begin(), histogram.end(), histogram.begin(), std::bind1st(std::multiplies<double>(), 1.0 / static_cast<double>(clip.nPixels())) );
// 
// // Compute the zero- and first-order cumulative moments of the normalised histogram up to the kth level
// std::vector<double> zeroMoments(256, 0.0), firstMoments(256, 0.0);
// for ( unsigned int level = 0; level < 256; ++level )
// {
// 	for ( unsigned int i = 1; i <= (level+1); ++i )
// 	{
// 		zeroMoments[level]	+= histogram[i-1];
// 		firstMoments[level]	+= histogram[i-1] * i;
// 	}
// }
// 
// // Compute the total mean level of the image
// double meanLevel = 0.0;
// for ( unsigned int level = 1; level <= 256; ++level )
// 	meanLevel += histogram[level-1] * level;
// 
// // Compute the variance of the class separability at every gray level	
// std::vector<double> variance(256, 0.0);
// for ( unsigned int level = 0; level < 256; ++level )
// 	variance[level] = pow((meanLevel * zeroMoments[level]) - firstMoments[level], 2) / (zeroMoments[level] * (1 - zeroMoments[level]));
// 	
// // Find the maximum value of variance
// unsigned int level = 0;
// double maxVariance = variance[0];
// for ( std::vector<double>::iterator varianceIterator = variance.begin(); varianceIterator < variance.end(); ++varianceIterator, ++level )
// {
// 	if ( *varianceIterator > maxVariance )
// 	{
// 		maxVariance = *varianceIterator;
// 		optimalThreshold_ = level;
// 	}
// }
// optimalThreshold_ = optimalThreshold_ / 255.0;
// 
// std::cout << "Optimal threshold with Otsu's method: " << optimalThreshold_ << std::endl;
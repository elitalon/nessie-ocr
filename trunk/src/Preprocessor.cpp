#include "Preprocessor.h"

///
/// @file
/// @brief Implementation of class Preprocessor
///

///
/// @details Initializes a Preprocessor object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
Preprocessor::Preprocessor ()
	: optimalThreshold_(80.0 / 256.0), backgroundReferenceGrayLevel_(1.0),
	noiseRemovalTime_(0.0), grayscaleConversionTime_(0.0), optimalThresholdComputingTime_(0.0)
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
void Preprocessor::optimalThreshold (double threshold)
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
void Preprocessor::backgroundReferenceGrayLevel (double grayLevel)
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
/// @return Elapsed time while converting the clip to a grayscale colorspace
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
double Preprocessor::grayscaleConversionTime () const
{
	return grayscaleConversionTime_;
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
/// @details The algorithm simply relies on the Magick++ utility to convert from one colorspace to another
/// 
/// @param[in,out] clip The clip where applying the algorithm over
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
void Preprocessor::convertToGrayscale (Clip& clip)
{
	if ( clip.colorspace() != COLORSPACE_GRAYSCALE )
		clip.colorspace(COLORSPACE_GRAYSCALE);
};


///
/// @details Algorithm explanation
/// 
/// @param[in,out] clip The clip where applying the algorithm over
/// 
/// @return The optimal threshold of the clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
double Preprocessor::computeOptimalThreshold (Clip& clip)
{
	// Implicit change of colorspace
	convertToGrayscale(clip);
	
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
/// @date 2008-10-01
///
double Preprocessor::findBackgroundReferenceGrayLevel (Clip& clip, unsigned int referenceGrayLevelNeighbours)
{
	// Implicit change of colorspace
	convertToGrayscale(clip);
	
	
	// Compute image histogram
	vector<unsigned int> histogram(256, 0);
	
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			// Get gray level of this pixel
			double grayLevel = clip.getPixel(i,j).grayLevel();
			
			// Update histogram
			histogram[floor(grayLevel * 255.0)] += 1;
		}
	}
	
	
	// Search the more frequent level of gray
	vector<unsigned int>::iterator histogramIterator;
	unsigned int moreFrequentGrayLevel = 0, levelCounter = 0;
	
	for (histogramIterator = histogram.begin(); histogramIterator != histogram.end(); ++histogramIterator, ++levelCounter)
	{
		if ( *histogramIterator > histogram[moreFrequentGrayLevel] )
			moreFrequentGrayLevel = levelCounter;
	}
	backgroundReferenceGrayLevel_ = moreFrequentGrayLevel * histogram[moreFrequentGrayLevel];
	
	
	// Search the neighbours of the more frequent level of gray
	vector<unsigned int>::reverse_iterator histogramReverseIterator( find (histogram.rbegin(), histogram.rend(), histogram[moreFrequentGrayLevel])++ );
	histogramIterator = histogramReverseIterator.base()++;
	double nFrequencies = histogram[moreFrequentGrayLevel];
	
	for ( unsigned int i = 1; i <= referenceGrayLevelNeighbours; ++i )
	{
		// Search forwards
		if ( histogramIterator != histogram.end() )
		{
			backgroundReferenceGrayLevel_ += (moreFrequentGrayLevel + i) * histogram[moreFrequentGrayLevel + i];
			++histogramIterator;
			nFrequencies += histogram[moreFrequentGrayLevel + i];
		}
		
		// Search backwards
		if ( histogramReverseIterator != histogram.rend() )
		{
			backgroundReferenceGrayLevel_ += (moreFrequentGrayLevel - i) * histogram[moreFrequentGrayLevel - i];
			++histogramReverseIterator;
			nFrequencies += histogram[moreFrequentGrayLevel - i];
		}
	}
	
	
	// Set the background reference gray level found
	backgroundReferenceGrayLevel_ = backgroundReferenceGrayLevel_ / nFrequencies;
	return backgroundReferenceGrayLevel_;
};


///
/// @details The 'isolated noise removal' algorithm tries to eliminate isolated noisy pixels from an clip.
/// The noisyNeighbours parameter defines how much isolated should be a noisy pixel to be removed. That means
/// a noisy pixel will be removed whenever it has less than noisyNeighbours whose gray level is over the noise threshold value,
/// which is controlled by the optimalThreshold attribute.
/// 
/// @remarks The changes made within this method remains after its ending. This includes the posible conversion to grayscale colorspace.
/// 
/// @param[in,out]	clip			The clip where applying the algorithm over
/// @param			noisyNeighbours	The noisy neighbours allowed for a pixel to consider it as isolated or not
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
void Preprocessor::removeIsolatedNoise (Clip& clip, unsigned int noisyNeighbours)
{
	// Implicit change of colorspace
	convertToGrayscale(clip);
	
	
	// Loop over the clip to remove every noisy isolated pixel
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			Pixel pixel = clip.getPixel(i, j);
			
			// Discard background pixels
			if ( (pixel.grayLevel() > optimalThreshold_) && (backgroundReferenceGrayLevel_ > optimalThreshold_) )
				continue;
			
			if ( (pixel.grayLevel() < optimalThreshold_) && (backgroundReferenceGrayLevel_ < optimalThreshold_) )
				continue;
	
				
			// Examine the pixel neighbourhood
			unsigned int nPixels = 0;
			
			for(int p = i-1; p < (signed int)i+2; p++)
			{
				for(int q = j-1; q < (signed int)j+2; q++)
				{
					// Check clip borders
					if ( (p < 0 || p >= (signed int)clip.width()) || (q < 0 || q >= (signed int)clip.height()) )
						continue;
					else
						nPixels++;
					
					// Get neighbour pixel gray level
					Pixel neighbourPixel = clip.getPixel(p, q);
					
					// Update the noisy pixel count
					if (neighbourPixel.grayLevel() > optimalThreshold_)
						; //backgroundPixels += 1;
				}
			}
		}
	}
	
};

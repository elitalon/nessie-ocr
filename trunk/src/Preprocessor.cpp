///
/// @file
/// @brief Definition of Preprocessor class
///

#include "Preprocessor.hpp"

#include "Clip.hpp"
#include <boost/timer.hpp>

#include <cmath>
#include <algorithm>




Preprocessor::Preprocessor ()
	:	optimalThreshold_(0),
		backgroundReferenceGrayLevel_(255),
		noiseRemovalTime_(0.0),
		optimalThresholdComputingTime_(0.0),
		backgroundReferenceGrayLevelFindingTime_(0.0)
{
	
};



///
/// @details The strategy proposed by M. Sonka, V. Hlavac and R. Boyle in "Image Processing, Analysis and Machine Vision" (Thomson Learning, 2008)
/// is to find a mean value between the mean value of background's gray level and the mean value of objects' gray level, starting from an initial
/// threshold value that is given by the member ::backgroundReferenceGrayLevel_.
///
const unsigned char& Preprocessor::computeOptimalThreshold (const Clip& clip)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	

	// Start with an initial threshold
	optimalThreshold_ = backgroundReferenceGrayLevel_;
	unsigned char currentThreshold = ~optimalThreshold_;	// Enforces current threshold to be different so the firts loop is always made
	
	
	// Loop as many times as needed to find the optimal threshold by averaging the pixel gray levels
	while (currentThreshold not_eq optimalThreshold_)
	{
		double backgroundMeanValue = 0, objectsMeanValue = 0;
		unsigned int nSamples = 0;
		
		// Count the pixels that belong to objects and the pixels that belong to background
		for ( unsigned int i = 0; i < clip.height(); ++i )
		{
			for ( unsigned int j = 0; j < clip.width(); ++j )
			{
				unsigned char grayLevel = clip(i, j);
				
				if ( grayLevel >= optimalThreshold_ )
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
		currentThreshold = optimalThreshold_;
		optimalThreshold_ = static_cast<unsigned char>( round((objectsMeanValue + backgroundMeanValue) / 2.0) );
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
/// @bug There are cases where the reference gray level found does not match with the real background gray level, because the assumption made about
/// the background's number of pixels is false. An alternative may be to find two reference gray levels; if the classification process does not work,
/// everything must be undone and start again with the second reference gray level.
/// 
const unsigned char& Preprocessor::findBackgroundReferenceGrayLevel (const Clip& clip, const unsigned int& referenceGrayLevelNeighbours)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	// Compute clip's histogram
	std::vector<unsigned int> histogram(256, 0);
	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			histogram[static_cast<unsigned int>(clip(i, j))] += 1;
		}
	}
	
		
	// Search the more frequent level of gray
	std::vector<unsigned int>::iterator histogramIterator;
	unsigned int moreFrequentGrayLevel = 0;
	unsigned int maximumAppearances	= histogram[0];
	
	for ( unsigned int l = 1; l < 256; ++l )
	{
		if ( histogram[l] > maximumAppearances )
		{
			moreFrequentGrayLevel	= l;
			maximumAppearances		= histogram[l];
		}
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
void Preprocessor::removeIsolatedNoise (Clip& clip, const unsigned int& isolationCoefficient)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	
	// Loop over the clip to remove every noisy isolated pixel
	for (unsigned int i=0; i < clip.height(); ++i)
	{
		for (unsigned int j=0; j < clip.width(); ++j)
		{
			unsigned char pixelGrayLevel = clip(i, j);
			
			// Comparison values to avoid pixels that clearly belong to the background
			bool backgroundPixelOnWhite = (backgroundReferenceGrayLevel_ > optimalThreshold_) and (pixelGrayLevel >= backgroundReferenceGrayLevel_);
			bool backgroundPixelOnBlack = (backgroundReferenceGrayLevel_ < optimalThreshold_) and (pixelGrayLevel <= backgroundReferenceGrayLevel_);
			
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
							unsigned char neighbourPixelGrayLevel = clip(p, q);

							// When background gray level is close to white but not the pixel, update the noisy neighbours counter
							if ( (backgroundReferenceGrayLevel_ >= optimalThreshold_) and (neighbourPixelGrayLevel >= optimalThreshold_) )
								nBackgroundPixels++;
							else
							{
								// When background gray level is close to black but not the pixel, update the noisy neighbours counter
								if ( (backgroundReferenceGrayLevel_ < optimalThreshold_) and (neighbourPixelGrayLevel <= optimalThreshold_) )
									nBackgroundPixels++;
							}
						}
					}
				}

				// Clear the noisy pixel if it is isolated
				if (nBackgroundPixels >= (nPixels - isolationCoefficient))
					clip(i, j) = backgroundReferenceGrayLevel_;
			}
		}
	}
	
	// Gather elapsed time
	noiseRemovalTime_ = timer.elapsed();
};




// ///
// /// @details The strategy proposed by N. Otsu in "A Threshold Selection Method from Gray-Level Histograms"
// /// (IEEE Transactions on Systems, Man, and Cybernetics, 1979) maximises the likelihood that the threshold is chosen so as to split the image between
// /// and object and its background. An optimal threshold is selected by the discriminant criterion, namely, so as to maximize the separability of the
// /// resultant classes in gray levels. The procedure is very simple, utilizing only the zeroth- and the first-order cumulative moments of the
// /// gray-level histogram.
// ///
// void Preprocessor::computeOtsuOptimalThreshold (const Clip& clip)
// {
// 	// Start timing
// 	boost::timer timer;
// 	timer.restart();
// 	
// 	// Get the pixels of the clip (this is faster than calling clip.getPixelGrayLevel() each time)
// 	std::vector<unsigned char> pixels	= clip.pixels();
// 	
// 	
// 	///
// 	/// 1. Compute the gray-level histogram and normalized it.
// 	///
// 	std::vector<double> histogram(256,0.0);
// 	std::vector<unsigned char>::iterator pixelsIterator;
// 	
// 	for ( pixelsIterator = pixels.begin(); pixelsIterator not_eq pixels.end(); ++pixelsIterator )
// 		histogram[static_cast<int>(*pixelsIterator)] += 1.0;
// 	
// 	double nPixels = static_castdoublet>( clip.nPixels() );
// 	std::transform (histogram.begin(), histogram.end(), histogram.begin(), std::bind2nd(std::divides<double>(), nPixels) );
// 	
// 	
// 	///
// 	/// 2. Compute the total mean level of the image \f$\mu_T\f$.
// 	///
// 	double meanGrayLevel = 0.0;
// 	for ( unsigned int k = 1; k <= 256; ++k )
// 		meanGrayLevel += histogram[k-1] * static_cast<double>(k);
// 		
// 	
// 	///
// 	/// 3. For each gray level \f$k\f$ compute \f$\omega(k)\f$ y \f$\mu(k)\f$, which are the zeroth- and the first-order cumulative moments of the histogram
// 	/// up to the \f$k\f$th level.
// 	///
// 	std::vector<double> omega(256,0.0);
// 	std::vector<double> mu(256,0.0);
// 	for ( unsigned int k = 0; k < 256; ++k )
// 	{
// 		for ( unsigned int i = 0; i <= k; ++i )
// 		{
// 			omega[k]	+= histogram[i];
// 			mu[k]		+= histogram[i] * static_cast<double>(i+1) ;
// 		}
// 	}
// 	
// 	
// 	///
// 	/// 4. Compute the variance of the class separability \f$\sigma_B^2(k)\f$.
// 	///
// 	std::vector<double> sigma(256,0.0);
// 	for ( unsigned int k = 0; k < 256; ++k )
// 	{
// 		double numerator	= (meanGrayLevel * omega[k]) - mu[k];
// 		double denominator	= omega[k] - (1.0 - omega[k]);
// 		
// 		sigma[k] = pow(numerator, 2) / denominator;
// 	}
// 	
// 	
// 	///
// 	/// 5. Find the \f$k\f$th level that makes a \f$\sigma_B^2(k)\f$ value the maximum.
// 	///
// 	optimalThreshold_ = 0;
// 	double maximumSigma = sigma[0];
// 	for ( unsigned int k = 1; k < 256; ++k )
// 	{
// 		if ( sigma[k] > maximumSigma )
// 		{
// 			maximumSigma		= sigma[k];
// 			optimalThreshold_	= static_cast<unsigned char>(k);
// 		}
// 	}
// 	
// 	// Gather elapsed time
// 	optimalThresholdComputingTime_ = timer.elapsed();
// };



// ///
// /// @details To compute the optimal threshold following an adaptive strategy we divided the clip into <em>n</em> subclips and apply the Sonka's method
// /// over them. Thus, a list of threshold values are returned, one for each subimage, that allows a thresholding technique to be more accurate.
// ///
// unsigned int Preprocessor::computeOptimalAdaptiveThreshold (const Clip& clip, std::vector<unsigned char>& thresholds)
// {
// 	// Stablish the side's size of the subimages
// 	const unsigned int subclipSide	= 100;
// 
// 	// Get the pixels of the clip (this is faster than calling clip.getPixelGrayLevel() each time)
// 	std::vector<unsigned char> pixels = clip.pixels();
// 	
// 	// Empty output vector
// 	thresholds.clear();
// 	
// 	// Explore subimages
// 	for ( unsigned int row = 0; row < ceil(static_cast<double>(clip.height()) / static_castdoublet>(subclipSide)) ; ++row )
// 	{
// 		for ( unsigned int column = 0; column < ceil(static_cast<double>(clip.width()) / static_castdoublet>(subclipSide)) ; ++column )
// 		{
// 			// Start with an initial threshold
// 			unsigned char optimalThreshold = backgroundReferenceGrayLevel_;
// 			unsigned char currentThreshold = ~optimalThreshold;	// Enforces current threshold to be different so the firts loop is always made
// 
// 			// Loop as many times as needed to find the optimal threshold by averaging the pixel gray levels
// 			while (currentThreshold not_eq optimalThreshold)
// 			{
// 				double backgroundMeanValue = 0, objectsMeanValue = 0;
// 				unsigned int nSamples = 0;
// 
// 				for ( unsigned int i = row * subclipSide; (i < ((row * subclipSide) + subclipSide)) and (i < clip.height()); ++i )
// 				{
// 					for ( unsigned int j = column * subclipSide; (j < ((column * subclipSide) + subclipSide)) and (j < clip.width()); ++j )
// 					{
// 						unsigned char grayLevel = pixels[i * clip.width() + j];
// 
// 						if ( grayLevel >= optimalThreshold )
// 						{
// 							backgroundMeanValue += static_cast<double>(grayLevel);
// 							nSamples++;
// 						}
// 						else
// 							objectsMeanValue += static_cast<double>(grayLevel);
// 					}
// 				}
// 
// 				backgroundMeanValue = round(backgroundMeanValue / static_cast<double>(nSamples));
// 				objectsMeanValue = round(objectsMeanValue / static_cast<double>(clip.nPixels() - nSamples));
// 
// 
// 				// Update the optimal threshold keeping the last one
// 				currentThreshold = optimalThreshold;
// 				optimalThreshold = static_cast<unsigned char>( round((objectsMeanValue + backgroundMeanValue) / 2.0) );
// 			}
// 			thresholds.push_back(optimalThreshold);
// 		}
// 	}
// 
// 	return thresholds.size();
// };

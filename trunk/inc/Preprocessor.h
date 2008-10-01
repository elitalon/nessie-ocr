#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H

///
/// @file
/// @brief Declaration of class Preprocessor
///

#include "Clip.h"

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

///
/// Preprocessor of the OCR process
/// 
/// This class encapsulates all the methods related to the stage of preprocessing. Its task
/// is to enhance the image quality by applying some techniques of image preprocessing theory.
/// By the way it has a several methods to obtain the elapsed time of every significant algorithm.
/// 
/// @remarks Note that every algorithm has been designed to work with a grayscale image. This means that, unless the method
/// convertToGrayscale is invoked before, an implicit conversion to the grayscale colorspace is applied.
/// 
/// @see Clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-30
///
class Preprocessor
{
	public:
		///
		/// Constructor
		///
		Preprocessor ();
		
		///
		/// Destructor
		///
		~Preprocessor ();

		///
		/// Returns the optimal threshold found in the last clip used
		///
		double optimalThreshold () const;
		
		///
		/// Sets the optimal threshold to use in algorithms
		///
		void optimalThreshold (double threshold);
		
		///
		/// Returns the background reference gray level in the last clip used
		///
		double backgroundReferenceGrayLevel () const;
		
		///
		/// Sets the background reference gray level to use in algorithms
		///
		void backgroundReferenceGrayLevel (double grayLevel);

		///
		/// Returns the elapsed time while applying the 'isolated noise removal' algorithm
		///
		double noiseRemovalTime () const;
		
		///
		/// Returns the elapsed time while converting the image to a grayscale colorspace
		///
		double grayscaleConversionTime () const;
		
		///
		/// Returns the elapsed time while founding the optimal threshold within the clip
		///
		double optimalThresholdComputingTime () const;
		
		///
		/// Returns the elapsed time while computing the background reference gray level within the clip
		///
		double backgroundReferenceGrayLevelFindingTime () const;

		///
		/// Converts the clip's colorspace to a grayscale
		///
		void convertToGrayscale (Clip& clip);
		
		///
		/// Computes the optimal threshold value within a clip
		///
		double computeOptimalThreshold (Clip& clip);
		
		///
		/// Computes the background reference gray level value within a clip
		///
		double findBackgroundReferenceGrayLevel (Clip& clip, unsigned int referenceGrayLevelNeighbours = 4);
		
		///
		/// Applies the 'isolated noise removal' algorithm
		///
		void removeIsolatedNoise (Clip& clip, unsigned int noisyNeighbours);
		
	private:
		///
		/// Optimal threshold value within the clip
		///
		double optimalThreshold_;
		
		///
		/// Background reference gray level
		///
		double backgroundReferenceGrayLevel_;
				
		///
		/// Elapsed time when applying the 'isolated noise removal' algorithm
		///
		double noiseRemovalTime_;
		
		///
		/// Elapsed time when converting the image to a grayscale colorspace
		///
		double grayscaleConversionTime_;
		
		///
		/// Elapsed time when converting the image to a grayscale colorspace
		///
		double optimalThresholdComputingTime_;
		
		///
		/// Elapsed time when computing the background gray level
		///
		double backgroundReferenceGrayLevelFindingTime_;
};

#endif  //_PREPROCESSOR_H

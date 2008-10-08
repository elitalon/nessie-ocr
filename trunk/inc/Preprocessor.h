///
/// @file
/// @brief Declaration of the class Preprocessor
///

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H


#include "Clip.h"


///
/// Preprocessor of the OCR process
/// 
/// This class encapsulates all the methods related to preprocessing stage. Its task
/// is to enhance the image quality by applying some techniques of image preprocessing theory and compute
/// a number of parameters such as the optimal thresolding value or the background reference gray level
/// 
/// @see Clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
///
class Preprocessor
{
	public:
		///
		/// Constructor
		///
		Preprocessor ();
		

		///
		/// Returns the optimal threshold found in the last clip used
		///
		/// @return Current optimal threshold computed from the last clip used
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline unsigned char optimalThreshold () const
		{
			return optimalThreshold_;
		};
		
		
		///
		/// Sets the optimal threshold to use in algorithms
		///
		/// @param threshold A value between 0 and 255 that stablishes the optimal threshold of a clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline void optimalThreshold (const unsigned char &threshold)
		{
			optimalThreshold_ = threshold;
		};
		
		
		///
		/// Returns the background reference gray level in the last clip used
		///
		/// @return Reference background gray level in the last clip used
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline unsigned char backgroundReferenceGrayLevel () const
		{
			return backgroundReferenceGrayLevel_;
		};
		
		
		///
		/// Sets the background reference gray level to use in algorithms
		///
		/// @param grayLevel Background reference gray level to use in algorithms
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline void backgroundReferenceGrayLevel (const unsigned char &grayLevel)
		{
			backgroundReferenceGrayLevel_ = grayLevel;
		};


		///
		/// Returns the elapsed time while applying the 'isolated noise removal' algorithm
		///
		/// @return Elapsed time when applying the 'isolated noise removal' algorithm
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline double noiseRemovalTime () const
		{
			return noiseRemovalTime_;
		};

				
		///
		/// Returns the elapsed time while founding the optimal threshold within the clip
		///
		/// @return Elapsed time while founding the optimal threshold within the clip
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline double optimalThresholdComputingTime () const
		{
			return optimalThresholdComputingTime_;
		};

		
		///
		/// Returns the elapsed time while computing the background reference gray level within the clip
		///
		/// @return Elapsed time while computing the background reference gray level
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline double backgroundReferenceGrayLevelFindingTime () const
		{
			return backgroundReferenceGrayLevelFindingTime_;
		};

		
		///
		/// Computes the optimal threshold value within a clip
		///
		unsigned char computeOptimalThreshold (const Clip &clip);

		
		///
		/// Computes the background reference gray level value within a clip
		///
		unsigned char findBackgroundReferenceGrayLevel (const Clip &clip, const unsigned int &referenceGrayLevelNeighbours = 4);

		
		///
		/// Applies the 'isolated noise removal' algorithm
		///
		void removeIsolatedNoise (Clip& clip, const unsigned int &isolationCoefficient = 1);
		
	private:
		///
		/// Optimal threshold value within the clip
		///
		unsigned char optimalThreshold_;
		
		///
		/// Background reference gray level
		///
		unsigned char backgroundReferenceGrayLevel_;
				
		///
		/// Elapsed time when applying the 'isolated noise removal' algorithm
		///
		double noiseRemovalTime_;
		
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

///
/// @file
/// @brief Declaration of the class Preprocessor
///

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H


class Clip;	// Forward declaration


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
/// @date 2008-10-11
///
class Preprocessor
{
	public:
		///
		/// Constructor
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
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
		unsigned char optimalThreshold () const;
				
		
		///
		/// Sets the optimal threshold to use in algorithms
		///
		/// @param threshold A value between 0 and 255 that stablishes the optimal threshold of a clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		void optimalThreshold (const unsigned char &threshold);
				
		
		///
		/// Returns the background reference gray level in the last clip used
		///
		/// @return Reference background gray level in the last clip used
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		unsigned char backgroundReferenceGrayLevel () const;
				

		///
		/// Returns the elapsed time while applying the 'isolated noise removal' algorithm
		///
		/// @return Elapsed time when applying the 'isolated noise removal' algorithm
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		double noiseRemovalTime () const;
		
				
		///
		/// Returns the elapsed time while founding the optimal threshold within the clip
		///
		/// @return Elapsed time while founding the optimal threshold within the clip
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		double optimalThresholdComputingTime () const;
		
		
		///
		/// Returns the elapsed time while computing the background reference gray level within the clip
		///
		/// @return Elapsed time while computing the background reference gray level
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		double backgroundReferenceGrayLevelFindingTime () const;
		
		
		///
		/// Computes the optimal threshold value within a clip
		/// 
		/// @pre You MUST call findBackgroundReferenceGrayLevel() method before calling this one, since it sets internal attributes.
		///
		/// @param clip The clip where applying the algorithm over
		/// 
		/// @return The optimal threshold of the clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		unsigned char computeOptimalThreshold (const Clip &clip);

		
		///
		/// Computes the background reference gray level value within a clip
		///
		/// @param	clip							The clip where applying the algorithm over
		/// @param	referenceGrayLevelNeighbours	Number of neighbours of the more frequent gray level to explore on each direction
		/// 
		/// @return The reference gray level of the background
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		unsigned char findBackgroundReferenceGrayLevel (const Clip &clip, const unsigned int &referenceGrayLevelNeighbours = 4);

		
		///
		/// Applies the 'isolated noise removal' algorithm
		///
		/// @pre You MUST call computeOptimalThreshold() and findBackgroundReferenceGrayLevel() methods before calling this one,
		/// since they set internal attributes.
		/// 
		/// @param[in,out]	clip					The clip where applying the algorithm over
		/// @param			isolationCoefficient	The maximum noisy neighbours for a pixel to consider it as isolated
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
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



//
// Implementation of inline functions
// 


///
/// @details
///
inline unsigned char Preprocessor::optimalThreshold () const
{
	return optimalThreshold_;
};


///
/// @details
///
inline void Preprocessor::optimalThreshold (const unsigned char &threshold)
{
	optimalThreshold_ = threshold;
};


///
/// @details
///
inline unsigned char Preprocessor::backgroundReferenceGrayLevel () const
{
	return backgroundReferenceGrayLevel_;
};


///
/// @details
///
inline double Preprocessor::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};

		
///
/// @details
///
inline double Preprocessor::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


///
/// @details
///
inline double Preprocessor::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


#endif  //_PREPROCESSOR_H

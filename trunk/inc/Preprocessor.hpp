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
		/// @date 2008-10-13
		///
		const unsigned char &optimalThreshold () const;
				
		
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
		/// @date 2008-10-13
		///
		const unsigned char &backgroundReferenceGrayLevel () const;
				

		///
		/// Returns the elapsed time while applying the 'isolated noise removal' algorithm
		///
		/// @return Elapsed time when applying the 'isolated noise removal' algorithm
		/// 
		/// @see removeIsolatedNoise()
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const double &noiseRemovalTime () const;
		
				
		///
		/// Returns the elapsed time while founding the optimal threshold within the clip
		///
		/// @return Elapsed time while founding the optimal threshold within the clip
		/// 
		/// @see computeOptimalThreshold()
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const double &optimalThresholdComputingTime () const;
		
		
		///
		/// Returns the elapsed time while computing the background reference gray level within the clip
		///
		/// @return Elapsed time while computing the background reference gray level
		/// 
		/// @see findBackgroundReferenceGrayLevel()
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const double &backgroundReferenceGrayLevelFindingTime () const;
		
		
		///
		/// Computes the optimal threshold value within a clip
		/// 
		/// @pre	You MUST call findBackgroundReferenceGrayLevel() method before calling this one, since it sets internal attributes.
		/// @post	The member #optimalThresholdComputingTime_ is modified.
		///
		/// @param clip			The clip where applying the algorithm over
		/// @param technique	An integer that tells the technique that must be used: 0 for Sonka's method or 1 for Otsu's method.
		/// 
		/// @see Clip, computeSonkaOptimalThreshold(), computeOtsuOptimalThreshold()
		/// 
		/// @return The optimal threshold of the clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned char &computeOptimalThreshold (const Clip &clip, const unsigned int &technique=0);

		
		///
		/// Computes the background reference gray level value within a clip.
		/// 
		/// @post	The member #backgroundReferenceGrayLevelFindingTime_ is modified.
		///
		/// @param	clip							The clip where applying the algorithm over
		/// @param	referenceGrayLevelNeighbours	Number of neighbours of the more frequent gray level to explore on each direction
		/// 
		/// @see Clip
		/// 
		/// @return The reference gray level of the background
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned char &findBackgroundReferenceGrayLevel (const Clip &clip, const unsigned int &referenceGrayLevelNeighbours = 4);

		
		///
		/// Applies the 'isolated noise removal' algorithm.
		///
		/// @pre	You MUST call computeOptimalThreshold() and findBackgroundReferenceGrayLevel() methods before calling this one,
		/// since they set internal attributes.
		/// @post	The clip may be modified if any noise is found.
		/// 
		/// @param[in,out]	clip					The clip where applying the algorithm over
		/// @param			isolationCoefficient	The maximum noisy neighbours for a pixel to consider it as isolated
		/// 
		/// @see Clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		void removeIsolatedNoise (Clip& clip, const unsigned int &isolationCoefficient = 0);
		
		
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
		
		
		///
		/// Implementation of optimal threshold computing following the Sonka's technique.
		/// 
		/// @param clip The clip where applying the algorithm over
		/// 
		/// @see Clip
		/// 
		/// @post The attribute #optimalThreshold_ is initialized to the threshold found
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-14
		///
		void computeSonkaOptimalThreshold (const Clip &clip);
		
		
		///
		/// Implementation of optimal threshold computing following the Otsu's technique.
		///
		/// @param clip The clip where applying the algorithm over
		/// 
		/// @see Clip
		/// 
		/// @post The attribute #optimalThreshold_ is initialized to the threshold found
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-14
		///
		void computeOtsuOptimalThreshold (const Clip &clip);
		
};



//
// Implementation of inline functions
// 


///
/// @details
///
inline const unsigned char &Preprocessor::optimalThreshold () const
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
inline const unsigned char &Preprocessor::backgroundReferenceGrayLevel () const
{
	return backgroundReferenceGrayLevel_;
};


///
/// @details
///
inline const double &Preprocessor::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};

		
///
/// @details
///
inline const double &Preprocessor::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


///
/// @details
///
inline const double &Preprocessor::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


#endif  //_PREPROCESSOR_H

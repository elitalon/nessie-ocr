///
/// @file
/// @brief Declaration of Preprocessor class
///

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H


class Clip;	// Forward declaration



///
/// Preprocessor of the OCR process.
/// 
/// This class encapsulates all the algorithms related to preprocessing stage of the OCR process. Its task
/// is to enhance the image quality by applying some techniques of image processing theory and compute
/// a number of parameters such as the optimal thresolding value or the background reference gray level.
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
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-08
	///
	Preprocessor ();


	///
	/// Returns the optimal threshold found in the last clip used.
	///
	/// @return Optimal threshold computed from the last clip used.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned char& optimalThreshold () const;


	///
	/// Sets the optimal threshold to use in algorithms.
	///
	/// @param threshold Value between 0 and 255 that stablishes the optimal threshold of a clip.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-08
	///
	void optimalThreshold (const unsigned char& threshold);


	///
	/// Returns the background reference gray level in the last clip used.
	///
	/// @return Reference background gray level in the last clip used
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned char& backgroundReferenceGrayLevel () const;


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
	const double& noiseRemovalTime () const;


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
	const double& optimalThresholdComputingTime () const;


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
	const double& backgroundReferenceGrayLevelFindingTime () const;


	///
	/// Computes the optimal threshold value in a clip following the Sonka's technique.
	/// 
	/// @pre	You MUST call findBackgroundReferenceGrayLevel() method before calling this one, since it sets internal attributes.
	/// 
	/// @post	The #optimalThresholdComputingTime_ member is modified.
	/// @post	The #optimalThreshold_ member is initialized to the threshold found
	///
	/// @param clip			The clip where applying the algorithm over
	/// 
	/// @see Clip
	/// 
	/// @return The optimal threshold of the clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	const unsigned char& computeOptimalThreshold (const Clip& clip);


	///
	/// Computes the background reference gray level value within a clip.
	/// 
	/// @post	The #backgroundReferenceGrayLevelFindingTime_ member is modified.
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
	const unsigned char& findBackgroundReferenceGrayLevel (const Clip& clip, const unsigned int& referenceGrayLevelNeighbours = 2);


	///
	/// Applies the 'isolated noise removal' algorithm.
	///
	/// @pre	You MUST call computeOptimalThreshold() and findBackgroundReferenceGrayLevel() methods before calling this one,
	/// since they set internal attributes.
	/// 
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
	void removeIsolatedNoise (Clip& clip, const unsigned int& isolationCoefficient = 0);


private:
	
	unsigned char	optimalThreshold_;							///< Optimal threshold value within the clip

	unsigned char	backgroundReferenceGrayLevel_;				///< Background reference gray level
	
	double			noiseRemovalTime_;							///< Elapsed time when applying the 'isolated noise removal' algorithm
	
	double			optimalThresholdComputingTime_;				///< Elapsed time when converting the image to a grayscale colorspace
	
	double			backgroundReferenceGrayLevelFindingTime_;	///< Elapsed time when computing the background gray level

};




inline const unsigned char& Preprocessor::optimalThreshold () const
{
	return optimalThreshold_;
};


inline void Preprocessor::optimalThreshold (const unsigned char& threshold)
{
	optimalThreshold_ = threshold;
};


inline const unsigned char& Preprocessor::backgroundReferenceGrayLevel () const
{
	return backgroundReferenceGrayLevel_;
};


inline const double& Preprocessor::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};


inline const double& Preprocessor::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


inline const double& Preprocessor::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


#endif  //_PREPROCESSOR_H

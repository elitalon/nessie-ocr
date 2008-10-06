///
/// @file
/// @brief Declaration of class Preprocessor
///

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H


// Forward declaration
class Clip;


///
/// Preprocessor of the OCR process
/// 
/// This class encapsulates all the methods related to preprocessing stage. Its task
/// is to enhance the image quality by applying some techniques of image preprocessing theory and compute
/// a number of parameters such as the optimal thresolding value or the background reference gray level
/// 
/// @remarks Every algorithm has been designed to work with a grayscale image. You MUST ensure that the Clip objects
/// come in such colorspace.
/// 
/// @see Clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
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
		void optimalThreshold (const double &threshold);
		
		///
		/// Returns the background reference gray level in the last clip used
		///
		double backgroundReferenceGrayLevel () const;
		
		///
		/// Sets the background reference gray level to use in algorithms
		///
		void backgroundReferenceGrayLevel (const double &grayLevel);

		///
		/// Returns the elapsed time while applying the 'isolated noise removal' algorithm
		///
		double noiseRemovalTime () const;
				
		///
		/// Returns the elapsed time while founding the optimal threshold within the clip
		///
		double optimalThresholdComputingTime () const;
		
		///
		/// Returns the elapsed time while computing the background reference gray level within the clip
		///
		double backgroundReferenceGrayLevelFindingTime () const;
		
		///
		/// Computes the optimal threshold value within a clip
		///
		double computeOptimalThreshold (const Clip &clip);
		
		///
		/// Computes the background reference gray level value within a clip
		///
		double findBackgroundReferenceGrayLevel (const Clip &clip, const unsigned int &referenceGrayLevelNeighbours = 4);
		
		///
		/// Applies the 'isolated noise removal' algorithm
		///
		void removeIsolatedNoise (Clip& clip, const unsigned int &isolationCoefficient = 1);
		
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
		double optimalThresholdComputingTime_;
		
		///
		/// Elapsed time when computing the background gray level
		///
		double backgroundReferenceGrayLevelFindingTime_;
};

#endif  //_PREPROCESSOR_H

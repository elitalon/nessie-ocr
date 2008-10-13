///
/// @file
/// @brief Declaration of the class Statistics
///

#if !defined(_STATISTICS_H)
#define _STATISTICS_H



///
/// Statistics about the text recognition process.
/// 
/// This class stores a number of statistical data regarding the elapsed time during the text recognition process,
/// accumulated internally mostly in algorithms.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
/// 
class Statistics
{
	public:
		///
		/// Constructor
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-04
		///
		Statistics ();
		
		
		///
		/// Returns the elapsed time in the reference gray level of the background finding algorithm
		///
		/// @return Elapsed time in the reference gray level of the background finding algorithm
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const double &backgroundReferenceGrayLevelFindingTime () const;
		
		
		///
		/// Returns the elapsed time in the optimal threshold computing algorithm
		///
		/// @return Elapsed time in the optimal threshold computing algorithm
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const double &optimalThresholdComputingTime () const;
		
		
		///
		/// Returns the elapsed time in the noise removal algorithm
		///
		/// @return Elapsed time in the noise removal algorithm
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const double &noiseRemovalTime () const;		
		
		
		///
		/// Returns the total elapsed time within the preprocessing stage
		///
		/// @return Total elapsed time within the preprocessing stage
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const double &preprocessingTime () const;
		
		
	private:
		///
		/// Declares the class Recognizer as friend
		///
		friend class Recognizer;
		
		///
		/// Elapsed time in the reference gray level of the background finding algorithm
		///
		double backgroundReferenceGrayLevelFindingTime_;
		
		///
		/// Elapsed time in the optimal threshold computing algorithm
		///
		double optimalThresholdComputingTime_;
		
		///
		/// Elapsed time in the noise removal algorithm
		///
		double noiseRemovalTime_;
				
		///
		/// Total elapsed time within the preprocessing stage
		/// 
		double preprocessingTime_;
		
		
		///
		/// Sets the elapsed time in the reference gray level of the background finding algorithm.
		/// 
		/// @param	time	Elapsed time in the reference gray level of the background finding algorithm
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-06
		///
		void backgroundReferenceGrayLevelFindingTime (const double &time);
		
		
		///
		/// Sets the elapsed time in the optimal threshold computing algorithm
		///
		/// @param	time	Elapsed time in the optimal threshold computing algorithm
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-06
		///
		void optimalThresholdComputingTime (const double &time);
		
		
		///
		/// Sets the elapsed time in the noise removal algorithm
		///
		/// @param	time	Elapsed time in the noise removal algorithm
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-06
		///
		void noiseRemovalTime (const double &time);
};



//
// Implementation of inline functions
//


///
/// @details
///
inline const double &Statistics::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


///
/// @details
///
inline const double &Statistics::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


///
/// @details
///
inline const double &Statistics::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};


///
/// @details
///
inline const double &Statistics::preprocessingTime () const
{
	return preprocessingTime_;
};


#endif  //_STATISTICS_H

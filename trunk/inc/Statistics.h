///
/// @file
/// @brief Declaration of class Statistics
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
/// @date 2008-10-06
/// 
class Statistics
{
	public:
		///
		/// Returns the elapsed time in the reference gray level of the background finding algorithm
		///
		double backgroundReferenceGrayLevelFindingTime () const;
		
		///
		/// Returns the elapsed time in the optimal threshold computing algorithm
		///
		double optimalThresholdComputingTime () const;
		
		///
		/// Returns the elapsed time in the noise removal algorithm
		///
		double noiseRemovalTime () const;
		
		///
		/// Returns the total elapsed time within the preprocessing stage
		///
		double preprocessingTime () const;
		
	private:
		///
		/// Constructor
		/// 
		Statistics ();
		
		///
		/// Destructor
		/// 
		~Statistics ();
		
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
		/// Sets the elapsed time in the reference gray level of the background finding algorithm
		///
		void backgroundReferenceGrayLevelFindingTime (const double &time);
		
		///
		/// Sets the elapsed time in the optimal threshold computing algorithm
		///
		void optimalThresholdComputingTime (const double &time);
		
		///
		/// Sets the elapsed time in the noise removal algorithm
		///
		void noiseRemovalTime (const double &time);
};

#endif  //_STATISTICS_H

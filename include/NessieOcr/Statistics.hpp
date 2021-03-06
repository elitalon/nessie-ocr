/// @file
/// @brief Declaration of Statistics class

#if !defined(_STATISTICS_H)
#define _STATISTICS_H


/// @brief		Statistics gathered during NessieOcr execution stages.
///
/// @details	This abstract base class provides a common interface for every stage of NessieOcr, allowing its redefinition so that derived classes
///	can be customized according to the stage they belong. The statitical data is gathered mostly in internal algorithms, and provides time results
///	among other parameters.
/// 
/// @see		PreprocessorStatistics, FeatureExtractorStatistics, ClassifierStatistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
class Statistics
{
	public:

		/// @brief	Constructor.
		explicit Statistics ();

		/// @brief	Destructor.
		virtual ~Statistics ();

		///	@brief	Get the total elapsed time.
		///
		///	@return Elapsed time in seconds.
		virtual const double& totalTime () const;
		
		/// @brief	Print the statistics to the standard output.
		virtual void print () const = 0;

	protected:

		double totalTime_;	///< Total elapsed time within a stage.

		/// @brief	Update the total elapsed time within a stage.
		/// 
		/// @post	#totalTime_ is set by summing all the individual timers.
		virtual void updateTotalTime () = 0;
};

inline const double& Statistics::totalTime () const
{
	return totalTime_;
}

#endif


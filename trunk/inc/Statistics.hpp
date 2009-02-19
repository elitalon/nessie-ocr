/// @file
/// @brief Declaration of Statistics class

#if !defined(_STATISTICS_H)
#define _STATISTICS_H


/// @brief		Statistical data gathered during the text recognition process.
///
/// @details	This abstract base class provides a common interface for every stage of the recognition process, allowing its redefinition
/// so that derived classes can be customized according to the stage they belong. The statitical data is gathered mostly in internal algorithms,
/// and provides time results among other parameters.
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

		/// @brief	Prints the statistical data gathered during the text recognition process.
		virtual void print () const = 0;

	protected:

		double totalTime_;	///< Total elapsed time during stage execution.

		/// @brief	Updates the stage total elapsed time.
		/// 
		/// @post	#totalTime_ is set by summing all the individual timers.
		virtual void updateTotalTime () = 0;
};

#endif


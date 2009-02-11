/// @file
/// @brief Declaration of FeatureExtractorStatistics class

#if !defined(_FEATURE_EXTRACTOR_STATISTICS_H)
#define _FEATURE_EXTRACTOR_STATISTICS_H

#include "Statistics.hpp"


/// @brief	Statistical data gathered during the feature extraction stage of the text recognition process.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class FeatureExtractorStatistics : public Statistics
{
	public:

		/// @brief	Constructor.
		explicit FeatureExtractorStatistics ();

		///	@brief	Copy constructor.
		FeatureExtractorStatistics (const FeatureExtractorStatistics& statistics);

		/// @brief	Destructor.
		virtual ~FeatureExtractorStatistics ();

		/// @brief Assignment operator.
		FeatureExtractorStatistics& operator= (const FeatureExtractorStatistics& statistics);

		/// @brief	Stores the elapsed time while building an array of patterns from a list of regions.
		///
		///	@post	The internal member is set to <em>elapsedTime</em>.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void patternsBuildingTime (const double& elapsedTime);

		///	@brief	Stores the elapsed time while computing the image moments of patterns.
		///
		///	@post	The internal member is set to <em>elapsedTime</em>.
		///
		///	@param	elapsedTime	Elapsed time in seconds.
		void momentsComputingTime (const double& elapsedTime);

		/// @brief	Prints the statistical data gathered.
		void print () const;

	private:

		double*	patternsBuildingTime_;	///< Elapsed time while building an array of patterns.

		double*	momentsComputingTime_;	///< Elapsed time while computing the image moments of patterns.

		/// @brief	Updates the total elapsed time.
		///
		/// @post	#totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void FeatureExtractorStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( patternsBuildingTime_ != 0 )
		totalTime_ += *patternsBuildingTime_;

	if ( momentsComputingTime_ != 0 )
		totalTime_ += *momentsComputingTime_;
};


inline void FeatureExtractorStatistics::patternsBuildingTime (const double& elapsedTime)
{
	if ( patternsBuildingTime_ == 0 )
		patternsBuildingTime_ = new double;

	*patternsBuildingTime_ = elapsedTime;
	updateTotalTime();
};


inline void FeatureExtractorStatistics::momentsComputingTime (const double& elapsedTime)
{
	if ( momentsComputingTime_ == 0 )
		momentsComputingTime_ = new double;

	*momentsComputingTime_ = elapsedTime;
	updateTotalTime();
};

#endif	//_STATISTICS_H


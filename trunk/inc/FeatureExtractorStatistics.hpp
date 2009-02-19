/// @file
/// @brief Declaration of FeatureExtractorStatistics class

#if !defined(_FEATURE_EXTRACTOR_STATISTICS_H)
#define _FEATURE_EXTRACTOR_STATISTICS_H

#include "Statistics.hpp"
#include <memory>


/// @brief	Statistical data gathered during the feature extraction stage of the text recognition process.
///
///	@see	Statistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
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

		std::auto_ptr<double>	patternsBuildingTime_;	///< Elapsed time while building an array of patterns.

		std::auto_ptr<double>	momentsComputingTime_;	///< Elapsed time while computing the image moments of patterns.

		/// @brief	Updates the total elapsed time.
		///
		/// @post	#totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void FeatureExtractorStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( patternsBuildingTime_.get() != 0 )
		totalTime_ += *patternsBuildingTime_.get();

	if ( momentsComputingTime_.get() != 0 )
		totalTime_ += *momentsComputingTime_.get();
};


inline void FeatureExtractorStatistics::patternsBuildingTime (const double& elapsedTime)
{
	patternsBuildingTime_.reset(new double(elapsedTime));
	updateTotalTime();
};


inline void FeatureExtractorStatistics::momentsComputingTime (const double& elapsedTime)
{
	momentsComputingTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

#endif


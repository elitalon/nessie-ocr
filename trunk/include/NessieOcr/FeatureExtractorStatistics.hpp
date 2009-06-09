/// @file
/// @brief Declaration of FeatureExtractorStatistics class

#if !defined(_FEATURE_EXTRACTOR_STATISTICS_H)
#define _FEATURE_EXTRACTOR_STATISTICS_H

#include "Statistics.hpp"
#include <memory>



///	@brief		Feature extraction stage statistics of NessieOcr.
///
///	@details	This class stores all the statistical data gathered during execution of methods of the feature extraction stage. Data can be write or read,
///	although a client program should be only interested in reading values. The statistical data	is automatically set whenever a method from a
///	FeatureExtractor object is called, but only the fields that method uses.
///
///	@see		Statistics, FeatureExtractor
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

		/// @brief	Assignment operator.
		FeatureExtractorStatistics& operator= (const FeatureExtractorStatistics& statistics);

		///	@brief	Set the elapsed time while computing the image moments of patterns.
		///
		///	@param	elapsedTime	Elapsed time in seconds.
		void momentsComputingTime (const double& elapsedTime);

		///	@brief	Get the elapsed time while computing the image moments of patterns.
		///
		///	@return	Elapsed time in seconds.
		double momentsComputingTime () const;

		/// @brief	Print the statistics gathered.
		void print () const;

	private:

		std::auto_ptr<double>	momentsComputingTime_;	///< Elapsed time while computing the image moments of patterns.

		/// @brief	Update the total elapsed time.
		///
		/// @post	#totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void FeatureExtractorStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( momentsComputingTime_.get() != 0 )
		totalTime_ += *momentsComputingTime_;
}

inline void FeatureExtractorStatistics::momentsComputingTime (const double& elapsedTime)
{
	momentsComputingTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double FeatureExtractorStatistics::momentsComputingTime () const
{
	return *momentsComputingTime_;
}

#endif


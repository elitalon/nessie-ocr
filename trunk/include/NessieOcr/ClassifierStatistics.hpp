/// @file
/// @brief Declaration of ClassifierStatistics class

#if !defined(_CLASSIFIER_STATISTICS_H)
#define _CLASSIFIER_STATISTICS_H

#include "Statistics.hpp"
#include <memory>


/// @brief	Statistical of classification stage.
///
///	@see	Statistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
class ClassifierStatistics : public Statistics
{
	public:

		/// @brief	Constructor.
		explicit ClassifierStatistics ();

		///	@brief	Copy constructor.
		ClassifierStatistics (const ClassifierStatistics& statistics);

		/// @brief	Destructor.
		virtual ~ClassifierStatistics ();

		///	@brief	Assignment operator.
		ClassifierStatistics& operator= (const ClassifierStatistics& statistics);

		///	@brief	Set the elapsed time while classifying the feature vectors.
		///
		///	@param	elapsedTime	Elapsed time in seconds.
		void classificationTime (const double& elapsedTime);

		///	@brief	Set the hit rate within training stage.
		///
		///	@param	rate	Hit rate in %.
		void hitRate (const double& rate);

		///	@brief	Set the miss rate within training stage.
		///
		///	@param	rate	Miss rate in %.
		void missRate (const double& rate);

		/// @brief	Print the statistics gathered.
		void print () const;

	private:

		std::auto_ptr<double>		classificationTime_;	///< Elapsed time while classifing the feature vectors.

		std::auto_ptr<double>		hitRate_;				///< Hit rate during training stage.

		std::auto_ptr<double>		missRate_;				///< Miss rate during training stage.

		/// @brief	Update the total elapsed time.
		///
		/// @post	#totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void ClassifierStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( classificationTime_.get() != 0 )
		totalTime_ += *classificationTime_.get();
}

inline void ClassifierStatistics::classificationTime (const double& elapsedTime)
{
	classificationTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline void ClassifierStatistics::hitRate (const double& rate)
{
	hitRate_.reset(new double(rate));
}

inline void ClassifierStatistics::missRate (const double& rate)
{
	missRate_.reset(new double(rate));
}

#endif


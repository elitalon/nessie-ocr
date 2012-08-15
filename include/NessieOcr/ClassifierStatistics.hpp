/// @file
/// @brief Declaration of ClassifierStatistics class

#if !defined(_CLASSIFIER_STATISTICS_H)
#define _CLASSIFIER_STATISTICS_H

#include "Statistics.hpp"
#include <memory>


///	@brief		Classification stage statistics of NessieOcr.
///
///	@details	This class stores all the statistical data gathered during execution of methods of the classification stage. Data can be write or read,
///	although a client program should be only interested in reading values. The statistical data	is automatically set whenever a method from a
///	Classifier or ClassificationAlgorithm object is called, but only the fields that method uses.
///
///	@see		Statistics, Classifier, ClassificationAlgorithm
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

		///	@brief	Get the elapsed time while classifying the feature vectors.
		///
		///	@return Elapsed time in seconds.
		double classificationTime ();

		///	@brief	Set the hit rate within training stage.
		///
		///	@param	rate	Hit rate in %.
		void hitRate (const double& rate);

		///	@brief	Get the hit rate within training stage.
		///
		///	@return Hit rate in %.
		double hitRate ();

		///	@brief	Set the miss rate within training stage.
		///
		///	@param	rate	Miss rate in %.
		void missRate (const double& rate);

		///	@brief	Get the miss rate within training stage.
		///
		///	@return Miss rate in %.
		double missRate ();

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
		totalTime_ += *classificationTime_;
}

inline void ClassifierStatistics::classificationTime (const double& elapsedTime)
{
	classificationTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double ClassifierStatistics::classificationTime ()
{
	return *classificationTime_;
}

inline void ClassifierStatistics::hitRate (const double& rate)
{
	hitRate_.reset(new double(rate));
}

inline double ClassifierStatistics::hitRate ()
{
	return *hitRate_;
}

inline void ClassifierStatistics::missRate (const double& rate)
{
	missRate_.reset(new double(rate));
}

inline double ClassifierStatistics::missRate ()
{
	return *missRate_;
}

#endif


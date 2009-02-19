/// @file
/// @brief Declaration of ClassifierStatistics class

#if !defined(_CLASSIFIER_STATISTICS_H)
#define _CLASSIFIER_STATISTICS_H

#include "Statistics.hpp"
#include <memory>


/// @brief	Statistical data gathered during the classification stage of the text recognition process.
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

		///	@brief	Stores the number of characters found during the classification process.
		///
		///	@post	The internal member is set to <em>n</em>.
		///
		///	@param	n	Number of characters.
		void charactersFound (const unsigned int& n);

		///	@brief	Stores the elapsed time while classifying the feature vectors.
		///
		///	@post	The internal member is set to <em>elapsedTime</em>.
		///
		///	@param	elapsedTime	Elapsed time in seconds.
		void classificationTime (const double& elapsedTime);

		/// @brief	Prints the statistical data gathered.
		void print () const;

	private:

		std::auto_ptr<unsigned int>	charactersFound_;		///< Numbers of characters found during the classification process.

		std::auto_ptr<double>		classificationTime_;	///< Elapsed time while classifing the feature vectors.

		/// @brief	Updates the total elapsed time.
		///
		/// @post	#totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void ClassifierStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( classificationTime_.get() != 0 )
		totalTime_ += *classificationTime_.get();
};


inline void ClassifierStatistics::charactersFound (const unsigned int& n)
{
	charactersFound_.reset(new unsigned int(n));
};


inline void ClassifierStatistics::classificationTime (const double& elapsedTime)
{
	classificationTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

#endif


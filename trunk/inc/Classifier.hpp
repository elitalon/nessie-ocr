/// @file
/// @brief Declaration of Classifier class

#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H


#include "FeatureVector.hpp"
#include "ClassifierStatistics.hpp"
#include "ClassificationParadigm.hpp"
#include <string>
#include <vector>



///	@brief		Classifier of the OCR process.
/// 
///	@details	This class encapsulates all the algorithms related to the classification stage of the OCR process. Its task is to match every feature
///	vector passed in the constructor to its associated character. In the very end of the process, a string of characters is available through the
/// Classifier::characters() method.
/// 
/// @see		FeatureVector, ClassifierStatistics
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-09
///
class Classifier
{
	public:

		///	@brief	Constructor.
		///
		///	@param	featureVectors	An array of feature vectors to classify.
		explicit Classifier (const std::vector<FeatureVector>& featureVectors);

		///	@brief	Returns the characters associated with the feature vectors passed in constructor.
		/// 
		/// @return	A std::string object with the characters found.
		const std::string& characters () const;

		///	@brief	Returns the statistics about the classification stage.
		/// 
		/// @return A ClassifierStatistics object with all the data gathered.
		const ClassifierStatistics& statistics () const;

		///	@brief	Executes the classification process over the feature vectors passed in constructor.
		///
		///	@param	paradigm	Classification paradigm to be used.
		void classify(const ClassificationParadigm& paradigm);

	private:

		ClassifierStatistics		statistics_;		///< Statistics about the classification of feature vectors.

		std::vector<FeatureVector>	featureVectors_;	///< Feature vectors to classify.

		std::string					characters_;		///< Characters found after the classification process.
};


inline const std::string& Classifier::characters () const
{
	return characters_;
};


inline const ClassifierStatistics& Classifier::statistics () const
{
	return statistics_;
};

#endif


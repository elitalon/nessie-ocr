/// @file
/// @brief Declaration of Classifier class

#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H

class FeatureVector;
class Text;
#include "ClassifierStatistics.hpp"
#include "ClassificationAlgorithm.hpp"
#include <string>
#include <vector>
#include <memory>


///	@brief		Classifier of the OCR process.
/// 
///	@details	This class represents the classification stage of the OCR process, providing an interface to encapsulate different classification paradigms.
///	Its task is to match every feature vector passed to its associated character. In the end of the process, a string of characters is available through the
///	Classifier::characters() method.
/// 
/// @see		ClassificationAlgorithm, ClassifierStatistics, FeatureVector, Dataset
///
///	@todo		Implement new paradigms of classification (neural networks, support vector machines,...).
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-09
class Classifier
{
	public:

		///	@brief	Constructor.
		explicit Classifier ();

		///	@brief	Destructor.
		virtual ~Classifier ();

		///	@brief	Get the characters associated with the feature vectors passed in constructor.
		/// 
		/// @return	An array of std::string objects with the characters found, one character per feature vector passed in Classifier::classify() method.
		virtual const std::vector<std::string>& characters () const;

		///	@brief	Get the statistics regarding the classification stage.
		/// 
		/// @return A ClassifierStatistics object.
		virtual const ClassifierStatistics& statistics () const;

		///	@brief	Classify each feature vector passed into its most probably class (character).
		///
		/// @param	featureVectors	An array of feature vectors to classify.
		///
		///	@return	An array of std::string objects with the characters found, one character per vector element.
		///
		///	@post	The recognized characters become also available through the Classifier::characters() method.
		virtual const std::vector<std::string>& performClassification (const std::vector<FeatureVector>& featureVectors) = 0;
		
		/// @brief	Train the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param	characters		An array of std::string objects with sample characters to train.
		/// @param	referenceText	A text to compare with the classification results character by character.
		virtual void performTraining (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText) = 0;

	protected:

		ClassifierStatistics					statistics_;				///< Statistics about the classification of feature vectors.

		std::vector<std::string>				characters_;				///< Characters found after the classification process.

		std::auto_ptr<ClassificationAlgorithm>	classificationAlgorithm_;	///< Concrete classification algorithm to be used.
};


inline const std::vector<std::string>& Classifier::characters () const
{
	return characters_;
};

inline const ClassifierStatistics& Classifier::statistics () const
{
	return statistics_;
};

#endif


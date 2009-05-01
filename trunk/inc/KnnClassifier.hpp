/// @file
/// @brief Declaration of KnnClassifier class

#if !defined(_KNN_CLASSIFIER_H)
#define _KNN_CLASSIFIER_H

class FeatureVector;
class ClassificationAlgorithm;
class Text;
#include "Classifier.hpp"
#include <string>
#include <vector>
#include <memory>


///	@brief		Classifier of the OCR process based on the KNN paradigm.
/// 
///	@details	This class implements the OCR classification stage using the KNN paradigm to match every feature vector to its associated character.
/// 
/// @see		Classifier, FeatureVector
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-04-29
class KnnClassifier : public Classifier
{
	public:

		///	@brief	Constructor.
		///
		///	@post	Input ClassificationAlgorithm object is released and managed internally.
		explicit KnnClassifier (std::auto_ptr<ClassificationAlgorithm> algorithm);

		///	@brief	Destructor.
		virtual ~KnnClassifier ();

		///	@brief	Classify each feature vector passed into its most probably class (character).
		///
		/// @param	featureVectors	An array of feature vectors to classify.
		///
		///	@return	An array of std::string objects with the characters found, one character per vector element.
		///
		///	@post	The recognized characters become also available through the Classifier::characters() method.
		const std::vector<std::string>& performClassification (const std::vector<FeatureVector>& featureVectors);

		/// @brief	Train the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param	characters		An array of std::string objects with sample characters to train.
		/// @param	referenceText	A text to compare with the classification results character by character.
		void performTraining (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText);
};

#endif


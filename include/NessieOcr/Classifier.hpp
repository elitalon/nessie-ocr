/// @file
/// @brief Declaration of Classifier class

#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H

class FeatureVector;
class Text;
class ClassificationAlgorithm;
#include "ClassifierStatistics.hpp"
#include <string>
#include <vector>


///	@brief		Classifier of the OCR process.
///
///	@details	This class represents the classification stage of NessieOcr, providing an interface to encapsulate different classification paradigms.
///	When performing a classification, its task is to match every feature vector passed to the most probably character. When performing a training, its task is
/// to compare the classified characters with a reference text, fixing the wrong decisions.
///
/// @see		ClassificationAlgorithm, ClassifierStatistics, FeatureVector, Text
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

		///	@brief	Get the statistics regarding the classification stage.
		///
		/// @return A ClassifierStatistics object.
		virtual const ClassifierStatistics& statistics () const;

		///	@brief	Classify each feature vector passed into its most probably class (character).
		///
		/// @param	featureVectors	An array of feature vectors to classify.
		///
		///	@return	An array of std::string objects with the characters found, one character per vector element.
		virtual std::vector<std::string> performClassification (const std::vector<FeatureVector>& featureVectors) = 0;

		/// @brief	Train the classifier, comparing each classification decision with a reference text.
		///
		///	@param	featureVectors	An array of feature vectors that matches the array of characters previously classified.
		/// @param	characters		An array of std::string objects with sample characters.
		/// @param	referenceText	A text to compare with the classification results character by character.
		virtual void performTraining (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText) = 0;
		
		/// @brief	Train the classifier, comparing the classification decision for a single pattern with an ASCII code.
		///
		///	@param	featureVector	A feature vector that matches a character previously classified.
		/// @param	character		A std::string object with sample character.
		/// @param	asciiCode		An ASCII code to compare with the classification result.
		virtual void performTraining (const FeatureVector& featureVector, const std::string& character, const unsigned int& asciiCode) = 0;

	protected:

		ClassifierStatistics		statistics_;				///< Statistics about the classification of feature vectors.

		ClassificationAlgorithm*	classificationAlgorithm_;	///< Concrete classification algorithm to be used.
};


inline const ClassifierStatistics& Classifier::statistics () const
{
	return statistics_;
}

#endif


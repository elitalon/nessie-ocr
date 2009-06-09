/// @file
/// @brief Declaration of ClassificationAlgorithm class

#if !defined(_CLASSIFICATION_ALGORITHM_H)
#define _CLASSIFICATION_ALGORITHM_H


class FeatureVector;
class Text;
#include <vector>
#include <string>

///	@brief		Algorithm used by NessieOcr in the classification stage.
///
///	@details	This class declares an abstract class that allows the definition of multiple classification algorithms, so that
///	a set of feature vectors can be classified using several paradigms. A ClassificationAlgorithm object is declared internally
///	within the Classifier class, since it is not allowed to modify the algorithm of a Classifier object.
///
///	@see	Classifier, FeatureVector, Text
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-04-29 
class ClassificationAlgorithm
{
	public:

		///	@brief	Constructor
		explicit ClassificationAlgorithm ();

		///	@brief	Destructor
		virtual ~ClassificationAlgorithm ();

		/// @brief	Classify a set of feature vectors into their most probably classes.
		/// 
		/// @param	featureVectors	An array of feature vectors.
		/// 
		/// @return An array of characters, one character per feature vector.
		virtual std::vector<std::string> classify (const std::vector<FeatureVector>& featureVectors) const = 0;
		
		/// @brief	Train the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param	featureVectors	An array of feature vectors that matches the classified characters.
		/// @param	characters		An array of std::string objects with classified characters to train.
		/// @param	referenceText	A text to compare with the classification results character by character.
		///
		///	@return	The hit rate achieved after training (e.g. 0,9 for 90%).
		virtual double train (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText) = 0;
};

#endif


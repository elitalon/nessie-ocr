/// @file
/// @brief Declaration of ClassificationAlgorithm class

#if !defined(_CLASSIFICATION_ALGORITHM_H)
#define _CLASSIFICATION_ALGORITHM_H


class FeatureVector;
class Text;
#include <vector>
#include <string>

///	@brief		Algorithm used by the OCR process in the classification stage.
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
		/// @return An array of characters, one character per feature vector passes.
		virtual std::vector<std::string> classify (const std::vector<FeatureVector>& featureVectors) = 0;
		
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


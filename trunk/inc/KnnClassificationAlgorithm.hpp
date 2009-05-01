/// @file
/// @brief Declaration of KnnClassificationAlgorithm class

#if !defined(_KNN_CLASSIFICATION_PARADIGM_H)
#define _KNN_CLASSIFICATION_PARADIGM_H


class FeatureVector;
class Dataset;
class Text;
#include "ClassificationAlgorithm.hpp"
#include <vector>
#include <string>
#include <memory>

///	@brief		Algorithm used by the OCR process in the classification stage based on the KNN paradigm.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-04-29 
class KnnClassificationAlgorithm : public ClassificationAlgorithm
{
	public:

		///	@brief	Constructor
		///	@post	The input Dataset object is released and becomes managed internally.
		explicit KnnClassificationAlgorithm (const unsigned int& kNeighbours, std::auto_ptr<Dataset>& dataset);

		///	@brief	Destructor
		virtual ~KnnClassificationAlgorithm ();

		/// @brief	Classify a set of feature vectors into their most probably classes.
		/// 
		/// @param	featureVectors	An array of feature vectors.
		/// 
		/// @return An array of characters, one character per feature vector passes.
		std::vector<std::string> classify (const std::vector<FeatureVector>& featureVectors);

		/// @brief	Train the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param	characters		An array of std::string objects with sample characters to train.
		/// @param	referenceText	A text to compare with the classification results character by character.
		///
		///	@return	The hit rate achieved after training (e.g. 0,9 for 90%).
		double train (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText);

	private:

		unsigned int			kNeighbours_;	///< Maximum number of negihbouring samples.

		std::auto_ptr<Dataset>	dataset_;		///< Set of previously trained samples.
};

#endif


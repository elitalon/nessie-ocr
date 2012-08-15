/// @file
/// @brief Declaration of KnnClassificationAlgorithm class

#if !defined(_KNN_CLASSIFICATION_PARADIGM_H)
#define _KNN_CLASSIFICATION_PARADIGM_H

class DatasetEngine;
class Dataset;
class FeatureVector;
class Text;
#include "ClassificationAlgorithm.hpp"
#include <vector>
#include <string>


///	@brief		Classification algorithm based on the KNN paradigm.
///
///	@details	This class implements the ClassificationAlgorithm class using the KNN paradigm for classifying and/or training purposes. The number of
///	neighbours to take into account is set in the class constructor, as well as the necessary dataset.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date	2009-04-29 
class KnnClassificationAlgorithm : public ClassificationAlgorithm
{
	public:

		///	@brief		Constructor
		///
		///	@param		kNeighbours	Number of neighbours to take when classifying.
		/// @param		engine		A dataset engine information to load a dataset.
		///
		///	@pre		The dataset must not be empty or set to a null value.
		///
		///	@warning	A client program or function must be aware since this class only uses the dataset and does not manage it.
		explicit KnnClassificationAlgorithm (const unsigned int& kNeighbours, DatasetEngine engine);

		///	@brief	Destructor
		~KnnClassificationAlgorithm ();

		/// @brief		Classify a set of feature vectors into their most probably classes.
		/// 
		/// @param		featureVectors	An array of feature vectors.
		/// 
		/// @return An array of characters, one character per feature vector passes.
		std::vector<std::string> classify (const std::vector<FeatureVector>& featureVectors) const;

		/// @brief		Train the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param		featureVectors	An array of feature vectors.
		/// @param		characters		An array of std::string objects with characters that match the feature vectors.
		/// @param		referenceText	A text to compare with the characters passed.
		///
		///	@pre		The size of <em>featureVectors</em>, <em>characters</em> and <em>referenceText</em> must be equal.
		///	@post		The dataset might be updated with the addition of new samples.
		///
		///	@return		The hit rate achieved after training (e.g. 0,9 for 90%).
		double train (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText);

		/// @brief	Train the classifier, comparing the classification decision for a single pattern with an ASCII code.
		///
		///	@param	featureVector	A feature vector that matches a character previously classified.
		/// @param	character		A std::string object with sample character.
		/// @param	asciiCode		An ASCII code to compare with the classification result.
		///
		///	@return	The hit rate achieved after training (e.g. 0,9 for 90%).
		double train (const FeatureVector& featureVector, const std::string& character, const unsigned int& asciiCode);
		
	private:

		unsigned int	kNeighbours_;	///< Maximum number of negihbouring samples.

		Dataset*		dataset_;		///< Dataset with previously trained characters.
};

#endif


/// @file
/// @brief Declaration of KnnClassifier class

#if !defined(_KNN_CLASSIFIER_H)
#define _KNN_CLASSIFIER_H

class FeatureVector;
class Text;
class Dataset;
#include "Classifier.hpp"
#include <string>
#include <vector>


///	@brief		Classifier of NessieOcr based on the KNN paradigm.
/// 
///	@details	This class implements the Classifier class using the KNN paradigm. A KNN classifier only needs as input parameters the number of neighbours and
///	a dataset.
/// 
/// @see		Classifier, Dataset, FeatureVector, Text
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-04-29
class KnnClassifier : public Classifier
{
	public:

		///	@brief		Constructor.
		///
		///	@param		nNeighbours	Number of neighbours to search for every sample.
		///	@param		dataset		Dataset to use in classification and training methods.
		///
		///	@warning	The dataset is only used by the class. A KnnClassifier object is not responsible of deallocating the dataset.
		explicit KnnClassifier (const unsigned int& nNeighbours, Dataset* const dataset);

		///	@brief	Destructor.
		virtual ~KnnClassifier ();

		///	@brief	Classify each feature vector passed into its most probably class (character).
		///
		/// @param	featureVectors	An array of feature vectors to classify.
		///
		///	@return	An array of std::string objects with the characters found, one character per vector in the array passed.
		std::vector<std::string> performClassification (const std::vector<FeatureVector>& featureVectors);

		/// @brief	Train the classifier, comparing each classification decision with a reference text.
		/// 
		///	@param	featureVectors	An array of feature vectors that matches the array of characters previously classified.
		/// @param	characters		An array of std::string objects with classified characters for training.
		/// @param	referenceText	A text to compare with the classificatios results to control the training decision.
		///
		///	@pre	The size of all input parameters must be equal.
		void performTraining (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText);
};

#endif


/// @file
/// @brief Declaration of Classifier class

#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H

#include "FeatureVector.hpp"
#include "ClassifierStatistics.hpp"
#include "ClassificationParadigm.hpp"
#include "Dataset.hpp"
#include <string>
#include <vector>
#include <memory>


///	@brief		Classifier of the OCR process.
/// 
///	@details	This class encapsulates all the algorithms regarding the classification stage of the OCR process. Its task is to match every feature
///	vector passed in the constructor to its associated character. In the very end of the process, a string of characters is available through the
/// Classifier::characters() method.
/// 
/// @see		FeatureVector, ClassifierStatistics, Dataset, ClassificationParadigm
///
///	@todo		Implement new paradigms of classification (neural networks, support vector machines,...).
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-09
class Classifier
{
	public:

		///	@brief	Constructor.
		///
		///	@param	featureVectors	An array of feature vectors.
		explicit Classifier (const std::vector<FeatureVector>& featureVectors);

		/// @brief	Set the feature vectors to classify.
		/// 
		/// @param	vectors	An array of feature vectors.
		///
		///	@post	The characters previously recognized are cleared.
		void featureVectors (const std::vector<FeatureVector>& vectors);

		///	@brief	Get the characters associated with the feature vectors passed in constructor.
		/// 
		/// @return	An array of std::string objects with the characters found, one character per vector element.
		const std::vector<std::string>& characters () const;

		///	@brief	Get the statistics regarding the classification stage.
		/// 
		/// @return A ClassifierStatistics object.
		const ClassifierStatistics& statistics () const;

		///	@brief	Execute the classification of feature vectors passed in constructor.
		///
		///	@param	paradigm	Classification paradigm to use.
		///	@param	dataset		Dataset to use.
		///
		///	@post	The recognized characters become available through the Classifier::characters() method.
		void classify(const ClassificationParadigm& paradigm, const std::auto_ptr<Dataset>& dataset);

	private:

		ClassifierStatistics		statistics_;		///< Statistics about the classification of feature vectors.

		std::vector<std::string>	characters_;		///< Characters found after the classification process.

		std::vector<FeatureVector>	featureVectors_;	///< Feature vectors to classify.

		/// @brief	Classify a feature vector into its most probably class using the KNN paradigm.
		/// 
		/// @param	featureVector	The feature vector to classify.
		/// @param	dataset			The dataset to use.
		/// 
		/// @return The class where the feature vector belongs to.
		unsigned int knn(const FeatureVector& featureVector, const std::auto_ptr<Dataset>& dataset) const;

		// Do not implement these methods, as they are only declared here to prevent objects to be copied. 
		Classifier (const Classifier&);
		Classifier& operator=(const Classifier&);
};


inline void Classifier::featureVectors (const std::vector<FeatureVector>& vectors)
{
	featureVectors_ = vectors;
	characters_.clear();
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


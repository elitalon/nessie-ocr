/// @file
/// @brief Definition of KnnClassifier class

#include "KnnClassifier.hpp"
#include "KnnClassificationAlgorithm.hpp"
#include "Text.hpp"
#include "Dataset.hpp"
#include "FeatureVector.hpp"
#include "NessieException.hpp"
#include <boost/timer.hpp>


KnnClassifier::KnnClassifier (const unsigned int& nNeighbours, Dataset* const dataset)
:	Classifier()
{
	if ( dataset == 0 )
		throw NessieException ("KnnClassifier::KnnClassifier() : The dataset is set to a null value.");

	classificationAlgorithm_ = new KnnClassificationAlgorithm(nNeighbours, dataset);
};


KnnClassifier::~KnnClassifier () {};


std::vector<std::string> KnnClassifier::performClassification (const std::vector<FeatureVector>& featureVectors)
{
	boost::timer timer;
	timer.restart();

	std::vector<std::string> characters = classificationAlgorithm_->classify(featureVectors);

	try
	{
		statistics_.classificationTime(timer.elapsed());
	}
	catch(...) {}

	return characters;
};


void KnnClassifier::performTraining (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText)
{
	if ( featureVectors.size() != characters.size() )
		throw NessieException ("KnnClassifier:performTraining() : The number of feature vectors is different from the number of characters classified.");

	if ( referenceText.size() != characters.size() )
		throw NessieException ("KnnClassifier::performTraining() : The size of reference text is different from the number of characters classified.");

	double hitRate = classificationAlgorithm_->train(featureVectors, characters, referenceText);

	try
	{
		statistics_.hitRate(hitRate);
		statistics_.missRate(100.0 - hitRate);
	}
	catch(...) {}
};


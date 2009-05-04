/// @file
/// @brief Definition of KnnClassifier class

#include "KnnClassifier.hpp"
#include "ClassificationAlgorithm.hpp"
#include "Text.hpp"
#include "FeatureVector.hpp"
#include <boost/timer.hpp>


KnnClassifier::KnnClassifier (std::auto_ptr<ClassificationAlgorithm> algorithm)
:	Classifier()
{
	classificationAlgorithm_ = algorithm;
};


KnnClassifier::~KnnClassifier () {};


const std::vector<std::string>& KnnClassifier::performClassification (const std::vector<FeatureVector>& featureVectors)
{
	boost::timer timer;
	timer.restart();

	characters_ = classificationAlgorithm_->classify(featureVectors);

	try
	{
		statistics_.classificationTime(timer.elapsed());
	}
	catch(...) {}

	return characters_;
};


void KnnClassifier::performTraining (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText)
{
	double hitRate = classificationAlgorithm_->train(featureVectors, characters, referenceText);

	try
	{
		statistics_.hitRate(hitRate);
		statistics_.missRate(100.0 - hitRate);
	}
	catch(...) {}
};


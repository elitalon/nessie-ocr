/// @file
/// @brief Definition of KnnClassifier class

#include "KnnClassifier.hpp"
#include "KnnClassificationAlgorithm.hpp"
#include "Text.hpp"
#include "DatasetEngine.hpp"
#include "FeatureVector.hpp"
#include "NessieException.hpp"
#include <boost/timer.hpp>


KnnClassifier::KnnClassifier (const unsigned int& nNeighbours, DatasetEngine engine)
:	Classifier()
{
	classificationAlgorithm_ = new KnnClassificationAlgorithm(nNeighbours, engine);
}


KnnClassifier::~KnnClassifier ()
{
	delete classificationAlgorithm_;
}


std::vector<std::string> KnnClassifier::performClassification (const std::vector<FeatureVector>& featureVectors)
{
	boost::timer timer;
	timer.restart();

	std::vector<std::string> characters( classificationAlgorithm_->classify(featureVectors) );

	statistics_.classificationTime(timer.elapsed());

	return characters;
}


void KnnClassifier::performTraining (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText)
{
	if ( featureVectors.size() != characters.size() )
		throw NessieException ("KnnClassifier:performTraining() : The number of feature vectors is different from the number of characters classified.");

	if ( referenceText.size() != characters.size() )
		throw NessieException ("KnnClassifier::performTraining() : The size of reference text is different from the number of characters classified.");

	double hitRate = classificationAlgorithm_->train(featureVectors, characters, referenceText);

	statistics_.hitRate(hitRate);
	statistics_.missRate(100.0 - hitRate);
}


void KnnClassifier::performTraining (const FeatureVector& featureVector, const std::string& character, const unsigned int& asciiCode)
{
	double hitRate = classificationAlgorithm_->train(featureVector, character, asciiCode);

	statistics_.hitRate(hitRate);
	statistics_.missRate(100.0 - hitRate);
}

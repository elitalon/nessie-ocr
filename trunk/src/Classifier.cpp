/// @file
/// @brief Definition of Classifier class


#include "Classifier.hpp"
#include <boost/timer.hpp>


Classifier::Classifier (const std::vector<FeatureVector>& featureVectors)
:	statistics_(),
	featureVectors_(featureVectors),
	characters_("")
{};


void Classifier::classify (const ClassificationParadigm& paradigm)
{
	boost::timer timer;
	timer.restart();

	if ( paradigm.id() == ClassificationParadigm::knn().id() )
	{
		;
	}

	if ( paradigm.id() == ClassificationParadigm::svm().id() )
	{
		;
	}
	
	try
	{
		statistics_.classificationTime(timer.elapsed());
		statistics_.charactersFound(characters_.size());
	}
	catch(...) {}
};


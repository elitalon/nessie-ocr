/// @file
/// @brief Definition of Classifier class


#include "Classifier.hpp"
#include <boost/timer.hpp>


Classifier::Classifier (const std::vector<FeatureVector>& featureVectors)
:	statistics_(ClassifierStatistics()),
	featureVectors_(featureVectors),
	characters_(std::string(""))
{};


void Classifier::classify ()
{
	boost::timer timer;
	timer.restart();

	for ( std::vector<FeatureVector>::iterator i = featureVectors_.begin(); i != featureVectors_.end(); ++i )
	{
		;
	}

	statistics_.classificationTime(timer.elapsed());
	statistics_.charactersFound(characters_.size());
};


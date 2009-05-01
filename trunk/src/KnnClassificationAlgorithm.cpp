/// @file
/// @brief Definition of KnnClassificationAlgorithm class

#include "KnnClassificationAlgorithm.hpp"
#include "FeatureVector.hpp"
#include "Dataset.hpp"
#include "Text.hpp"
#include "NessieException.hpp"
#include <utility>
#include <map>
#include <algorithm>
#include <sstream>


KnnClassificationAlgorithm::KnnClassificationAlgorithm (const unsigned int& kNeighbours, std::auto_ptr<Dataset>& dataset)
:	ClassificationAlgorithm(),
	kNeighbours_(kNeighbours),
	dataset_(dataset)
{};


KnnClassificationAlgorithm::~KnnClassificationAlgorithm () {};


unsigned int knn(const FeatureVector& featureVector, const std::auto_ptr<Dataset>& dataset);
std::vector<std::string> KnnClassificationAlgorithm::classify (const std::vector<FeatureVector>& featureVectors)
{
	std::vector<std::string> characters(0);

	if ( dataset_->size() > 0 ) 
	{   
		for( unsigned int i = 0; i < featureVectors.size(); ++i )
		{   
			unsigned int code;

			code = knn(featureVectors.at(i), dataset_);

			characters.push_back(dataset_->character(code));
		}   
	}   
	else
		characters.assign(featureVectors.size(), std::string(""));

	return characters;
};


unsigned int knn(const FeatureVector& featureVector, const std::auto_ptr<Dataset>& dataset)
{
	return 32;
};


double KnnClassificationAlgorithm::train (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText)
{
	unsigned int patternNo = 0;
	double hits = 0.0;

	for ( std::vector<std::string>::const_iterator i = characters.begin(); i != characters.end(); ++i )
	{
		try
		{
			unsigned int code;
			if ( *i == referenceText.at(patternNo) )
			{
				code = dataset_->code(*i);
				hits += 1.0;
			}
			else
				code = dataset_->code(referenceText.at(patternNo));

			if ( code != 256 )
				dataset_->addSample(Sample(featureVectors.at(patternNo), code));
		}
		catch (std::exception& e)
		{
			std::stringstream patternNoStr;
			patternNoStr << patternNo;
			
			std::string message(e.what());
			throw NessieException ("KnnClassificationAlgorithm::train() : Training of sample " + patternNoStr.str() + " could not be completed. " + message);
		}

		++patternNo;
	}

	return (hits / characters.size()) * 100;
};


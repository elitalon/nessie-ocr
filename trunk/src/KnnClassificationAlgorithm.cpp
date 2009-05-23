/// @file
/// @brief Definition of KnnClassificationAlgorithm class

#include "KnnClassificationAlgorithm.hpp"
#include "Dataset.hpp"
#include "FeatureVector.hpp"
#include "Text.hpp"
#include "NessieException.hpp"
#include <utility>
#include <map>
#include <sstream>


KnnClassificationAlgorithm::KnnClassificationAlgorithm (const unsigned int& kNeighbours, Dataset* const dataset)
:	ClassificationAlgorithm(),
	kNeighbours_(kNeighbours),
	dataset_(dataset)
{
	if ( dataset == 0 )
		throw NessieException ("KnnClassificationAlgorithm::KnnClassificationAlgorithm() : The dataset is set to a null value.");
}


KnnClassificationAlgorithm::~KnnClassificationAlgorithm () {}


std::vector<std::string> KnnClassificationAlgorithm::classify (const std::vector<FeatureVector>& featureVectors) const
{
	if ( dataset_->features() != featureVectors.begin()->size() )
		throw NessieException ("KnnClassificationAlgorithm::classify() : The number of features stored in the dataset is different from the one expected by the program.");
	
	std::vector<std::string> characters(0);
	if ( dataset_->size() > 0 )
	{
		typedef std::pair<double, Sample> Neighbour;

		for( unsigned int k = 0; k < featureVectors.size(); ++k )
		{
			std::multimap<double, Sample> kNearestNeighbours;

			// Search the K nearest neighbours
			for( unsigned int i = 0; i < dataset_->size(); ++i )
			{
				double distance	= featureVectors.at(k).computeEuclideanDistance(dataset_->at(i).first);
				Sample sample	= dataset_->at(i);

				if( kNearestNeighbours.size() < kNeighbours_ )
					kNearestNeighbours.insert( Neighbour(distance, sample) );
				else
				{
					std::multimap<double, Sample>::iterator j = kNearestNeighbours.upper_bound( distance );

					if ( j != kNearestNeighbours.end() )
					{
						kNearestNeighbours.insert(j, Neighbour(distance, sample));
						kNearestNeighbours.erase(j);
					}
				}
			}
			
			if ( kNeighbours_ == 1 )
				characters.push_back( dataset_->character(kNearestNeighbours.begin()->second.second) );
			else
			{
				// Gather the class of the k nearest neighbours
				std::map<unsigned int, unsigned int> classes;	// (label, appearances)

				for ( std::multimap<double, Sample>::iterator i = kNearestNeighbours.begin(); i != kNearestNeighbours.end(); ++i )
				{
					if ( classes.count(i->second.second) == 0 )
						classes.insert( std::pair<unsigned int, unsigned int>(i->second.second, 1) );
					else
						classes[i->second.second]++;
				}

				// Get the most probably class
				unsigned int label = classes.begin()->first;
				for ( std::map<unsigned int, unsigned>::iterator i = classes.begin(); i != classes.end(); ++i )
				{
					if ( classes[label] < i->second )
						label = i->first;
				}

				characters.push_back(dataset_->character(label));
			}
		}
	}
	else
		characters.assign(featureVectors.size(), std::string(""));

	return characters;
}


double KnnClassificationAlgorithm::train (const std::vector<FeatureVector>& featureVectors, const std::vector<std::string>& characters, const Text& referenceText)
{
	if ( dataset_->features() != featureVectors.begin()->size() )
		throw NessieException ("KnnClassificationAlgorithm::train() : The number of features stored in the dataset is different from the one expected by the program.");

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
}


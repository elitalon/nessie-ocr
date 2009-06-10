/// @file
/// @brief Definition of KnnClassificationAlgorithm class

#include "KnnClassificationAlgorithm.hpp"
#include "DatasetEngine.hpp"
#include "Dataset.hpp"
#include "PlainTextDataset.hpp"
#include "MySqlDataset.hpp"
#include "PostgreSqlDataset.hpp"
#include "FeatureVector.hpp"
#include "Text.hpp"
#include "NessieException.hpp"
#include <utility>
#include <map>
#include <sstream>


KnnClassificationAlgorithm::KnnClassificationAlgorithm (const unsigned int& kNeighbours, DatasetEngine engine)
:	ClassificationAlgorithm(),
	kNeighbours_(kNeighbours),
	dataset_(0)
{
	if ( engine.type() == DatasetEngineType::PlainText() )
		dataset_ = new PlainTextDataset (engine.filename());

#if defined(_WITH_POSTGRESQL_DATASET_)
	if ( engine.type() == DatasetEngineType::PostgreSql() )
		dataset_ = new PostgreSqlDataset  (engine.database(), engine.username(), engine.password());
#endif

#if defined(_WITH_MYSQL_DATASET_)
	if ( engine.type() == DatasetEngineType::MySql() )
		dataset_ = new MySqlDataset (engine.database(), engine.username(), engine.password());
#endif
}


KnnClassificationAlgorithm::~KnnClassificationAlgorithm ()
{
	delete dataset_;
}


std::vector<std::string> KnnClassificationAlgorithm::classify (const std::vector<FeatureVector>& featureVectors) const
{
	if ( dataset_->features() != featureVectors.begin()->size() )
		throw NessieException ("KnnClassificationAlgorithm::classify() : The number of features stored in the dataset is different from the one expected by the program.");
	
	if ( dataset_->size() > 0 )
	{
		typedef std::pair<double, unsigned int> Neighbour;	// (distance, label)
		
		std::vector<std::string> characters(0);
		characters.reserve(featureVectors.size());

		for( unsigned int k = 0; k < featureVectors.size(); ++k )
		{
			// Search the K nearest neighbours
			std::multimap<double, unsigned int> kNearestNeighbours;

			for( unsigned int i = 0; i < dataset_->size(); ++i )
			{
				double distance	= featureVectors.at(k).computeEuclideanDistance(dataset_->at(i).first);

				if( kNearestNeighbours.size() < kNeighbours_ )
					kNearestNeighbours.insert( Neighbour(distance, dataset_->at(i).second) );
				else
				{
					std::multimap<double, unsigned int>::iterator j = kNearestNeighbours.upper_bound( distance );

					if ( j != kNearestNeighbours.end() )
					{
						kNearestNeighbours.insert(j, Neighbour(distance, dataset_->at(i).second));
						kNearestNeighbours.erase(j);
					}
				}
			}
			

			if ( kNeighbours_ == 1 )
				characters.push_back( dataset_->character(kNearestNeighbours.begin()->second) );
			else
			{
				// Gather the class of the k nearest neighbours
				std::map<unsigned int, unsigned int> classes;	// (label, appearances)

				for ( std::multimap<double, unsigned int>::iterator i = kNearestNeighbours.begin(); i != kNearestNeighbours.end(); ++i )
				{
					if ( classes.count(i->second) == 0 )
						classes.insert( std::pair<unsigned int, unsigned int>(i->second, 1) );
					else
						classes[i->second]++;
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

		return characters;
	}
	else
		return std::vector<std::string>(featureVectors.size(), "");
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


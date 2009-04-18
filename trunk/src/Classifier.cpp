/// @file
/// @brief Definition of Classifier class

#include "Classifier.hpp"
#include <boost/timer.hpp>
#include <utility>
#include <algorithm>
#include <cmath>

Classifier::Classifier (const std::vector<FeatureVector>& featureVectors)
:	statistics_(),
	characters_(0),
	featureVectors_(featureVectors)
{};


void Classifier::classify (const ClassificationParadigm& paradigm, const std::auto_ptr<Dataset>& dataset)
{
	boost::timer timer;
	timer.restart();

	characters_.clear();
	if ( dataset->size() > 0 )
	{
		for( unsigned int i = 0; i < featureVectors_.size(); ++i )
		{
			unsigned int code;

			if ( paradigm.id() == ClassificationParadigm::knn().id() )
				code = knn(featureVectors_.at(i), dataset);

			characters_.push_back(dataset->character(code));
		}	
	}
	else
		characters_.assign(featureVectors_.size(), std::string(""));

	try
	{
		statistics_.classificationTime(timer.elapsed());
	}
	catch(...) {}
};


unsigned int Classifier::knn(const FeatureVector& featureVector, const std::auto_ptr<Dataset>& dataset) const
{
	typedef std::pair<double, unsigned int> Neighbour;	// (distance, class)
	std::vector<Neighbour> neighbours(0);
	neighbours.reserve(dataset->size());

	// Compute the distance from every sample in the dataset.
	for( unsigned int i = 0; i < dataset->size(); ++i )
	{
		double distance		= featureVector.computeEuclideanDistance(dataset->at(i).first);
		unsigned int code	= dataset->at(i).second;

		neighbours.push_back(Neighbour(distance, code));
	}
	std::sort(neighbours.begin(), neighbours.end());
	
	const unsigned int KNN = 1;

	// Store the class of the K nearest neighbours
	std::vector<unsigned int> kNearestNeighbours(0);
	kNearestNeighbours.reserve(KNN);
	for ( std::vector<Neighbour>::iterator i = neighbours.begin(); i != neighbours.begin() + KNN; ++i )
		kNearestNeighbours.push_back(i->second);

	// Get the unique candidate classes
	std::vector<unsigned int> candidateClasses(0);
	for ( unsigned int i = 0; i < KNN; ++i )
	{
		if ( not std::binary_search(candidateClasses.begin(), candidateClasses.end(), kNearestNeighbours.at(i)) )
			candidateClasses.push_back(kNearestNeighbours.at(i));
	}

	// Count how many times a class appears in the KNN set.
	std::vector<unsigned int> classAppearances(candidateClasses.size());
	for ( unsigned int i = 0; i < candidateClasses.size(); ++i )
		classAppearances.at(i) = std::count(kNearestNeighbours.begin(), kNearestNeighbours.end(), candidateClasses.at(i));

	std::vector<unsigned int>::iterator	j = std::max_element(classAppearances.begin(), classAppearances.end());
	if ( *j < 2 )
		return kNearestNeighbours.front();
	else
	{
		std::vector<unsigned int>::iterator	k = classAppearances.begin();
		unsigned int index = 0;
		while ( k != j )
		{
			++index;
			++k;
		}

		return candidateClasses.at(index);
	}	
};

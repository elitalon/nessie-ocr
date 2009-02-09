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

	/*
	// Compute euclidean distances with every sample in the training set
	std::deque< std::pair<double, unsigned int> > euclideanDistances(dataset_.size());

	for ( unsigned int i = 0; i < dataset_.size(); ++i )
	{
	DataSet::Sample referenceSample = dataset_.getSample(i);

	FeatureVector difference;
	difference = referenceSample.first - sample_;

	double term = 0.0;
	for ( unsigned int j = 0; j < dataset_.nFeatures(); ++j )
	term += pow(difference(j), 2);

	term = sqrt(term);

	euclideanDistances.at(i) = std::pair<double, unsigned int>(term, i);
	}

	// Compute the probability of classify a shape into a category
	unsigned int k = 5;
	std::deque<unsigned int> categoryFrequencies(256, 0);
	for ( unsigned int i = 0; i < k; ++i )
	{
	unsigned int category = euclideanDistances.at(i).second;	// Index within the data set of a k-neighbour

	categoryFrequencies.at(category) += 1.0;
	}

	// Get the most probably category (its ASCII code)
	std::deque<unsigned int>::iterator mostFrequentCategory = std::max_element(categoryFrequencies.begin(), categoryFrequencies.end());
	unsigned int categoryMatched = 0;

	std::deque<unsigned int>::iterator i = categoryFrequencies.begin();
	while ( i not_eq mostFrequentCategory )
	{
	++categoryMatched;
	++i;
	}
	*/

	statistics_.classificationTime(timer.elapsed());
	statistics_.charactersFound(characters_.size());
};


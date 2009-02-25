/// @file
/// @brief Definition of FeatureVector class

#include "FeatureVector.hpp"
#include <cmath>


FeatureVector::FeatureVector()
:	features_(0),
	size_(0)
{};


FeatureVector::FeatureVector(const unsigned int& n)
:	features_(std::vector<double>(n, 0.0)),
	size_(n)
{};


double FeatureVector::computeEuclideanDistance (const FeatureVector& featureVector) const
{
	FeatureVector tmp(*this - featureVector);

	double result = 0.0;
	for ( unsigned int i = 0; i < this->size_; ++i )
		result += pow(tmp.at(i), 2);

	return sqrt(result);
};


double FeatureVector::computeMahalanobisDistance (const FeatureVector& featureVector) const
{
	return 0.0;
};


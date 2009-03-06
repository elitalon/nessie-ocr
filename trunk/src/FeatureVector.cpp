/// @file
/// @brief Definition of FeatureVector class

#include "FeatureVector.hpp"
#include "NessieException.hpp"
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


FeatureVector FeatureVector::operator+ (const FeatureVector& featureVector) const
{
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator+() : Size of vectors to sum must be equal");

	FeatureVector temp(this->size_);

	for ( unsigned int i = 0; i < this->size_; ++i )
		temp.features_.at(i) = this->features_.at(i) + featureVector.features_.at(i);

	return temp;
};


FeatureVector FeatureVector::operator- (const FeatureVector& featureVector) const
{
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator-() : Size of vectors to subtract must be equal");

	FeatureVector temp(this->size_);

	for ( unsigned int i = 0; i < this->size_; ++i )
		temp.features_.at(i) = this->features_.at(i) - featureVector.features_.at(i);

	return temp;
};


double FeatureVector::operator* (const FeatureVector& featureVector) const
{
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator*() : Size of vectors to multiply must be equal");

	double result = 0.0;

	for ( unsigned int i = 0; i < this->size_; ++i )
		result += this->features_.at(i) * featureVector.features_.at(i);

	return result;
};


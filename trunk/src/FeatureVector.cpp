/// @file
/// @brief Definition of FeatureVector class

#include "FeatureVector.hpp"


FeatureVector::FeatureVector()
:	features_(0),
	size_(0)
{};


FeatureVector::FeatureVector(const unsigned int& n)
:	features_(std::vector<double>(n, 0.0)),
	size_(n)
{};


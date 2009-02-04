/// @file
/// @brief Definition of FeatureVector class

#include "FeatureVector.hpp"


FeatureVector::FeatureVector(const unsigned int& nFeatures)
:	features_(std::vector<double>(nFeatures, 0.0)),
	size_(nFeatures)
{};


///
/// @file
/// @brief Definition of FeatureVector class
///


#include "FeatureVector.hpp"


FeatureVector::FeatureVector(const unsigned int& nFeatures)
	:	features_(std::vector<double>(nFeatures)),
		size_(nFeatures)
{
	for ( unsigned int i = 0; i < size_; ++i )
		features_.at(i) = 0.0;
};


FeatureVector::~FeatureVector()
{

};

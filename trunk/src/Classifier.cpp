///
/// @file
/// @brief Definition of Classifier class
///


#include "Classifier.hpp"
#include "Shape.hpp"




Classifier::Classifier (const DataSet& dataset)
	:	dataset_(dataset),
		sample_(FeatureVector(dataset.nFeatures())),
		matchingShapeTime_(0.0)
{
	
};



Classifier::~Classifier ()
{
	
};



std::string Classifier::matchShape (const Shape& shape)
{
	return "";
};

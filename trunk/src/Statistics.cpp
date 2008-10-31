///
/// @file
/// @brief Definition of Statistics class
///

#include "Statistics.hpp"



Statistics::Statistics ()
	:	backgroundReferenceGrayLevelFindingTime_(0.0),
		optimalThresholdComputingTime_(0.0),
		noiseRemovalTime_(0.0),
		preprocessingTime_(0.0),
		thresholdingTime_(0.0),
		shapesFindingTime_(0.0),
		segmentationTime_(0.0)
{
	
};

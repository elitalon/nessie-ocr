///
/// @file
/// @brief Definition of Statistics class
///

#include "Statistics.hpp"


///
/// @details Initializes a Statistics object with timers set to 0.0
/// 
Statistics::Statistics ()
	:	backgroundReferenceGrayLevelFindingTime_(0.0), optimalThresholdComputingTime_(0.0), noiseRemovalTime_(0.0),
		thresholdingTime_(0.0), shapesFindingTime_(0.0)
{
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
	
	segmentationTime_ = thresholdingTime_ + shapesFindingTime_;
};

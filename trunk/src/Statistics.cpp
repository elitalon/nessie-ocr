///
/// @file
/// @brief Implementation of the class Statistics
///

#include "Statistics.h"


///
/// @details Initializes a Statistics object with timers set to 0.0
/// 
Statistics::Statistics ()
	: backgroundReferenceGrayLevelFindingTime_(0.0), optimalThresholdComputingTime_(0.0), noiseRemovalTime_(0.0)
{
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


///
/// @details
/// 
void Statistics::backgroundReferenceGrayLevelFindingTime (const double &time)
{
	backgroundReferenceGrayLevelFindingTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


///
/// @details
/// 
void Statistics::optimalThresholdComputingTime (const double &time)
{
	optimalThresholdComputingTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


///
/// @details
/// 
void Statistics::noiseRemovalTime (const double &time)
{
	noiseRemovalTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};

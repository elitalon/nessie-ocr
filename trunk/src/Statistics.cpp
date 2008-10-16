///
/// @file
/// @brief Implementation of the class Statistics
///

#include "Statistics.hpp"


///
/// @details Initializes a Statistics object with timers set to 0.0
/// 
Statistics::Statistics ()
	:	backgroundReferenceGrayLevelFindingTime_(0.0), optimalThresholdComputingTime_(0.0), noiseRemovalTime_(0.0),
		thresholdingTime_(0.0), floodFillingTime_(0.0)
{
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
	
	segmentationTime_ = thresholdingTime_ + floodFillingTime_;
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


///
/// @details
///
void Statistics::thresholdingTime (const double &time)
{
	thresholdingTime_ = time;
	
	segmentationTime_ = thresholdingTime_ + floodFillingTime_;
};


///
/// @details
///
void Statistics::floodFillingTime (const double &time)
{
	floodFillingTime_ = time;
	
	segmentationTime_ = thresholdingTime_ + floodFillingTime_;
};
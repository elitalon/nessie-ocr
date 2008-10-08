///
/// @file
/// @brief Implementation of the class Statistics
///

#include "Statistics.h"


///
/// @details Initializes a Statistics object with timers set to 0
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
Statistics::Statistics ()
	: backgroundReferenceGrayLevelFindingTime_(0.0), optimalThresholdComputingTime_(0.0), noiseRemovalTime_(0.0)
{
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


///
/// @param	time	Elapsed time in the reference gray level of the background finding algorithm
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-06
///
void Statistics::backgroundReferenceGrayLevelFindingTime (const double &time)
{
	backgroundReferenceGrayLevelFindingTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


///
/// @param	time	Elapsed time in the optimal threshold computing algorithm
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-06
///
void Statistics::optimalThresholdComputingTime (const double &time)
{
	optimalThresholdComputingTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


///
/// @param	time	Elapsed time in the noise removal algorithm
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-06
///
void Statistics::noiseRemovalTime (const double &time)
{
	noiseRemovalTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};

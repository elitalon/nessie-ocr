///
/// @file
/// @brief Implementation of class Statistics
///

#include "Statistics.h"


///
/// @details Initializes a Statistics object with timers set to 0
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
Statistics::Statistics () :
	backgroundReferenceGrayLevelFindingTime_(0.0), optimalThresholdComputingTime_(0.0), noiseRemovalTime_(0.0)
{
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


///
/// @details Destroys a Statistics object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-17
///
Statistics::~Statistics ()
{
	
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
double Statistics::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
double Statistics::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
double Statistics::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
double Statistics::preprocessingTime () const
{
	return preprocessingTime_;
};

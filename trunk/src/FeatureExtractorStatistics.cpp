/// @file
/// @brief Definition of FeatureExtractorStatistics class

#include "FeatureExtractorStatistics.hpp"
#include <iostream>


FeatureExtractorStatistics::FeatureExtractorStatistics ()
:	Statistics(),	// Invoke base class copy constructor
	patternsBuildingTime_(0),
	momentsComputingTime_(0)
{};


FeatureExtractorStatistics::FeatureExtractorStatistics (const FeatureExtractorStatistics& statistics)
:	Statistics(statistics),	// Invoke base class copy constructor
	patternsBuildingTime_(0),
	momentsComputingTime_(0)
{
	if ( statistics.patternsBuildingTime_ != 0 )
		patternsBuildingTime_ = new double(*statistics.patternsBuildingTime_);

	if ( statistics.momentsComputingTime_ != 0 )
		momentsComputingTime_ = new double(*statistics.momentsComputingTime_);
};


FeatureExtractorStatistics& FeatureExtractorStatistics::operator= (const FeatureExtractorStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.patternsBuildingTime_ != 0 )
	{
		double* tmp = new double(*statistics.patternsBuildingTime_);
		delete patternsBuildingTime_;
		patternsBuildingTime_ = tmp;
	}

	if ( statistics.momentsComputingTime_ != 0 )
	{
		double* tmp = new double(*statistics.momentsComputingTime_);
		delete momentsComputingTime_;
		momentsComputingTime_ = tmp;
	}

	return *this;
};


FeatureExtractorStatistics::~FeatureExtractorStatistics ()
{
	delete patternsBuildingTime_;
	delete momentsComputingTime_;
};


void FeatureExtractorStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Feature extraction stage statistics" << std::endl;

	if ( patternsBuildingTime_ != 0 )
		std::cout << "  - Patterns building time       : " << *patternsBuildingTime_ << std::endl;

	if ( momentsComputingTime_ != 0 )
		std::cout << "  - Moments computing time       : " << *momentsComputingTime_ << std::endl;

	std::cout << "  - Total elapsed time           : " << totalTime_ << std::endl;
};


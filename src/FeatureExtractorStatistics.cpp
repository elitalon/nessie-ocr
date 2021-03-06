/// @file
/// @brief Definition of FeatureExtractorStatistics class

#include "FeatureExtractorStatistics.hpp"
#include <iostream>


FeatureExtractorStatistics::FeatureExtractorStatistics ()
:	Statistics(),
	momentsComputingTime_(0)
{}


FeatureExtractorStatistics::FeatureExtractorStatistics (const FeatureExtractorStatistics& statistics)
:	Statistics(statistics),
	momentsComputingTime_(0)
{
	if ( statistics.momentsComputingTime_.get() != 0 )
		momentsComputingTime_.reset( new double (*statistics.momentsComputingTime_));
}


FeatureExtractorStatistics& FeatureExtractorStatistics::operator= (const FeatureExtractorStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.momentsComputingTime_.get() != 0 )
		momentsComputingTime_.reset( new double (*statistics.momentsComputingTime_ ));
	
	return *this;
}


FeatureExtractorStatistics::~FeatureExtractorStatistics () {};


void FeatureExtractorStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Feature extraction stage statistics" << std::endl;

	if ( momentsComputingTime_.get() != 0 )
		std::cout << "  - Moments computing time        : " << *momentsComputingTime_ << " s" << std::endl;

	std::cout << "  - Total elapsed time            : " << totalTime_  << " s" << std::endl;
}


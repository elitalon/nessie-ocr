/// @file
/// @brief Definition of Statistics class

#include "Statistics.hpp"
#include <iostream>


Statistics::Statistics ()
	:	totalTime_(0.0)
{};

PreprocessorStatistics::PreprocessorStatistics ()
	:	clipSize_(0),
		globalThresholdingTime_(0.0)
{};

FeatureExtractionStatistics::FeatureExtractionStatistics ()
{};

ClassificationStatistics::ClassificationStatistics ()
{};

Statistics::~Statistics () {};

PreprocessorStatistics::~PreprocessorStatistics () {};

FeatureExtractionStatistics::~FeatureExtractionStatistics () {};

ClassificationStatistics::~ClassificationStatistics () {};

const void PreprocessorStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Preprocessing stage statistics" << std::endl;
	std::cout << "  - Number of pixels         : " << clipSize_ << std::endl;
	std::cout << "  - Global thresholding time : " << globalThresholdingTime_ << std::endl;
	std::cout << "  - Total elapsed time       : " << totalTime_ << std::endl;
};

const void FeatureExtractionStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Feature extraction stage statistics" << std::endl;
	std::cout << "  - Total elapsed time  : " << totalTime_ << std::endl;
};

const void ClassificationStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Classification stage statistics" << std::endl;
	std::cout << "  - Total elapsed time  : " << totalTime_ << std::endl;
};
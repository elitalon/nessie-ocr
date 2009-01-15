/// @file
/// @brief Definition of Statistics class

#include "Statistics.hpp"
#include <iostream>


Statistics::Statistics ()
	:	totalTime_(0.0)
{};


Statistics::~Statistics () {};



PreprocessorStatistics::PreprocessorStatistics ()
	:	clipSize_(0),
		optimalThreshold_(127),
		globalThresholdingTime_(0.0),
		templateFilteringTime_(0.0),
		averagingFilteringTime_(0.0)
{};


PreprocessorStatistics::~PreprocessorStatistics ()
{};


void PreprocessorStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Preprocessing stage statistics" << std::endl;
	std::cout << "  - Number of pixels         : " << clipSize_ << std::endl;
	std::cout << "  - Optimal threshold        : " << static_cast<unsigned int>(optimalThreshold_) << std::endl;
	std::cout << "  - Global thresholding time : " << globalThresholdingTime_ << std::endl;
	std::cout << "  - Template filtering time  : " << templateFilteringTime_ << std::endl;
	std::cout << "  - Averaging filtering time : " << averagingFilteringTime_ << std::endl;
	std::cout << "  - Total elapsed time       : " << totalTime_ << std::endl;
};



FeatureExtractionStatistics::FeatureExtractionStatistics ()
{};


FeatureExtractionStatistics::~FeatureExtractionStatistics ()
{};


void FeatureExtractionStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Feature extraction stage statistics" << std::endl;
	std::cout << "  - Total elapsed time  : " << totalTime_ << std::endl;
};



ClassificationStatistics::ClassificationStatistics ()
{};


ClassificationStatistics::~ClassificationStatistics ()
{};


void ClassificationStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Classification stage statistics" << std::endl;
	std::cout << "  - Total elapsed time  : " << totalTime_ << std::endl;
};


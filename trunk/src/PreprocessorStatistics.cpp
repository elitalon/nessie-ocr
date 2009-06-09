/// @file
/// @brief Definition of PreprocessorStatistics class

#include "PreprocessorStatistics.hpp"
#include <iostream>


PreprocessorStatistics::PreprocessorStatistics ()
:	Statistics(),
	clipSize_(0),
	optimalThreshold_(0),
	nRegions_(0),
	nLines_(0),
	averageSpaceBetweenCharacters_(0),
	averageCharacterHeight_(0),
	averageCharacterWidth_(0),
	averagingFilteringTime_(0),
	globalThresholdingTime_(0),
	templateFilteringTime_(0),
	segmentationTime_(0),
	patternsBuildingTime_(0),
	skeletonizationTime_(0),
	slantingCorrectionTime_(0)
{}


PreprocessorStatistics::PreprocessorStatistics (const PreprocessorStatistics& statistics)
:	Statistics(statistics),
	clipSize_(0),
	optimalThreshold_(0),
	nRegions_(0),
	nLines_(0),
	averageSpaceBetweenCharacters_(0),
	averageCharacterHeight_(0),
	averageCharacterWidth_(0),
	averagingFilteringTime_(0),
	globalThresholdingTime_(0),
	templateFilteringTime_(0),
	segmentationTime_(0),
	patternsBuildingTime_(0),
	skeletonizationTime_(0),
	slantingCorrectionTime_(0)
{
	if ( statistics.clipSize_.get() != 0 )
		clipSize_.reset(new unsigned int(*statistics.clipSize_));

	if ( statistics.optimalThreshold_.get() != 0 )
		optimalThreshold_.reset(new unsigned char(*statistics.optimalThreshold_));

	if ( statistics.nRegions_.get() != 0 )
		nRegions_.reset(new unsigned int(*statistics.nRegions_));

	if ( statistics.nLines_.get() != 0 )
		nLines_.reset(new unsigned int(*statistics.nLines_));

	if ( statistics.averageSpaceBetweenCharacters_.get() != 0 )
		averageSpaceBetweenCharacters_.reset(new double(*statistics.averageSpaceBetweenCharacters_));
	
	if ( statistics.averageCharacterHeight_.get() != 0 )
		averageCharacterHeight_.reset(new double(*statistics.averageCharacterHeight_));

	if ( statistics.averageCharacterWidth_.get() != 0 )
		averageCharacterWidth_.reset(new double(*statistics.averageCharacterWidth_));

	if ( statistics.averagingFilteringTime_.get() != 0 )
		averagingFilteringTime_.reset(new double(*statistics.averagingFilteringTime_));

	if ( statistics.globalThresholdingTime_.get() != 0 )
		globalThresholdingTime_.reset(new double(*statistics.globalThresholdingTime_));

	if ( statistics.templateFilteringTime_.get() != 0 )
		templateFilteringTime_.reset(new double(*statistics.templateFilteringTime_));

	if ( statistics.segmentationTime_.get() != 0 )
		segmentationTime_.reset(new double(*statistics.segmentationTime_));

	if ( statistics.skeletonizationTime_.get() != 0 )
		skeletonizationTime_.reset(new double(*statistics.skeletonizationTime_));

	if ( statistics.patternsBuildingTime_.get() != 0 )
		patternsBuildingTime_.reset( new double (*statistics.patternsBuildingTime_ ));

	if ( statistics.skeletonizationTime_.get() != 0 )
		skeletonizationTime_.reset(new double(*statistics.skeletonizationTime_));

	if ( statistics.slantingCorrectionTime_.get() != 0 )
		slantingCorrectionTime_.reset(new double(*statistics.slantingCorrectionTime_));
}


PreprocessorStatistics::~PreprocessorStatistics () {}


PreprocessorStatistics& PreprocessorStatistics::operator= (const PreprocessorStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.clipSize_.get() != 0 )
		clipSize_.reset(new unsigned int(*statistics.clipSize_));

	if ( statistics.optimalThreshold_.get() != 0 )
		optimalThreshold_.reset(new unsigned char(*statistics.optimalThreshold_));

	if ( statistics.nRegions_.get() != 0 )
		nRegions_.reset(new unsigned int(*statistics.nRegions_));

	if ( statistics.nLines_.get() != 0 )
		nLines_.reset(new unsigned int(*statistics.nLines_));

	if ( statistics.averageSpaceBetweenCharacters_.get() != 0 )
		averageSpaceBetweenCharacters_.reset(new double(*statistics.averageSpaceBetweenCharacters_));
	
	if ( statistics.averageCharacterHeight_.get() != 0 )
		averageCharacterHeight_.reset(new double(*statistics.averageCharacterHeight_));

	if ( statistics.averageCharacterWidth_.get() != 0 )
		averageCharacterWidth_.reset(new double(*statistics.averageCharacterWidth_));

	if ( statistics.averagingFilteringTime_.get() != 0 )
		averagingFilteringTime_.reset(new double(*statistics.averagingFilteringTime_));

	if ( statistics.globalThresholdingTime_.get() != 0 )
		globalThresholdingTime_.reset(new double(*statistics.globalThresholdingTime_));

	if ( statistics.templateFilteringTime_.get() != 0 )
		templateFilteringTime_.reset(new double(*statistics.templateFilteringTime_));

	if ( statistics.segmentationTime_.get() != 0 )
		segmentationTime_.reset(new double(*statistics.segmentationTime_));

	if ( statistics.skeletonizationTime_.get() != 0 )
		skeletonizationTime_.reset(new double(*statistics.skeletonizationTime_));

	if ( statistics.patternsBuildingTime_.get() != 0 )
		patternsBuildingTime_.reset( new double (*statistics.patternsBuildingTime_ ));

	if ( statistics.skeletonizationTime_.get() != 0 )
		skeletonizationTime_.reset(new double(*statistics.skeletonizationTime_));

	if ( statistics.slantingCorrectionTime_.get() != 0 )
		slantingCorrectionTime_.reset(new double(*statistics.slantingCorrectionTime_));

	return *this;
}


void PreprocessorStatistics::print () const
{
	std::cout << std::endl << "Preprocessing stage statistics" << std::endl;
	
	if ( clipSize_.get() != 0 )
		std::cout << "  - Clip size                     : " << *clipSize_ << " pixels" << std::endl;

	if ( optimalThreshold_.get() != 0 )
		std::cout << "  - Optimal threshold             : " << static_cast<unsigned int>(*optimalThreshold_) << std::endl;

	if ( nRegions_.get() != 0 )
		std::cout << "  - Number of regions             : " << *nRegions_ << std::endl;

	if ( nLines_.get() != 0 )
		std::cout << "  - Number of lines               : " << *nLines_ << std::endl;

	if ( averageSpaceBetweenCharacters_.get() != 0 )
		std::cout << "  - Average inter-character space : " << *averageSpaceBetweenCharacters_ << " pixels" << std::endl;

	if ( averageCharacterHeight_.get() != 0 )
		std::cout << "  - Average character height      : " << *averageCharacterHeight_ << " pixels" << std::endl;

	if ( averageCharacterWidth_.get() != 0 )
		std::cout << "  - Average character width       : " << *averageCharacterWidth_ << " pixels" << std::endl;

	if ( averagingFilteringTime_.get() != 0 )
		std::cout << "  - Averaging filtering time      : " << *averagingFilteringTime_ << " s" << std::endl;

	if ( globalThresholdingTime_.get() != 0 )
		std::cout << "  - Global thresholding time      : " << *globalThresholdingTime_ << " s" << std::endl;

	if ( templateFilteringTime_.get() != 0 )
		std::cout << "  - Template filtering time       : " << *templateFilteringTime_ << " s" << std::endl;

	if ( segmentationTime_.get() != 0 )
		std::cout << "  - Segmentation time             : " << *segmentationTime_ << " s" << std::endl;

	if ( patternsBuildingTime_.get() != 0 )
		std::cout << "  - Patterns building time        : " << *patternsBuildingTime_ << " s" << std::endl;

	if ( skeletonizationTime_.get() != 0 )
		std::cout << "  - Skeletonization time          : " << *skeletonizationTime_ << " s" << std::endl;

	if ( slantingCorrectionTime_.get() != 0 )
		std::cout << "  - Slanting correction time      : " << *slantingCorrectionTime_ << " s" << std::endl;

	std::cout << "  - Total elapsed time            : " << totalTime_ << " s" << std::endl;
}


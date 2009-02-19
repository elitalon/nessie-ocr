/// @file
/// @brief Definition of PreprocessorStatistics class

#include "PreprocessorStatistics.hpp"
#include <iostream>


PreprocessorStatistics::PreprocessorStatistics ()
:	Statistics(),	// Invoke base class constructor
	clipSize_(0),
	optimalThreshold_(0),
	globalThresholdingTime_(0),
	templateFilteringTime_(0),
	averagingFilteringTime_(0),
	thinningTime_(0),
	nRegionsBeforeMerging_(0),
	nLineDelimiters_(0),
	nRegionsAfterMerging_(0),
	regionsExtractionTime_(0),
	slantAngleEstimation_(0),
	slantingCorrectionTime_(0),
	spacesBetweenWords_(0),
	meanInterRegionSpace_(0),
	spacesLocationFindingTime_(0)
{};


PreprocessorStatistics::PreprocessorStatistics (const PreprocessorStatistics& statistics)
:	Statistics(statistics),	// Invoke base class copy constructor
	clipSize_(0),
	optimalThreshold_(0),
	globalThresholdingTime_(0),
	templateFilteringTime_(0),
	averagingFilteringTime_(0),
	thinningTime_(0),
	nRegionsBeforeMerging_(0),
	nLineDelimiters_(0),
	nRegionsAfterMerging_(0),
	regionsExtractionTime_(0),
	slantAngleEstimation_(0),
	slantingCorrectionTime_(0),
	spacesBetweenWords_(0),
	meanInterRegionSpace_(0),
	spacesLocationFindingTime_(0)
{
	if ( statistics.clipSize_.get() != 0 )
		clipSize_.reset(new unsigned int(*statistics.clipSize_.get()));

	if ( statistics.optimalThreshold_.get() != 0 )
		optimalThreshold_.reset(new unsigned char(*statistics.optimalThreshold_.get()));

	if ( statistics.globalThresholdingTime_.get() != 0 )
		globalThresholdingTime_.reset(new double(*statistics.globalThresholdingTime_.get()));

	if ( statistics.templateFilteringTime_.get() != 0 )
		templateFilteringTime_.reset(new double(*statistics.templateFilteringTime_.get()));

	if ( statistics.averagingFilteringTime_.get() != 0 )
		averagingFilteringTime_.reset(new double(*statistics.averagingFilteringTime_.get()));

	if ( statistics.thinningTime_.get() != 0 )
		thinningTime_.reset(new double(*statistics.thinningTime_.get()));

	if ( statistics.nRegionsBeforeMerging_.get() != 0 )
		nRegionsBeforeMerging_.reset(new unsigned int(*statistics.nRegionsBeforeMerging_.get()));

	if ( statistics.nLineDelimiters_.get() != 0 )
		nLineDelimiters_.reset(new unsigned int(*statistics.nLineDelimiters_.get()));

	if ( statistics.nRegionsAfterMerging_.get() != 0 )
		nRegionsAfterMerging_.reset(new unsigned int(*statistics.nRegionsAfterMerging_.get()));

	if ( statistics.regionsExtractionTime_.get() != 0 )
		regionsExtractionTime_.reset(new double(*statistics.regionsExtractionTime_.get()));

	if ( statistics.slantAngleEstimation_.get() != 0 )
		slantAngleEstimation_.reset(new double(*statistics.slantAngleEstimation_.get()));

	if ( statistics.slantingCorrectionTime_.get() != 0 )
		slantingCorrectionTime_.reset(new double(*statistics.slantingCorrectionTime_.get()));

	if ( statistics.spacesBetweenWords_.get() != 0 )
		spacesBetweenWords_.reset(new unsigned int(*statistics.spacesBetweenWords_.get()));

	if ( statistics.meanInterRegionSpace_.get() != 0 )
		meanInterRegionSpace_.reset(new double(*statistics.meanInterRegionSpace_.get()));

	if ( statistics.spacesLocationFindingTime_.get() != 0 )
		spacesLocationFindingTime_.reset(new double(*statistics.spacesLocationFindingTime_.get()));
};


PreprocessorStatistics::~PreprocessorStatistics () {};


PreprocessorStatistics& PreprocessorStatistics::operator= (const PreprocessorStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.clipSize_.get() != 0 )
		clipSize_.reset(new unsigned int(*statistics.clipSize_.get()));

	if ( statistics.optimalThreshold_.get() != 0 )
		optimalThreshold_.reset(new unsigned char(*statistics.optimalThreshold_.get()));

	if ( statistics.globalThresholdingTime_.get() != 0 )
		globalThresholdingTime_.reset(new double(*statistics.globalThresholdingTime_.get()));

	if ( statistics.templateFilteringTime_.get() != 0 )
		templateFilteringTime_.reset(new double(*statistics.templateFilteringTime_.get()));

	if ( statistics.averagingFilteringTime_.get() != 0 )
		averagingFilteringTime_.reset(new double(*statistics.averagingFilteringTime_.get()));

	if ( statistics.thinningTime_.get() != 0 )
		thinningTime_.reset(new double(*statistics.thinningTime_.get()));

	if ( statistics.nRegionsBeforeMerging_.get() != 0 )
		nRegionsBeforeMerging_.reset(new unsigned int(*statistics.nRegionsBeforeMerging_.get()));

	if ( statistics.nLineDelimiters_.get() != 0 )
		nLineDelimiters_.reset(new unsigned int(*statistics.nLineDelimiters_.get()));

	if ( statistics.nRegionsAfterMerging_.get() != 0 )
		nRegionsAfterMerging_.reset(new unsigned int(*statistics.nRegionsAfterMerging_.get()));

	if ( statistics.regionsExtractionTime_.get() != 0 )
		regionsExtractionTime_.reset(new double(*statistics.regionsExtractionTime_.get()));

	if ( statistics.slantAngleEstimation_.get() != 0 )
		slantAngleEstimation_.reset(new double(*statistics.slantAngleEstimation_.get()));

	if ( statistics.slantingCorrectionTime_.get() != 0 )
		slantingCorrectionTime_.reset(new double(*statistics.slantingCorrectionTime_.get()));

	if ( statistics.spacesBetweenWords_.get() != 0 )
		spacesBetweenWords_.reset(new unsigned int(*statistics.spacesBetweenWords_.get()));

	if ( statistics.meanInterRegionSpace_.get() != 0 )
		meanInterRegionSpace_.reset(new double(*statistics.meanInterRegionSpace_.get()));

	if ( statistics.spacesLocationFindingTime_.get() != 0 )
		spacesLocationFindingTime_.reset(new double(*statistics.spacesLocationFindingTime_.get()));

	return *this;
};


void PreprocessorStatistics::print () const
{
	std::cout << std::endl << "Preprocessing stage statistics" << std::endl;
	
	if ( clipSize_.get() != 0 )
		std::cout << "  - Number of pixels             : " << *clipSize_.get() << std::endl;

	if ( averagingFilteringTime_.get() != 0 )
		std::cout << "  - Averaging filtering time     : " << *averagingFilteringTime_.get() << std::endl;

	if ( optimalThreshold_.get() != 0 )
		std::cout << "  - Optimal threshold            : " << static_cast<unsigned int>(*optimalThreshold_) << std::endl;

	if ( globalThresholdingTime_.get() != 0 )
		std::cout << "  - Global thresholding time     : " << *globalThresholdingTime_.get() << std::endl;

	if ( templateFilteringTime_.get() != 0 )
		std::cout << "  - Template filtering time      : " << *templateFilteringTime_.get() << std::endl;

	if ( thinningTime_.get() != 0 )
		std::cout << "  - Thinning time                : " << *thinningTime_.get() << std::endl;

	if ( nRegionsAfterMerging_.get() != 0 )
		std::cout << "  - Regions before merging       : " << *nRegionsBeforeMerging_.get() << std::endl;

	if ( nLineDelimiters_.get() != 0 )
		std::cout << "  - Line delimiters              : " << *nLineDelimiters_.get() << std::endl;

	if ( nRegionsBeforeMerging_.get() != 0 )
		std::cout << "  - Regions after merging        : " << *nRegionsAfterMerging_.get() << std::endl;

	if ( regionsExtractionTime_.get() != 0 )
		std::cout << "  - Regions extraction time      : " << *regionsExtractionTime_.get() << std::endl;

	if ( slantAngleEstimation_.get() != 0 )
		std::cout << "  - Slant angle estimation       : " << *slantAngleEstimation_.get() << std::endl;

	if ( slantingCorrectionTime_.get() != 0 )
		std::cout << "  - Slanting correction time     : " << *slantingCorrectionTime_.get() << std::endl;

	if ( spacesBetweenWords_.get() != 0 )
		std::cout << "  - Spaces between words found   : " << *spacesBetweenWords_.get() << std::endl;

	if ( meanInterRegionSpace_.get() != 0 )
		std::cout << "  - Mean inter-region space      : " << *meanInterRegionSpace_.get() << std::endl;

	if ( spacesLocationFindingTime_.get() != 0 )
		std::cout << "  - Spaces location finding time : " << *spacesLocationFindingTime_.get() << std::endl;

	std::cout << "  - Total elapsed time           : " << totalTime_ << std::endl;
};


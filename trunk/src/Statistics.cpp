/// @file
/// @brief Definition of Statistics class

#include "Statistics.hpp"
#include <iostream>


Statistics::Statistics ()
:	totalTime_(0.0)
{};


Statistics::~Statistics () {};




PreprocessorStatistics::PreprocessorStatistics ()
:	Statistics(),	// Invoke base class constructor
	clipSize_(0),
	optimalThreshold_(0),
	globalThresholdingTime_(0),
	templateFilteringTime_(0),
	averagingFilteringTime_(0),
	thinningTime_(0),
	regionsExtractionTime_(0),
	nRegionsBeforeMerging_(0),
	nRegionsAfterMerging_(0),
	nLineDelimiters_(0),
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
	regionsExtractionTime_(0),
	nRegionsBeforeMerging_(0),
	nRegionsAfterMerging_(0),
	nLineDelimiters_(0),
	slantAngleEstimation_(0),
	slantingCorrectionTime_(0),
	spacesBetweenWords_(0),
	meanInterRegionSpace_(0),
	spacesLocationFindingTime_(0)
{
	if ( statistics.clipSize_ != 0 )
		clipSize_ = new unsigned int(*statistics.clipSize_);

	if ( statistics.optimalThreshold_ != 0 )
		optimalThreshold_ = new unsigned char(*statistics.optimalThreshold_);

	if ( statistics.globalThresholdingTime_ != 0 )
		globalThresholdingTime_ = new double(*statistics.globalThresholdingTime_);

	if ( statistics.templateFilteringTime_ != 0 )
		templateFilteringTime_ = new double(*statistics.templateFilteringTime_);

	if ( statistics.averagingFilteringTime_ != 0 )
		averagingFilteringTime_ = new double(*statistics.averagingFilteringTime_);

	if ( statistics.thinningTime_ != 0 )
		thinningTime_ = new double(*statistics.thinningTime_);

	if ( statistics.regionsExtractionTime_ != 0 )
		regionsExtractionTime_ = new double(*statistics.regionsExtractionTime_);

	if ( statistics.nRegionsBeforeMerging_ != 0 )
		nRegionsBeforeMerging_ = new unsigned int(*statistics.nRegionsBeforeMerging_);

	if ( statistics.nRegionsAfterMerging_ != 0 )
		nRegionsAfterMerging_ = new unsigned int(*statistics.nRegionsAfterMerging_);

	if ( statistics.nLineDelimiters_ != 0 )
		nLineDelimiters_ = new unsigned int(*statistics.nLineDelimiters_);

	if ( statistics.slantAngleEstimation_ != 0 )
		slantAngleEstimation_ = new double(*statistics.slantAngleEstimation_);

	if ( statistics.slantingCorrectionTime_ != 0 )
		slantingCorrectionTime_ = new double(*statistics.slantingCorrectionTime_);

	if ( statistics.spacesBetweenWords_ != 0 )
		spacesBetweenWords_ = new unsigned int(*statistics.spacesBetweenWords_);

	if ( statistics.meanInterRegionSpace_ != 0 )
		meanInterRegionSpace_ = new double(*statistics.meanInterRegionSpace_);

	if ( statistics.spacesLocationFindingTime_ != 0 )
		spacesLocationFindingTime_ = new double(*statistics.spacesLocationFindingTime_);

};


PreprocessorStatistics::~PreprocessorStatistics ()
{
	delete clipSize_;
	delete optimalThreshold_;
	delete globalThresholdingTime_;
	delete templateFilteringTime_;
	delete averagingFilteringTime_;
	delete thinningTime_;		
	delete regionsExtractionTime_;
	delete nRegionsBeforeMerging_;
	delete nRegionsAfterMerging_;
	delete nLineDelimiters_;
	delete slantAngleEstimation_;
	delete slantingCorrectionTime_;
	delete spacesBetweenWords_;
	delete meanInterRegionSpace_;
	delete spacesLocationFindingTime_;
};


PreprocessorStatistics& PreprocessorStatistics::operator= (const PreprocessorStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.clipSize_ != 0 )
	{
		unsigned int* tmp = new unsigned int(*statistics.clipSize_);
		delete clipSize_;
		clipSize_ = tmp;
	}

	if ( statistics.optimalThreshold_ != 0 )
	{
		unsigned char* tmp = new unsigned char(*statistics.optimalThreshold_);
		delete optimalThreshold_;
		optimalThreshold_ = tmp;
	}

	if ( statistics.globalThresholdingTime_ != 0 )
	{
		double* tmp = new double(*statistics.globalThresholdingTime_);
		delete globalThresholdingTime_;
		globalThresholdingTime_ = tmp;
	}

	if ( statistics.templateFilteringTime_ != 0 )
	{
		double* tmp = new double(*statistics.templateFilteringTime_);
		delete templateFilteringTime_;
		templateFilteringTime_ = tmp;
	}

	if ( statistics.averagingFilteringTime_ != 0 )
	{
		double* tmp = new double(*statistics.averagingFilteringTime_);
		delete averagingFilteringTime_;
		averagingFilteringTime_ = tmp;
	}

	if ( statistics.thinningTime_ != 0 )
	{
		double* tmp = new double(*statistics.thinningTime_);
		delete thinningTime_;
		thinningTime_ = tmp;
	}

	if ( statistics.regionsExtractionTime_ != 0 )
	{
		double* tmp = new double(*statistics.regionsExtractionTime_);
		delete regionsExtractionTime_;
		regionsExtractionTime_ = tmp;
	}

	if ( statistics.nRegionsBeforeMerging_ != 0 )
	{
		unsigned int* tmp = new unsigned int(*statistics.nRegionsBeforeMerging_);
		delete nRegionsBeforeMerging_;
		nRegionsBeforeMerging_ = tmp;
	}

	if ( statistics.nRegionsAfterMerging_ != 0 )
	{
		unsigned int* tmp = new unsigned int(*statistics.nRegionsAfterMerging_);
		delete nRegionsAfterMerging_;
		nRegionsAfterMerging_ = tmp;
	}

	if ( statistics.nLineDelimiters_ != 0 )
	{
		unsigned int* tmp = new unsigned int(*statistics.nLineDelimiters_);
		delete nLineDelimiters_;
		nLineDelimiters_ = tmp;
	}

	if ( statistics.slantAngleEstimation_ != 0 )
	{
		double* tmp = new double(*statistics.slantAngleEstimation_);
		delete slantAngleEstimation_;
		slantAngleEstimation_ = tmp;
	}

	if ( statistics.slantingCorrectionTime_ != 0 )
	{
		double* tmp = new double(*statistics.slantingCorrectionTime_);
		delete slantingCorrectionTime_;
		slantingCorrectionTime_ = tmp;
	}

	if ( statistics.spacesBetweenWords_ != 0 )
	{
		unsigned int* tmp = new unsigned int(*statistics.spacesBetweenWords_);
		delete spacesBetweenWords_;
		spacesBetweenWords_ = tmp;
	}

	if ( statistics.meanInterRegionSpace_ != 0 )
	{
		double* tmp = new double(*statistics.meanInterRegionSpace_);
		delete meanInterRegionSpace_;
		meanInterRegionSpace_ = tmp;
	}

	if ( statistics.spacesLocationFindingTime_ != 0 )
	{
		double* tmp = new double(*statistics.spacesLocationFindingTime_);
		delete spacesLocationFindingTime_;
		spacesLocationFindingTime_ = tmp;
	}

	return *this;
};


void PreprocessorStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Preprocessing stage statistics" << std::endl;
	if ( clipSize_ != 0 )
		std::cout << "  - Number of pixels             : " << *clipSize_ << std::endl;

	if ( averagingFilteringTime_ != 0 )
		std::cout << "  - Averaging filtering time     : " << *averagingFilteringTime_ << std::endl;

	if ( optimalThreshold_ != 0 )
		std::cout << "  - Optimal threshold            : " << static_cast<unsigned int>(*optimalThreshold_) << std::endl;

	if ( globalThresholdingTime_ != 0 )
		std::cout << "  - Global thresholding time     : " << *globalThresholdingTime_ << std::endl;

	if ( templateFilteringTime_ != 0 )
		std::cout << "  - Template filtering time      : " << *templateFilteringTime_ << std::endl;

	if ( thinningTime_ != 0 )
		std::cout << "  - Thinning time                : " << *thinningTime_ << std::endl;

	if ( regionsExtractionTime_ != 0 )
		std::cout << "  - Regions extraction time      : " << *regionsExtractionTime_ << std::endl;

	if ( nRegionsAfterMerging_ != 0 )
		std::cout << "  - Regions before merging       : " << *nRegionsBeforeMerging_ << std::endl;

	if ( nRegionsBeforeMerging_ != 0 )
		std::cout << "  - Regions after merging        : " << *nRegionsAfterMerging_ << std::endl;

	if ( nLineDelimiters_ != 0 )
		std::cout << "  - Line delimiters              : " << *nLineDelimiters_ << std::endl;

	if ( slantAngleEstimation_ != 0 )
		std::cout << "  - Slant angle estimation       : " << *slantAngleEstimation_ << std::endl;

	if ( slantingCorrectionTime_ != 0 )
		std::cout << "  - Slanting correction time     : " << *slantingCorrectionTime_ << std::endl;

	if ( spacesBetweenWords_ != 0 )
		std::cout << "  - Spaces between words found   : " << *spacesBetweenWords_ << std::endl;

	if ( meanInterRegionSpace_ != 0 )
		std::cout << "  - Mean inter-region space      : " << *meanInterRegionSpace_ << std::endl;

	if ( spacesLocationFindingTime_ != 0 )
		std::cout << "  - Spaces location finding time : " << *spacesLocationFindingTime_ << std::endl;

	std::cout << "  - Total elapsed time           : " << totalTime_ << std::endl;
};




FeatureExtractionStatistics::FeatureExtractionStatistics () {};


FeatureExtractionStatistics::~FeatureExtractionStatistics () {};


void FeatureExtractionStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Feature extraction stage statistics" << std::endl;
	std::cout << "  - Total elapsed time  : " << totalTime_ << std::endl;
};




ClassificationStatistics::ClassificationStatistics () {};


ClassificationStatistics::~ClassificationStatistics () {};


void ClassificationStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Classification stage statistics" << std::endl;
	std::cout << "  - Total elapsed time  : " << totalTime_ << std::endl;
};


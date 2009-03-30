/// @file
/// @brief Definition of PreprocessorStatistics class

#include "PreprocessorStatistics.hpp"
#include <iostream>


PreprocessorStatistics::PreprocessorStatistics ()
:	Statistics(),	// Invoke base class constructor
	clipSize_(0),
	optimalThreshold_(0),
	nCharacters_(0),
	nLines_(0),
	slantAngle_(0),
	averageInterCharacterSpace_(0),
	averageCharacterHeight_(0),
	globalThresholdingTime_(0),
	templateFilteringTime_(0),
	averagingFilteringTime_(0),
	segmentationTime_(0),
	thinningTime_(0),
	slantingCorrectionTime_(0),
	patternsBuildingTime_(0)
{};


PreprocessorStatistics::PreprocessorStatistics (const PreprocessorStatistics& statistics)
:	Statistics(statistics),	// Invoke base class copy constructor
	clipSize_(0),
	optimalThreshold_(0),
	nCharacters_(0),
	nLines_(0),
	slantAngle_(0),
	averageInterCharacterSpace_(0),
	averageCharacterHeight_(0),
	globalThresholdingTime_(0),
	templateFilteringTime_(0),
	averagingFilteringTime_(0),
	segmentationTime_(0),
	thinningTime_(0),
	slantingCorrectionTime_(0),
	patternsBuildingTime_(0)
{
	if ( statistics.clipSize_.get() != 0 )
		clipSize_.reset(new unsigned int(*statistics.clipSize_.get()));

	if ( statistics.optimalThreshold_.get() != 0 )
		optimalThreshold_.reset(new unsigned char(*statistics.optimalThreshold_.get()));

	if ( statistics.nCharacters_.get() != 0 )
		nCharacters_.reset(new unsigned int(*statistics.nCharacters_.get()));

	if ( statistics.nLines_.get() != 0 )
		nLines_.reset(new unsigned int(*statistics.nLines_.get()));

	if ( statistics.slantAngle_.get() != 0 )
		slantAngle_.reset(new double(*statistics.slantAngle_.get()));

	if ( statistics.averageInterCharacterSpace_.get() != 0 )
		averageInterCharacterSpace_.reset(new double(*statistics.averageInterCharacterSpace_.get()));
	
	if ( statistics.averageCharacterHeight_.get() != 0 )
		averageCharacterHeight_.reset(new double(*statistics.averageCharacterHeight_.get()));

	if ( statistics.globalThresholdingTime_.get() != 0 )
		globalThresholdingTime_.reset(new double(*statistics.globalThresholdingTime_.get()));

	if ( statistics.templateFilteringTime_.get() != 0 )
		templateFilteringTime_.reset(new double(*statistics.templateFilteringTime_.get()));

	if ( statistics.averagingFilteringTime_.get() != 0 )
		averagingFilteringTime_.reset(new double(*statistics.averagingFilteringTime_.get()));

	if ( statistics.segmentationTime_.get() != 0 )
		segmentationTime_.reset(new double(*statistics.segmentationTime_.get()));

	if ( statistics.thinningTime_.get() != 0 )
		thinningTime_.reset(new double(*statistics.thinningTime_.get()));

	if ( statistics.slantingCorrectionTime_.get() != 0 )
		slantingCorrectionTime_.reset(new double(*statistics.slantingCorrectionTime_.get()));

	if ( statistics.patternsBuildingTime_.get() != 0 )
		patternsBuildingTime_.reset( new double (*statistics.patternsBuildingTime_.get() ));
};


PreprocessorStatistics::~PreprocessorStatistics () {};


PreprocessorStatistics& PreprocessorStatistics::operator= (const PreprocessorStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.clipSize_.get() != 0 )
		clipSize_.reset(new unsigned int(*statistics.clipSize_.get()));

	if ( statistics.optimalThreshold_.get() != 0 )
		optimalThreshold_.reset(new unsigned char(*statistics.optimalThreshold_.get()));

	if ( statistics.nCharacters_.get() != 0 )
		nCharacters_.reset(new unsigned int(*statistics.nCharacters_.get()));

	if ( statistics.nLines_.get() != 0 )
		nLines_.reset(new unsigned int(*statistics.nLines_.get()));

	if ( statistics.slantAngle_.get() != 0 )
		slantAngle_.reset(new double(*statistics.slantAngle_.get()));

	if ( statistics.averageInterCharacterSpace_.get() != 0 )
		averageInterCharacterSpace_.reset(new double(*statistics.averageInterCharacterSpace_.get()));

	if ( statistics.averageCharacterHeight_.get() != 0 )
		averageCharacterHeight_.reset(new double(*statistics.averageCharacterHeight_.get()));

	if ( statistics.globalThresholdingTime_.get() != 0 )
		globalThresholdingTime_.reset(new double(*statistics.globalThresholdingTime_.get()));

	if ( statistics.templateFilteringTime_.get() != 0 )
		templateFilteringTime_.reset(new double(*statistics.templateFilteringTime_.get()));

	if ( statistics.averagingFilteringTime_.get() != 0 )
		averagingFilteringTime_.reset(new double(*statistics.averagingFilteringTime_.get()));

	if ( statistics.segmentationTime_.get() != 0 )
		segmentationTime_.reset(new double(*statistics.segmentationTime_.get()));

	if ( statistics.thinningTime_.get() != 0 )
		thinningTime_.reset(new double(*statistics.thinningTime_.get()));

	if ( statistics.slantingCorrectionTime_.get() != 0 )
		slantingCorrectionTime_.reset(new double(*statistics.slantingCorrectionTime_.get()));

	if ( statistics.patternsBuildingTime_.get() != 0 )
		patternsBuildingTime_.reset( new double (*statistics.patternsBuildingTime_.get() ));

	return *this;
};


void PreprocessorStatistics::print () const
{
	std::cout << std::endl << "Preprocessing stage statistics" << std::endl;
	
	if ( clipSize_.get() != 0 )
		std::cout << "  - Clip size                     : " << *clipSize_.get() << " pixels" << std::endl;

	if ( optimalThreshold_.get() != 0 )
		std::cout << "  - Optimal threshold             : " << static_cast<unsigned int>(*optimalThreshold_) << std::endl;

	if ( nCharacters_.get() != 0 )
		std::cout << "  - Number of characters          : " << *nCharacters_.get() << std::endl;

	if ( nLines_.get() != 0 )
		std::cout << "  - Number of lines               : " << *nLines_.get() << std::endl;

	if ( slantAngle_.get() != 0 )
		std::cout << "  - Slant angle                   : " << *slantAngle_.get() << " degrees" << std::endl;

	if ( averageInterCharacterSpace_.get() != 0 )
		std::cout << "  - Average inter-character space : " << *averageInterCharacterSpace_.get() << " pixels" << std::endl;

	if ( averageCharacterHeight_.get() != 0 )
		std::cout << "  - Average character height      : " << *averageCharacterHeight_.get() << " pixels" << std::endl;

	if ( globalThresholdingTime_.get() != 0 )
		std::cout << "  - Global thresholding time      : " << *globalThresholdingTime_.get() << " s" << std::endl;

	if ( averagingFilteringTime_.get() != 0 )
		std::cout << "  - Averaging filtering time      : " << *averagingFilteringTime_.get() << " s" << std::endl;

	if ( templateFilteringTime_.get() != 0 )
		std::cout << "  - Template filtering time       : " << *templateFilteringTime_.get() << " s" << std::endl;

	if ( segmentationTime_.get() != 0 )
		std::cout << "  - Segmentation time             : " << *segmentationTime_.get() << " s" << std::endl;

	if ( thinningTime_.get() != 0 )
		std::cout << "  - Thinning time                 : " << *thinningTime_.get() << " s" << std::endl;

	if ( slantingCorrectionTime_.get() != 0 )
		std::cout << "  - Slanting correction time      : " << *slantingCorrectionTime_.get() << " s" << std::endl;

	if ( patternsBuildingTime_.get() != 0 )
		std::cout << "  - Patterns building time        : " << *patternsBuildingTime_.get() << " s" << std::endl;

	std::cout << "  - Total elapsed time            : " << totalTime_ << " s" << std::endl;
};


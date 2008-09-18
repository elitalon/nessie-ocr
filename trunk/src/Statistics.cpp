#include "Statistics.h"


///
/// Initializes a Statistics object with timers set to 0
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
Statistics::Statistics ()
	: nWords(0),
	wordRates(list<WordRate>()),
	noiseRemovalTime(0.0),
	grayscaleConversionTime(0.0),
	floodFillingTime(0.0),
	thresholdingTime(0.0),
	featureVectorsBuildingTime(0.0),
	charactersExtractionTime(0.0)
{
	this->preprocessingTime = this->grayscaleConversionTime + this->noiseRemovalTime;
	this->segmentationTime = this->thresholdingTime + this->floodFillingTime;
	this->classificationTime = this->featureVectorsBuildingTime + this->charactersExtractionTime;
};


///
/// Destroys a Statistics object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-17
///
Statistics::~Statistics ()
{
	
};

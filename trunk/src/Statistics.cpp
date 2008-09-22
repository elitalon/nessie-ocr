#include "Statistics.h"


///
/// @details Initializes a Statistics object with timers set to 0
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
///
Statistics::Statistics () : nWords(0), wordRates(vector<WordRate>(0)), noiseRemovalTime(0.0), grayscaleConversionTime(0.0),
	floodFillingTime(0.0), thresholdingTime(0.0), featureVectorsBuildingTime(0.0), charactersExtractionTime(0.0)
{
	this->preprocessingTime		= this->grayscaleConversionTime		+ this->noiseRemovalTime;
	this->segmentationTime		= this->thresholdingTime			+ this->floodFillingTime;
	this->classificationTime	= this->featureVectorsBuildingTime	+ this->charactersExtractionTime;
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

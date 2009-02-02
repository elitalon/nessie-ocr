/// @file
/// @brief Implementation of the class Recognizer

#include "Recognizer.hpp"
#include "FeatureExtractor.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"
#include <vector>
#include <boost/timer.hpp>


Recognizer::Recognizer ()
:	text_(),
	preprocessingStatistics_(0),
	featureExtractorStatistics_(0),
	classificationStatistics_(0)
{};


Recognizer::~Recognizer ()
{
	delete preprocessingStatistics_;
	delete featureExtractorStatistics_;
	delete classificationStatistics_;
};


/// @details	This method executes the recognition process in four stages: preprocessing, feature extraction, classification and postprocessing.
///
/// @details	As the first important step, image and data <em>preprocessing</em> serve the purpose of extracting regions of interest, enhancing and cleaning up
/// the images, so that they can be directly and efficiently processed by the feature extraction stage.
void Recognizer::extractText (const Clip& pressClip)
{
	// Preprocessing stage
	Preprocessor preprocessor(pressClip);
	preprocessor.applyAveragingFilters();
	preprocessor.applyGlobalThresholding();
	preprocessor.applyTemplateFilters();
	preprocessor.extractRegions();
	preprocessor.correctSlanting();

	// Feature extraction stage
	FeatureExtractor featureExtractor(preprocessor.regions());

	// Classification stage
	
	// Postprocessing stage
	std::vector<unsigned int> spaceLocations = preprocessor.findSpacesBetweenWords();
	
	// Gather statistics
	preprocessingStatistics_	= new PreprocessorStatistics(preprocessor.statistics());
	featureExtractorStatistics_	= new FeatureExtractorStatistics(featureExtractor.statistics());
	classificationStatistics_	= new ClassificationStatistics();
};


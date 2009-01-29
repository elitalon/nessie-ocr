/// @file
/// @brief Implementation of the class Recognizer

#include "Recognizer.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"


Recognizer::Recognizer ()
	:	text_(),
		preprocessingStatistics_(0),
		featureExtractionStatistics_(0),
		classificationStatistics_(0)
{};


Recognizer::~Recognizer ()
{
	delete preprocessingStatistics_;
	delete featureExtractionStatistics_;
	delete classificationStatistics_;
};


/// @details This method executes the recognition process in four stages: preprocessing, feature extraction, classification and postprocessing.
///
/// As the first important step, image and data <em>preprocessing</em> serve the purpose of extracting regions of interest, enhancing and cleaning up
/// the images, so that they can be directly and efficiently processed by the feature extraction stage.
void Recognizer::extractText (const Clip& pressClip)
{
	// Preprocessing stage
	Preprocessor preprocessor(pressClip);
	//preprocessor.applyAveragingFilters();
	preprocessor.applyGlobalThresholding();
	preprocessor.applyTemplateFilters();
	preprocessor.extractRegions();
	preprocessor.correctSlanting();
	std::vector<unsigned int> spaceLocations = preprocessor.findSpacesBetweenWords();
	preprocessingStatistics_ = new PreprocessorStatistics(preprocessor.statistics());


	// Feature extraction stage
	featureExtractionStatistics_ = new FeatureExtractionStatistics();

	// Classification stage
	classificationStatistics_ = new ClassificationStatistics();
};


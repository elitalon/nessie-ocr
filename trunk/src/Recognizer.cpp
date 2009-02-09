/// @file
/// @brief Implementation of the class Recognizer

#include "Recognizer.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"
#include "FeatureExtractor.hpp"
#include <vector>
#include <string>
#include <sstream>


Recognizer::Recognizer ()
:	text_(Text()),
	preprocessingStatistics_(0),
	featureExtractorStatistics_(0),
	classifierStatistics_(0)
{};


Recognizer::~Recognizer ()
{
	delete preprocessingStatistics_;
	delete featureExtractorStatistics_;
	delete classifierStatistics_;
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
	featureExtractor.computeMoments();
	std::vector<Pattern> patterns(featureExtractor.patterns());
	
	unsigned int patternNo = 0;
	for ( std::vector<Pattern>::iterator i = patterns.begin(); i != patterns.end(); ++i )
	{
		std::ostringstream ostr;
		ostr << patternNo++;
		std::string filename("pattern");
		filename.append(ostr.str().append(".bmp"));
		(*i).writeToOutputImage(filename,true);
	}

	// Classification stage
	
	// Postprocessing stage
	std::vector<unsigned int> spaceLocations = preprocessor.findSpacesBetweenWords();
	
	// Gather statistics
	preprocessingStatistics_	= new PreprocessorStatistics(preprocessor.statistics());
	featureExtractorStatistics_	= new FeatureExtractorStatistics(featureExtractor.statistics());
	classifierStatistics_		= new ClassifierStatistics();
};


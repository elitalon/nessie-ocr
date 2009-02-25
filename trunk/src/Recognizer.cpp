/// @file
/// @brief Implementation of Recognizer class

#include "Recognizer.hpp"
#include "NessieException.hpp"
#include "Dataset.hpp"
#include "Clip.hpp"
#include "Statistics.hpp"
#include "Preprocessor.hpp"
#include "FeatureExtractor.hpp"
#include "Classifier.hpp"
#include <vector>
#include <string>
#include <sstream>


Recognizer::Recognizer (const Dataset* dataset)
:	dataset_(dataset),
	text_(),
	preprocessingStatistics_(0),
	featureExtractorStatistics_(0),
	classifierStatistics_(0)
{
	if ( dataset_ == 0 )
		throw NessieException ("Recognizer::Recognizer() : A null pointer was passed to the constructor. You must provide an instantiated Dataset object.");
};


Recognizer::~Recognizer() {};


/// @details	This method executes the recognition process in four stages: preprocessing, feature extraction, classification and postprocessing.
///
/// @details	As the first important step, image and data <em>preprocessing</em> serve the purpose of extracting regions of interest, enhancing and cleaning up
/// the images, so that they can be directly and efficiently processed by the feature extraction stage.
void Recognizer::extractText (const Clip& pressClip, const ClassificationParadigm& paradigm)
{
	Preprocessor preprocessor(pressClip);
	preprocessor.applyAveragingFilters();
	preprocessor.applyGlobalThresholding();
	preprocessor.applyTemplateFilters();
	preprocessor.extractRegions();
	preprocessor.correctSlanting();

	FeatureExtractor featureExtractor(preprocessor.regions());
	featureExtractor.computeMoments(dataset_->features());
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

	Classifier classifier(featureExtractor.featureVectors());
	classifier.classify(paradigm, dataset_);

	std::vector<unsigned int> spaceLocations = preprocessor.findSpacesBetweenWords();
	
	try
	{
		preprocessingStatistics_.reset(	new PreprocessorStatistics(preprocessor.statistics()) );
		featureExtractorStatistics_.reset( new FeatureExtractorStatistics(featureExtractor.statistics()) );
		classifierStatistics_.reset( new ClassifierStatistics(classifier.statistics()) );
	}
	catch (...) {}
};


void Recognizer::printStatistics () const
{
	try
	{
		if ( preprocessingStatistics_.get() != 0 )
			preprocessingStatistics_->print();

		if ( featureExtractorStatistics_.get() != 0 )
			featureExtractorStatistics_->print();

		if ( classifierStatistics_.get() != 0 )
			classifierStatistics_->print();
	}
	catch (...) {}	// An error while printing the statistics should not stop the program.
};


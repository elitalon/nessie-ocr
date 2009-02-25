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
#include <string>
#include <sstream>


Recognizer::Recognizer (const Dataset* dataset)
:	dataset_(dataset),
	regions_(0),
	spaceLocations_(0),
	patterns_(0),
	featureVectors_(0),
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
	doPreprocessing(pressClip);
	doFeatureExtraction();
	doClassification(paradigm);
};


void Recognizer::doPreprocessing (const Clip& pressClip)
{
	regions_.clear();
	spaceLocations_.clear();

	Preprocessor preprocessor(pressClip);
	preprocessor.applyAveragingFilters();
	preprocessor.applyGlobalThresholding();
	preprocessor.applyTemplateFilters();
	preprocessor.extractRegions();
	preprocessor.correctSlanting();

	regions_ = preprocessor.regions();
	spaceLocations_ = preprocessor.findSpacesBetweenWords();

	try
	{
		preprocessingStatistics_.reset(	new PreprocessorStatistics(preprocessor.statistics()) );
	}
	catch(...) {}
};


void Recognizer::doFeatureExtraction ()
{
	patterns_.clear();
	featureVectors_.clear();

	FeatureExtractor featureExtractor(regions_);
	patterns_ = featureExtractor.patterns();
	featureExtractor.computeMoments(dataset_->features());
	featureVectors_ = featureExtractor.featureVectors();

	unsigned int patternNo = 0;
	for ( std::vector<Pattern>::iterator i = patterns_.begin(); i != patterns_.end(); ++i )
	{
		std::ostringstream ostr;
		ostr << patternNo++;
		std::string filename("pattern");
		filename.append(ostr.str().append(".bmp"));
		(*i).writeToOutputImage(filename,true);
	}

	try
	{
		featureExtractorStatistics_.reset( new FeatureExtractorStatistics(featureExtractor.statistics()) );
	}
	catch (...) {}
};


void Recognizer::doFeatureExtraction (const std::list<Region>& regions)
{
	regions_ = regions;
	doFeatureExtraction();
};


void Recognizer::doClassification (const ClassificationParadigm& paradigm)
{
	text_.clear();

	Classifier classifier(featureVectors_);
	classifier.classify(paradigm, dataset_);

	try
	{
		classifierStatistics_.reset( new ClassifierStatistics(classifier.statistics()) );
	}
	catch (...) {}
};


void Recognizer::doClassification (const std::vector<FeatureVector>& featureVectors, const ClassificationParadigm& paradigm)
{
	featureVectors_ = featureVectors;
	doClassification(paradigm);
};


void Recognizer::doPostprocessing ()
{
	;
};


void Recognizer::doPostprocessing (Text& text, const std::vector<unsigned int>& spaceLocations)
{
	text_ = text;
	spaceLocations_ = spaceLocations;
	doPostprocessing();
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


/// @file
/// @brief Implementation of Recognizer class

#include "Recognizer.hpp"
#include "NessieException.hpp"
#include "Dataset.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"
#include "FeatureExtractor.hpp"
#include "Classifier.hpp"
#include <string>
#include <iostream>
#include <boost/regex.hpp>


Recognizer::Recognizer (std::auto_ptr<Dataset>& dataset)
:	dataset_(dataset),
	spaceLocations_(0),
	patterns_(0),
	featureVectors_(0),
	characters_(0),
	text_(),
	preprocessingStatistics_(),
	featureExtractorStatistics_(),
	classifierStatistics_()
{
	if ( dataset_.get() == 0 )
		throw NessieException ("Recognizer::Recognizer() : A null pointer was passed to the constructor. You must provide an instantiated Dataset object.");
};

Recognizer::Recognizer (Dataset* dataset)
:	dataset_(dataset),
	spaceLocations_(0),
	patterns_(0),
	featureVectors_(0),
	characters_(0),
	text_(),
	preprocessingStatistics_(),
	featureExtractorStatistics_(),
	classifierStatistics_()
{
	if ( dataset_.get() == 0 )
		throw NessieException ("Recognizer::Recognizer() : A null pointer was passed to the constructor. You must provide an instantiated Dataset object.");

	dataset = 0;
};


Recognizer::~Recognizer() {};


void Recognizer::extractText (const Clip& pressClip, const ClassificationParadigm& paradigm)
{
	doPreprocessing(pressClip);
	doFeatureExtraction();
	doClassification(paradigm);
	doPostprocessing();
};


void Recognizer::doPreprocessing (const Clip& pressClip)
{
	patterns_.clear();
	spaceLocations_.clear();

	Preprocessor preprocessor(pressClip);
	preprocessor.removeNoiseByLinearFiltering();
	preprocessor.applyGlobalThresholding();
	preprocessor.removeNoiseByTemplateMatching();
	preprocessor.isolateRegions();
	preprocessor.correctSlanting();
	spaceLocations_ = preprocessor.findSpacesBetweenWords();
	text_.averageCharacterHeight(preprocessor.averageCharacterHeight());
	
	preprocessor.buildPatterns();
	preprocessor.skeletonizePatterns();
	patterns_ = preprocessor.patterns();

	preprocessingStatistics_ = preprocessor.statistics();
};


void Recognizer::doFeatureExtraction ()
{
	featureVectors_.clear();

	FeatureExtractor featureExtractor(patterns_);
	featureExtractor.computeMoments(dataset_->features());
	featureVectors_ = featureExtractor.featureVectors();

	featureExtractorStatistics_ = featureExtractor.statistics();
};


void Recognizer::doClassification (const ClassificationParadigm& paradigm)
{
	characters_.clear();

	Classifier classifier(featureVectors_);
	classifier.classify(paradigm, dataset_);
	characters_ = classifier.characters();

	classifierStatistics_ = classifier.statistics();
};


void Recognizer::doPostprocessing ()
{
	text_.clear();

	if ( characters_.size() > 0 )
	{
		for ( std::vector<unsigned int>::reverse_iterator i = spaceLocations_.rbegin(); i != spaceLocations_.rend(); ++i )
		{
			try
			{
				characters_.insert(characters_.begin() + *i, " ");
			}
			catch (...) {}
		}

		for ( std::vector<std::string>::iterator i = characters_.begin(); i != characters_.end(); ++i )
			text_.addCharacter(*i);

		std::string brokenText(text_.content());
		boost::regex pattern("- ");
		text_.content(regex_replace(brokenText, pattern, ""));
		
		pattern = ",,";
		text_.content(regex_replace(brokenText, pattern, "\""));
		
		pattern = "''";
		text_.content(regex_replace(brokenText, pattern, "\""));
	}
};


void Recognizer::printStatistics () const
{
	preprocessingStatistics_.print();
	featureExtractorStatistics_.print();
	classifierStatistics_.print();
};


void Recognizer::trainClassifier (const Clip& pressClip, const std::string& text, const ClassificationParadigm& paradigm)
{
	doPreprocessing(pressClip);
	doFeatureExtraction();
	doClassification(paradigm);

	const boost::regex pattern("\\s*");
	Text referenceText;
	referenceText.content(regex_replace(text, pattern, ""));

	std::cout << characters_.size() << std::endl;
	std::cout << referenceText.size() << std::endl;
	if ( characters_.size() == referenceText.size() )
	{
		unsigned int patternNo = 0;
		double hits = 0.0;

		for ( std::vector<std::string>::iterator i = characters_.begin(); i != characters_.end(); ++i )
		{
			try
			{
				unsigned int code;
				if ( *i == referenceText.at(patternNo) )
				{
					code = dataset_->code(*i);
					hits += 1.0;
				}
				else
					code = dataset_->code(referenceText.at(patternNo));
				
				//if ( code != 256 )
				//	dataset_->addSample(Sample(featureVectors_.at(patternNo), code));
			}
			catch(std::exception& e)
			{
				std::cerr << "Training of sample " << patternNo << " could not be completed. " << e.what() << std::endl;
			}

			++patternNo;
		}

		classifierStatistics_.hitRate( (hits / characters_.size()) * 100 );
		classifierStatistics_.missRate( (1 - hits / characters_.size()) * 100 );
	}
};


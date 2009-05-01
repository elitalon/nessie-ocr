/// @file
/// @brief Implementation of NessieOcr class

#include "NessieOcr.hpp"
#include "NessieException.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"
#include "FeatureExtractor.hpp"
#include "KnnClassifier.hpp"
#include "Pattern.hpp"
#include "FeatureVector.hpp"
#include <string>
#include <boost/regex.hpp>


NessieOcr::NessieOcr ()
:	spaceLocations_(0),
	patterns_(0),
	featureVectors_(0),
	characters_(0),
	text_(),
	preprocessingStatistics_(),
	featureExtractorStatistics_(),
	classifierStatistics_()
{};


NessieOcr::~NessieOcr() {};


void NessieOcr::extractText (const Clip& pressClip, std::auto_ptr<ClassificationAlgorithm>& algorithm)
{
	doPreprocessing(pressClip);
	doFeatureExtraction();
	doClassification(algorithm);
	doPostprocessing();
};


void NessieOcr::doPreprocessing (const Clip& pressClip)
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


void NessieOcr::doFeatureExtraction ()
{
	featureVectors_.clear();

	FeatureExtractor featureExtractor(patterns_);
	featureExtractor.computeMoments();
	featureVectors_ = featureExtractor.featureVectors();

	featureExtractorStatistics_ = featureExtractor.statistics();
};


void NessieOcr::doClassification (std::auto_ptr<ClassificationAlgorithm>& algorithm)
{
	characters_.clear();

	std::auto_ptr<Classifier> classifier;
	classifier.reset( new KnnClassifier(algorithm) );
	classifier->performClassification(featureVectors_);
	characters_ = classifier->characters();

	classifierStatistics_ = classifier->statistics();
};


void NessieOcr::doPostprocessing ()
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


void NessieOcr::printStatistics () const
{
	preprocessingStatistics_.print();
	featureExtractorStatistics_.print();
	classifierStatistics_.print();
};


#include <iostream>
void NessieOcr::trainClassifier (const Clip& pressClip, const std::string& text, std::auto_ptr<ClassificationAlgorithm>& algorithm)
{
	doPreprocessing(pressClip);
	doFeatureExtraction();
	
	characters_.clear();
	std::auto_ptr<Classifier> classifier;
	classifier.reset( new KnnClassifier(algorithm) );
	classifier->performClassification(featureVectors_);
	characters_ = classifier->characters();

	const boost::regex pattern("\\s*");
	Text referenceText;
	referenceText.content(regex_replace(text, pattern, ""));

	std::cout << std::endl << "Size of reference text: " << referenceText.size() << std::endl;

	if ( characters_.size() == referenceText.size() )
		classifier->performTraining(featureVectors_, characters_, referenceText);
	
	classifierStatistics_ = classifier->statistics();
};


/// @file
/// @brief Implementation of NessieOcr class

#include "NessieOcr.hpp"
#include "NessieException.hpp"
#include "Pattern.hpp"
#include "FeatureVector.hpp"

#include "PreprocessorStatistics.hpp"
#include "FeatureExtractorStatistics.hpp"
#include "ClassifierStatistics.hpp"

#include "Preprocessor.hpp"
#include "FeatureExtractor.hpp"
#include "Classifier.hpp"

#include <boost/regex.hpp>
#include <sstream>
#include <iostream>


NessieOcr::NessieOcr ()
:	spaceLocations_(0),
	patterns_(0),
	featureVectors_(0),
	characters_(0),
	text_(),
	preprocessingStatistics_(0),
	featureExtractionStatistics_(0),
	classificationStatistics_(0)
{}


NessieOcr::~NessieOcr() {}


const Text& NessieOcr::recognize (const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width, const std::auto_ptr<Classifier>& classifier)
{
	if ( classifier.get() == 0 )
		throw NessieException ("NessieOcr::train() : The classifier is set to a null value. Please, provide a valid classifier.");

	doPreprocessing(page, x, y, height, width);
	doFeatureExtraction();
	doClassification(classifier);
	doPostprocessing();

	return text_;
}


void NessieOcr::train (const std::auto_ptr<Classifier>& classifier, const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width, const std::string& text)
{
	if ( classifier.get() == 0 )
		throw NessieException ("NessieOcr::train() : The classifier is set to a null value. Please, provide a valid classifier.");

	doPreprocessing(page, x, y, height, width);
	doFeatureExtraction();
	characters_ = classifier->performClassification(featureVectors_);

	const boost::regex pattern("\\s*");
	Text referenceText;
	referenceText.assign(regex_replace(text, pattern, ""));

	std::cout << std::endl << "Size of reference text: " << referenceText.size() << std::endl;

	if ( characters_.size() == referenceText.size() )
		classifier->performTraining(featureVectors_, characters_, referenceText);

	classificationStatistics_.reset (new ClassifierStatistics(classifier->statistics()) );
}


void NessieOcr::exportPatternImages () const
{
	unsigned int patternNo = 0;

	for ( std::vector<Pattern>::const_iterator i = patterns_.begin(); i != patterns_.end(); ++i )
	{
		std::ostringstream filename;
		filename << "pattern" << patternNo++ << ".bmp";

		i->writeToOutputImage(filename.str(), true);
	}
}


void NessieOcr::printStatistics () const
{
	if ( preprocessingStatistics_.get() != 0 )
		preprocessingStatistics_->print();
	else
		std::cout << std::endl << "There is no statistics for the preprocessing stage." << std::endl;

	if ( featureExtractionStatistics_.get() != 0 )
		featureExtractionStatistics_->print();
	else
		std::cout << std::endl << "There is no statistics for the feature extraction stage." << std::endl;

	if ( classificationStatistics_.get() != 0 )
		classificationStatistics_->print();
	else
		std::cout << std::endl << "There is no statistics for the classification stage." << std::endl;
}


void NessieOcr::doPreprocessing (const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width)
{
	Preprocessor preprocessor(page, x, y, height, width);
	preprocessor.removeNoiseByLinearFiltering();
	preprocessor.applyGlobalThresholding();
	preprocessor.removeNoiseByTemplateMatching();
	std::ostringstream filename;
	spaceLocations_ = preprocessor.isolateRegions();

	text_.averageCharacterHeight(preprocessor.averageCharacterHeight());

	preprocessor.buildPatterns();
	preprocessor.skeletonizePatterns();
	patterns_ = preprocessor.patterns();

	preprocessingStatistics_.reset ( new PreprocessorStatistics(preprocessor.statistics()) );
}


void NessieOcr::doFeatureExtraction ()
{
	FeatureExtractor featureExtractor;
	featureExtractor.computeMoments(patterns_);
	featureVectors_ = featureExtractor.featureVectors();

	featureExtractionStatistics_.reset ( new FeatureExtractorStatistics(featureExtractor.statistics()) );
}


void NessieOcr::doClassification (const std::auto_ptr<Classifier>& classifier)
{
	characters_ = classifier->performClassification(featureVectors_);

	classificationStatistics_.reset ( new ClassifierStatistics(classifier->statistics()) );
}


void NessieOcr::doPostprocessing ()
{
	text_.clear();

	if ( characters_.size() > 0 )
	{
		for ( std::vector<unsigned int>::reverse_iterator i = spaceLocations_.rbegin(); i != spaceLocations_.rend(); ++i )
			characters_.insert(characters_.begin() + *i, " ");

		for ( std::vector<std::string>::iterator i = characters_.begin(); i != characters_.end(); ++i )
			text_.append(*i);

		// Remove broken words due to line breaks
		std::string brokenText(text_.data());
		boost::regex pattern("-\\s*[,.]?\\s*");
		text_.assign(regex_replace(brokenText, pattern, ""));

		// Remove non-alphanumeric characters
		brokenText = text_.data();
		pattern = "[\\?¿,;.:\\!+*/=<>'\\()\\{}\\[\\]|]+";
		text_.assign(regex_replace(brokenText, pattern, ""));

		// This character must be removed in a separate pattern
		brokenText = text_.data();
		pattern = "¡+";
		text_.assign(regex_replace(brokenText, pattern, ""));

		// Remove innecesary spaces
		brokenText = text_.data();
		pattern = "\\s+";
		text_.assign(regex_replace(brokenText, pattern, " "));
	}
}


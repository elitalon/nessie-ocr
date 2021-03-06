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

	if ( characters_.size() == referenceText.size() )
		classifier->performTraining(featureVectors_, characters_, referenceText);

	classificationStatistics_.reset (new ClassifierStatistics(classifier->statistics()) );
}


void NessieOcr::train (const std::auto_ptr<Classifier>& classifier, const Magick::Image& pattern, const unsigned int& asciiCode)
{
	if ( classifier.get() == 0 )
		throw NessieException ("NessieOcr::train() : The classifier is set to a null value. Please, provide a valid classifier.");

	// Build pattern from the input image
	if ( pattern.columns() > Pattern::planeSize() )
		throw NessieException ("Preprocessor::Preprocessor() : The input image width cannot be wider than the default pattern width.");

	if ( pattern.rows() > Pattern::planeSize() )
		throw NessieException ("Preprocessor::Preprocessor() : The input image height cannot be wider than the default pattern height.");

	Magick::Pixels imageView(const_cast<Magick::Image&>(pattern));
	Magick::PixelPacket *pixels = imageView.get(0, 0, pattern.columns(), pattern.rows());
	Pattern p;

	for ( unsigned int i = 0; i < imageView.rows(); ++i )
	{
		for ( unsigned int j = 0; j < imageView.columns(); ++j )
		{
			Magick::ColorGray graylevel(*pixels++);
			p.at(i,j) = ( graylevel.shade() == 0.0 )?1:0;
		}
	}

	patterns_.clear();
	patterns_.push_back(p);

	// Extract features from the pattern
	doFeatureExtraction();

	// Classify and train the pattern
	characters_ = classifier->performClassification(featureVectors_);
	classifier->performTraining(featureVectors_.front(), characters_.front(), asciiCode);
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
		std::cout << std::endl << "There are no statistics for the preprocessing stage." << std::endl;

	if ( featureExtractionStatistics_.get() != 0 )
		featureExtractionStatistics_->print();
	else
		std::cout << std::endl << "There are no statistics for the feature extraction stage." << std::endl;

	if ( classificationStatistics_.get() != 0 )
		classificationStatistics_->print();
	else
		std::cout << std::endl << "There are no statistics for the classification stage." << std::endl;
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

	if ( !characters_.empty() )
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


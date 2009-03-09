/// @file
/// @brief Implementation of Recognizer class

#include "Recognizer.hpp"
#include "NessieException.hpp"
#include "Dataset.hpp"
#include "Statistics.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"
#include "FeatureExtractor.hpp"
#include "Classifier.hpp"
#include <string>
#include <iostream>
#include <sstream>


Recognizer::Recognizer (std::auto_ptr<Dataset>& dataset)
:	dataset_(dataset),
	regions_(0),
	spaceLocations_(0),
	patterns_(0),
	featureVectors_(0),
	characters_(0),
	text_(),
	preprocessingStatistics_(0),
	featureExtractorStatistics_(0),
	classifierStatistics_(0)
{
	if ( dataset_.get() == 0 )
		throw NessieException ("Recognizer::Recognizer() : A null pointer was passed to the constructor. You must provide an instantiated Dataset object.");
};

Recognizer::Recognizer (Dataset* const dataset)
:	dataset_(dataset),
	regions_(0),
	spaceLocations_(0),
	patterns_(0),
	featureVectors_(0),
	characters_(0),
	text_(),
	preprocessingStatistics_(0),
	featureExtractorStatistics_(0),
	classifierStatistics_(0)
{
	if ( dataset_.get() == 0 )
		throw NessieException ("Recognizer::Recognizer() : A null pointer was passed to the constructor. You must provide an instantiated Dataset object.");
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
		i->writeToOutputImage(filename,true);
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
	characters_.clear();

	Classifier classifier(featureVectors_);
	classifier.classify(paradigm, dataset_);
	characters_ = classifier.characters();

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
	text_.clear();
	
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
	unsigned int i = brokenText.find("- ");
	while ( i != std::string::npos )
	{
		brokenText.replace(i, 2, "");
		i = brokenText.find("- ");
	}
	
	text_.content(brokenText);
};


void Recognizer::doPostprocessing (const std::vector<std::string>& characters, const std::vector<unsigned int>& spaceLocations)
{
	characters_ = characters;
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


void Recognizer::trainClassifier (const Clip& pressClip, const ClassificationParadigm& paradigm)
{
	doPreprocessing(pressClip);
	doFeatureExtraction();
	doClassification(paradigm);

	unsigned int regionNo = 0;
	for ( std::vector<std::string>::iterator i = characters_.begin(); i != characters_.end(); ++i )
	{
		try
		{
			std::cout << "Region #" << regionNo << ":" << std::endl;
			
			std::cout << " - Feature vector      : ";
			for ( unsigned int j = 0; j < dataset_->features(); ++j )
				std::cout << featureVectors_.at(regionNo).at(j) << " ";
			std::cout << std::endl;
		
			std::cout << " - Candidate character : ";
			unsigned int code = dataset_->code(*i);
			if ( code != 256 )
				std::cout << *i << "(" << code << ")" << std::endl;
			else
				std::cout << "none" << std::endl;
			
			std::cout << " - Valid classification [y/N]? ";
			unsigned char userAnswer;
			std::cin >> userAnswer;

			if ( userAnswer == 'y' )
				dataset_->addSample(Sample(featureVectors_.at(regionNo), code));
			else
			{
				unsigned int code = 256;

				while ( code == 256 )
				{
					std::cout << " - Please, enter the right character: ";
					std::string character;
					std::cin >> character;
				
					code = dataset_->code(character);
					if ( code != 256 )
						dataset_->addSample(Sample(featureVectors_.at(regionNo), code));
				}
			}
		}
		catch(std::exception& e)
		{
			std::cout << "The training of sample " << regionNo << " could not be completed: " << e.what() << std::endl;
		}
		std::cout << std::endl;
		
		++regionNo;
	}
};


void Recognizer::trainClassifier (const Clip& pressClip, const std::vector<std::string>& referenceText, const ClassificationParadigm& paradigm)
{
	doPreprocessing(pressClip);
	doFeatureExtraction();
	doClassification(paradigm);

	if ( characters_.size() == referenceText.size() )
	{
		unsigned int regionNo = 0;
		for ( std::vector<std::string>::iterator i = characters_.begin(); i != characters_.end(); ++i )
		{
			try
			{
				unsigned int code;
				if ( *i == referenceText.at(regionNo) )
					code = dataset_->code(*i);
				else
					code = dataset_->code(referenceText.at(regionNo));
				
				if ( code != 256 )
					dataset_->addSample(Sample(featureVectors_.at(regionNo), code));
			}
			catch(std::exception& e)
			{
				std::cout << "The training of sample " << regionNo << " could not be completed: " << e.what() << std::endl;
			}

			++regionNo;
		}
	}
};


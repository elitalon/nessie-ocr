/// @file
/// @brief Implementation of a command line program for testing purposes.

#include <Magick++.h>
#include "NessieOcr.hpp"
#include "DatasetEngine.hpp"
#include "KnnClassifier.hpp"
#include "Text.hpp"

#include <boost/program_options.hpp>
#include <boost/timer.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

namespace po = boost::program_options;


/// @param argc		Number of command line arguments.
/// @param argv[]	Command line arguments.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-16
int main (int argc, char *argv[])
{
	// Declare program arguments and options
	po::options_description visibleOptions("Options");
	visibleOptions.add_options()
		("file,f",				po::value<std::string>(), "Use a plain text file as classification dataset.")
		("database,d",			po::value<std::string>()->default_value("db_nessieocr"), "Use a database as classification dataset. Superseded by the --file option.")
		("user,u",				po::value<std::string>()->default_value("nessieocr"), "Database user.")
		("password,p",			po::value<std::string>()->default_value("nessieocr"), "Database user's password.")
		("text-training,t",		po::value<std::string>(), "Use a plain text file as reference text to execute a training.")
		("auto-training,a",		"Use the image names without extension as the ASCII code to execute a training. E.g. 65.bmp means A.")
		("knn,k",				po::value<unsigned int>()->default_value(1), "Maximum number of neighbours when using the KNN algorithm.")
		("create-patterns,c",	"Create an output BMP image for each pattern found in the input image.")
		("statistics,s",		"Show statistical data regarding the OCR process.")
		("help,h",				"Print this help message");
	po::options_description hiddenOptions("Hidden options");

	std::vector<std::string> inputImages(0);
	hiddenOptions.add_options() ("image", po::value< std::vector<std::string> >(&inputImages), "Input image file to process");
	po::positional_options_description p;
	p.add("image", -1);

	po::options_description availableOptions("Available options");
	availableOptions.add(visibleOptions).add(hiddenOptions);


	// Parse the command line
	po::variables_map passedOptions;
	try
	{
		po::store(po::command_line_parser(argc, argv).options(availableOptions).positional(p).run(), passedOptions);
		po::notify(passedOptions);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}


	// Show help message
	if ( passedOptions.count("help") )
	{
		std::cout << std::endl << "Usage: ocrtest [options] <image>" << std::endl;
		std::cout << visibleOptions << std::endl;
		return 0;
	}


	// Test program arguments
	if ( !passedOptions.count("image") )
	{
		std::cerr << "ocrtest: Missing image file." << std::endl;
		std::cerr << std::endl << "Usage: ocrtest [options] <image>" << std::endl;
		std::cerr << visibleOptions << std::endl;
		return 1;
	}

		
	// Define the classifier
	std::auto_ptr<Classifier> classifier;
	try
	{
		if ( passedOptions.count("file") )
		{
			std::string filename (passedOptions["file"].as<std::string>());
			classifier.reset( new KnnClassifier(passedOptions["knn"].as<unsigned int>(), DatasetEngine::PlainText(filename)) );
		}
		else
		{
			std::string database ( passedOptions["database"].as<std::string>() );
			std::string username ( passedOptions["user"].as<std::string>() );
			std::string password ( passedOptions["password"].as<std::string>() );

			classifier.reset( new KnnClassifier(passedOptions["knn"].as<unsigned int>(), DatasetEngine::PostgreSql(database, username, password)) );
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
	// Create the OCR
	NessieOcr ocr;
	try
	{
		if ( passedOptions.count("text-training") )
		{
			std::ifstream inputFile( passedOptions["text-training"].as<std::string>().data() );
			if ( not inputFile.is_open() || not inputFile.good() )
			{
				std::cerr << "ocrtest: The file passed for training is not valid." << std::endl;
				return 1;
			}
			
			// Load reference text for training using a set of characters extracted from a clip
			std::string text;
			std::string line;
			while ( inputFile.good() )
			{   
				getline(inputFile, line);

				if (!line.empty())
					text.append(line);
			}   
			inputFile.close();

			Magick::Image image( inputImages.at(0) );
			if ( image.magick() == "PDF" )
			{
				image.resolutionUnits(Magick::PixelsPerInchResolution);
				image.density("800x800");
				image.read( inputImages.at(0) );
			}

			ocr.train(classifier, image, 0, 0, image.rows(), image.columns(), text);

			// Show statistics
			if ( passedOptions.count("statistics") )
				ocr.printStatistics();
		}
		else
		{
			if ( passedOptions.count("auto-training") )
			{
				// Execute a training using the image name as the reference ASCII code.
				for( std::vector<std::string>::iterator i = inputImages.begin(); i != inputImages.end(); ++i )
				{
					// Extrac image name
					boost::regex pattern("^/?(\\w+\\/)*(\\w+)(\\.\\w+)?$");
					boost::smatch m;
					regex_match(*i, m, pattern);
					
					// Get the ASCII code
					std::istringstream imageName(m[2]);
					unsigned int asciiCode;
					imageName >> asciiCode;

					// Load the image
					Magick::Image image(*i);
					if ( image.magick() == "PDF" )
					{
						image.resolutionUnits(Magick::PixelsPerInchResolution);
						image.density("800x800");
						image.read( *i );
					}

					// Execute training
					ocr.train(classifier, *i, asciiCode);

					// Show statistics
					if ( passedOptions.count("statistics") )
						ocr.printStatistics();
				}
			}
			else
			{
				// Load image and recognize text
				for( std::vector<std::string>::iterator i = inputImages.begin(); i != inputImages.end(); ++i )
				{
					Magick::Image image(*i);
					if ( image.magick() == "PDF" )
					{
						image.resolutionUnits(Magick::PixelsPerInchResolution);
						image.density("800x800");
						image.read( *i );
					}

					Text text( ocr.recognize(image, 0, 0, image.rows(), image.columns(), classifier) );

					if ( !text.data().empty() )
						std::cout << std::endl << text.data() << std::endl << std::endl;

					// Show statistics
					if ( passedOptions.count("statistics") )
					{
						std::cout << "Total word count  : " << text.nWords() << std::endl;
						std::cout << "Average word size : " << text.averageWordSize() << std::endl;
						ocr.printStatistics();
					}
				}
			}
		}
		
		// Create BMP images for patterns
		if ( passedOptions.count("create-patterns") )
			ocr.exportPatternImages();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

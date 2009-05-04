/// @file
/// @brief Implementation of a command line program for training purposes.

#include <Magick++.h>
#include "Clip.hpp"
#include "NessieOcr.hpp"
#include "PostgreSqlDataset.hpp"
#include "PlainTextDataset.hpp"
#include "KnnClassificationAlgorithm.hpp"
#include "Pattern.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>

namespace po = boost::program_options;


/// @param argc		Number of command line arguments.
/// @param argv[]	Command line arguments.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-16
int main (int argc, char *argv[])
{
	try
	{
		// Declare program arguments and options
		std::string inputImage;

		po::options_description visibleOptions("Options");
		visibleOptions.add_options()
			("file,f",				po::value<std::string>(), "Use a plain text file as classification dataset.")
			("database,d",			po::value<std::string>()->default_value("db_nessieocr"), "Use a database as classification dataset. Superseded by the --file option.")
			("user,u",				po::value<std::string>()->default_value("nessieocr"), "Database user.")
			("password,p",			po::value<std::string>()->default_value("nessieocr"), "Database user's password.")
			("training,t",			po::value<std::string>(), "Use a plain text file as reference text to execute a training stage.")
			("knn,k",				po::value<unsigned int>()->default_value(1), "Maximum number of neighbours when using the KNN algorithm.")
			("create-patterns,c",	"Create an output BMP image for each pattern found in the input image.")
			("statistics,s",		"Show statistical data regarding the OCR process.")
			("help,h",				"Print this help message");
		po::options_description hiddenOptions("Hidden options");
		
		hiddenOptions.add_options() ("image", po::value<std::string>(&inputImage), "Input image file to process");
		po::positional_options_description p;
		p.add("image", -1);

		po::options_description availableOptions("Available options");
		availableOptions.add(visibleOptions).add(hiddenOptions);


		// Parse the command line
		po::variables_map passedOptions;
		po::store(po::command_line_parser(argc, argv).options(availableOptions).positional(p).run(), passedOptions);
		po::notify(passedOptions);


		// Show help message
		if ( passedOptions.count("help") )
		{
			std::cout << std::endl << "Usage: tester [options] <image>" << std::endl;
			std::cout << visibleOptions << std::endl;
			return 0;
		}


		// Load input image
		if ( !passedOptions.count("image") )
		{
			std::cerr << "tester: Missing image file." << std::endl;
			std::cerr << std::endl << "Usage: tester [options] <image>" << std::endl;
			std::cerr << visibleOptions << std::endl;
			return 1;
		}
		Magick::Image image( inputImage );
		if ( image.magick() == "PDF" )
		{
			image.resolutionUnits(Magick::PixelsPerInchResolution);
			image.density("800x800");
			image.read( inputImage );
		}
		Clip pressClip(image, 0, 0, image.rows(), image.columns());
	

		// Load dataset
		std::auto_ptr<Dataset> dataset;
		if ( passedOptions.count("file") )
			dataset.reset( new PlainTextDataset(passedOptions["file"].as<std::string>()) );
		else
		{
			std::string databaseName( passedOptions["database"].as<std::string>() );
			std::string databaseUser( passedOptions["user"].as<std::string>() );
			std::string databasePassword( passedOptions["password"].as<std::string>() );
			
			dataset.reset( new PostgreSqlDataset(databaseName, databaseUser, databasePassword) );
		}


		// Define the classification algorithm
		std::auto_ptr<ClassificationAlgorithm> algorithm;
		algorithm.reset( new KnnClassificationAlgorithm (passedOptions["knn"].as<unsigned int>(), dataset) );


		// Create the OCR
		NessieOcr ocr;


		// Load reference text for training
		if ( passedOptions.count("training") )
		{
			std::ifstream inputFile( passedOptions["training"].as<std::string>().data() );
			if ( not inputFile.is_open() || not inputFile.good() )
			{
				std::cerr << "tester: The file passed for training is not valid." << std::endl;
				return 1;
			}

			std::string text;
			while ( inputFile.good() )
			{   
				std::string line;
				getline(inputFile, line);

				if (!line.empty())
					text.append(line);
			}   
			inputFile.close();

			ocr.trainClassifier(pressClip, text, algorithm);
		}
		else
		{
			ocr.extractText(pressClip, algorithm);
			std::cout << ocr.text().content() << std::endl;
		}


		// Create BMP images for patterns
		if ( passedOptions.count("create-patterns") )
		{
			unsigned int patternNo = 0;
			std::vector<Pattern> patterns = ocr.patterns();
			for ( std::vector<Pattern>::iterator i = patterns.begin(); i != patterns.end(); ++i )
			{
				std::ostringstream ostr;
				ostr << patternNo++;
				std::string filename("pattern");
				filename.append(ostr.str().append(".bmp"));
				i->writeToOutputImage(filename,true);
			}
		}
		

		// Show statistics
		if ( passedOptions.count("statistics") )
			ocr.printStatistics();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}


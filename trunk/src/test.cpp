/// @file
/// @brief Implementation of a command line program for training purposes.

#include <Magick++.h>
#include "Clip.hpp"
#include "PlainTextDataset.hpp"
#include "PostgreSqlDataset.hpp"
#include "Recognizer.hpp"
#include "ClassificationParadigm.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
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
		// Declare program supported options.
		po::options_description availableOptions("Available options");
		availableOptions.add_options()
			("help,h",		"Print this help message")
			("training,t",	po::value<std::string>(),"Executes a dataset training instead of a normal OCR")
			("filename,f",	po::value<std::string>(), "Use a plain text file as dataset")
			("database,d",	po::value<std::string>(), "Use a database as dataset (e.g. db_nessie). Superseded by the <filename> option")
			("username,u",	po::value<std::string>(), "Username when connecting to the database. The <database> argument will be used by default")
			("password,p",	po::value<std::string>(), "Password when connecting to the database. The <user> argument will be used by default")
			("image",		po::value<std::string>(), "Input image file to process");
		po::positional_options_description p;
		p.add("image", -1);

		// Parse the command line
		po::variables_map passedOptions;
		po::store(po::command_line_parser(argc, argv).options(availableOptions).positional(p).run(), passedOptions);
		po::notify(passedOptions);

		if ( passedOptions.count("help") )
		{
			std::cout << "Usage: tester [options] <image>" << std::endl;
			std::cout << availableOptions;
			return 0;
		}

		if ( !passedOptions.count("image") )
		{
			std::cout << "The image file was not specified." << std::endl;
			return 1;
		}

		// Create a press clip from an external image.
		Magick::Image image( passedOptions["image"].as<std::string>() );
		Clip pressClip(image, 0, 0, image.rows(), image.columns());
		
		if ( !passedOptions.count("filename") && !passedOptions.count("database") )
		{
			std::cout << "The classification dataset was not specified." << std::endl;
			return 1;
		}

		// Create a dataset to use in the classification stage.
		std::auto_ptr<Dataset> dataset;
		if ( passedOptions.count("filename") )
		{
			std::string filename( passedOptions["filename"].as<std::string>() );
			dataset.reset( new PlainTextDataset(filename) );
		}
		else
		{
			std::string dbName( passedOptions["database"].as<std::string>() );
			std::string username(dbName);
			std::string password(username);

			if ( passedOptions.count("username") )
				username = passedOptions["username"].as<std::string>();
			
			if ( passedOptions.count("password") )
				password = passedOptions["password"].as<std::string>();

			dataset.reset( new PostgreSqlDataset(dbName, username, password) );
		}

		// Create a recognizer and executes the required action
		Recognizer recon( dataset.get() );

		if ( passedOptions.count("training") )
		{
			std::string filename( passedOptions["training"].as<std::string>() );
			if ( filename != "" )
			{
				std::ifstream inputFile( filename.data() );
				if ( not inputFile.is_open() or not inputFile.good() )
				{
					std::cout << "The file passed for training is not valid." << std::endl;
					return 1;
				}

				std::vector<std::string> referenceText(0);
				while ( inputFile.good() )
				{   
					std::string character;
					getline(inputFile, character);
					if (!character.empty())
						referenceText.push_back(character);
				}   
				inputFile.close();	
			
				recon.trainClassifier(pressClip, referenceText, ClassificationParadigm::knn());
			}
			else
				recon.trainClassifier(pressClip, ClassificationParadigm::knn());
		}
		else
		{
			recon.extractText(pressClip, ClassificationParadigm::knn());
			std::cout << "Text extracted: " << recon.text().content() << std::endl;
		}
		recon.printStatistics();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}


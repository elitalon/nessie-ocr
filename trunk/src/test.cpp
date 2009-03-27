/// @file
/// @brief Implementation of a command line program for training purposes.

#include <Magick++.h>
#include "Clip.hpp"
#include "PlainTextDataset.hpp"
#include "PostgreSqlDataset.hpp"
#include "MySqlDataset.hpp"
#include "Recognizer.hpp"
#include "ClassificationParadigm.hpp"
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
		// Declare program supported options.
		po::options_description availableOptions("Available options");
		availableOptions.add_options()
			("help,h",		"Print this help message")
			("file,f",			po::value<std::string>(), "Use the content of a file as reference text to execute a dataset training instead of an OCR. Superseded by the <result> option.")
			("result,r",		po::value<std::string>(), "Use a string as reference text to execute a dataset training instead of an OCR.")
			("interactive,i",	"Execute a dataset interactive training instead of an OCR.")
			("text,t",			po::value<std::string>(), "Use a plain text file as dataset.")
			("database,d",		po::value<std::string>(), "Use a database as dataset (e.g. db_nessie). Superseded by the <filename> option.")
			("username,u",		po::value<std::string>(), "Username when connecting to the database. The <database> argument will be used by default.")
			("password,p",		po::value<std::string>(), "Password when connecting to the database. The <user> argument will be used by default.")
			("image",			po::value<std::string>(), "Input image file to process");
		po::positional_options_description p;
		p.add("image", -1);

		// Parse the command line
		po::variables_map passedOptions;
		po::store(po::command_line_parser(argc, argv).options(availableOptions).positional(p).run(), passedOptions);
		po::notify(passedOptions);


		// Help option
		if ( passedOptions.count("help") )
		{
			std::cout << "Usage: tester [options] <image>" << std::endl;
			std::cout << availableOptions;
			return 0;
		}


		// The image filename is mandatory.
		if ( !passedOptions.count("image") )
		{
			std::cerr << "The image file was not specified." << std::endl;
			return 1;
		}
		Magick::Image image;
		image.resolutionUnits(Magick::PixelsPerInchResolution);
		image.density("800x800");
		image.read( passedOptions["image"].as<std::string>() );
		Clip pressClip(image, 0, 0, image.rows(), image.columns());
	

		// Dataset option
		if ( !passedOptions.count("database") && !passedOptions.count("text") )
		{
			std::cerr << "The classification dataset was not specified." << std::endl;
			return 1;
		}

		std::auto_ptr<Dataset> dataset;
		if ( passedOptions.count("text") )
		{
			if ( passedOptions["text"].as<std::string>() != "" )
			{
				std::string filename( passedOptions["text"].as<std::string>() );
				dataset.reset( new PlainTextDataset(filename) );
			}
			else
			{
				std::cerr << "The plain text file was not correctly specified." << std::endl;
				return 1;
			}
		}
		else
		{
			if ( passedOptions["database"].as<std::string>() != "" )
			{
				std::string dbName( passedOptions["database"].as<std::string>() );
				std::string username(dbName);
				std::string password(username);

				if ( passedOptions.count("username") )
				{
					username = passedOptions["username"].as<std::string>();
					password = username;
				}

				if ( passedOptions.count("password") )
					password = passedOptions["password"].as<std::string>();

				dataset.reset( new PostgreSqlDataset(dbName, username, password) );
				//dataset.reset( new MySqlDataset(dbName, username, password) );
			}
			else
			{
				std::cerr << "The database name was not correctly specified." << std::endl;
				return 1;
			}
		}
		Recognizer recon( dataset );

	
		// Training options
		if ( passedOptions.count("file") || passedOptions.count("result") || passedOptions.count("interactive") )
		{
			if ( passedOptions.count("interactive") )
				recon.trainClassifier(pressClip, ClassificationParadigm::knn());
			else
			{
				if ( passedOptions.count("result") )
					recon.trainClassifier(pressClip, passedOptions["result"].as<std::string>(), ClassificationParadigm::knn());
				else
				{
						std::ifstream inputFile( passedOptions["file"].as<std::string>().data() );
						if ( not inputFile.is_open() or not inputFile.good() )
						{
							std::cerr << "The file passed for training is not valid." << std::endl;
							return 1;
						}

						std::string text("");
						while ( inputFile.good() )
						{   
							std::string line;
							getline(inputFile, line);

							if (!line.empty())
								text.append(line);
						}   
						inputFile.close();

						recon.trainClassifier(pressClip, text, ClassificationParadigm::knn());
				}
			}
		}
		else
		{
			recon.extractText(pressClip, ClassificationParadigm::knn());
			std::cout << "Text extracted    : " << recon.text().content() << std::endl;
			std::cout << "No. of characters : " << recon.text().size() << std::endl;
		}

		unsigned int patternNo = 0;
		std::vector<Pattern> patterns = recon.patterns();
		for ( std::vector<Pattern>::iterator i = patterns.begin(); i != patterns.end(); ++i )
		{
			std::ostringstream ostr;
			ostr << patternNo++;
			std::string filename("pattern");
			filename.append(ostr.str().append(".bmp"));
			i->writeToOutputImage(filename,true);
		}
		recon.printStatistics();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}


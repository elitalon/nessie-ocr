/// @file
/// @brief Implementation of a command line program for testing purposes

#include <Magick++.h>
#include "Clip.hpp"
#include "PlainTextDataset.hpp"
#include "PostgreSqlDataset.hpp"
#include "Recognizer.hpp"
#include "ClassificationParadigm.hpp"
#include <boost/timer.hpp>
#include <iostream>
#include <memory>


/// @param argc		Number of command line arguments.
/// @param argv[]	Command line arguments.
///
///	@todo	Encapsulate all classes in a namespace, e.g. NessieOcr
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-16
///
int main (int argc, char const *argv[])
{
	try
	{
		if ( argc < 1 )
		{
			std::cout << "Missing arguments!" << std::endl;
			return 1;
		}

		boost::timer timer;
		timer.restart();

		Magick::Image image( argv[1] );
		
		Clip pressClip(image, 0, 0, image.rows(), image.columns());

		std::auto_ptr<Dataset> dataset( new PlainTextDataset("samples.dataset") );
		std::cout << "The dataset contains " << dataset->size() << " samples" << std::endl;
		for ( unsigned int i = 0; i < dataset->size(); ++i )
		{
			for ( unsigned int j = 0; j < dataset->at(i).first.size(); ++j )
				std::cout << dataset->at(i).first.at(j) << " ";
			std::cout << dataset->at(i).second << std::endl;
		}
		Recognizer recon( dataset.get() );
		recon.extractText(pressClip, ClassificationParadigm::knn());

		std::cout << recon.text().content() << std::endl;
		recon.printStatistics();

		std::cout << std::endl << "Total time since program started: " << timer.elapsed() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}


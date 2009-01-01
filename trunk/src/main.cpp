/// @file
/// @brief Implementation of a command line program for testing purposes

#include <Magick++.h>
#include "Clip.hpp"
#include "Recognizer.hpp"
#include <iostream>
#include <boost/timer.hpp>


///
/// @todo Check documentation for pre- and post-conditions.
///
/// @todo Modify internal data structures to use 0 and 1 for pixel intensity values.
///
/// @todo Locate algorithms and see if it is possible to apply the "Template Method" pattern.
///
/// @param argc Number of command line arguments
/// @param argv Command line arguments
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-16
///
int main (int argc, char const *argv[])
{
	try
	{
		if ( argc <= 1 )
		{
			std::cout << "Missing arguments!" << std::endl;
			return 1;
		}

		boost::timer timer;
		timer.restart();
		
		Magick::Image image( argv[1] );

		Clip pressClip(image, 0, 0, image.rows(), image.columns());

		Recognizer recon;
		recon.extractText(pressClip);

		std::cout << "Total time since program started: " << timer.elapsed() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

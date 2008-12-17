///
/// @file
/// @brief Implementation of a command line program for testing purposes
///

#include <Magick++.h>
#include "Recognizer.hpp"
#include <iostream>



///
/// @todo Check documentation for pre- and post-conditions.
///
/// @todo Modify internal data structures to use 0 and 1 for pixel intensity values.
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

		// Load an image object with the filename passed
		Magick::Image image( argv[1] );

		// Create a Recognizer object from the image loaded
		Recognizer recon( image );

		// Execute the OCR process
		recon.obtainText();

	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

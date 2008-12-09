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
/// @todo Develop the KNN algorithm.
///
/// @todo Develop the Classifier class.
///
/// @todo Remove Recognizer::writeExternalImage
///
/// @todo Change condition for joining line markers to ( (*currentLineMarkerIterator).first - ((*previousLineMarkerIterator).second + 1) >= meanShapeHeight )
///
/// @todo Explore other conditions for joining line markers like computing the mean distance between lines
///
/// @todo Modify the Shape internal data structures to store the relative coordinates instead of the absolute coordinates.
///
/// @todo Modify Segmenter::applyThreshold to use 0 and 1
///
/// @todo Convert Statistics into a virtual class and design new Statistics classes for every recognition stage, with more specifics parameters
///
/// @todo Add constraints to the Dataset class to avoid writing invalid data
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

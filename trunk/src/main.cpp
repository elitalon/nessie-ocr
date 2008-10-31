///
/// @file
/// @brief Implementation of a command line program for testing purposes
///

#include <Magick++.h>	
#include "Recognizer.hpp"
#include <iostream>



/// 
/// @todo Study the possibility of moving the typedef Pixel inside the Shape.hpp file.
/// @todo Check documentation for pre- and post-conditions.
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
		
		std::cout << "Background finding time      : " << recon.statistic().backgroundReferenceGrayLevelFindingTime() << std::endl;
		std::cout << "Threshold computing time     : " << recon.statistic().optimalThresholdComputingTime() << std::endl;
		std::cout << "Noise removal time           : " << recon.statistic().noiseRemovalTime() << std::endl;
		std::cout << "Preprocessing time           : " << recon.statistic().preprocessingTime() << std::endl;
		std::cout << std::endl;
						
		std::cout << "Thresholding time            : " << recon.statistic().thresholdingTime() << std::endl;
		std::cout << "Shapes finding time          : " << recon.statistic().shapesFindingTime() << std::endl;
		std::cout << "Segmentation time            : " << recon.statistic().segmentationTime() << std::endl;
		std::cout << std::endl;
		
		std::cout << "Total OCR time               : " << recon.statistic().preprocessingTime() + recon.statistic().segmentationTime() << std::endl;
		
		// Write results to the internal image
		recon.writeExternalImage( image );
				
		// Create a new PNG image with the results of OCR process
		std::string filename(argv[1]);
		filename.replace(filename.find_last_of('.'), filename.size(), "Results.png");
		image.write( filename );
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

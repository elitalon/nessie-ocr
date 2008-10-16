///
/// @file
/// @brief Implementation of a command line program for testing purposes
///
#include <Magick++.h>

#include "Recognizer.hpp"

#include <iostream>


///
/// @todo Develop an adaptative threshold algorithm
/// @todo Develop an algorithm to fill characters that may have white pixels within
/// @todo Enhance Preprocessor::computeOptimalThreshold()
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
		std::cout << "Background finding time:     " << recon.statistic().backgroundReferenceGrayLevelFindingTime() << std::endl;
		std::cout << "Threshold computing time:    " << recon.statistic().optimalThresholdComputingTime() << std::endl;
		std::cout << "Noise removal time:          " << recon.statistic().noiseRemovalTime() << std::endl;
		std::cout << "Preprocessing time:          " << recon.statistic().preprocessingTime() << std::endl;
		std::cout << std::endl;
				
		std::cout << "Thresholding time:           " << recon.statistic().thresholdingTime() << std::endl;
		std::cout << "Segmentation time:           " << recon.statistic().segmentationTime() << std::endl;
		std::cout << std::endl;
		
		// Write results to the internal image
		recon.writeExternalImage(image);
		
		// Create a new image with the results of OCR process
		std::string filename(argv[1]);
		image.write( filename.insert(filename.find_last_of('.'), "results") );
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

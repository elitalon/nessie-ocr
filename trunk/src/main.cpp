#include <iostream>
using namespace std;

#include <Magick++.h>
using namespace Magick;

#include "Recognizer.hpp"

///
/// Command line program for testing purposes.
///
int main (int argc, char const *argv[])
{
	try
	{
		Image image( argv[1] );
		Recognizer recon( image );
		
		recon.obtainText();
		cout << "Background finding time:     " << recon.statistic().backgroundReferenceGrayLevelFindingTime() << endl;
		cout << "Thresholding computing time: " << recon.statistic().optimalThresholdComputingTime() << endl;
		cout << "Noise removal time:          " << recon.statistic().noiseRemovalTime() << endl;
		cout << "Preprocessing time:          " << recon.statistic().preprocessingTime() << endl;
		
		recon.writeExternalImage(image);
		image.write("results.png");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

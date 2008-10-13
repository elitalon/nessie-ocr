#include <iostream>
#include <vector>
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
		
		vector<ClipLocation> c;
		c.push_back( ClipLocation(0,	100,	147, 	206) );
		c.push_back( ClipLocation(147,	100,	147, 	206) );
		c.push_back( ClipLocation(294,	100,	147, 	206) );
		
		
		recon.obtainText(c);
		cout << "Background finding time:     " << recon.statistic(0).backgroundReferenceGrayLevelFindingTime() << endl;
		cout << "Thresholding computing time: " << recon.statistic(0).optimalThresholdComputingTime() << endl;
		cout << "Noise removal time:          " << recon.statistic(0).noiseRemovalTime() << endl;
		cout << "Preprocessing time:          " << recon.statistic(0).preprocessingTime() << endl;
		cout << endl;
		
		cout << "Background finding time:     " << recon.statistic(1).backgroundReferenceGrayLevelFindingTime() << endl;
		cout << "Thresholding computing time: " << recon.statistic(1).optimalThresholdComputingTime() << endl;
		cout << "Noise removal time:          " << recon.statistic(1).noiseRemovalTime() << endl;
		cout << "Preprocessing time:          " << recon.statistic(1).preprocessingTime() << endl;
		cout << endl;
		
		cout << "Background finding time:     " << recon.statistic(2).backgroundReferenceGrayLevelFindingTime() << endl;
		cout << "Thresholding computing time: " << recon.statistic(2).optimalThresholdComputingTime() << endl;
		cout << "Noise removal time:          " << recon.statistic(2).noiseRemovalTime() << endl;
		cout << "Preprocessing time:          " << recon.statistic(2).preprocessingTime() << endl;
		cout << endl;
		
		recon.writeExternalImage(image);
		image.write("results.png");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

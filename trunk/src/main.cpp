#include <iostream>
#include <ctime>
using namespace std;

#include <Magick++.h>
using namespace Magick;

#include "Recognizer.h"

///
/// Command line program for testing purposes.
///
int main (int argc, char const *argv[])
{
	try
	{
		Image image( argv[1] );
		Recognizer recon( image );
		
		clock_t initialTime, elapsedTime;
		double microseconds = 0.0;

		for ( unsigned int i = 0; i < 1000; ++i )
		{
			initialTime = clock();
			recon.obtainText();
			elapsedTime = clock();
			
			microseconds = microseconds + ((elapsedTime - initialTime) / 1000.0);
		}
		std::cout << microseconds / CLOCKS_PER_SEC << std::endl;	

		recon.writeExternalImage(image);
		image.write("results.png");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

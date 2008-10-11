#include <iostream>
using namespace std;

#include <Magick++.h>
using namespace Magick;

#include "Recognizer.h"

#include "boost/timer.hpp"

///
/// Command line program for testing purposes.
///
int main (int argc, char const *argv[])
{
	try
	{
		Image image( argv[1] );
		Recognizer recon( image );
		
		boost::timer timer; 
		
		double microseconds = 0.0;
		
		for ( unsigned int i = 0; i < 1000; ++i )
		{
			timer.restart();
			recon.obtainText();
			microseconds += timer.elapsed();
		}
		
		cout << microseconds / 1000.0 << endl;
		recon.writeExternalImage(image);
		image.write("results.png");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

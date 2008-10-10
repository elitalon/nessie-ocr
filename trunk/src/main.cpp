#include <iostream>
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
		recon.obtainText();
		recon.writeExternalImage(image);
		
		image.write("results.png");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

#include <iostream>
using namespace std;

#include "Clip.h"
#include "Preprocessor.h"

#include <Magick++.h>
using namespace Magick;



///
/// Command line program for testing purposes.
///
int main (int argc, char const *argv[])
{
	try
	{
		// Load image form disk
		Image img(argv[1]);
		
		// Create a clip from the image
		Clip pressClip (img, 0, 0, img.rows(), img.columns());
		
		// Create a preprocessor
		Preprocessor preprocessor;
		
		// Find the background reference level
		cout << preprocessor.findBackgroundReferenceGrayLevel(pressClip) << endl;	
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	catch (NessieException &error)
	{
		cout << error.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown error" << endl;
	}
    return 0;
}

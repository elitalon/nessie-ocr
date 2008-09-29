#include <iostream>
using namespace std;

#include "Clip.h"
#include "Pixel.h"

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
		
		// Make a clip from the image
		Clip pressClip (img, 0, 0, img.rows(), img.columns());
		
		pressClip.colorspace(COLORSPACE_RGB);
		
		// Change the color of every pixel to red
		for (unsigned int i=0; i < pressClip.height(); ++i)
		{
			for (unsigned int j=0; j < pressClip.width(); ++j)
			{
				Pixel p = pressClip.getPixel(i,j);
				pressClip.setPixel(i, j, p.red(), p.green(), p.blue());
			}
		}
		
		// Write result to another file
		pressClip.image().write("test.png");
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

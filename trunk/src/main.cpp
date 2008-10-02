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
	Image img;
	
	img.read( argv[1] );
	
	Clip clip(img, 0, 0, img.rows(), img.columns());
	
	Preprocessor preprocessor;
	
	preprocessor.removeIsolatedNoise(clip, 1);
	
	clip.image().write("result.png");
}
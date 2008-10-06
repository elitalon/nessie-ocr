#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

#include <Magick++.h>
using namespace Magick;

#include "Clip.h"
#include "Preprocessor.h"

///
/// Command line program for testing purposes.
///
int main (int argc, char const *argv[])
{
	Image img;
	
	img.read(argv[1]);
	
	Clip clip(img, 0,0,img.rows(), img.columns());
	Preprocessor p;
	
	p.computeOptimalThreshold(clip);
	p.removeIsolatedNoise(clip, 2);
	
	return 0;
}
#include <iostream>
using namespace std;

#include "Style.h"


///
/// Command line program for testing purposes.
///
/// @author Eliezer Talón
/// @date 2008-09-18
int main (int argc, char const *argv[])
{
	Style sty(0, FontColor(256, 256, 256), NORMAL);

	cout << sty.getColor().red << endl;
	cout << sty.getColor().green << endl;
	cout << sty.getColor().blue << endl;
	return 0;
}
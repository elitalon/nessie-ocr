#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Text.h"

///
/// Command line program for testing purposes.
///
/// @author Eliezer Talón
/// @date 2008-09-22
/// 
int main (int argc, char const *argv[])
{
	Text str("pepito");
	str.removeCharacter(8);
	cout << str.getContent() << endl;
	
    return 0;
}

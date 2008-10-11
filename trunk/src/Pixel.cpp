///
/// @file
/// @brief Implementation of the class Pixel
///

#include "Pixel.hpp"


///
/// @details Initializes a empty Pixel object located at (0,0)
/// 
Pixel::Pixel ()
	: x_(0), y_(0), grayLevel_(0)
{
	
};


///
/// @details Initializes a Pixel object with the coordinates and gray level provided. If the gray level
/// 
Pixel::Pixel(const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel)
	:	x_(x), y_(y), grayLevel_(grayLevel)
{
	
};

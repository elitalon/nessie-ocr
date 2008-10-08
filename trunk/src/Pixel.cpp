///
/// @file
/// @brief Implementation of the class Pixel
///

#include "Pixel.h"


///
/// @details Initializes a empty Pixel object located at (0,0)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
Pixel::Pixel ()
	: x_(0), y_(0), grayLevel_(0.0)
{
	
};


///
/// @details Initializes a Pixel object with the coordinates and gray level provided. If the gray level
/// 
/// @param x			X coordinate (row) of the pixel
/// @param y			Y coordinate (colum) of the pixel
/// @param grayLevel	Pixel gray level
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
/// 
Pixel::Pixel(const unsigned int &x, const unsigned int &y, const double &grayLevel)
	:	x_(x), y_(y)
{
	if ( grayLevel < 0.0 )
		grayLevel_ = 0.0;
	else
	{
		if ( grayLevel > 1.0 )
			grayLevel_ = 1.0;
		else
			grayLevel_ = grayLevel;
	}
};


/// 
/// @return The gray level of the pixel
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
double Pixel::grayLevel () const
{
	return grayLevel_;
};


/// 
/// @param grayLevel The gray level of the pixel
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Pixel::grayLevel (const double &grayLevel)
{
	if ( grayLevel < 0.0 )
		grayLevel_ = 0.0;
	else
	{
		if ( grayLevel > 1.0 )
			grayLevel_ = 1.0;
		else
			grayLevel_ = grayLevel;
	}
};

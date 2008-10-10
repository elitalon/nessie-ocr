///
/// @file
/// @brief Implementation of the class Clip
///

#include "Clip.h"
#include "NessieException.h"

#include <iostream>

///
/// @details Initializes a Clip object located at coordinates (x,y) in the source image, with the height and width passed.
/// The x value indicates the row within the image, while the y value indicates the column. If x or y are out of the image borders,
/// an exception is thrown. If the width and height are over the image borders the clip is truncated.
/// 
/// @param image	The underlying image where the clip belongs to
/// @param x		The upper left-most pixel X coordinate of the clip
/// @param y		The upper left-most pixel Y coordinate of the clip
/// @param height	The height of the clip
/// @param width	The width of the clip
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
///
Clip::Clip (const std::vector<unsigned char> &image, const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width)
	: x_(x), y_(y), width_(width), height_(height)
{
	// Compute the number of pixels within the clip
	nPixels_ = width_ * height_;
	
	// Allocate space for the clip
	pixels_.reserve(nPixels_);
	
	// Copy the contents of the frame within the source image to the clip
	unsigned int index = (x * width_) + y;
	std::vector<unsigned char>::const_iterator imageIterator = image.begin() + index;
	
	pixels_.assign (imageIterator, (imageIterator + nPixels_));
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// The gray level must be normalized in a value from 0 to 255, otherwise it is truncated.
///
/// @param x			The upper left-most pixel X coordinate of the clip
/// @param y			The upper left-most pixel Y coordinate of the clip
/// @param grayLevel	The new gray level for the pixel at coordinates (x,y)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
///
void Clip::setPixelGrayLevel (const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel)
{
	unsigned int index = (x * width_) + y;
	
	if ( index >= pixels_.size() )
		throw NessieException ("Clip::setPixelGrayLevel(const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel) : The coordinates are outside the clip");

	pixels_[index] = grayLevel;
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// 
/// @param x	The upper left-most pixel X coordinate of the clip
/// @param y	The upper left-most pixel Y coordinate of the clip
/// 
/// @return The gray level of the pixel
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
///
unsigned char Clip::getPixelGrayLevel (const unsigned int &x, const unsigned int &y) const
{
	unsigned int index = (x * width_) + y;
	
	if ( index >= pixels_.size() )
		throw NessieException ("Clip::getPixelGrayLevel(const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel) : The coordinates are outside the clip");
		
	return pixels_[index];
};

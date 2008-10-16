///
/// @file
/// @brief Implementation of the class Clip
///

#include "Clip.hpp"
#include "NessieException.hpp"


///
/// @details Initializes a Clip object located at coordinates (x,y) in the source image, with the height and width passed.
/// The x value indicates the row within the image, while the y value indicates the column.
/// 
Clip::Clip (const std::vector<unsigned char> &image, const unsigned int &imageWidth, const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width)
	: x_(x), y_(y), width_(width), height_(height)
{
	// Compute the number of pixels within the clip
	nPixels_ = width_ * height_;
	
	// Allocate space for the clip
	pixels_.reserve(nPixels_);
	
	// Copy the contents of the frame within the source image to the clip
	for ( unsigned int i = x; i < (x + height_); ++i )
	{
		std::vector<unsigned char>::const_iterator rowIterator = image.begin();
		advance (rowIterator, (i * imageWidth) + y);
		
		for ( unsigned int j = 0; j < width_; ++j )
		{
			pixels_.push_back(*rowIterator);
			advance (rowIterator, 1);
		}
	}
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// The gray level must be normalized in a value from 0 to 255, otherwise it is truncated.
///
void Clip::setPixelGrayLevel (const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel)
{
	unsigned int index = (x * width_) + y;
	
	if ( index >= pixels_.size() )
		throw NessieException ("Clip::setPixelGrayLevel() : The coordinates are outside the clip");

	pixels_[index] = grayLevel;
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// 
const unsigned char &Clip::getPixelGrayLevel (const unsigned int &x, const unsigned int &y) const
{
	unsigned int index = (x * width_) + y;
	
	if ( index >= pixels_.size() )
		throw NessieException ("Clip::getPixelGrayLevel() : The coordinates are outside the clip");
		
	return pixels_[index];
};

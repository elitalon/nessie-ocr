///
/// @file
/// @brief Implementation of class Clip
///

#include "Clip.h"
#include "NessieException.h"

#include <iostream>
#include <Magick++.h>


///
/// @details Initializes a Clip object located at coordinates (x,y) in the source image, with the height and width passed.
/// The x value indicates the row within the image, while the y value indicates the column. If x or y are out of the image borders,
/// an exception is thrown. If the width and height are over the image borders the clip is truncated.
/// 
/// @remarks By default the image is always converted into a grayscale colorspace
/// 
/// @param image	The underlying image where the clip belongs to
/// @param x		The upper left-most pixel X coordinate of the clip
/// @param y		The upper left-most pixel Y coordinate of the clip
/// @param height	The height of the clip
/// @param width	The width of the clip
/// 
/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Magick++::Image</a>
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
Clip::Clip (const Magick::Image &image, const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width)
	: image_(image)
{
	try
	{
		// Associate a frame with the image
		frame_ = new Magick::Pixels(image_);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	
	// Test the clip top left-most corner is inside the image
	if ( x >= image_.rows() or x < 0 )
	{
		delete frame_;
		throw NessieException ("In constructor Clip::Clip(): The X coordinate of clip's upper leftmost pixel is out of image borders");
	}
	else
		x_ = x;
	
	if ( y >= image_.columns() or y < 0 )
	{
		delete frame_;
		throw NessieException ("In constructor Clip::Clip(): The Y coordinate of clip's upper leftmost pixel is out of image borders");
	}
	else
		y_ = y;
	
		
	// Test the clip size is consistent with the image size
	if ( (x_ + height) > image_.rows() )
		height_ = image_.rows() - x_;
	else
		height_ = height;
	
	if ( (y_ + width) > image_.columns() )
		width_ = image_.columns() - y_;
	else
		width_ = width;
		
	
	try
	{
		// Initializes the pointer to the clip origin
		originPixel_ = frame_->get(x_, y_, width_, height_);
		
		// Convert the image into a grayscale mode
		image_.type(Magick::GrayscaleType);		
	}
	catch (std::exception &e)
	{
		delete frame_;
		std::cout << e.what() << std::endl;
	}
};


///
/// @details Destroys a Clip object, deleting all the associated data from Magick++ API
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
Clip::~Clip ()
{
	delete frame_;
};


///
/// @return The underlying image where the clip belongs to
/// 
/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Magick++::Image</a>
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
Magick::Image Clip::image ()
{
	return image_;
};


///
/// @return The upper left-most pixel X coordinate of the clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
unsigned int Clip::x () const
{
	return x_;
};


///
/// @details If the new value x is over the image borders, an exception is thrown.
/// 
/// @param x The upper left-most pixel X coordinate of the clip
/// 
/// @throw NessieException
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Clip::x (const unsigned int &x)
{
	if ( x >= image_.rows() or x < 0 )
		throw NessieException ("Clip::xOrigin(const unsigned int &x): The X coordinate of clip's upper leftmost pixel is out of image borders");
	else
		x_ = x;
	
	adjustClipSize();
	relocateClipOrigin();
};


///
/// @return The upper left-most pixel Y coordinate of the clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
unsigned int Clip::y () const
{
	return y_;
};


///
/// @details If the new value y is over the image borders, an exception is thrown.
/// 
/// @param y The upper left-most pixel Y coordinate of the clip
/// 
/// @throw NessieException
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Clip::y (const unsigned int &y)
{
	if ( y >= image_.columns() or y < 0 )
		throw NessieException ("Clip::yOrigin(const unsigned int &y): The Y coordinate of clip's upper leftmost pixel is out of image borders");
	else
		y_ = y;
	
	adjustClipSize();
	relocateClipOrigin();
};


///
/// @return The height of the clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
unsigned int Clip::height () const
{
	return height_;
};


///
/// @details If the height is over the image borders the clip is truncated to its maximum allowed value.
/// 
/// @param height The height of the clip
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Clip::height (const unsigned int &height)
{
	if ( (x_ + height) > image_.rows() )
		height_ = image_.rows() - x_;
	else
		height_ = height;
	
	relocateClipOrigin();
};


///
/// @return The width of the clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
unsigned int Clip::width () const
{
	return width_;
};


///
/// @details If the width is over the image borders the clip is truncated to its maximum allowed value.
/// 
/// @param width The height of the clip
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Clip::width (const unsigned int &width)
{
	if ( (y_ + width) > image_.columns() )
		width_ = image_.columns() - y_;
	else
		width_ = width;
	
	relocateClipOrigin();
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// 
/// @param x	The upper left-most pixel X coordinate of the clip
/// @param y	The upper left-most pixel Y coordinate of the clip
/// 
/// @return The pixel at coordinates (x,y)
/// 
/// @see Pixel
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
/// 
Pixel Clip::getPixel (const unsigned int &x, const unsigned int &y) const
{
	// Check the location is inside the clip borders
	if ( (x >= height_) or (x < 0) )
		throw NessieException ("Clip::getPixel(const unsigned int &x, const unsigned int &y): The X coordinate is out of image borders");
	
	if ( (y >= width_) or (y < 0) )
		throw NessieException ("Clip::getPixel(const unsigned int &x, const unsigned int &y): The Y coordinate is out of image borders");
	
	// Get the pixel at desired location
	Magick::PixelPacket* selectedPixel = originPixel_ + (x * width_) + y;
	
	try
	{
		// Build a Pixel object with the pixel gray level
		Magick::ColorGray grayLevel(*selectedPixel);
		return Pixel(x, y, grayLevel.shade());
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return Pixel();
	}
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// The gray level must be normalized in a value from 0 to 1, otherwise it is truncated either to 0 if it's less than 0
/// or to 1 if it's greater than 1.
///
/// @param x			The upper left-most pixel X coordinate of the clip
/// @param y			The upper left-most pixel Y coordinate of the clip
/// @param grayLevel	The new gray level for the pixel at coordinates (x,y)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Clip::setPixel (const unsigned int &x, const unsigned int &y, const double &grayLevel)
{
	try
	{
		// Ensure that there is only one reference to underlying image.
		// If this is not done, then image pixels will not be modified.
		image_.modifyImage();
	
		// Check the location is inside the clip borders
		if ( x >= height_ or x < 0 )
			throw NessieException ("Clip::setPixel(const unsigned int &x, const unsigned int &y, const double &grayLevel): The X coordinate is out of image borders");

		if ( y >= width_ or y < 0 )
			throw NessieException ("Clip::setPixel(const unsigned int &x, const unsigned int &y, const double &grayLevel): The Y coordinate is out of image borders");

		// Get the pixel at desired location
		Magick::PixelPacket* selectedPixel = originPixel_ + (x * width_) + y;

		// Assign the desired value to the pixel
		*selectedPixel = Magick::ColorGray(grayLevel);

		// Apply changes on the image
		frame_->sync();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-06
///
unsigned int Clip::nPixels () const
{
	return (height_ * width_);
};


///
/// @details When any of the clip attributes change, it is neccesary to relocate the clip position over the source image
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
///
void Clip::relocateClipOrigin ()
{
	try
	{		
		// Relocate the pointer to the clip new origin
		originPixel_ = frame_->get(x_, y_, width_, height_);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}	
};


///
/// @details When the clip origin changes, it is neccesary to test whether the clip dimensions fall out of the
/// underlying image or not
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
/// 
void Clip::adjustClipSize ()
{
	if ( (y_ + width_) > image_.columns() )
		width_ = image_.columns() - y_;
	
	if ( (x_ + height_) > image_.rows() )
		height_ = image_.rows() - x_;
};

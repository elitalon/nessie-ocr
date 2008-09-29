#include "Clip.h"

///
/// @file
/// @brief Implementation of class Clip
///


///
/// @details Initializes a Clip object located at coordinates (xOrigin,yOrigin) in the source image, with the height and width passed.
/// The xOrigin value allows access to the image rows, while the yOrigin value allows access to the image columns. If the xOrigin and
/// yOrigin are out of the image borders, an exception is thrown. If the width and height are over the image borders the clip is
/// truncated. Note that, as in C and C++, indexes begin at (0,0).
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
Clip::Clip (Image image, unsigned int xOrigin, unsigned int yOrigin, unsigned int height, unsigned int width) : image_(image)
{
	try
	{
		// Associate a frame with the image
		frame_ = new Pixels(image_);
	}
	catch (exception& e)
	{
		delete frame_;
		cout << e.what() << endl;
	}
	
	
	// Test the clip borders are inside the image
	if ( xOrigin >= image_.rows() || xOrigin < 0 )
		throw NessieException ("Clip::Clip: The X coordinate of clip's upper leftmost pixel is out of image borders");
	else
		xOrigin_ = xOrigin;
	
	if ( yOrigin >= image_.columns() || yOrigin < 0 )
		throw NessieException ("Clip::Clip: The Y coordinate of clip's upper leftmost pixel is out of image borders");
	else
		yOrigin_ = yOrigin;
	
	
	// Test the clip size is consistent with the image size
	if ( (xOrigin_ + width) > image_.columns() )
		width_ = image_.columns() - xOrigin_;
	else
		width_ = width;
	
	if ( (yOrigin_ + height) > image_.rows() )
		height_ = image_.rows() - yOrigin_;
	else
		height_ = height;
		
	
	try
	{
		// Initializes the pointer to the clip origin
		originPixel_ = frame_->get(xOrigin_, yOrigin_, width_, height_);
		
		// Initializes the image colorspace
		switch (image_.type())
		{
			case GrayscaleType:
			{
				colorspace_ = COLORSPACE_GRAYSCALE;
				break;
			}
			case TrueColorType:
			{
				colorspace_ = COLORSPACE_RGB;
				break;
			}
			case BilevelType:
			{
				colorspace_ = COLORSPACE_MONOCHROMATIC;
				break;
			}
			default:
			{
				colorspace_ = COLORSPACE_UNDEFINED;
				break;
			}
		}
	}
	catch (exception& e)
	{
		delete frame_;
		cout << e.what() << endl;
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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
Image Clip::image ()
{
	return image_;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
unsigned int Clip::xOrigin () const
{
	return xOrigin_;
};


///
/// @details If the new value x is over the image borders, an exception is thrown.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::xOrigin (unsigned int x)
{
	if ( x >= image_.rows() || x < 0 )
		throw NessieException ("Clip::xOrigin: The X coordinate of clip's upper leftmost pixel is out of image borders");
	else
		xOrigin_ = x;
	
	adjustClipSize();
	relocateClipOrigin();
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
unsigned int Clip::yOrigin () const
{
	return yOrigin_;
};


///
/// @details If the new value y is over the image borders, an exception is thrown.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::yOrigin (unsigned int y)
{
	if ( y >= image_.columns() || y < 0 )
		throw NessieException ("Clip::yOrigin: The Y coordinate of clip's upper leftmost pixel is out of image borders");
	else
		yOrigin_ = y;
	
	adjustClipSize();
	relocateClipOrigin();
};


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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::height (unsigned int height)
{
	if ( (yOrigin_ + height) > image_.rows() )
		height_ = image_.rows() - yOrigin_;
	else
		height_ = height;
	
	relocateClipOrigin();
};


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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::width (unsigned int width)
{
	if ( (xOrigin_ + width) > image_.columns() )
		width_ = image_.columns() - xOrigin_;
	else
		width_ = width;
	
	relocateClipOrigin();
};


///
/// @see Colorspace
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-24
///
Colorspace Clip::colorspace () const
{
	return colorspace_;
};


///
/// @details By setting the colorspace to a certain value the image colorspace changes, affecting all its pixels
/// and the information regarding the image colors.
/// 
/// @see Colorspace
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::colorspace (Colorspace colorspace)
{
	try
	{
		// Ensure that there is only one reference to underlying image.
		// If this is not done, then image pixels will not be modified.
		image_.modifyImage();
		
		// Convert the image colorspace to the new one
		switch (colorspace)
		{
			case COLORSPACE_GRAYSCALE:
			{
				image_.type( GrayscaleType );
				colorspace_ = COLORSPACE_GRAYSCALE;
				break;
			}
			case COLORSPACE_RGB:
			{
				image_.type( TrueColorType );
				colorspace_ = COLORSPACE_RGB;
				break;
			}
			case COLORSPACE_MONOCHROMATIC:
			{
				image_.type( BilevelType );
				colorspace_ = COLORSPACE_MONOCHROMATIC;
				break;
			}
			default:
			{
				// The colorspace remains the same
				break;
			}
		}
		
		// Apply changes on the image
		frame_->sync();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
bool Clip::isGrayscale () const
{
	if ( colorspace_ == COLORSPACE_GRAYSCALE )
		return true;
	else
		return false;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
bool Clip::isColor () const
{
	if ( colorspace_ == COLORSPACE_RGB )
		return true;
	else
		return false;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
bool Clip::isMonochromatic () const
{
	if ( colorspace_ == COLORSPACE_MONOCHROMATIC )
		return true;
	else
		return false;
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// If the image colorspace is undefined, an exception is also thrown.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
/// 
Pixel Clip::getPixel (unsigned int x, unsigned int y) const
{
	// Check the location is inside the clip borders
	if ( x >= frame_->rows() || x < 0 )
		throw NessieException ("Clip::getPixel: The X coordinate is out of image borders");
	
	if ( y >= frame_->columns() || y < 0 )
		throw NessieException ("Clip::getPixel: The Y coordinate is out of image borders");
	
	// Get the pixel at desired location
	PixelPacket* selectedPixel = originPixel_ + (x * frame_->columns()) + y;
	
	// Build a new Pixel object with color information depending on image colorspace
	switch (colorspace_)
	{
		case COLORSPACE_GRAYSCALE:
		{
			ColorGray grayLevel(*selectedPixel);
			return Pixel(x, y, grayLevel.shade());
			break;
		}
		case COLORSPACE_RGB:
		{
			ColorRGB rgbColor(*selectedPixel);
			return Pixel(x, y, rgbColor.red(), rgbColor.green(), rgbColor.blue());
			break;
		}
		case COLORSPACE_MONOCHROMATIC:
		{
			ColorMono isForeground(*selectedPixel);
			return Pixel(x, y, isForeground.mono());
			break;
		}
		default:
		{
			throw NessieException ("Clip::getPixel: The pixel cannot be returned because the image colorspace is undefined");
			break;
		}
	}
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// If the image colorspace is not grayscale no changes are made. The gray level must be normalized in a value from 0 to 1,
/// otherwise it is truncated either to 0 if it's less than 0 or to 1 if it's greater than 1.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::setPixel (unsigned int x, unsigned int y, double grayLevel)
{
	if ( colorspace_ != COLORSPACE_GRAYSCALE )
		return;
	
	try
	{
		// Ensure that there is only one reference to underlying image.
		// If this is not done, then image pixels will not be modified.
		image_.modifyImage();
	
		// Check the location is inside the clip borders
		if ( x >= frame_->rows() || x < 0 )
			throw NessieException ("Clip::setPixel: The X coordinate is out of image borders");

		if ( y >= frame_->columns() || y < 0 )
			throw NessieException ("Clip::setPixel: The Y coordinate is out of image borders");

		// Get the pixel at desired location
		PixelPacket* selectedPixel = originPixel_ + (x * frame_->columns()) + y;

		// Assign the desired value to the pixel
		*selectedPixel = ColorGray(grayLevel);

		// Apply changes on the image
		frame_->sync();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// If the image colorspace is not RGB no changes are made. Each channel value must be normalized in a value from 0 to 1,
/// otherwise it is truncated either to 0 if it's less than 0 or to 1 if it's greater than 1.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::setPixel (unsigned int x, unsigned int y, double red, double green, double blue)
{
	if ( colorspace_ != COLORSPACE_RGB )
		return;
	
	try
	{
		// Ensure that there is only one reference to underlying image.
		// If this is not done, then image pixels will not be modified.
		image_.modifyImage();
		
		// Check the location is inside the clip borders
		if ( x >= frame_->rows() || x < 0 )
			throw NessieException ("Clip::setPixel: The X coordinate is out of image borders");

		if ( y >= frame_->columns() || y < 0 )
			throw NessieException ("Clip::setPixel: The Y coordinate is out of image borders");

		// Get the pixel at desired location
		PixelPacket* selectedPixel = originPixel_ + (x * frame_->columns()) + y;

		// Assign the desired value to the pixel
		*selectedPixel = ColorRGB(red, green, blue);

		// Apply changes on the image
		frame_->sync();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// If the image colorspace is not monochromatic no changes are made
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::setPixel (unsigned int x, unsigned int y, bool isForeground)
{
	if ( colorspace_ != COLORSPACE_MONOCHROMATIC )
		return;
	
	try
	{
		// Ensure that there is only one reference to underlying image.
		// If this is not done, then image pixels will not be modified.
		image_.modifyImage();
		
		// Check the location is inside the clip borders
		if ( x >= frame_->rows() || x < 0 )
			throw NessieException ("Clip::setPixel: The X coordinate is out of image borders");

		if ( y >= frame_->columns() || y < 0 )
			throw NessieException ("Clip::setPixel: The Y coordinate is out of image borders");

		// Get the pixel at desired location
		PixelPacket* selectedPixel = originPixel_ + (x * frame_->columns()) + y;

		// Assign the desired value to the pixel
		*selectedPixel = ColorMono(isForeground);

		// Apply changes on the image
		frame_->sync();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
};


///
/// @details When any of the clip attributes change, it is neccesary to relocate the clip position over the source image
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
void Clip::relocateClipOrigin ()
{
	try
	{		
		// Relocate the pointer to the clip new origin
		originPixel_ = frame_->get(xOrigin_, yOrigin_, width_, height_);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}	
};


///
/// @details When the clip origin changes, it is neccesary to test whether the clip dimensions fall out of the
/// underlying image or not
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
/// 
void Clip::adjustClipSize ()
{
	if ( (yOrigin_ + width_) > image_.columns() )
		width_ = image_.columns() - yOrigin_;
	
	if ( (xOrigin_ + height_) > image_.rows() )
		height_ = image_.rows() - xOrigin_;
};

#include "Pixel.h"

///
/// @file
/// @brief Implementation of class Pixel
///

///
/// @details Initializes a Pixel object using a grayscale colorspace. When using grayscale representation
/// all the pixels are considered as belonging to the foreground, and they have a zero value per RGB channel.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
Pixel::Pixel(unsigned int x, unsigned int y, double grayLevel)
	:	x_(x), y_(y), grayLevel_(grayLevel), red_(0.0), green_(0.0), blue_(0.0), isForeground_(true), colorspace_(COLORSPACE_GRAYSCALE)
{
	
};


///
/// @details Initializes a Pixel object using a RGB colorspace. When using RGB representation
/// all the pixels are considered as belonging to the foreground, and they have an associated grayscale value
/// computed according to the equation \f$grayLevel = (0.3 * redValue) + (0.59 * greenValue) + (0.11 * blueValue) \f$
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
Pixel::Pixel(unsigned int x, unsigned int y, double red, double green, double blue)
	:	x_(x), y_(y), red_(red), green_(green), blue_(blue), isForeground_(true), colorspace_(COLORSPACE_RGB)
{
	grayLevel_ = (0.3 * red) + (0.59 * green) + (0.11 * blue);
};


///
/// @details Initializes a Pixel object using a monochromatic colorspace. When using a monochromatic representation
/// all the pixels have a zero or one value per channel both on RGB and grayscale colorspace. Note that this does not mean
/// the foreground color is black or white, it's just a way of representing boolean values. The true foreground color should
/// be gathered using the appropiate method in class Clip.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
Pixel::Pixel(unsigned int x, unsigned int y, bool isForeground)
	:	x_(x), y_(y), isForeground_(isForeground), colorspace_(COLORSPACE_MONOCHROMATIC)
{
	if ( isForeground )
	{
		grayLevel_ = 0.0;
		red_ = 0.0;
		green_ = 0.0;
		blue_ = 0.0;
	}
	else
	{
		grayLevel_ = 1.0;
		red_ = 1.0;
		green_ = 1.0;
		blue_ = 1.0;
	}
};


///
/// @details Destroys a Pixel object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
///
Pixel::~Pixel ()
{
	
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
unsigned int Pixel::x () const
{
	return x_;
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
unsigned int Pixel::y () const
{
	return y_;
};


///
/// @details If the pixel colorspace is not COLORSPACE_GRAYSCALE then this method returns
/// a certain value depending on what is the current colorspace. If it is COLORSPACE_MONOCHROMATIC this method
/// returns 0.0 when the pixel belongs to the foreground or 1.0 otherwise. If it is COLORSPACE_RGB this method
/// returns the associated grayscale value computed according to the equation
/// \f$grayLevel = (0.3 * redValue) + (0.59 * greenValue) + (0.11 * blueValue)\f$
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
double Pixel::grayLevel () const
{
	return grayLevel_;
};


///
/// @details If the pixel current colorspace is different from COLORSPACE_GRAYSCALE no change is made
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Pixel::grayLevel (double grayLevel)
{
	if ( colorspace_ == COLORSPACE_GRAYSCALE )
	{
		if ( grayLevel < 0.0 )
			grayLevel_ = 0.0;
		else
		{
			if ( grayLevel > 1.0 )
				grayLevel = 1.0;
			else
				grayLevel_ = grayLevel;
		}
		
		isForeground_ = true;
		red_ = 0.0;
		green_ = 0.0;
		blue_ = 0.0;
	}
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Pixel::red (double value)
{
	if ( value < 0.0 )
		red_ = 0.0;
	else
	{
		if ( value > 1.0 )
			red_ = 1.0;
		else
			red_ = value;
	}

	// Compute the grayscale equivalent value
	grayLevel_ = (0.3 * red_) + (0.59 * green_) + (0.11 * blue_);
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Pixel::green (double value)
{
	if ( value < 0.0 )
		green_ = 0.0;
	else
	{
		if ( value > 1.0 )
			green_ = 1.0;
		else
			green_ = value;
	}
	
	// Compute the grayscale equivalent value
	grayLevel_ = (0.3 * red_) + (0.59 * green_) + (0.11 * blue_);
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Pixel::blue (double value)
{
	if ( value < 0.0 )
		blue_ = 0.0;
	else
	{
		if ( value > 1.0 )
			blue_ = 1.0;
		else
			blue_ = value;
	}
	
	// Compute the grayscale equivalent value
	grayLevel_ = (0.3 * red_) + (0.59 * green_) + (0.11 * blue_);
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
double Pixel::red () const
{
	return red_;
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
double Pixel::green () const
{
	return green_;
};


/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
double Pixel::blue () const
{
	return blue_;
};


///
/// @details If the pixel current colorspace is different from COLORSPACE_RGB no change is made
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Pixel::setColor (double red, double green, double blue)
{
	if ( colorspace_ == COLORSPACE_RGB )
	{
		if ( red < 0.0 )
			red_ = 0.0;
		else
		{
			if ( red > 1.0 )
				red_ = 1.0;
			else
				red_ = red;
		}
		
		if ( green < 0.0 )
			green_ = 0.0;
		else
		{
			if ( green > 1.0 )
				green_ = 1.0;
			else
				green_ = green;
		}
		
		if ( blue < 0.0 )
			blue_ = 0.0;
		else
		{
			if ( blue > 1.0 )
				blue_ = 1.0;
			else
				blue_ = blue;
		}
		
		// Set the other representations
		grayLevel_ = (0.3 * red_) + (0.59 * green_) + (0.11 * blue_);
		isForeground_ = true;
	}
};


/// 
/// @details If the pixel colorspace is not COLORSPACE_MONOCHROMATIC this method returns
/// always true.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
bool Pixel::isForeground () const
{
	return isForeground_;
};


///
/// @details If the pixel current colorspace is different from COLORSPACE_MONOCHROMATIC no change is made.
/// Note that this does not mean the foreground color is black or white, it's just a way of representing boolean values.
/// The true foreground color should be gathered using the appropiate method in class Clip.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Pixel::isForeground (bool isForeground)
{
	if ( colorspace_ == COLORSPACE_MONOCHROMATIC )
	{
		isForeground_ = isForeground;
		
		if ( isForeground_ )
		{
			grayLevel_ = 0.0;
			red_ = 0.0;
			green_ = 0.0;
			blue_ = 0.0;
		}
		else
		{
			grayLevel_ = 1.0;
			red_ = 1.0;
			green_ = 1.0;
			blue_ = 1.0;
		}
	}
		
};

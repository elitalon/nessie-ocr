#if !defined(_PIXEL_H)
#define _PIXEL_H

///
/// @file
/// @brief Declaration of class Pixel
///

#include "Colorspace.h"

#include <Magick++.h>
using namespace Magick;

///
/// Information about an image pixel.
///
/// This class stores all the information of a pixel within a press clip,
/// no matter if we are dealing with the clip itself, or some other data structure
/// which makes use of it. Every pixel has a location, given by a pair of coordinates
/// x and y, and a color information, which may come in three formats: grayscale, RGB
/// or monochromatic.
/// 
/// The Clip::getColorspace() method gives the current colorspace that is associated
/// with the pixel and its underlying image, so that the right methods here can be invoked. If
/// a method related to one colorspace (e.g. getGrayLevel()) is called when the current colorspace
/// is actually another (e.g. COLORSPACE_RGB), a predefined value is returned. See the different
/// methods documentation to know what are these values.
/// 
/// @see Clip, Colorspace
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
class Pixel
{
	public:
		///
		/// Constructor
		///
		Pixel (unsigned int x, unsigned int y, double grayLevel);
	
		///
		/// Constructor
		///
		Pixel (unsigned int x, unsigned int y, double red, double green, double blue);
		
		///
		/// Constructor
		///
		Pixel (unsigned int x, unsigned int y, bool foreground);

		///
		/// Destructor
		///
		~Pixel ();
		
		///
		/// Returns the pixel's X coordinate 
		///
		unsigned int x () const;
		
		///
		/// Returns the pixel's Y coordinate 
		///
		unsigned int y () const;
		
		///
		/// Returns the pixel's gray level
		///
		double grayLevel () const;
		
		///
		/// Sets the pixel's gray level
		///
		void grayLevel (double grayLevel);
		
		///
		/// Returns the pixel's red component in RGB colorspace
		///
		double red () const;
		
		///
		/// Sets the pixel's red component in RGB colorspace
		///
		void red (double value);
		
		///
		/// Returns the pixel's green component in RGB colorspace
		///
		double green () const;
		
		///
		/// Sets the pixel's green component in RGB colorspace
		///
		void green (double value);
		
		///
		/// Returns the pixel's blue component in RGB colorspace
		///
		double blue () const;
		
		///
		/// Sets the pixel's blue component in RGB colorspace
		///
		void blue (double value);
		
		///
		/// Sets the pixel's color in RGB colorspace
		///
		void setColor (double red, double green, double blue);
		
		///
		/// Returns true if the pixel belongs to the image foreground
		///
		bool isForeground () const;
		
		///
		/// Sets whether the pixel belongs to the foreground or not
		///
		void isForeground (bool isForeground);

	private:
		///
		/// Pixel's X coordinate
		///
		unsigned int x_;
		
		///
		/// Pixel's Y coordinate
		///
		unsigned int y_;
		
		///
		/// Pixel's gray level.
		///
		double grayLevel_;
		
		///
		/// Pixel's red component in RGB colorspace
		///
		double red_;
		
		///
		/// Pixel's green component in RGB colorspace
		///
		double green_;
		
		///
		/// Pixel's blue component in RGB colorspace
		///
		double blue_;
		
		///
		/// Tells if the pixel belongs to the image foreground
		///
		bool isForeground_;
		
		///
		/// Colorspace of pixel
		///
		Colorspace colorspace_;
};

#endif  //_PIXEL_H

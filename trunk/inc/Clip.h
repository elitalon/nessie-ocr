#if !defined(_CLIP_H)
#define _CLIP_H

///
/// @file
/// @brief Declaration of class Clip
///

#include "NessieException.h"
#include "Pixel.h"
#include "Colorspace.h"

#include <Magick++.h>
using namespace Magick;

#include <exception>
#include <iostream>
using namespace std;


///
/// Press clip where the recognizer has to extract the text from.
/// 
/// This class manages the press clip where the recognizer has to extract the text,
/// loading it with the Magick++ utilities. The press clip is an image that may come
/// in several formats, such JPEG, PDF, PNG, etc. The ImageMagick library provides
/// an abstraction layer to keep the code independent from the format.
/// 
/// The idea behind this class is to encapsulate all the interactions with the Magick++ API, so that
/// the rest of the classes have a unified way to work with the original image.
/// 
/// @see Pixel, Colorspace
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
class Clip
{
	public:
		///
		/// Constructor
		///
		Clip (Image image, const unsigned int &xOrigin, const unsigned int &yOrigin, const unsigned int &height, const unsigned int &width);
		
		///
		/// Destructor
		///
		~Clip ();
		
		///
		/// Returns the current Image object
		///
		Image image ();
				
		///
		/// Returns the X coordinate of the clip's upper leftmost pixel
		///
		unsigned int xOrigin () const;
		
		///
		/// Sets the X coordinate of the clip's upper leftmost pixel
		///
		void xOrigin (const unsigned int &x);
		
		///
		/// Returns the Y coordinate of the clip's upper leftmost pixel
		///
		unsigned int yOrigin () const;
		
		///
		/// Sets the Y coordinate of the clip's upper leftmost pixel
		///
		void yOrigin (const unsigned int &y);
		
		///
		/// Returns the clip's height
		///
		unsigned int height () const;
		
		///
		/// Sets the clip's height
		///
		void height (const unsigned int &height);
		
		///
		/// Returns the clip's width
		///
		unsigned int width () const;
		
		///
		/// Sets the clip's width
		///
		void width (const unsigned int &width);
		
		///
		/// Returns the clip's current colorspace
		///
		Colorspace colorspace () const;
		
		///
		/// Sets the clip's current colorspace
		///
		void colorspace (const Colorspace &colorspace);
		
		///
		/// Returns true if the clip is in grayscale
		///
		bool isGrayscale () const;
		
		///
		/// Returns true if the clip is in color
		///
		bool isColor () const;
		
		///
		/// Returns true if the clips is in black and white
		///
		bool isMonochromatic () const;
		
		///
		/// Returns the pixel at coordinates (x,y)
		///
		Pixel getPixel (const unsigned int &x, const unsigned int &y) const;
		
		///
		/// Sets the gray level of a pixel at coordinates (x,y)
		///
		void setPixel (const unsigned int &x, const unsigned int &y, const double &grayLevel);
		
		///
		/// Sets the color of a pixel at coordinates (x,y)
		///
		void setPixel (const unsigned int &x, const unsigned int &y, const double &red, const double &green, const double &blue);
		
		///
		/// Sets whether a pixel at coordinates (x,y) belongs to the foreground or not
		///
		void setPixel (const unsigned int &x, const unsigned int &y, const bool &isForeground);
		
	private:
		///
		/// Image where the clip belongs to
		///
		Image image_;
		
		///
		/// X coordinate of the clip's upper leftmost pixel
		///
		unsigned int xOrigin_;

		///
		/// Y coordinate of the clip's upper leftmost pixel
		///
		unsigned int yOrigin_;

		///
		/// Height of the clip in pixels
		///
		unsigned int height_;

		///
		/// Width of the clip in pixels
		///
		unsigned int width_;
		
		///
		/// Clip's colorspace. It is modified automatically when the clip's image source changes
		///
		Colorspace colorspace_;
		
		///
		/// Pixels frame where the clip is located. It is modified automatically when the clip attributes change
		///
		Pixels* frame_;
		
		///
		/// Frame's upper leftmost pixel. It is modified automatically when information about the clip attributes change
		///
		PixelPacket* originPixel_;
		
		///
		/// Relocates the origin of the clip
		///
		void relocateClipOrigin ();
		
		///
		/// Adjusts the size of the clip
		///
		void adjustClipSize ();
};

#endif  //_CLIP_H

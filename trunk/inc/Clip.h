///
/// @file
/// @brief Declaration of class Clip
///

#if !defined(_CLIP_H)
#define _CLIP_H


#include "Pixel.h"
#include <Magick++.h>



///
/// Press clip where the recognizer has to extract the text from.
/// 
/// This class manages the press clips on a image loaded with the Magick++ utilities.
/// The press clip is an image that may come in several formats, such JPEG, PDF, PNG, etc.
/// The Magick++ library (an API for the ImageMagick suite) provides an abstraction layer
/// to keep the code independent from the image format.
/// 
/// The idea behind this class is to encapsulate all the interactions with Magick++,
/// so that the rest of the classes have an unified way to work with the original image.
/// 
/// @see Pixel, <a href="http://www.imagemagick.org">ImageMagick</a>, <a href="http://www.imagemagick.org/Magick++/">Magick++ API</a>
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-06
///
class Clip
{
	public:
		///
		/// Constructor
		///
		Clip (const Magick::Image &image, const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width);
		
		///
		/// Destructor
		///
		~Clip ();
		
		///
		/// Returns the current Image object
		///
		Magick::Image image ();
				
		///
		/// Returns the X coordinate of the clip's upper leftmost pixel
		///
		unsigned int x () const;
		
		///
		/// Sets the X coordinate of the clip's upper leftmost pixel
		///
		void x (const unsigned int &x);
		
		///
		/// Returns the Y coordinate of the clip's upper leftmost pixel
		///
		unsigned int y () const;
		
		///
		/// Sets the Y coordinate of the clip's upper leftmost pixel
		///
		void y (const unsigned int &y);
		
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
		/// Returns the pixel at coordinates (x,y)
		///
		Pixel getPixel (const unsigned int &x, const unsigned int &y) const;
		
		///
		/// Sets the gray level of a pixel at coordinates (x,y)
		///
		void setPixel (const unsigned int &x, const unsigned int &y, const double &grayLevel);
		
		///
		/// Returns the gray level of a pixel at coordinates (x,y)
		///
		double getPixelGrayLevel (const unsigned int &x, const unsigned int &y) const;
		
		///
		/// Returns the number of pixels within the clip
		///
		unsigned int nPixels () const;
		
	private:
		///
		/// Image where the clip belongs to
		///
		Magick::Image image_;
		
		///
		/// X coordinate of the clip's upper leftmost pixel
		///
		unsigned int x_;

		///
		/// Y coordinate of the clip's upper leftmost pixel
		///
		unsigned int y_;

		///
		/// Height of the clip in pixels
		///
		unsigned int height_;

		///
		/// Width of the clip in pixels
		///
		unsigned int width_;
		
		///
		/// Frame within the image where the clip is located. It is modified automatically when the clip attributes change
		///
		Magick::Pixels* frame_;
		
		///
		/// Frame's upper leftmost pixel. It is modified automatically when the clip attributes change
		///
		Magick::PixelPacket* originPixel_;

		
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

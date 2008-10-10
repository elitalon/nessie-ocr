///
/// @file
/// @brief Declaration of the class Clip
///

#if !defined(_CLIP_H)
#define _CLIP_H

#include <vector>



///
/// Press clip where the recognizer has to extract the text from.
/// 
/// This class stores a press clip as a set of pixels from the source image that representes the whole page
/// of a newspaper. The class that creates a Clip object must ensure that all the coordinates passed to the constructor
/// are inside the underlying image, since internally Clip only tests the coordinates when accesing the object later.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
///
class Clip
{
	public:
		///
		/// Constructor
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
		Clip (const std::vector<unsigned char> &image, const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width);
		
				
		///
		/// Sets the gray level of a pixel at coordinates (x,y)
		///
		/// @param x			The upper left-most pixel X coordinate of the clip
		/// @param y			The upper left-most pixel Y coordinate of the clip
		/// @param grayLevel	The new gray level for the pixel at coordinates (x,y)
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		void setPixelGrayLevel (const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel);
		
		
		///
		/// Returns the gray level of a pixel at coordinates (x,y)
		///
		/// @param x	The upper left-most pixel X coordinate of the clip
		/// @param y	The upper left-most pixel Y coordinate of the clip
		/// 
		/// @return The gray level of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		unsigned char getPixelGrayLevel (const unsigned int &x, const unsigned int &y) const;
		
		
		///
		/// Returns the pixels that defines the press clip.
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-07
		///
		std::vector<unsigned char> pixels () const;
		
		
		///
		/// Returns the number of pixels within the press clip.
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-07
		///
		unsigned int nPixels () const;
		
		
		///
		/// Returns the top left-most pixel x coordinate
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		///
		unsigned int x () const;
		
		
		///
		/// Returns the top left-most pixel y coordinate
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		///
		unsigned int y () const;
		
		
		///
		/// Returns the width of the clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		unsigned int width () const;
		
		
		///
		/// Returns the height of the clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		unsigned int height () const;
		
	private:
		///
		/// Top left-most pixel x coordinate
		///
		const unsigned int x_;
		
		///
		/// Top left-most pixel y coordinate
		///
		const unsigned int y_;
		
		///
		/// The width of the pixels
		///
		const unsigned int width_;
		
		///
		/// The height of the pixel
		///
		const unsigned int height_;
		
		///
		/// A set of pixels that defines the press clip
		///
		std::vector<unsigned char> pixels_;
		
		///
		/// Number of pixels within the image
		///
		unsigned int nPixels_;
};



//
// Implementation of inline functions
// 


///
/// @details
/// 
inline std::vector<unsigned char> Clip::pixels () const
{
	return pixels_;
};


///
/// @details
/// 
inline unsigned int Clip::nPixels () const
{
	return nPixels_;
};


///
/// @details
/// 
inline unsigned int Clip::x () const
{
	return x_;
};


///
/// @details
/// 
inline unsigned int Clip::y () const
{
	return y_;
};


///
/// @details
/// 
inline unsigned int Clip::width () const
{
	return width_;
};


///
/// @details
/// 
inline unsigned int Clip::height () const
{
	return height_;
};
#endif  //_CLIP_H

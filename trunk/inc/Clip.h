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
		Clip (const std::vector<unsigned char> &image, const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width);
		
		
		///
		/// Destructor
		///
		~Clip ();
		
				
		///
		/// Sets the gray level of a pixel at coordinates (x,y)
		///
		void setPixelGrayLevel (const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel);
		
		
		///
		/// Returns the gray level of a pixel at coordinates (x,y)
		///
		unsigned char getPixelGrayLevel (const unsigned int &x, const unsigned int &y) const;
		
		
		///
		/// Returns the pixels that defines the press clip.
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-07
		///
		inline std::vector<unsigned char> pixels () const
		{
			return pixels_;
		};
		
		
		///
		/// Returns the number of pixels within the press clip.
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-07
		///
		inline unsigned int nPixels () const
		{
			return nPixels_;
		};
		
		
		///
		/// Returns the width of the clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline unsigned int width () const
		{
			return width_;
		};
		
		
		///
		/// Returns the height of the clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline unsigned int height () const
		{
			return height_;
		};
		
	private:
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

#endif  //_CLIP_H

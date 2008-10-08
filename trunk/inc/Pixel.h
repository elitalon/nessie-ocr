///
/// @file
/// @brief Declaration of class Pixel
///

#if !defined(_PIXEL_H)
#define _PIXEL_H


///
/// Information about an image pixel.
///
/// This class stores all the information of a pixel within a press clip. Every pixel has a location
/// given by a pair of coordinates (x,y) and a color information in a grayscale colorspace of 256 levels.
/// 
/// The gray level of a pixel is normalized value between 0.0 and 1.0, where 0 corresponds to 0.0 (black)
/// and 255 corresponds to 1.0 (white). A monochromatic colorspace can be emulated using only 0.0 and 1.0.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
/// 
class Pixel
{
	public:
		///
		/// Constructor
		///
		Pixel ();


		///
		/// Constructor
		///		
		Pixel (const unsigned int &x, const unsigned int &y, const double &grayLevel);

		
		/// 
		/// @return The x coordinate (row) of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline unsigned int x () const
		{
			return x_;
		};
		
		
		/// 
		/// @return The y coordinate (column) of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline unsigned int y () const
		{
			return y_;
		};
		
		
		///
		/// Returns the pixel's gray level
		///
		double grayLevel () const;
		
		
		///
		/// Sets the pixel's gray level
		///
		void grayLevel (const double &grayLevel);

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
};

#endif  //_PIXEL_H

///
/// @file
/// @brief Declaration of the class Pixel
///

#if !defined(_PIXEL_H)
#define _PIXEL_H


///
/// Information about an image pixel.
///
/// This class stores all the information of a pixel within a press clip. Every pixel has a location
/// given by a pair of coordinates (x,y) and a color information in a grayscale colorspace of 256 levels.
/// 
/// The gray level of a pixel is a value between 0 and 255, where 0 corresponds to black and 255 corresponds to white.
/// A monochromatic colorspace can be emulated using only 0 and 255.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-10
/// 
class Pixel
{
	public:
		///
		/// Constructor
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		///
		Pixel ();


		///
		/// Constructor
		///	
		/// @param x			X coordinate (row) of the pixel
		/// @param y			Y coordinate (colum) of the pixel
		/// @param grayLevel	Pixel gray level
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		/// 
		Pixel (const unsigned int &x, const unsigned int &y, const unsigned char &grayLevel);

		
		/// 
		/// Returns the x coordinate of the pixel
		/// 
		/// @return The x coordinate (row) of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &x () const;		
		
		
		/// 
		/// Returns the y coordinate of the pixel
		/// 
		/// @return The y coordinate (column) of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &y () const;		
		
		
		///
		/// Returns the pixel's gray level
		///
		/// @return The gray level of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned char &grayLevel () const;
		
		
		///
		/// Sets the pixel's gray level
		///
		/// @param grayLevel The gray level of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		///
		void grayLevel (const unsigned char &grayLevel);


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
		unsigned char grayLevel_;
};



//
// Implementation of inline functions
// 


/// 
/// @details
/// 
inline const unsigned int &Pixel::x () const
{
	return x_;
};


/// 
/// @details
/// 
inline const unsigned int &Pixel::y () const
{
	return y_;
};


/// 
/// @details
/// 

inline const unsigned char &Pixel::grayLevel () const
{
	return grayLevel_;
};


/// 
/// @details
/// 
inline void Pixel::grayLevel (const unsigned char &grayLevel)
{
	grayLevel_ = grayLevel;
};

#endif  //_PIXEL_H

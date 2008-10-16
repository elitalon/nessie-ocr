///
/// @file
/// @brief Declaration of the class Shape
///

#if !defined(_SHAPE_H)
#define _SHAPE_H

#include <vector>

#include "Pixel.hpp"



///
///	The shape of a character within a press clip.
/// 
/// This class stores a set of pixels and all the information necessary to identify a shape that represents
/// a character within a press clip. Every shape has four representative pixels of ink, located on each extreme of the shape:
/// one pixel at the top, one pixel at the bottom, one pixel on the left and one pixel on the right. If there is more than one pixel
/// sharing a extreme position, the pixel at the center is taken. In addition, a pixel on the centra position is taken by computing the
/// centroid of the shape.
/// 
/// @see Pixel
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-13
///
class Shape
{
	public:
		
		///
		/// Constructor
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		Shape();
		
		
		///
		/// Returns the coordinates of the left-most pixel
		/// 
		/// @return A pair of coordinates
		/// 
		/// @see Pixel
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const Pixel &leftPixel ();
		
		
		///
		/// Returns the coordinates of the right-most pixel
		/// 
		/// @return A pair of coordinates
		/// 
		/// @see Pixel
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const Pixel &rightPixel ();
		
		
		///
		/// Returns the coordinates of the top pixel
		/// 
		/// @return A pair of coordinates
		/// 
		/// @see Pixel
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///		
		const Pixel &topPixel ();
		
		
		///
		/// Returns the coordinates of the bottom pixel
		/// 
		/// @return A pair of coordinates
		/// 
		/// @see Pixel
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///		
		const Pixel &bottomPixel ();
		
		
		///
		/// Returns the coordinates of the central pixel
		/// 
		/// @return A pair of coordinates
		/// 
		/// @see Pixel
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///		
		const Pixel &centralPixel ();
		
		
		///
		/// Returns the set of pixels that defines the shape.
		/// 
		/// @return A vector of values, where each value is the value of ink of each pixel
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const std::vector<unsigned char> &pixels ();
		
		
		///
		/// Returns the height of the shape.
		/// 
		/// @return The height of the shape
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &height ();
		
		
		///
		/// Returns the width of the shape.
		/// 
		/// @return The width of the shape
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &width ();
		
		
		///
		/// Adds a pixel to the shape.
		/// 
		/// @param pixel	Coordinates of the pixel
		/// @param hasInk	Tells whether the pixel has ink or not
		/// 
		/// @see Pixel
		/// 
		/// @author	Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///	
		void addPixel (const Pixel &pixel, const bool &hasInk);

		
	private:
		///
		/// Pixel of ink on the left-most position
		///
		Pixel leftPixel_;
		
		///
		/// Pixel of ink on the right-most position
		///
		Pixel rightPixel_;
		
		///
		/// Pixel of ink at the top position
		///
		Pixel topPixel_;
		
		///
		/// Pixel of ink at the bottom position
		///
		Pixel bottomPixel_;
		
		///
		/// Pixel of ink at central position
		///
		Pixel centralPixel_;
		
		///
		/// Set of pixels that defines the whole shape
		///
		std::vector<unsigned char> pixels_;
		
		///
		/// Height of the shape
		///
		unsigned int height_;
		
		///
		/// Width of the shape
		///
		unsigned int width_;
};


//
// Implementation of inline functions
// 


///
/// @details
///
inline const Pixel &Shape::leftPixel ()
{
	return leftPixel_;
};


///
/// @details
///
inline const Pixel &Shape::rightPixel ()
{
	return rightPixel_;
};

		
///
/// @details
///
inline const Pixel &Shape::topPixel ()
{
	return topPixel_;
};

		
///
/// @details
///
inline const Pixel &Shape::bottomPixel ()
{
	return bottomPixel_;
};

		
///
/// @details
///
inline const Pixel &Shape::centralPixel ()
{
	return centralPixel_;
};


///
/// @details
///
inline const std::vector<unsigned char> &Shape::pixels ()
{
	return pixels_;
};


///
/// @details
///
inline const unsigned int &Shape::height ()
{
	return height_;
};


///
/// @details
///
inline const unsigned int &Shape::width ()
{
	return width_;
};

#endif  //_SHAPE_H

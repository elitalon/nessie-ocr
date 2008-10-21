///
/// @file
/// @brief Declaration of the class Shape
///

#if !defined(_SHAPE_H)
#define _SHAPE_H


#include "Pixel.hpp"

#include <vector>



///
///	The shape of a character in a press clip.
/// 
/// This class stores a set of pixels and all the information necessary to identify a shape that represents
/// a character in a press clip. Every shape has four representative pixels of ink, located on each extreme of the shape:
/// one pixel at the top, one pixel at the bottom, one pixel on the left and one pixel on the right. In addition, a pixel
/// on the central position is set by computing the centroid of the shape.
/// 
/// @see Pixel
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-21
///
class Shape
{
public:
	
	///
	/// Constructor
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	Shape();
	
	
	///
	/// Allows access to a pixel in the shape.
	///
	/// @param index	The position in the shape
	/// 
	/// @return A reference to the coordinates of the pixel at the desired index that allows modifications.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	Pixel &operator() (const unsigned int &index);
	
	
	///
	/// Allows access to a pixel in the shape.
	///
	/// @param index	The position in the shape
	/// 
	/// @return A reference to the coordinates of the pixel at the desired index.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	Pixel operator() (const unsigned int &index) const;
	
	
	///
	/// Returns the width of the shape.
	/// 
	/// @return The width of the shape
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &width () const;
	
	
	///
	/// Returns the height of the shape.
	/// 
	/// @return The height of the shape
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &height () const;
	
	
	///
	/// Returns the number of ink pixels in the shape
	/// 
	/// @return The number of ink pixels
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	const unsigned int &size () const;
	
	
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
	const Pixel &leftPixel () const;
	
	
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
	const Pixel &rightPixel () const;
	
	
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
	const Pixel &topPixel () const;
	
	
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
	const Pixel &bottomPixel () const;
	
	
	///
	/// Adds a pixel to the shape.
	/// 
	/// @param pixel The pixel to add
	/// 
	/// @see Pixel
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///	
	void addPixel (const Pixel &pixel);

	
	
private:
	///
	/// Width of the shape
	///
	unsigned int width_;
	
	///
	/// Height of the shape
	///
	unsigned int height_;
	
	///
	/// A set of pixel coordinates that defines the whole shape
	///
	std::vector<Pixel> pixels_;
	
	///
	/// Number of ink pixels within the shape
	///
	unsigned int size_;
	
	///
	/// Pixel of ink at the left-most position
	///
	Pixel leftPixel_;
	
	///
	/// Pixel of ink at the right-most position
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
};



//
// Implementation of inline functions
// 


///
/// @details
///
inline Pixel &Shape::operator() (const unsigned int &index)
{
	return pixels_.at(index);
};


///
/// @details
///
inline Pixel Shape::operator() (const unsigned int &index) const
{
	return pixels_.at(index);
};


///
/// @details
///
inline const unsigned int &Shape::width () const
{
	return width_;
};


///
/// @details
///
inline const unsigned int &Shape::height () const
{
	return height_;
};


///
/// @details
///
inline const unsigned int &Shape::size () const
{
	return size_;
};


///
/// @details
///
inline const Pixel &Shape::leftPixel () const
{
	return leftPixel_;
};


///
/// @details
///
inline const Pixel &Shape::rightPixel () const
{
	return rightPixel_;
};

		
///
/// @details
///
inline const Pixel &Shape::topPixel () const
{
	return topPixel_;
};

		
///
/// @details
///
inline const Pixel &Shape::bottomPixel () const
{
	return bottomPixel_;
};


#endif  //_SHAPE_H

///
/// @file
/// @brief Declaration of Shape class
///

#if !defined(_SHAPE_H)
#define _SHAPE_H


#include <vector>
#include <utility>



///
/// @typedef Pixel
/// 
/// @brief Coordinates of an image pixel.
///
/// @details This pair keeps the coordinates of a pixel in a press clip. The first member representes the x coordinate (the row)
/// and the second member representes the y coordinate (the column)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-13
/// 
typedef std::pair<unsigned int, unsigned int> Pixel;




///
///	The shape of a character in a press clip.
/// 
/// This class stores a set of pixels and all the information necessary to identify a shape that represents
/// a character in a press clip. Every shape has four representative pixels of ink, located on each extreme of the shape:
/// one pixel at the top, one pixel at the bottom, one pixel on the left and one pixel on the right.
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
	/// Constructor.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	Shape();
	
	
	///
	/// Allows read-and-write access to a pixel in the shape.
	///
	/// @param index	The position in the shape
	/// 
	/// @return A reference to the coordinates of a pixel at the given index.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	Pixel& operator() (const unsigned int& index);
	
	
	///
	/// Allows read-only access to a pixel in the shape.
	///
	/// @param index	The position in the shape
	/// 
	/// @return A reference to the coordinates of the pixel at the given index.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	Pixel operator() (const unsigned int& index) const;

	
	///
	/// Appends a shape to a current one
	/// 
	/// @param shape	Shape to be appended
	/// 
	/// @return Shape object as a result of appending the pixels of both shapes
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-28
	///
	Shape operator+ (const Shape& shape) const;
	
	
	///
	/// Evaluates the position of a shape respect to another in a press clip.
	/// 
	/// @param shape	Shape of reference
	/// 
	/// @return True if the current shape is placed before than the shape of reference in a press, false otherwise.
	/// 
	/// @author Eliezer Talón(elitalon@gmail.com)
	/// @date 2008-10-30
	///
	bool operator< (const Shape& shape);
	
	
	///
	/// Returns the width of the shape.
	/// 
	/// @return Width of the shape in pixels
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int& width () const;
	
	
	///
	/// Returns the height of the shape.
	/// 
	/// @return Height of the shape in pixels
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int& height () const;
	
	
	///
	/// Returns the number of pixels in the shape
	/// 
	/// @return Number of pixels in the shape
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	const unsigned int& size () const;
	
	
	///
	/// Returns the coordinates of the leftmost pixel
	/// 
	/// @return A pair of coordinates
	/// 
	/// @see Pixel
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const Pixel& leftPixel () const;
	
	
	///
	/// Returns the coordinates of the rightmost pixel
	/// 
	/// @return A pair of coordinates
	/// 
	/// @see Pixel
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const Pixel& rightPixel () const;
	
	
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
	const Pixel& topPixel () const;
	
	
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
	const Pixel& bottomPixel () const;
	
	
	///
	/// Returns the coordinates of the shape's barycenter
	/// 
	/// @return A pair of coordinates
	/// 
	/// @see Pixel
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-30
	///		
	Pixel barycenter () const;
	
	
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
	void addPixel (const Pixel& pixel);
	
	
private:

	unsigned int		width_;			///< Width of the shape	

	unsigned int		height_;		///< Height of the shape
	
	std::vector<Pixel>	pixels_;		///< Set of pixel coordinates that defines the whole shape
	
	unsigned int		size_;			///< Number of pixels in the shape
	
	Pixel				leftPixel_;		///< Pixel at the leftmost position
		
	Pixel				rightPixel_;	///< Pixel at the rightmost position
		
	Pixel				topPixel_;		///< Pixel at the top position
		
	Pixel				bottomPixel_;	///< Pixel at the bottom position
};





inline Pixel& Shape::operator() (const unsigned int& index)
{
	return pixels_.at(index);
};


inline Pixel Shape::operator() (const unsigned int& index) const
{
	return pixels_.at(index);
};


inline const unsigned int& Shape::width () const
{
	return width_;
};


inline const unsigned int& Shape::height () const
{
	return height_;
};


inline const unsigned int& Shape::size () const
{
	return size_;
};


inline const Pixel& Shape::leftPixel () const
{
	return leftPixel_;
};


inline const Pixel& Shape::rightPixel () const
{
	return rightPixel_;
};

		
inline const Pixel& Shape::topPixel () const
{
	return topPixel_;
};

		
inline const Pixel& Shape::bottomPixel () const
{
	return bottomPixel_;
};


inline Pixel Shape::barycenter () const
{
	Pixel barycenter(0,0);
	
	for ( unsigned int i = 0; i < pixels_.size(); ++i )
	{
		barycenter.first	+= pixels_.at(i).first;
		barycenter.second	+= pixels_.at(i).second;
	}
	barycenter.first	= barycenter.first	/ size_;
	barycenter.second	= barycenter.second / size_;
	
	return barycenter;
};


inline Shape Shape::operator+ (const Shape& shape) const
{
	Shape temp;
	
	// Copy the pixels of this shape
	for ( unsigned int i = 0; i < this->size(); ++i )
		temp.addPixel( (*this)(i) );
	
	// Copy the pixels of the second shape
	for ( unsigned int i = 0; i < shape.size(); ++i )
		temp.addPixel( shape(i) );
	
	return temp;
};


inline bool Shape::operator< (const Shape& shape)
{
	bool shapeAbove = (this->bottomPixel().first < shape.topPixel().first) and (this->topPixel().first < shape.topPixel().first);
	
	if ( shapeAbove )
		return true;
	else
	{
		bool shapeBelow = (this->bottomPixel().first > shape.bottomPixel().first) and (this->topPixel().first > shape.bottomPixel().first);
		
		if ( shapeBelow )
			return false;
		else
		{
			// Shapes in the same line
			bool shapeOnTheLeft		= (this->leftPixel().second < shape.leftPixel().second) and (this->rightPixel().second <= shape.leftPixel().second);
			bool shapeOnTheRight	= (this->leftPixel().second >= shape.rightPixel().second) and (this->rightPixel().second > shape.rightPixel().second);
			
			if ( shapeOnTheLeft )
				return true;
			else
			{
				if ( shapeOnTheRight )
					return false;
				else
					return true;
			}
		}
	}
};

#endif  //_SHAPE_H

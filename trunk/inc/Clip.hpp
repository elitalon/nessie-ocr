///
/// @file
/// @brief Declaration of the class Clip
///

#if !defined(_CLIP_H)
#define _CLIP_H

#include <vector>
#include "NessieException.hpp"



///
/// Press clip where the recognizer has to extract the text from.
/// 
/// This class stores a press clip as a set of pixels from an underlying image that representes the whole page
/// of a newspaper. The class that creates a Clip object should ensure that all the coordinates passed to the constructor
/// are correct, though the constructor makes some simple tests.
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
	/// @param image		The underlying image where the clip belongs to
	/// @param imageWidth	The width of the underlying image
	/// @param row			The row in the underlying image where the upper left-most pixel of the clip is at
	/// @param column		The column in the underlying image where the upper left-most pixel of the clip is at
	/// @param height		The height of the clip
	/// @param width		The width of the clip
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	Clip (const std::vector<unsigned char> &image, const unsigned int &imageWidth, const unsigned int &row, const unsigned int &column, const unsigned int &height, const unsigned int &width);
	
	
	///
	/// Destructor.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	~Clip ();
	
	
	///
	/// Allows access to a pixel in the clip.
	///
	/// @param row		The row where the pixel is at.
	/// @param column	The column where the pixel is at.
	/// 
	/// @return A reference to the gray level of the pixel at the desired location that allows modifications.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	unsigned char &operator() (const unsigned int &row, const unsigned int &column);
	
	
	///
	/// Allows access to a pixel in the clip.
	///
	/// @param row		The row where the pixel is at.
	/// @param column	The column where the pixel is at.
	/// 
	/// @return The gray level of the pixel at the desired location.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	unsigned char operator() (const unsigned int &row, const unsigned int &column) const;
		
	
	///
	/// Returns the row in the underlying image where the upper left-most pixel of the clip is at
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	const unsigned int &row () const;
	
	
	///
	/// Returns the column in the underlying image where the upper left-most pixel of the clip is at
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	const unsigned int &column () const;
	
	
	///
	/// Returns the width of the clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &width () const;
	
	
	///
	/// Returns the height of the clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &height () const;
		
	
	///
	/// Returns the number of pixels in the clip.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &size () const;
	
	
private:
	///
	/// Row in the underlying image where the upper left-most pixel of the clip is at
	///
	const unsigned int row_;
	
	///
	/// Column in the underlying image where the upper left-most pixel of the clip is at
	///
	const unsigned int column_;
	
	///
	/// The width of the clip
	///
	const unsigned int width_;
	
	///
	/// The height of the clip
	///
	const unsigned int height_;
	
	///
	/// A set of pixels that defines the press clip
	///
	unsigned char *pixels_;
	
	///
	/// Number of pixels in the clip
	///
	unsigned int size_;
};



//
// Implementation of inline functions
// 


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// The gray level must be normalized in a value from 0 to 255, otherwise it is truncated.
///
inline unsigned char &Clip::operator() (const unsigned int &row, const unsigned int &column)
{
	if ( (row < 0) or (column < 0) or (row >= height_) or (column >= width_) )
		throw NessieException ("Clip::operator() : Subscripts are out bounds");
		
	return pixels_[row * width_ + column];
};


///
/// @details If either the x coordinate or the y coordinate are out of the image borders, an exception is thrown.
/// 
inline unsigned char Clip::operator() (const unsigned int &row, const unsigned int &column) const
{
	if ( (row < 0) or (column < 0) or (row >= height_) or (column >= width_) )
		throw NessieException ("Clip::operator() : Subscripts are out bounds");
		
	return pixels_[row * width_ + column];
};


///
/// @details
/// 
inline const unsigned int &Clip::row () const
{
	return row_;
};


///
/// @details
/// 
inline const unsigned int &Clip::column () const
{
	return column_;
};


///
/// @details
/// 
inline const unsigned int &Clip::width () const
{
	return width_;
};


///
/// @details
/// 
inline const unsigned int &Clip::height () const
{
	return height_;
};


///
/// @details
/// 
inline const unsigned int &Clip::size () const
{
	return size_;
};

#endif  //_CLIP_H

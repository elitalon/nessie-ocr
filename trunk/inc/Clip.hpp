///
/// @file
/// @brief Declaration of Clip class
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
/// are correct, though the constructor only makes some simple checks.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
///
class Clip
{
public:
	
	///
	/// Constructor.
	///
	/// @param image		Underlying image where the clip belongs to
	/// @param imageWidth	Width of the underlying image
	/// @param row			Row in the underlying image where the upper leftmost pixel of the clip is at
	/// @param column		Column in the underlying image where the upper leftmost pixel of the clip is at
	/// @param height		Height of the clip
	/// @param width		Width of the clip
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
	/// Allows read-and-write access to a pixel in the clip.
	///
	/// @param row		Row in the clip where the pixel is at.
	/// @param column	Column in the clip where the pixel is at.
	/// 
	/// @return A reference to the gray level of the pixel at the given location.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	unsigned char &operator() (const unsigned int &row, const unsigned int &column);


	///
	/// Allows read-only access to a pixel in the clip.
	///
	/// @param row		Row in the clip where the pixel is at.
	/// @param column	Column in the clip where the pixel is at.
	/// 
	/// @return Gray level of the pixel at the given location.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	unsigned char operator() (const unsigned int &row, const unsigned int &column) const;


	///
	/// Returns the row in the underlying image where the upper leftmost pixel of the clip is at.
	/// 
	/// @return Row in the underlying image where the upper leftmost pixel of the clip is at.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	const unsigned int &row () const;


	///
	/// Returns the column in the underlying image where the upper leftmost pixel of the clip is at.
	/// 
	/// @return Column in the underlying image where the upper leftmost pixel of the clip is at.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	const unsigned int &column () const;


	///
	/// Returns the width of the clip.
	/// 
	/// @return Width of the clip in pixels
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &width () const;


	///
	/// Returns the height of the clip.
	/// 
	/// @return Height of the clip in pixels
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &height () const;


	///
	/// Returns the number of pixels in the clip.
	/// 
	/// @return Number of pixels in the clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int &size () const;


private:

	const unsigned int	row_;		///< Row in the underlying image where the upper leftmost pixel of the clip is at

	const unsigned int	column_;	///< Column in the underlying image where the upper leftmost pixel of the clip is at

	const unsigned int	width_;		///< Width of the clip

	const unsigned int	height_;	///< Height of the clip

	unsigned char		*pixels_;	///< Set of pixels that defines the press clip

	unsigned int		size_;		///< Number of pixels in the clip
};




inline unsigned char &Clip::operator() (const unsigned int &row, const unsigned int &column)
{
	if ( (row < 0) or (column < 0) or (row >= height_) or (column >= width_) )
		throw NessieException ("Clip::operator() : Subscripts are out bounds");

	return pixels_[row * width_ + column];
};


inline unsigned char Clip::operator() (const unsigned int &row, const unsigned int &column) const
{
	if ( (row < 0) or (column < 0) or (row >= height_) or (column >= width_) )
		throw NessieException ("Clip::operator() : Subscripts are out bounds");

	return pixels_[row * width_ + column];
};


inline const unsigned int &Clip::row () const
{
	return row_;
};


inline const unsigned int &Clip::column () const
{
	return column_;
};


inline const unsigned int &Clip::width () const
{
	return width_;
};


inline const unsigned int &Clip::height () const
{
	return height_;
};


inline const unsigned int &Clip::size () const
{
	return size_;
};

#endif  //_CLIP_H

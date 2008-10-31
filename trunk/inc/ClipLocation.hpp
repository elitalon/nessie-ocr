///
/// @file
/// @brief Declaration of ClipLocation class
///

#if !defined(_CLIP_LOCATION_H)
#define _CLIP_LOCATION_H



///
/// Location of a press clip inside a newspaper page.
/// 
/// @details This class stores all the necessary information to locate a press clip inside a newspaper page. This information includes the coordinates
/// of the press clip's top leftmost pixel, its height and its width.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-11
/// 
class ClipLocation
{
public:

	///
	/// Constructor.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-11
	///
	ClipLocation ();


	///
	/// Constructor.
	/// 
	/// @param row		Row where the upper leftmost pixel is at.
	/// @param column	Column where the upper leftmost pixel is at.
	/// @param height	Height of the clip.
	/// @param width	Width of the clip.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-11
	///
	ClipLocation (const unsigned int& row, const unsigned int& column, const unsigned int& height, const unsigned int& width);


	///
	/// Returns the row where the upper leftmost pixel is at.
	/// 
	/// @return Row where the upper leftmost pixel is at.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int& row () const;


	///
	/// Sets the row where the upper leftmost pixel is at.
	/// 
	/// @param row	New row value where the upper leftmost pixel will be set.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-11		
	///
	void row (const unsigned int& row);


	///
	/// Returns the column where the upper leftmost pixel is at.
	/// 
	/// @return Column where the upper leftmost pixel is at.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int& column () const;


	///
	/// Sets the column where the upper leftmost pixel is at.
	/// 
	/// @param column	New column value where the upper leftmost pixel will be set.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-11
	///
	void column (const unsigned int& column);


	///
	/// Returns the height of the press clip.
	/// 
	/// @return Height of the press clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int& height () const;


	///
	/// Sets the height of the press clip
	/// 
	/// @param height	New height value of the press clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-11
	///
	void height (const unsigned int& height);


	///
	/// Returns the width of the press clip
	/// 
	/// @return Width of the press clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned int& width () const;


	///
	/// Sets the width of the press clip
	/// 
	/// @param width	New width value of the press clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-11
	///
	void width (const unsigned int& width);


private:
	
	unsigned int	row_;		///< Row where the upper leftmost pixel is at.

	unsigned int	column_;	///< Column where the upper leftmost pixel is at.

	unsigned int	height_;	///< Height of the press clip

	unsigned int	width_;		///< Width of the press clip
};



inline const unsigned int& ClipLocation::row () const
{
	return row_;
};


inline const unsigned int& ClipLocation::column () const
{
	return column_;
};


inline const unsigned int& ClipLocation::height () const
{
	return height_;
};


inline const unsigned int& ClipLocation::width () const
{
	return width_;
};


inline void ClipLocation::row (const unsigned int& row)
{
	row_ = row;
};


inline void ClipLocation::column (const unsigned int& column)
{
	column_ = column;
};


inline void ClipLocation::height (const unsigned int& height)
{
	height_ = height;
};


inline void ClipLocation::width (const unsigned int& width)
{
	width_ = width;
};

#endif  //_CLIP_LOCATION_H

///
/// @file
/// @brief Declaration of the class ClipLocation
///

#if !defined(_CLIP_LOCATION_H)
#define _CLIP_LOCATION_H



///
/// Location of a press clip within a newspaper page.
/// 
/// @details This class stores the coordinates of the top left-most pixel of a clip, its height and its width. The x coordinate corresponds
/// to the row, while the y coordinate corresponds to the column. The height and width attributes are expressed in pixels.
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
		/// @param x		The upper left-most pixel X coordinate of the clip
		/// @param y		The upper left-most pixel Y coordinate of the clip
		/// @param height	The height of the clip
		/// @param width	The width of the clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		ClipLocation (const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width);
		
		
		///
		/// Returns the x coordinate
		/// 
		/// @return X coordinate
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &x () const;
		
		
		///
		/// Returns the y coordinate
		/// 
		/// @return Y coordinate
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &y () const;
		
		
		///
		/// Returns the height
		/// 
		/// @return Height of the press clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &height () const;
		
		
		///
		/// Returns the width
		/// 
		/// @return Width of the pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const unsigned int &width () const;
		
		
		///
		/// Sets the x coordinate
		/// 
		/// @param x The x coordinate of the top left-most pixel of the press clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11		
		///
		void x (const unsigned int &x);
		
		
		///
		/// Sets the y coordinate
		/// 
		/// @param y The y coordinate of the top left-most pixel of the press clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		void y (const unsigned int &y);
		
		
		///
		/// Sets the height
		/// 
		/// @param height The height of the press clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		void height (const unsigned int &height);
		
		
		///
		/// Sets the width
		/// 
		/// @param width The width coordinate of the press clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		void width (const unsigned int &width);
		
		
		///
		/// Returns the number of pixels
		/// 
		/// @return Number of pixels of the press clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		unsigned int size () const;


	private:
		unsigned int x_;			///< x coordinate
	
		unsigned int y_;			///< y coordinate
	
		unsigned int height_;		///< Height of the press clip
	
		unsigned int width_;		///< Width of the press clip
};



//
// Implementation of inline functions
// 

inline const unsigned int &ClipLocation::x () const
{
	return x_;
};


inline const unsigned int &ClipLocation::y () const
{
	return y_;
};


inline const unsigned int &ClipLocation::height () const
{
	return height_;
};


inline const unsigned int &ClipLocation::width () const
{
	return width_;
};


inline void ClipLocation::x (const unsigned int &x)
{
	x_ = x;
};


inline void ClipLocation::y (const unsigned int &y)
{
	y_ = y;
};


inline void ClipLocation::height (const unsigned int &height)
{
	height_ = height;
};


inline void ClipLocation::width (const unsigned int &width)
{
	width_ = width;
};


inline unsigned int ClipLocation::size () const
{
	return height_ * width_;
};

#endif  //_CLIP_LOCATION_H

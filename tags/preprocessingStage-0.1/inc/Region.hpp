/// @file
/// @brief Declaration of Region class

#if !defined(_REGION_H)
#define _REGION_H


#include <vector>
#include <utility>


/// @typedef	PixelCoordinates.
/// @brief		Internal representation of pixel coordinates in a 2D coordinates system.
/// @author		Eliezer Talón (elitalon@gmail.com)
/// @date		2009-01-19
typedef std::pair<unsigned int, unsigned int> PixelCoordinates;



///	@brief		Set of ink pixels that defines an isolated region in the press clip.
/// 
/// @details	After preprocessing a press clip, a list of regions is available to build a set of patterns suitable for feature extraction and classification.
///	Such a region, as stored in this class, contains only the absolute coordinates of ink pixels that belongs to it. In addition, it has a virtual pixel
///	of ink, located on the top leftmost corner of the region, and the coordinates of its borders. Notice that every pair of coordinates that a method of this
/// class returns means absolute values according to its global position in the underlying press clip.
/// 
///	@see		PixelCoordinates
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-19
///
class Region
{
	public:

		/// @brief	Constructor.
		Region();

		/// @brief	Allows read-and-write access to the coordinates of a pixel in the region.
		///
		/// @param	index	The position of a pair of coordinates.
		/// 
		/// @return	A pair of coordinates.
		PixelCoordinates& operator() (const unsigned int& index);

		/// @brief	Allows read-only access to the coordinates of a pixel in the region.
		///
		/// @param	index	The position of a pair of coordinates.
		/// 
		/// @return A pair of coordinates.
		PixelCoordinates operator() (const unsigned int& index) const;

		/// @brief	Adds a region to the current one.
		/// 
		/// @param	region	Region whose coordinates are going to be added.
		/// 
		/// @return A Region object as a result of joining the pixel coordinates of both regions.
		Region operator+ (const Region& region) const;

		/// @brief	Evaluates if a region position is less than another, according to their position in text when reading from up to down and left to right.
		/// 
		/// @param	region	Region of reference.
		/// 
		/// @return True if the current region is placed before than <em>region</em> in a press clip, false otherwise.
		bool operator< (const Region& region) const;

		/// @brief	@brief	Returns the height of the region.
		/// 
		/// @return Height of the region in pixels.
		const unsigned int& height () const;

		/// @brief	@brief	Returns the width of the region.
		/// 
		/// @return Width of the region in pixels.
		const unsigned int& width () const;

		/// @brief	@brief	Returns the number of pixels in the region.
		/// 
		/// @return Number of pixels.
		const unsigned int& size () const;

		/// @brief	@brief	Returns the coordinates of the top leftmost pixel.
		/// 
		/// @return A PixelCoordinates object with the coordinates of the top leftmost pixel.
		const PixelCoordinates& topLeftmostPixelCoordinates () const;

		///	@brief	Returns the X-axis coordinate of the top pixel in the region.
		///
		/// @return X-axis coordinate of the top pixel.
		const unsigned int& topBorderRow () const;

		///	@brief	Returns the X-axis coordinate of the bottom pixel in the region.
		///
		/// @return X-axis coordinate of the bottom pixel.
		const unsigned int& bottomBorderRow () const;

		///	@brief	Returns the Y-axis coordinate of the leftmost pixel in the region.
		///
		/// @return Y-axis coordinate of the leftmost pixel.
		const unsigned int& leftBorderColumn () const;

		///	@brief	Returns the Y-axis coordinate of the rightmost pixel in the region.
		///
		/// @return Y-axis coordinate of the rightmost pixel.
		const unsigned int& rightBorderColumn () const;

		/// @brief	Adds a pair of pixel coordinates to the region.
		/// 
		/// @param	coordinates		Coordinates of the pixel.
		void addCoordinates(const PixelCoordinates& coordinates);

		/// @brief	Normalize the coordinates of every pixel.
		///
		///	@post	The coordinates are translated so that the top leftmost pixel is located at (0,0).
		void normalizeCoordinates ();

	private:

		std::vector<PixelCoordinates>	coordinates_;					///< Set of pixel coordinates that defines the whole region.

		unsigned int					height_;						///< Region height in pixels.

		unsigned int					width_;							///< Region width in pixels.

		unsigned int					size_;							///< Number of pixels in the region.

		PixelCoordinates				topLeftmostPixelCoordinates_;	///< Coordinates of the top leftmost pixel in the region.

		unsigned int					topBorderRow_;					///< X-axis coordinate of the top pixel in the region.

		unsigned int					bottomBorderRow_;				///< X-axis coordinate of the bottom pixel in the region.

		unsigned int					leftBorderColumn_;				///< Y-axis coordinate of the leftmost pixel in the region.

		unsigned int					rightBorderColumn_;				///< Y-axis coordinate of the rightmost pixel in the region.
};


inline PixelCoordinates& Region::operator() (const unsigned int& index)
{
	return coordinates_.at(index);
};


inline PixelCoordinates Region::operator() (const unsigned int& index) const
{
	return coordinates_.at(index);
};


inline Region Region::operator+ (const Region& region) const
{
	Region temp;

	for ( std::vector<PixelCoordinates>::const_iterator i = this->coordinates_.begin(); i not_eq coordinates_.end(); ++i )
		temp.addCoordinates( (*i) );

	for ( std::vector<PixelCoordinates>::const_iterator i = region.coordinates_.begin(); i not_eq region.coordinates_.end(); ++i )
		temp.addCoordinates( (*i) );

	return temp;
};


inline bool Region::operator< (const Region& region) const
{
	if ( this->bottomBorderRow() < region.topBorderRow() )
		return true;
	else
	{
		if ( region.bottomBorderRow() < this->topBorderRow() )
			return false;
		else
			return ( this->topLeftmostPixelCoordinates().second < region.topLeftmostPixelCoordinates().second );
	}
};


inline const unsigned int& Region::height () const
{
	return height_;
};


inline const unsigned int& Region::width () const
{
	return width_;
};


inline const unsigned int& Region::size () const
{
	return size_;
};


inline const PixelCoordinates& Region::topLeftmostPixelCoordinates () const
{
	return topLeftmostPixelCoordinates_;
};


inline const unsigned int& Region::topBorderRow () const
{
	return topBorderRow_;
};


inline const unsigned int& Region::bottomBorderRow () const
{
	return bottomBorderRow_;
};


inline const unsigned int& Region::leftBorderColumn () const
{
	return leftBorderColumn_;
};


inline const unsigned int& Region::rightBorderColumn () const
{
	return rightBorderColumn_;
};

#endif  //_REGION_H

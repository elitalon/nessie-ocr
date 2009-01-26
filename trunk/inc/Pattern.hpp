/// @file
/// @brief Declaration of Pattern class

#if !defined(_PATTERN_H)
#define _PATTERN_H


#include <vector>



///	A pattern in a press clip to be recognized as a character.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-16
///
class Pattern
{
public:
	
	/// Constructor.
	Pattern();
	
	/// Allows read-and-write access to a pixel in the pattern.
	///
	/// @param index	The position in the pattern
	/// 
	/// @return A reference to the coordinates of a pixel at the given index.
	unsigned int& operator() (const unsigned int& index);
	
	/// Allows read-only access to a pixel in the pattern.
	///
	/// @param index	The position in the pattern
	/// 
	/// @return A reference to the coordinates of the pixel at the given index.
	unsigned int operator() (const unsigned int& index) const;

	/// Returns the height of the pattern.
	/// 
	/// @return Height of the pattern in pixels
	const unsigned int& height () const;

	/// Returns the width of the pattern.
	/// 
	/// @return Width of the pattern in pixels
	const unsigned int& width () const;	
	
	/// Returns the number of pixels in the pattern
	/// 
	/// @return Number of pixels in the pattern
	const unsigned int& size () const;
	
private:

	std::vector<unsigned int>	pixels_;		///< Set of pixel coordinates that defines the whole pattern
	
	unsigned int				width_;			///< Width of the pattern	

	unsigned int				height_;		///< Height of the pattern
	
	unsigned int				size_;			///< Number of pixels in the pattern
};



inline unsigned int& Pattern::operator() (const unsigned int& index)
{
	return pixels_.at(index);
};


inline unsigned int Pattern::operator() (const unsigned int& index) const
{
	return pixels_.at(index);
};


inline const unsigned int& Pattern::width () const
{
	return width_;
};


inline const unsigned int& Pattern::height () const
{
	return height_;
};


inline const unsigned int& Pattern::size () const
{
	return size_;
};

#endif  //_PATTERN_H


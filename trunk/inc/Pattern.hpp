/// @file
/// @brief Declaration of Pattern class

#if !defined(_PATTERN_H)
#define _PATTERN_H

class Region;
#include <vector>
#include <string>
#include <utility>


///	@brief		Set of pixels that defines a pattern to be recognized as a character in classification stage.
///
///	@details	A pattern is a matrix of binary pixels that holds a region found in the preprocessing stage. Thus, it is composed of ink pixels,
///	i.e. the region pixels, and a number of background pixels to fill the holes in the matrix that do not belong to the region.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-02
///
class Pattern
{
	public:

		///	@brief	Constructor.
		///
		///	@param	region	A Region object from which builds the pattern.
		explicit Pattern(const Region& region);

		/// @brief	Allows read-and-write access to a pixel in the pattern.
		///
		/// @param	x	X-axis coordinate of pixel.
		/// @param	y	Y-axis coordinate of pixel.
		///
		/// @return A reference to the gray level value of a pixel at given coordinates.
		unsigned int& operator() (const unsigned int& x, const unsigned int& y);

		/// @brief	Allows read-only access to a pixel in the pattern.
		///
		/// @param	x	X-axis coordinate of pixel.
		/// @param	y	Y-axis coordinate of pixel.
		///
		/// @return A reference to the gray level value of a pixel at given coordinates.
		unsigned int operator() (const unsigned int& x, const unsigned int& y) const;

		/// @brief	Returns the height of the pattern.
		///
		/// @return Height of the pattern in pixels.
		const unsigned int& height () const;

		/// @brief	Returns the width of the pattern.
		///
		/// @return Width of the pattern in pixels.
		const unsigned int& width () const;

		/// @brief	Returns the number of pixels in the pattern.
		///
		/// @return	Number of pixels in the pattern.
		const unsigned int& size () const;

		/// @brief	Computes the centroid of a pattern using geometric moments.
		/// 
		/// @return	The coordinates of the centroid as a pair of integers.
		std::pair<unsigned int, unsigned int> centroid () const;

		/// @brief	Creates a new image in the filesystem using Magick++ with the pattern drawn.
		///
		/// @param	outputFile		A string with the image name in the filesystem.
		/// @param	invert			A boolean value that decides whether to invert the pixel values or not.
		///
		/// @post	A new image file is created in the filesystem. The image type is assigned according to the file extension provided in the
		///			filename (e.g. "foo.png" selects PNG as the image type). Otherwise the image type is Magick++'s implementation-dependent.
		void writeToOutputImage (const std::string& outputFile, const bool& invert=false) const;

	private:

		std::vector<unsigned int>	pixels_;		///< Set of pixels that defines the whole pattern.

		unsigned int				height_;		///< Height of the pattern.

		unsigned int				width_;			///< Width of the pattern.

		unsigned int				size_;			///< Number of pixels in the pattern.

		// Explicitly disallowed compiler-generated methods. DO NOT IMPLEMENT!!
		Pattern ();
};


inline unsigned int& Pattern::operator() (const unsigned int& x, const unsigned int& y)
{
	return pixels_.at(x * width_ + y);
};


inline unsigned int Pattern::operator() (const unsigned int& x, const unsigned int& y) const
{
	return pixels_.at(x * width_ + y);
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


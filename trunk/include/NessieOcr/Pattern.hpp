/// @file
/// @brief Declaration of Pattern class

#if !defined(_PATTERN_H)
#define _PATTERN_H

#include <vector>
#include <string>
#include <utility>


///	@brief		Set of pixels that defines a pattern to be recognized as a character in classification stage.
///
///	@details	A pattern is a matrix of binary pixels that represents a character found in the preprocessing stage. Thus, it is composed of ink pixels,
///	and a number of background pixels to fill the holes in the matrix that do not belong to the character. Every pattern has a fixed size, since a
///	pre-requisite for an optimal classification is that patterns must be normalized to constant width and height.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-02
class Pattern
{
	public:

		///	@brief	Constructor.
		explicit Pattern ();

		/// @brief	Allow read-and-write access to a pixel in the pattern.
		///
		/// @param	x	X-axis coordinate of pixel.
		/// @param	y	Y-axis coordinate of pixel.
		///
		/// @return Gray level of a pixel at given coordinates.
		unsigned int& at (const unsigned int& x, const unsigned int& y);

		/// @brief	Allow read-only access to a pixel in the pattern.
		///
		/// @param	x	X-axis coordinate of pixel.
		/// @param	y	Y-axis coordinate of pixel.
		///
		/// @return Gray level of a pixel at given coordinates.
		const unsigned int& at (const unsigned int& x, const unsigned int& y) const;

		/// @brief	Get the height of the pattern.
		///
		/// @return Height of the pattern in pixels.
		const unsigned int& height () const;

		/// @brief	Get the width of the pattern.
		///
		/// @return Width of the pattern in pixels.
		const unsigned int& width () const;

		/// @brief	Get the number of pixels in the pattern.
		///
		/// @return	Number of pixels in the pattern.
		const unsigned int& size () const;

		/// @brief	Get the side size of the standard plane used for every pattern.
		///
		/// @return	Side size in pixels.
		static unsigned int planeSize () { return 35; };
		
		/// @brief	Computes the centroid of a pattern using geometric moments.
		/// 
		/// @return	The coordinates of the centroid as a pair of integers.
		std::pair<unsigned int, unsigned int> centroid () const;

		/// @brief	Computes the area of a pattern, i.e. the number of ink pixels it has.
		/// 
		/// @return	Area of the pattern in pixels.
		unsigned int area () const;

		///	@brief	Clean the pattern by deleting every pixel of ink.
		///	
		///	@post	Every pixel is set to background, i.e. to zero.
		void clean ();

		/// @brief	Create a new image in the filesystem using Magick++ with the pattern drawn.
		///
		/// @param	outputFile		A string with the image name in the filesystem.
		/// @param	invert			A boolean value that decides whether to invert the pixel values or not.
		///
		/// @post	A new image file is created in the filesystem. The image type is assigned according to the file extension provided in the
		///			filename (e.g. "foo.png" selects PNG as the image type). Otherwise the image type is Magick++'s implementation-dependent.
		void writeToOutputImage (const std::string& outputFile, const bool& invert=false) const;

	private:

		std::vector<unsigned int>	pixels_;	///< Set of pixels that defines the whole pattern.

		unsigned int				height_;	///< Height of the pattern.

		unsigned int				width_;		///< Width of the pattern.

		unsigned int				size_;		///< Number of pixels in the pattern.
};


inline unsigned int& Pattern::at (const unsigned int& x, const unsigned int& y)
{
	return pixels_.at(x * width_ + y);
}

inline const unsigned int& Pattern::at (const unsigned int& x, const unsigned int& y) const
{
	return pixels_.at(x * width_ + y);
}

inline const unsigned int& Pattern::width () const
{
	return width_;
}

inline const unsigned int& Pattern::height () const
{
	return height_;
}

inline const unsigned int& Pattern::size () const
{
	return size_;
}
		
inline void Pattern::clean ()
{
	pixels_.assign(size_, 0);
}
#endif


/// @file
/// @brief Declaration of Clip class

#if !defined(_CLIP_H)
#define _CLIP_H

#include <Magick++.h>
#include <vector>
#include <string>


/// @brief Press clip of a newspaper page.
///
/// @details This class manages a press clip within a newspaper's page, storing it as a set of pixels from an underlying image that
/// representes the whole page. It is assumed that the origin of coordinates is located at the top leftmost pixel in the underlying
///	image, as well in the clip itself.
///
/// @details The newspaper pages are images that may come in several formats, such JPEG, PDF, PNG, etc. The Magick++ library (an API
///	for the ImageMagick suite) provides an abstraction layer to keep the code independent from the image format, so that other classes
///	have an unified way to work with images. In future modifications any other library can be added to load images. In such case, the
///	<em>constructor</em> and the writeToOutputImage method must be overloaded.
///
/// @see <a href="http://www.imagemagick.org/Magick++/">Magick++ API</a>
///
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
///
class Clip
{
	public:

		/// @brief		Constructor.
		///
		/// @param		image	Underlying image which the clip belongs to.
		/// @param		x		X-axis coordinate of the row in the underlying image where the top leftmost pixel of the clip is.
		/// @param		y		Y-axis coordinate of the column in the underlying image where the top leftmost pixel of the clip is.
		/// @param		height	Height of the clip in pixels.
		/// @param		width	Width of the clip in pixels.
		///
		/// @post		The image is stored internally using a grayscale colorspace.
		///
		/// @exception	NessieException	If the clip partially falls outside the underlying image.
		explicit Clip (const Magick::Image& image, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width);

		/// @brief	Allows read-and-write access to a pixel in the clip.
		///
		/// @param	x	X-axis coordinate of the row where the requested pixel is.
		/// @param	y	Y-axis coordinates of the column where the requested pixel is.
		///
		/// @return	The gray level of pixel at given coordinates.
		unsigned char& operator() (const unsigned int& x, const unsigned int& y);

		/// @brief	Allows read-only access to a pixel in the clip.
		///
		/// @param	x	X-axis coordinate of the row where the pixel is.
		/// @param	y	Y-axis coordinate of the column where the pixel is.
		///
		/// @return	The gray level of pixel at given coordinates.
		unsigned char operator() (const unsigned int& x, const unsigned int& y) const;

		/// @brief	Returns the width of the clip.
		///
		/// @return	Width of the clip in pixels.
		const unsigned int& width () const;

		/// @brief	Returns the height of the clip.
		///
		/// @return Height of the clip in pixels.
		const unsigned int& height () const;

		/// @brief	Returns the number of pixels in the clip.
		///
		/// @return	Number of pixels in the clip.
		const unsigned int& size () const;

		/// @brief	Creates a new image in the filesystem using Magick++, reflecting the current state of the press clip.
		///
		/// @param	outputFile		A string with the image name in the filesystem.
		/// @param	scalingFactor	Top limit of the source image scale to use in the output image (i.e. 1 for [0..1], 255 for [0..255], etc.).
		///
		/// @post	A new image file is created in the filesystem. The image type is assigned according to the file extension provided in the
		///			filename (e.g. "foo.png" selects PNG as the image type). Otherwise the image type is Magick++'s implementation-dependent.
		void writeToOutputImage (const std::string& outputFile, const double& scalingFactor = 1.0) const;

	private:

		std::vector<unsigned char>	pixels_;	///< Set of pixels that defines the press clip.

		unsigned int				x_;			///< X-axis coordinate of the row in the underlying image where the top leftmost pixel of the press clip is.

		unsigned int				y_;			///< Y-axis coordinate of the column in the underlying image where the top leftmost pixel of the press clip is.

		unsigned int				width_;		///< Width of the clip in pixels.

		unsigned int				height_;	///< Height of the clip in pixels.

		unsigned int				size_;		///< Size of the clip in pixels.

		// Explicitly disallowed compiler-generated methods. DO NOT IMPLEMENT!!
		Clip ();
};


inline unsigned char& Clip::operator() (const unsigned int &x, const unsigned int &y)
{
	return pixels_.at(x * width_ + y);
};


inline unsigned char Clip::operator() (const unsigned int &x, const unsigned int &y) const
{
	return pixels_.at(x * width_ + y);
};


inline const unsigned int& Clip::width () const
{
	return width_;
};


inline const unsigned int& Clip::height () const
{
	return height_;
};


inline const unsigned int& Clip::size () const
{
	return size_;
};

#endif


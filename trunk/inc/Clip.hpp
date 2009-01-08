/// @file
/// @brief Declaration of Clip class

#if !defined(_CLIP_H)
#define _CLIP_H

#include <Magick++.h>
#include <deque>
#include <string>


///
/// Press clip in which a newspaper's is divided
///
/// This class manages a press clip within a newspaper's page, storing it as a set of pixels from an underlying image that
/// representes the whole page. The newspaper pages are images that may come in several formats, such JPEG, PDF, PNG, etc.
/// The Magick++ library (an API for the ImageMagick suite) provides an abstraction layer to keep the code independent from
/// the image format, so that other classes have an unified way to work with images. In future modifications any other library
/// can be added to load images. In such case, the constructor and the writeToExternalImage method must be overloaded.
///
/// @see <a href="http://www.imagemagick.org/Magick++/">Magick++ API</a>
///
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
///
class Clip
{
public:

	///
	/// Constructor.
	///
	/// @param image		Underlying image where the clip belongs to.
	/// @param row			Row in the underlying image where the upper leftmost pixel of the clip is at.
	/// @param column		Column in the underlying image where the upper leftmost pixel of the clip is at.
	/// @param height		Height of the clip.
	/// @param width		Width of the clip.
	///
	/// @post The image is stored internally using a grayscale colorspace.
	///
	/// @exception If press clip's parameters fall outside the underlying image, an exception is thrown.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	explicit Clip (const Magick::Image& image, const unsigned int& row, const unsigned int& column, const unsigned int& height, const unsigned int& width);


	///
	/// Allows read-and-write access to a pixel in the clip.
	///
	/// @param row		Row in the clip where the pixel is at.
	/// @param column	Column in the clip where the pixel is at.
	///
	/// @return A reference to the gray level of the pixel at given location.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	unsigned char& operator() (const unsigned int& row, const unsigned int& column);


	///
	/// Allows read-only access to a pixel in the clip.
	///
	/// @param row		Row in the clip where the pixel is at.
	/// @param column	Column in the clip where the pixel is at.
	///
	/// @return The gray level of the pixel at given location.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	unsigned char operator() (const unsigned int& row, const unsigned int& column) const;


	///
	/// Returns the width of the clip.
	///
	/// @return Width of the clip in pixels.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	const unsigned int& width () const;


	///
	/// Returns the height of the clip.
	///
	/// @return Height of the clip in pixels.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	const unsigned int& height () const;


	///
	/// Returns the number of pixels in the clip.
	///
	/// @return Number of pixels in the clip.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	const unsigned int& size () const;


	///
	/// Creates a new image file using Magick++ that reflects the current state of the press clip.
	///
	/// @param outputFile	A string with the name of the image created in the file system.
	///
	/// @post A new image file is created in the filesystem. The image type is assigned according
	/// to the file extension that comes with the filename (e.g. "foo.png" selects PNG as the image
	/// type). Otherwise the image type is Magick++'s implementation-dependent.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	void writeToOutputImage (const std::string& outputFile) const;

private:

	std::deque<unsigned char>	pixels_;	///< Set of pixels that defines the press clip.

	unsigned int				row_;		///< Row in the underlying image where the upper leftmost pixel of the press clip is at.

	unsigned int				column_;	///< Column in the underlying image where the upper leftmost pixel of the press clip is at.

	unsigned int				width_;		///< Width of the clip in pixels.

	unsigned int				height_;	///< Height of the clip in pixels.

	unsigned int				size_;		///< Size of the clip in pixels.


	// Explicitly disallowed compiler-generated functions. DO NOT IMPLEMENT THEM!!
	Clip ();
};



inline unsigned char& Clip::operator() (const unsigned int &row, const unsigned int &column)
{
	return pixels_.at(row * width_ + column);
};


inline unsigned char Clip::operator() (const unsigned int &row, const unsigned int &column) const
{
	return pixels_.at(row * width_ + column);
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

#endif  //_CLIP_H

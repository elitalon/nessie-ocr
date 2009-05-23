/// @file
/// @brief Definition of Clip class

#include "Clip.hpp"
#include "NessieException.hpp"
#include <cmath>


Clip::Clip (const Magick::Image& image, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width)
:	pixels_(0),
	width_(width),
	height_(height),
	size_(0)
{
	if ( (height == 0) && (width == 0) )
		throw NessieException ("Clip::Clip() : Constructor has 0 size.");

	if ( width > image.columns() )
		throw NessieException ("Clip::Clip() : The press clip's width cannot be wider than the underlying image's.");

	if ( height > image.rows() )
		throw NessieException ("Clip::Clip() : The press clip's height cannot be higher than the underlying image's.");

	if ( x >= image.rows() || y >= image.columns() )
		throw NessieException ("Clip::Clip() : The press clip's top leftmost pixel falls outside the image.");

	if( (x + height) > image.rows() || (y + width) > image.columns() )
		throw NessieException ("Clip::Clip() : The clip does not fall completely within the underlying image.");

	size_ = width_ * height_;
	pixels_.reserve(size_);

	Magick::Pixels frame(const_cast<Magick::Image&>(image));
	Magick::PixelPacket *pixels = frame.get(x, y, width_, height_);

	Magick::ColorGray grayLevel;
	for ( unsigned int i = 0; i < height_; ++i )
	{
		for ( unsigned int j = 0; j < width_; ++j )
		{
			grayLevel = *pixels++;
			pixels_.push_back( static_cast<unsigned char>(round(grayLevel.shade() * 255.0)) );
		}
	}
}


void Clip::writeToOutputImage (const std::string& outputFile, const double& scalingFactor ) const
{
	Magick::Image outputImage = Magick::Image(Magick::Geometry(width_, height_), Magick::ColorGray(1.0));
	outputImage.type( Magick::GrayscaleType );

	Magick::Pixels view(outputImage);
	Magick::PixelPacket *originPixel = view.get(0, 0, width_, height_);
	Magick::PixelPacket *pixel;

	for ( unsigned int i = 0; i < view.rows(); ++i )
	{
		for ( unsigned int j = 0; j < view.columns(); ++j )
		{
			pixel = originPixel + (i * view.columns()) + j;

			*pixel = Magick::ColorGray ( static_cast<double>(pixels_.at(i * width_ + j)) / scalingFactor );
		}
	}

	view.sync();
	outputImage.syncPixels();
	outputImage.write(outputFile);
}


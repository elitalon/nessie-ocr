/// @file
/// @brief Definition of Pattern class

#include "Pattern.hpp"
#include <Magick++.h>
#include <cmath>
#include <algorithm>


Pattern::Pattern ()
:	pixels_(std::vector<unsigned int>(Pattern::planeSize() * Pattern::planeSize(), 0)),
	height_(Pattern::planeSize()),
	width_(Pattern::planeSize()),
	size_(Pattern::planeSize() * Pattern::planeSize())
{}


std::pair<unsigned int, unsigned int> Pattern::centroid () const
{
	unsigned int m10 = 0;
	unsigned int m01 = 0;

	// Compute moments of first order
	for ( unsigned int i = 0; i < height_; ++i )
	{
		for (unsigned int j = 0; j < width_; ++j )
		{
			m10 += i * pixels_.at(i * width_ + j);
			m01 += j * pixels_.at(i * width_ + j);
		}
	}

	unsigned int area = this->area();
	if ( area == 0 )
		area = 1;

	m10 = round( m10 / area );
	m01 = round( m01 / area );

	return std::pair<unsigned int, unsigned int>(m10,m01);
}


unsigned int Pattern::area () const
{
	return std::count(pixels_.begin(), pixels_.end(), 1);
}


void Pattern::writeToOutputImage (const std::string& outputFile, const bool& invert) const
{
	// Create an empty Image
	Magick::Image outputImage = Magick::Image(Magick::Geometry(width_, height_), Magick::ColorGray(1.0));
	outputImage.type( Magick::GrayscaleType );

	// Create a view over the image
	Magick::Pixels view(outputImage);
	Magick::PixelPacket *originPixel = view.get(0, 0, width_, height_);
	Magick::PixelPacket *pixel;

	// Assign values to the image
	for ( unsigned int i = 0; i < view.rows(); ++i )
	{
		for ( unsigned int j = 0; j < view.columns(); ++j )
		{
			pixel = originPixel + (i * view.columns()) + j;

			if ( not invert )
				*pixel = Magick::ColorGray ( static_cast<double>(pixels_.at(i * width_ + j)) );
			else
				*pixel = Magick::ColorGray ( static_cast<double>(not (pixels_.at(i * width_ + j) ^ 0)) );
		}
	}

	// Write changes to disc
	view.sync();
	outputImage.syncPixels();
	outputImage.write(outputFile);
}


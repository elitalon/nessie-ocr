/// @file
/// @brief Definition of Pattern class

#include "Pattern.hpp"
#include "Region.hpp"
#include <cmath>
#include <Magick++.h>


Pattern::Pattern (const Region& region)
:	pixels_(std::vector<unsigned int>(0)),
	height_(region.height()),
	width_(region.width()),
	size_(0)
{
	size_ = height_ * width_;
	pixels_.resize(size_, 0);

	for ( unsigned int i = 0; i < region.size(); ++i )
		pixels_.at(region(i).first * width_ + region(i).second) = 1;
};


std::pair<unsigned int, unsigned int> Pattern::centroid () const
{
	unsigned int area = 0;
	unsigned int m10 = 0;
	unsigned int m01 = 0;

	for ( unsigned int i = 0; i < height_; ++i )
	{
		for (unsigned int j = 0; j < width_; ++j )
		{
			area += pixels_.at(i * width_ + j);
			m10 += i * pixels_.at(i * width_ + j);
			m01 += j * pixels_.at(i * width_ + j);
		}
	}

	m10 = round( m10 / area );
	m01 = round( m01 / area );

	return std::pair<unsigned int, unsigned int>(m10,m01);
};


void Pattern::writeToOutputImage (const std::string& outputFile, const bool& invert) const
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

			if ( not invert )
				*pixel = Magick::ColorGray ( static_cast<double>(pixels_.at(i * width_ + j)) );
			else
				*pixel = Magick::ColorGray ( static_cast<double>(not (pixels_.at(i * width_ + j) ^ 0)) );
		}
	}

	view.sync();
	outputImage.syncPixels();
	outputImage.write(outputFile);
};


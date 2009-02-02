/// @file
/// @brief Definition of Pattern class

#include "Pattern.hpp"
#include "Region.hpp"
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


void Pattern::writeToOutputImage (const std::string& outputFile) const
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

			*pixel = Magick::ColorGray ( static_cast<double>(pixels_.at(i * width_ + j)) );
		}
	}

	view.sync();
	outputImage.syncPixels();
	outputImage.write(outputFile);
};


/// @file
/// @brief Definition of Pattern class

#include "Pattern.hpp"
#include "Region.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"
#include <cmath>
#include <algorithm>
#include <Magick++.h>
#include <list>
#include <iostream>

const unsigned int Pattern::planeSize_ = 35;


Pattern::Pattern ()
:	pixels_(0),
	height_(0),
	width_(0),
	size_(0)
{};


Pattern::Pattern (const Region& region)
:	pixels_(std::vector<unsigned int>(planeSize_ * planeSize_, 0)),
	height_(planeSize_),
	width_(planeSize_),
	size_(planeSize_ * planeSize_)
{
	try
	{
		// Normalize region using a Magick++ object
		Magick::Image regionImage(Magick::Geometry(region.width(), region.height()), Magick::ColorGray(1.0));
		regionImage.type( Magick::GrayscaleType );

		Magick::Pixels view(regionImage);
		Magick::PixelPacket *originPixel = view.get(0, 0, region.width(), region.height());
		Magick::PixelPacket *pixel;

		for ( unsigned int i = 0; i < region.size(); ++i )
		{
			pixel	= originPixel + (region.at(i).first * view.columns() + region.at(i).second);
			*pixel	= Magick::ColorGray (0.0);
		}
		view.sync();
		regionImage.syncPixels();
		regionImage.scale( Magick::Geometry(planeSize_, planeSize_) );

		// Preprocess the normalized region
		Clip clip(regionImage, 0, 0, regionImage.rows(), regionImage.columns());
		Preprocessor preprocessor(clip);
		preprocessor.applyAveragingFilters();
		preprocessor.applyGlobalThresholding();
		preprocessor.applyTemplateFilters();
		preprocessor.extractRegions();
		std::list<Region> regions(preprocessor.regions());
		
		if ( regions.size() > 1 )	// Merge subregions if preprocessing splitted the original region
		{
			Region tmp;
			
			for ( std::list<Region>::iterator i = regions.begin(); i != regions.end(); ++i )
				tmp = tmp + *i;
			
			regions.clear();
			regions.push_back(tmp);
		}

		// Build the pattern
		Region normalizedRegion(regions.front());
		for ( unsigned int i = 0; i < normalizedRegion.size(); ++i )
			pixels_.at(normalizedRegion.at(i).first * width_ + normalizedRegion.at(i).second) = 1;

		if ( regionImage.rows() < planeSize_ )	// Shift rows from top to the center
		{
			unsigned int offset = (planeSize_ - regionImage.rows()) / 2;
			
			while ( offset != 0 )
			{
				for ( int i = planeSize_-2; i >= 0; --i )
				{
					for ( unsigned int j = 0; j < planeSize_; ++j )
						pixels_.at((i+1) * planeSize_ + j) = pixels_.at(i * planeSize_ + j);
				}
				for ( unsigned int j = 0; j < planeSize_; ++j )
					pixels_.at(j) = 0;
				
				--offset;
			}
		}
		
		if ( regionImage.columns() < planeSize_ )	// Shift columns from left to center
		{
			unsigned int offset = (planeSize_ - regionImage.columns()) / 2;

			while ( offset != 0 )
			{
				for ( unsigned int i = 0; i < planeSize_; ++i )
				{
					for ( int j = planeSize_-2; j >= 0; --j )
						pixels_.at(i * planeSize_ + (j+1)) = pixels_.at(i * planeSize_ + j);
				}
				for ( unsigned int i = 0; i < planeSize_; ++i )
					pixels_.at(i * planeSize_) = 0;
					
				--offset;
			}
		}		
	}
	catch (...) {}	// Ignore the exception, a blank pattern will be created.
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


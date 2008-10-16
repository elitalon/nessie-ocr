///
/// @file
/// @brief Implementation of the class Recognizer
///

#include "Recognizer.hpp"

#include <cmath>
#include <iostream>

#include "Preprocessor.hpp"
#include "Segmenter.hpp"
#include "NessieException.hpp"


///
/// @details Creates a new Recognizer object loading the image from disk. If the image is multi-frame only the first one is
/// taken, e.g. the first page of a PDF with multiple pages.
///
Recognizer::Recognizer (const std::string &path) : texts_(std::vector<Text>(0)), statistics_(std::vector<Statistics>(0))
{
	// Load image from disk
	std::vector<Magick::Image> images;
	Magick::readImages( &images, path );
	
	Magick::Image image = images[0];
	
	// Store the image dimensions
	width_	= image.columns();
	height_	= image.rows();
	
	// Load image into the internal vector
	loadImage(image);
};


///
/// @details Creates a new Recognizer object from an image loaded externally with methods from Magick++ API.
/// If the image is multi-frame only the first one is taken, e.g. the first page of a PDF with multiple pages.
/// 
Recognizer::Recognizer (Magick::Image &image) : texts_(std::vector<Text>(0)), statistics_(std::vector<Statistics>(0))
{
	// Store the image dimensions
	width_	= image.columns();
	height_	= image.rows();
	
	// Load image into the internal vector
	loadImage(image);
};


///
/// @details It is assumed that the image is a clip itself we can obtain the text processing the whole image. Since there is only
/// one clip you can gather its text and its statistics by simply calling text() and statistics() with no parameters at all.
///
void Recognizer::obtainText ()
{
	obtainText(0, 0, height_, width_);
};


///
/// @details Each set of points provides us a clip that can be located within the page.
/// 
void Recognizer::obtainText (const std::vector<ClipLocation> &coordinates)
{
	std::vector<ClipLocation>::const_iterator coordinatesIterator;
	 
	for ( coordinatesIterator = coordinates.begin(); coordinatesIterator not_eq coordinates.end(); ++coordinatesIterator )
	{
		unsigned int x		= (*coordinatesIterator).x();
		unsigned int y		= (*coordinatesIterator).y();
		unsigned int height	= (*coordinatesIterator).height();
		unsigned int width	= (*coordinatesIterator).width();
		
		obtainText(x, y, height, width);
	}
};


///
/// @details If the clip falls outside the image an exception is thrown unless it can be truncated safety. By default the text
/// extracted and the statistical data regarding the recognition process are saved in the first position of internal data structures.
/// That means you can gather them by simply calling text() and statistics() with no parameters at all.
/// 
void Recognizer::obtainText (const unsigned int &x, const unsigned int &y, unsigned int &height, unsigned int &width)
{
	// Test the upper left-most pixel X coordinate is inside the source image
	if ( (x >= height_) or (x < 0) )
		throw NessieException ("Recognizer::obtainText() : The x coordinate of the clip's top left-most pixel is outside the image");
		
	// Test the upper left-most pixel Y coordinate is inside the source image
	if ( (y >= width_) or (y < 0) )
		throw NessieException ("Recognizer::obtainText() : The y coordinate of the clip's top left-most pixel is outside the image");
	
	// Truncate the clip's height if it is higher than the image
	if ( (height > height_) or (height < 0) )
		height = height_;
		
	// Truncate the clip's width if it is wider than the image
	if ( (width > width_) or (width < 0) )
		width = width_;
		
	// Truncate the clip's height if it is outside the source image
	if ((x + height) > height_)
		height = height_ - x;
	
	// Truncate the clip's width if it is outside the source image
	if ((y + width) > width_)
		width = width_ - y;
	
	
	// Creates the clip
	Clip clip(image_, width_, x, y, height, width);
	

	//
	// Preprocessing stage
	//
	Preprocessor preprocessor;
	std::cout << "Background reference level:  " << static_cast<unsigned int>(preprocessor.findBackgroundReferenceGrayLevel(clip)) << std::endl;
	std::cout << "Optimal threshold:           " << static_cast<unsigned int>(preprocessor.computeOptimalThreshold(clip)) << std::endl << std::endl;
	preprocessor.removeIsolatedNoise(clip);
	updateImage(clip);
	
	
	//
	// Segmentation stage
	//
	Segmenter segmenter;
	// segmenter.applyThreshold(clip, preprocessor.optimalThreshold(), preprocessor.backgroundReferenceGrayLevel());
	// 	updateImage(clip);
	// 	segmenter.applyFloodFill(clip);
	
	
	//
	// Classification stage
	//
	
	
	// Gather execution times
	Statistics stats;
	
	stats.backgroundReferenceGrayLevelFindingTime( preprocessor.backgroundReferenceGrayLevelFindingTime() );
	stats.optimalThresholdComputingTime( preprocessor.optimalThresholdComputingTime() );
	stats.noiseRemovalTime( preprocessor.noiseRemovalTime() );
	
	stats.thresholdingTime( segmenter.thresholdingTime() );
	stats.floodFillingTime( segmenter.floodFillingTime() );
	
	statistics_.push_back(stats);
};


///
/// @details If either the source or the target are bigger or smaller than its counterpart, only the pixels whose coordinates match are changed.
/// 
void Recognizer::writeExternalImage (Magick::Image &externalImage) const
{
	// Test if the image is empty to create a new one
	if ( (externalImage.rows() == 0) and (externalImage.columns() == 0) )
		externalImage = Magick::Image(Magick::Geometry(width_, height_), "white");
	
	
	// Assume the internal image dimensions are at least greater or equal to the external image dimensions
	unsigned int rows = height_, columns = width_;
	
	
	// Test the external image is lower than the internal image
	if ( externalImage.rows() < height_ )
		rows = externalImage.rows();
	
	// Test the external image is narrower than the internal image
	if ( externalImage.columns() < width_ )
		columns = externalImage.columns();
	
	
	// Convert the external image into a grayscale colorspace
	externalImage.type( Magick::GrayscaleType );
		
	// Ensure that there is only one reference to underlying image.
	// If this is not done, then image pixels will not be modified.
	externalImage.modifyImage();

	// Allocate pixel view
	Magick::Pixels view(externalImage);
	Magick::PixelPacket *originPixel = view.get(0, 0, columns, rows);

	// Copy the current data into the external image
	for ( unsigned int i = 0; i < rows; ++i )
	{
		for ( unsigned int j = 0; j < columns; ++j )
		{
			unsigned int index = (i * columns) + j;
			Magick::PixelPacket *pixel = originPixel + index;

			*pixel = Magick::ColorGray( static_cast<double>(image_[index]) / 255.0 );
		}
	}
	
	// Synchronize changes to the image
	view.sync();
};


///
/// @details The image is automatically converted into a grayscale colorspace according with the RGB values within
/// the original source. If the image comes already in a grayscale colorspace no conversion is applied.
/// 
void Recognizer::loadImage (Magick::Image &image)
{
	// Reserve enough space
	image_.reserve(height_ * width_);
	image_.resize(height_ * width_);
	
	// Convert the image into grayscale colorspace
	image.type( Magick::GrayscaleType );
	
	// Ensure that there is only one reference to underlying image
	// If this is not done, then image pixels will not be modified.
	image.modifyImage();
	
	// Allocate pixel view
	Magick::Pixels view(image);
	Magick::PixelPacket *pixels = view.get(0, 0, width_, height_);
	
	// Copy the image into the internal data structure
	for ( unsigned int i = 0; i < height_; ++i )
	{
		for ( unsigned int j = 0; j < width_; ++j )
		{
			Magick::ColorGray grayLevel(*pixels++);

			image_[(i * width_) + j] = static_cast<unsigned char>( round(grayLevel.shade() * 255.0) );
		}
	}	
};


///
/// @details Since the only way of passing a Clip object to this method is invoking Recognizer::obtainText(), and the dimensions are controlled inside
/// that method, here it is assumed that all the coordinates are valid.
/// 
void Recognizer::updateImage (const Clip &clip)
{
	// Get all the pixels of the clip (this is faster than calling Clip::getPixelGrayLevel() each time)
	std::vector<unsigned char> pixels = clip.pixels();
	std::vector<unsigned char>::iterator pixelsIterator = pixels.begin();
	
	unsigned int clipBottomBorder	= clip.x() + clip.height();
	unsigned int clipLeftBorder		= clip.y() + clip.width();
	
	for ( unsigned int i = clip.x(); i < clipBottomBorder; ++i )
	{
		for ( unsigned int j = clip.y(); j < clipLeftBorder; ++j )
		{
			image_[(i * width_) + j] = *pixelsIterator;
			advance(pixelsIterator, 1);
		}
	}
};

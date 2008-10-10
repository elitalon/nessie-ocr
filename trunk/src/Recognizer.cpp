///
/// @file
/// @brief Implementation of the class Recognizer
///

#include "Recognizer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "Clip.h"
#include "Preprocessor.h"
#include "NessieException.h"


///
/// @details Creates a new Recognizer object loading the image from disk. If the image is multi-frame only the first one is
/// taken, e.g. the first page of a PDF with multiple pages.
/// 
/// @param path Relative path within the filesystem where the image is
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-10
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
/// @param image An Image object from the Magick++ API previously loaded
/// 
/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Image</a>
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-10
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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-09
///
void Recognizer::obtainText ()
{
	obtainText(0, 0, height_, width_);
};


///
/// @details Each set of points provides us a clip that can be located within the page.
/// 
/// @param coordinates A list of coordinates to locate a number of clips within the page
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-09
///
void Recognizer::obtainText (const std::vector<int> &coordinates)
{
	//std::vector<int>::iterator coordinatesIterator;
	// 
	// for ( coordinatesIterator = coordinates.begin(); coordinatesIterator not_eq coordinates.end(); ++coordinatesIterator )
	// {
	// 	obtainText(0,0,0,0);
	// }
};


///
/// @details If the clip falls outside the image an exception is thrown unless it can ne truncated safety. By default the text
/// extracted and the statistical data regarding the recognition process are saved in the first position of internal data structures.
/// That means you can gather them by simply calling text() and statistics() with no parameters at all.
/// 
/// @param x		Top left-most pixel X coordinate
/// @param y		Top left-most pixel Y coordinate
/// @param height	Clip's height
/// @param width	Clip's width
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-09
///
void Recognizer::obtainText (const unsigned int &x, const unsigned int &y, unsigned int &height, unsigned int &width)
{
	// Test the upper left-most pixel X coordinate is inside the source image
	if ( (x >= height_) or (x < 0) )
		throw NessieException ("Recognizer::obtainText() : The x coordinate of the clip's top left-most pixel is outside the image");
		
	// Test the upper left-most pixel Y coordinate is inside the source image
	if ( (y >= width_) or (y < 0) )
		throw NessieException ("Recognizer::obtainText() : The y coordinate of the clip's top left-most pixel is outside the image");
	
	// Test the clip's height is not bigger than the image
	if ( (height > height_) or (height < 0) )
		throw NessieException ("Recognizer::obtainText() : The height of the clip is bigger than the image's height or less than 0");
		
	// Test the clip's width is not bigger than the image
	if ( (width > width_) or (width < 0) )
		throw NessieException ("Recognizer::obtainText() : The width of the clip is bigger than the image's width or less than 0");
		
	// Truncate the clip's height if it is outside the source image
	if ((x + height) > height_)
		height = height_ - x;
	
	// Truncate the clip's width if it is outside the source image
	if ((y + width) > width_)
		width = width_ - y;
	
	// Creates the clip
	Clip clip(image_, x, y, height, width);
	
	
	// Preprocessing stage
	Preprocessor preprocessor;
	preprocessor.computeOptimalThreshold(clip);
	preprocessor.removeIsolatedNoise(clip);
	updateImage(clip);
	
	
	// Segmentation stage
	
	
	// Classification stage
};


///
/// @details If either the source or the target are bigger or smaller than its counterpart, only the pixels that match each other are changed.
/// 
/// @param externalImage The destination Image object from the Magick++ API previously created
/// 
/// @remarks The image will be converted to a grayscale colorspace
/// 
/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Image</a>
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-09
///
void Recognizer::writeExternalImage (Magick::Image &externalImage) const
{
	unsigned int rows = height_, columns = width_;
	
	// Test if the image is empty to create a new one
	if ( (externalImage.rows() == 0) and (externalImage.columns() == 0) )
		externalImage = Magick::Image(Magick::Geometry(width_, height_), "white");
	
	// Test if the external image fits into the current image
	if ( externalImage.rows() < height_ )
		rows = externalImage.rows();
	
	if ( externalImage.columns() < width_ )
		columns = externalImage.columns();
	
	// Convert the image into a grayscale colorspace
	externalImage.type( Magick::GrayscaleType );
	
	// Ensure that there is only one reference to underlying image
	// If this is not done, then image pixels will not be modified.
	externalImage.modifyImage();
		
	// Copy the current data into the external image
	for ( unsigned int i = 0; i < rows; ++i )
	{
		for ( unsigned int j = 0; j < columns; ++j )
		{
			unsigned int index = (i * columns) + j;
			
			Magick::ColorGray color;
			color.shade(static_cast<double>(image_[index]) / 255.0);
			externalImage.pixelColor(j, i, color);
		}
	}
	
	// Save changes to image.
	externalImage.syncPixels();
};


///
/// @details The image is automatically converted into a grayscale colorspace according with the RGB values within
/// the original source. If the image comes already in a grayscale colorspace no conversion is applied.
/// 
/// @param image An Image object from the Magick++ API previously created
/// 
/// @remarks The image is converted to a grayscale colorspace internally
/// 
/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Image</a>
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-09
///
void Recognizer::loadImage (Magick::Image &image)
{
	// Convert the image into grayscale colorspace
	image.type( Magick::GrayscaleType );
	
	// Ensure that there is only one reference to underlying image
	// If this is not done, then image pixels will not be modified.
	image.modifyImage();
	
	// Copy the image into the internal data structure
	image_.reserve(height_ * width_);
	for ( unsigned int i = 0; i < height_; ++i )
	{
		for ( unsigned int j = 0; j < width_; ++j )
		{
			Magick::ColorGray grayLevel	= image.pixelColor(j, i);
			
			image_.push_back( static_cast<unsigned char>(round(grayLevel.shade() * 255.0)) );
		}
	}	
};


///
/// @details Since the only way of loading a Clip object is executing the obtainText() method, and there the dimensions are controlled, here
/// it is assumed that all the coordinates are valid.
/// 
/// @param clip The clip where the new data is taken
/// 
/// @see Clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-10
///
void Recognizer::updateImage (const Clip &clip)
{
	unsigned int p = 0, q;
	for ( unsigned int i = clip.x(); i < clip.height(); ++i )
	{
		q = 0;
		for ( unsigned int j = clip.y(); j < clip.width(); ++j )
		{
			image_[(i * width_) + j] = clip.getPixelGrayLevel(p, q++);
		}
		p++;
	}
};

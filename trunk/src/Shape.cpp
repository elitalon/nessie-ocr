///
/// @file
/// @brief Definition of Shape class
///

#include "Shape.hpp"
#include <cmath>


Shape::Shape ()
	:	width_(0),
		height_(0),
		pixels_(std::vector<Pixel>(0)),
		size_(0),
		leftPixel_(Pixel(0,0)),
		rightPixel_(Pixel(0,0)),
		topPixel_(Pixel(0,0)),
		bottomPixel_(Pixel(0,0))
{

};



void Shape::addPixel (const Pixel& pixel)
{
	// Add the pixel and update the size_ member
	pixels_.push_back( pixel );
	size_ = pixels_.size();
	
	
	// Initialize the extreme pixels the first time we invoke this method
	if ( size_ == 1 )
	{
		topPixel_		= pixels_.at(0);
		bottomPixel_	= pixels_.at(0);
		leftPixel_		= pixels_.at(0);
		rightPixel_		= pixels_.at(0);
	}
	else	// Update the significant pixels
	{
		if ( pixel.first < topPixel_.first )
			topPixel_ = pixel;
			
		if ( pixel.first > bottomPixel_.first )
			bottomPixel_ = pixel;
		
		if ( pixel.second > rightPixel_.second )
			rightPixel_ = pixel;
		
		if ( pixel.second < leftPixel_.second )
			leftPixel_ = pixel;			
	}
	
	
	// Update the width and height of shape
	width_ = rightPixel_.second - leftPixel_.second + 1;
	height_ = bottomPixel_.first - topPixel_.first + 1;
};



///
/// @details A shape is splitted by its weakest column, i.e. the column that has the less count of pixels. Columns with few pixels are assumed to be noise that
/// might cause the union of two different characters.
///
void Shape::split (Shape& leftShape, Shape& rightShape) const
{
	// Find the column that divides the source shape in two equal parts
	unsigned int centerColumn = round( (this->rightPixel_.second + this->leftPixel_.second) / 2 );
	
	
	// Search the weakest column of pixels towards right
	unsigned int weakestRightColumn = centerColumn;
	unsigned int nPreviousPixelsOnTheRight = this->height_;
	for ( unsigned int iColumn = centerColumn; iColumn <= this->rightPixel_.second; ++iColumn )
	{
		unsigned int nCurrentPixels = 0;
		for ( std::vector<Pixel>::const_iterator iPixel = this->pixels_.begin(); iPixel not_eq this->pixels_.end(); ++iPixel )
		{
			if ( (*iPixel).second == iColumn )
				nCurrentPixels++;
		}
		
		// Not found pixels means the segmentation process failed
		if ( nCurrentPixels > 0 and nCurrentPixels < nPreviousPixelsOnTheRight )
		{
			nPreviousPixelsOnTheRight	= nCurrentPixels;
			weakestRightColumn			= iColumn;
		}
	}
	
	
	// Search the weakest column of pixels towards left
	unsigned int weakestLeftColumn = centerColumn;
	unsigned int nPreviousPixelsOnTheLeft = this->height_;
	for ( unsigned int iColumn = centerColumn; iColumn >= this->leftPixel_.second; --iColumn )
	{
		unsigned int nCurrentPixels = 0;
		for ( std::vector<Pixel>::const_iterator iPixel = this->pixels_.begin(); iPixel not_eq this->pixels_.end(); ++iPixel )
		{
			if ( (*iPixel).second == iColumn )
				nCurrentPixels++;
		}
		
		// Not found pixels means the segmentation process failed
		if ( nCurrentPixels > 0 and nCurrentPixels < nPreviousPixelsOnTheLeft )
		{
			nPreviousPixelsOnTheLeft = nCurrentPixels;
			weakestLeftColumn = iColumn;
		}
	}
	
	// Decide the breakpoint
	unsigned int breakpointColumn;
	if ( nPreviousPixelsOnTheRight < nPreviousPixelsOnTheLeft )
		breakpointColumn = weakestRightColumn;
	else
		breakpointColumn = weakestLeftColumn;
	
	// Split the shape
	leftShape.pixels_.clear();
	rightShape.pixels_.clear();
	for ( std::vector<Pixel>::const_iterator iPixel = this->pixels_.begin(); iPixel not_eq this->pixels_.end(); ++iPixel )
	{
		if ( (*iPixel).second < breakpointColumn )
			leftShape.addPixel((*iPixel));
		else
			rightShape.addPixel((*iPixel));
	}
};

///
/// @file
/// @brief Definition of Shape class
///

#include "Shape.hpp"



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



void Shape::addPixel (const Pixel &pixel)
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

///
/// @file
/// @brief Implementation of the class Shape
///

#include "Shape.hpp"


///
/// @details Initializes a Shape object.
///
Shape::Shape ()
	:	leftPixel_(Pixel(0,0)), rightPixel_(Pixel(0,0)), topPixel_(Pixel(0,0)), bottomPixel_(Pixel(0,0)), centralPixel_(Pixel(0,0)),
		pixels_(std::vector<unsigned char>(0)), height_(0), width_(0)
{

};


/// 
/// @details
///	
void Shape::addPixel (const Pixel &pixel, const bool &isInk)
{
	
};

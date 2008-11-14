///
/// @file
/// @brief Definition of Clip class
///

#include "Clip.hpp"
#include "NessieException.hpp"



///
/// @details Initializes a Clip object located at coordinates (row,column) in the underlying image, with the height and width passed.
/// 
Clip::Clip (const std::vector<unsigned char>& image, const unsigned int& imageWidth, const unsigned int& row, const unsigned int& column, const unsigned int& height, const unsigned int& width)
	:	row_(row),
		column_(column),
		width_(width),
		height_(height),
		pixels_(std::vector<unsigned char>(0)),
		size_(0)
{
	if ( (height == 0) and (width == 0) )
		throw NessieException ("Clip::Clip() : Constructor has 0 size");
	
	if ( width > imageWidth )
		throw NessieException ("Clip::Clip() : Clip's width cannot be wider than underlying image's width");
		
	// Number of pixels within the clip
	size_ = width * height;
	
	// Space allocation for the clip
	pixels_.reserve(size_);
	
	// Copy the data from the underlying image
	for ( unsigned int i = row; i < (row + height); ++i )
	{
		for ( unsigned int j = column; j < (column + width); ++j )
			pixels_.push_back( image.at(i * width + j) );
	}
};



Clip::~Clip ()
{

}

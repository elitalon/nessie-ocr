///
/// @file
/// @brief Definition of Clip class
///

#include "Clip.hpp"



///
/// @details Initializes a Clip object located at coordinates (row,column) in the underlying image, with the height and width passed.
/// 
Clip::Clip (const std::vector<unsigned char>& image, const unsigned int& imageWidth, const unsigned int& row, const unsigned int& column, const unsigned int& height, const unsigned int& width)
	:	row_(row),
		column_(column),
		width_(width),
		height_(height),
		pixels_(0),
		size_(0)
{
	if ( (height == 0) and (width == 0) )
		throw NessieException ("Clip::Clip() : Constructor has 0 size");
	
	if ( width > imageWidth )
		throw NessieException ("Clip::Clip() : Clip's width cannot be wider than underlying image's width");
		
	// Number of pixels within the clip
	size_ = width * height;
	
	// Space allocation for the clip
	pixels_ = new unsigned char[size_];
	
	// Copy the data from the underlying image
	for ( unsigned int i = row; i < (row + height); ++i )
	{
		std::vector<unsigned char>::const_iterator rowIterator = image.begin();
		advance (rowIterator, (i * imageWidth) + column);
		
		for ( unsigned int j = 0; j < width; ++j )
		{
			pixels_[i * width + j] = *rowIterator;
			advance (rowIterator, 1);
		}
	}
};



Clip::Clip (const Clip& clip)
	:	row_(clip.row_),
		column_(clip.column_),
		width_(clip.width_),
		height_(clip.height_),
		pixels_(0),
		size_(clip.size_)
{
	// Space allocation for the clip
	this->pixels_ = new unsigned char[clip.size_];
	
	// Copy the data from the source clip
	for ( unsigned int i = 0; i < clip.size_; ++i )
		this->pixels_[i] = clip.pixels_[i];
};



Clip::~Clip ()
{
	delete[] pixels_;
}

///
/// @file
/// @brief Definition of Clip class
///

#include "Clip.hpp"



///
/// @details Initializes a Clip object located at coordinates (row,column) in the underlying image, with the height and width passed.
/// 
Clip::Clip (const std::vector<unsigned char> &image, const unsigned int &imageWidth, const unsigned int &row, const unsigned int &column, const unsigned int &height, const unsigned int &width)
	:	row_(row),
		column_(column),
		width_(width),
		height_(height)
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



///
/// @details Destroys a Clip object.
///
Clip::~Clip ()
{
	delete[] pixels_;
}

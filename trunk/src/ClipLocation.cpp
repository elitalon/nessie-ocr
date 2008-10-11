///
/// @file
/// @brief Implementation of the class ClipLocation
///

#include "ClipLocation.hpp"


///
/// @details Initializes a ClipLocation object with every data set to 0
/// 
ClipLocation::ClipLocation ()
	: x_(0), y_(0), height_(0), width_(0)
{

};


///
/// @details Initializes a ClipLocation object with every data set according to the values passed
/// 
ClipLocation::ClipLocation (const unsigned int &x, const unsigned int &y, const unsigned int &height, const unsigned int &width)
	: x_(x), y_(y), height_(height), width_(width)
{
	
};
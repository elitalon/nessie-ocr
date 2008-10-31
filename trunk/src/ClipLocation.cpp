///
/// @file
/// @brief Definition of ClipLocation class
///

#include "ClipLocation.hpp"


///
/// @details Initializes a ClipLocation object with every data set to 0.
/// 
ClipLocation::ClipLocation ()
	: row_(0), column_(0), height_(0), width_(0)
{

};


///
/// @details Initializes a ClipLocation object with every data set according to the values passed.
/// 
ClipLocation::ClipLocation (const unsigned int &row, const unsigned int &column, const unsigned int &height, const unsigned int &width)
	: row_(row), column_(column), height_(height), width_(width)
{
	
};

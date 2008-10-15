///
/// @file
/// @brief Declaration of the custom type Pixel
///

#if !defined(_PIXEL_H)
#define _PIXEL_H

#include <utility>


///
/// @typedef Pixel
/// 
/// @brief Information about an image pixel.
///
/// @details This pair keeps the coordinates of a pixel within a press clip. The first member representes the x coordinate (the row)
/// and the second member representes the y coordinate (the column)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-13
/// 
typedef std::pair<unsigned int, unsigned int> Pixel;

#endif  //_PIXEL_H

#if !defined(_COLORSPACE_H)
#define _COLORSPACE_H

///
/// @file
/// @brief Declaration of enumeration Colorspace
///

#include <Magick++.h>
using namespace Magick;

///
/// Colorspace of an image.
/// 
/// This enumeration represents the different colorspaces that an image may have. This enumeration
/// depends internally on Magick++ image types implementation
/// (see <a href="http://www.imagemagick.org/Magick++/Enumerations.html#ImageType">ImageType on Magick++ documentation</a>).
/// Only three choices are given, though there are many options available in Magick++.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
///
enum Colorspace
{
	COLORSPACE_GRAYSCALE,		///< A grayscale colorspace
	COLORSPACE_RGB,				///< A RGB colorspace
	COLORSPACE_MONOCHROMATIC,	///< A monochromatic colorspace
	COLORSPACE_UNDEFINED		///< An undefined colorspace
};

#endif  //_COLORSPACE_H

#include "FontColor.h"


///
/// @details Initializes a FontColor object with all RGB components set to 0
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
FontColor::FontColor () : red(0), green(0), blue(0)
{
	
};


///
/// @details Initializes a FontColor object with the components set to the values passed.
/// Since the color must be expressed using a RGB scale of 256 possible values,
/// any value over 255 will be truncated
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
FontColor::FontColor (unsigned int red_, unsigned int green_, unsigned int blue_)
	: red(red_ > 255?255:red_), green(green_ > 255?255:green_), blue(blue_ > 255?255:blue_)
{
	
};


///
/// @details Destroys a FontColor object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
FontColor::~FontColor ()
{

};

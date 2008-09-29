#include "RgbColor.h"

///
/// @file
/// @brief Implementation of struct RgbColor
///


///
/// @details Initializes a RgbColor object with all RGB components set to 0
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
RgbColor::RgbColor () : red(0.0), green(0.0), blue(0.0)
{
	
};


///
/// @details Initializes a RgbColor object with the components set to the values passed.
/// Since the color must be expressed using a RGB scale of 256 possible values normalized between 0 and 1,
/// any value out this scale will be truncated
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
RgbColor::RgbColor (double redChannel, double greenChannel, double blueChannel)
{
	if ( redChannel > 1.0 )
		red = 1.0;
	else
	{
		if ( redChannel < 0.0 )
			red = 0.0;
		else
			red = redChannel;
	}
	
	if ( greenChannel > 1.0 )
		green = 1.0;
	else
	{
		if ( greenChannel < 0.0 )
			green = 0.0;
		else
			green = greenChannel;
	}
	
	if ( blueChannel > 1.0 )
		blue = 1.0;
	else
	{
		if ( blueChannel < 0.0 )
			blue = 0.0;
		else
			blue = blueChannel;
	}
};


///
/// @details Destroys a RgbColor object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
/// 
RgbColor::~RgbColor ()
{

};

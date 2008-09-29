#include "Style.h"

///
/// @file
/// @brief Implementation of class Style
///


///
/// @details Initializes a Style object with size set to 0, color set to black and weight set to normal
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
///
Style::Style () : size_(0), color_(RgbColor()), weight_(FONT_NORMAL)
{
	
};


///
/// @details Initializes a Style object with size, color and weight set to the values passed
/// 
/// @param size		Font size in points (pt)
/// @param color	Font color in RGB colorspace
/// @param weight	Font weight according to values in FontWeight
/// 
/// @see RgbColor, FontWeight
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
Style::Style (unsigned int size, RgbColor color, FontWeight weight) : size_(size), color_(color), weight_(weight)
{
	
};


///
/// @details Destroys a Style object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
Style::~Style ()
{

};


///
/// @details A bold font may be only bold, bold and italic or bold and underlined
/// 
/// @return True if the font is bold
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
bool Style::isBold () const
{
	switch (weight_)
	{
		case FONT_BOLD | FONT_BOLD_ITALIC | FONT_BOLD_UNDERLINED:
		{
			return true;
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
};


///
/// @details An italic font may be only italic, italic and bold or italic and underlined
/// 
/// @return True if the font is italic
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
bool Style::isItalic () const
{
	switch (weight_)
	{
		case FONT_ITALIC | FONT_BOLD_ITALIC | FONT_ITALIC_UNDERLINED:
		{
			return true;
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
};


///
/// @details An underlined font may be only underlined, underlined and italic or underlined and bold
/// 
/// @return True if the font is underlined
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
bool Style::isUnderlined () const
{
	switch (weight_)
	{
		case FONT_UNDERLINED | FONT_ITALIC_UNDERLINED | FONT_BOLD_UNDERLINED:
		{
			return true;
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
};


///
/// @details A normal font is neither bold, nor italic, nor underlined
/// 
/// @return True if the font is normal
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
bool Style::isNormal () const
{
	switch (this->weight_)
	{
		case FONT_NORMAL:
		{
			return true;
			break;
		}
		default:
		{
			return false;
			break;
		}
	}
};


///
/// @details The size is expressed in points (pt)
/// 
/// @return The size of the font in points (pt)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
unsigned int Style::size () const
{
	return size_;
};


///
/// @details The size is expressed in points (pt)
/// 
/// @param size Font size in points (pt)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Style::size (unsigned int size)
{
	size_ = size;
};


/// 
/// @return The color of the font in RGB representation
/// 
/// @see RgbColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
RgbColor Style::color () const
{
	return color_;
};


/// 
/// @param color Font color in RGB colorspace
/// 
/// @see RgbColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Style::color (RgbColor color)
{
	color_ = color;
};


/// 
/// @details The font color is created internally as a RgbColor object with the values passed
/// 
/// @param red		Color value of red channel
/// @param green	Color value of green channel
/// @param blue		Color value of blue channel
/// 
/// @see RgbColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Style::color (double red, double green, double blue)
{
	color_ = RgbColor(red, green, blue);
};


///
/// @return The weight of the font
/// 
/// @see FontWeight
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
FontWeight Style::weight () const
{
	return weight_;
};


///
/// @details The weight must be passed using a literal value of FontWeight enumeration.
/// 
/// @param weight Font weight according to values in FontWeight
/// 
/// @see FontWeight
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
void Style::weight (FontWeight weight)
{
	weight_ = weight;
};

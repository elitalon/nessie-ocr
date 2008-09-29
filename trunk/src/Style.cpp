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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
unsigned int Style::getSize () const
{
	return size_;
};


///
/// @details The size is expressed in points (pt)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
void Style::setSize (unsigned int size)
{
	size_ = size;
};


/// 
/// @see RgbColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
///
RgbColor Style::getColor () const
{
	return color_;
};


/// 
/// @see RgbColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
///
void Style::setColor (RgbColor color)
{
	color_ = color;
};


/// 
/// @details The font color is created internally as a RgbColor object with the values passed
/// 
/// @see RgbColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
///
void Style::setColor (double red, double green, double blue)
{
	color_ = RgbColor(red, green, blue);
};


///
/// @see FontWeight
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
FontWeight Style::getWeight () const
{
	return weight_;
};


///
/// @details The weight must be passed using a literal value of FontWeight enumeration.
/// 
/// @see FontWeight
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
void Style::setWeight (FontWeight weight)
{
	weight_ = weight;
};

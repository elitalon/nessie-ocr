#include "Style.h"


///
/// Initializes a Style object with size set to 0, color set to black and weight set to normal
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
Style::Style () : size(0), color(FontColor()), weight(NORMAL)
{
	
};


///
/// Initializes a Style object with size, color and weight set to the values passed
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
Style::Style (unsigned int size_, FontColor color_, FontWeight weight_) : size(size_), color(color_), weight(weight_)
{
	
};


///
/// Destroys a Style object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
Style::~Style ()
{
	
};


///
/// A bold font may be only bold, bold and italic or bold and underlined
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
bool Style::isBold ()
{
	switch (this->weight)
	{
		case BOLD | BOLD_ITALIC | BOLD_UNDERLINED:
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
/// A italic font may be only italic, italic and bold or italic and underlined
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
bool Style::isItalic ()
{
	switch (this->weight)
	{
		case ITALIC | BOLD_ITALIC | ITALIC_UNDERLINED:
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
/// An underlined font may be only underlined, underlined and italic or underlined and bold
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
bool Style::isUnderlined ()
{
	switch (this->weight)
	{
		case UNDERLINED | ITALIC_UNDERLINED | BOLD_UNDERLINED:
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
/// A normal font is neither bold, nor italic, nor underlined
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
bool Style::isNormal ()
{
	switch (this->weight)
	{
		case NORMAL:
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
/// The size is expressed in points (pt)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
unsigned int Style::getSize ()
{
	return this->size;
};


///
/// The size is expressed in points (pt)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
void Style::setSize (unsigned int size_)
{
	this->size = size_;
};


/// 
/// @see FontColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
FontColor Style::getColor ()
{
	return this->color;
};


/// 
/// @see FontColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
void Style::setColor (FontColor color_)
{
	this->color = color_;
};


/// 
/// The font color is created internally as a FontColor object with the values passed
/// 
/// @see FontColor
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
void Style::setColor (unsigned int red_, unsigned int green_, unsigned int blue_)
{
	this->color = FontColor(red_, green_, blue_);
};


///
/// @see FontWeight
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
FontWeight Style::getWeight ()
{
	return this->weight;
};


///
/// The weight must be passed using a literal value of FontWeight enumeration.
/// 
/// @see FontWeight
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
void Style::setWeight (FontWeight weight_)
{
	this->weight = weight_;
};

#include "Style.h"


///
/// @details Initializes a Style object with size set to 0, color set to black and weight set to normal
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
Style::Style () : size(0), color(FontColor()), weight(NORMAL)
{
	
};


///
/// @details Initializes a Style object with size, color and weight set to the values passed
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
Style::Style (unsigned int size_, FontColor color_, FontWeight weight_) : size(size_), color(color_), weight(weight_)
{
	
};


///
/// @details Destroys a Style object
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
Style::~Style ()
{

};


///
/// @details A bold font may be only bold, bold and italic or bold and underlined
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
bool Style::isBold () const
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
/// @details An italic font may be only italic, italic and bold or italic and underlined
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
bool Style::isItalic () const
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
/// @details An underlined font may be only underlined, underlined and italic or underlined and bold
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
bool Style::isUnderlined () const
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
/// @details A normal font is neither bold, nor italic, nor underlined
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
bool Style::isNormal () const
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
/// @details The size is expressed in points (pt)
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
unsigned int Style::getSize () const
{
	return this->size;
};


///
/// @details The size is expressed in points (pt)
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
FontColor Style::getColor () const
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
/// @details The font color is created internally as a FontColor object with the values passed
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
FontWeight Style::getWeight () const
{
	return this->weight;
};


///
/// @details The weight must be passed using a literal value of FontWeight enumeration.
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

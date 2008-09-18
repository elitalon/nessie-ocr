#if !defined(_FONTWEIGHT_H)
#define _FONTWEIGHT_H

///
/// \file
///

/// Font weight of a character
/// 
/// This enumeration represents the different types of font weight that
/// a character may have. All the possible combinations are present, though
/// in a normal text the most common are the three first font weights: bold,
/// italic and normal.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
enum FontWeight
{
	NORMAL,				///< Normal font, without decorations
	BOLD,				///< Only bold
	ITALIC,				///< Only italic
	UNDERLINED,			///< Normal but underlined
	BOLD_ITALIC,		///< Both bold and italic
	BOLD_UNDERLINED,	///< Both bold and underlined
	ITALIC_UNDERLINED	///< Both italic and underlined
};

#endif  //_FONTWEIGHT_H

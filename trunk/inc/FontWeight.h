#if !defined(_FONTWEIGHT_H)
#define _FONTWEIGHT_H

///
/// @file
/// @brief Declaration of enumeration FontWeight
///

/// 
/// Font weight of a character
/// 
/// This enumeration represents the different types of font weight that
/// a character may have. All the possible combinations are present, though
/// in a normal text the most common are the three first font weights: bold,
/// italic and normal.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
///
enum FontWeight
{
	FONT_NORMAL,			///< Normal font, without decorations
	FONT_BOLD,				///< Only bold
	FONT_ITALIC,			///< Only italic
	FONT_UNDERLINED,		///< Normal but underlined
	FONT_BOLD_ITALIC,		///< Both bold and italic
	FONT_BOLD_UNDERLINED,	///< Both bold and underlined
	FONT_ITALIC_UNDERLINED	///< Both italic and underlined
};

#endif  //_FONTWEIGHT_H

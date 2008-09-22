#if !defined(_FONTPROPORTIONALITY_H)
#define _FONTPROPORTIONALITY_H

///
/// @file
///


///
/// Font proportionality of a character
/// 
/// This enumeration represents the different types of font proportionality that
/// a text may have. The monospaced type is usual in fixed width fonts,
/// while proportional type is usual in Roman fonts.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
enum FontProportionality
{
	MONOSPACED,		///< In fixed width fonts
	PROPORTIONAL	///< In Roman fonts
};

#endif  //_FONTPROPORTIONALITY_H

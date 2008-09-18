#if !defined(_FONTCOLOR_H)
#define _FONTCOLOR_H

///
/// Font color of a character
/// 
/// This struct represents the color of font that a character has. The
/// color value is stored using the RGB color space with 256 values per
/// component, and the three components separated.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
///
struct FontColor
{
	public:
		
		///
		/// Red component
		///
		unsigned int red;
		
		///
		/// Green component
		///
		unsigned int green;
		
		///
		/// Blue component
		///
		unsigned int blue;
		
		
		///
		/// Constructor
		///
		FontColor ();
		
		///
		/// Constructor
		///
		FontColor (unsigned int red_, unsigned int green_, unsigned int blue_);
		
		///
		/// Destructor
		///
		~FontColor ();
};

#endif  //_FONTCOLOR_H

#if !defined(_STYLE_H)
#define _STYLE_H

#include "FontWeight.h"
#include "FontColor.h"


///
/// Font style of a character
/// 
/// This class stores information about the font style of a character
/// in the recognized text. Due to the different design styles in newspapers,
/// a text may contain different kinds of style. That's why we must keep the
/// style of every single character.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18 
///
class Style
{
	public:
	
		///
		/// Constructor
		///
		Style ();
	
		///
		/// Constructor
		///
		Style (unsigned int size_, FontColor color_, FontWeight weight_);
	
		///
		/// Destructor
		///
		~Style ();
	
		///
		/// Returns true if the font weight is bold
		///
		bool isBold () const;
	
		///
		/// Returns true if the font weight is italic
		///
		bool isItalic () const;
	
		///
		/// Returns true if the font weight is underlined
		///
		bool isUnderlined () const;
	
		///
		/// Returns true if the font weight is normal
		///
		bool isNormal () const;

		///
		/// Returns the font size
		///
		unsigned int getSize () const;
	
		///
		/// Sets the font size
		///
		void setSize (unsigned int size_);

		///
		/// Returns the font color
		///
		FontColor getColor () const;
	
		///
		/// Sets the font color
		///
		void setColor (FontColor color_);
	
		///
		/// Sets the font color
		///
		void setColor (unsigned int red_, unsigned int green_, unsigned int blue_);
	
		///
		/// Returns the font weight
		///
		FontWeight getWeight () const;

		///
		/// Sets the font weight
		///
		void setWeight (FontWeight weight_);


	private:
	
		///
		/// Size of the character in points
		///
		unsigned int size;
	
		///
		/// Color of the character
		///
		FontColor color;
	
		///
		/// Font weight of the character
		///
		FontWeight weight;		
};

#endif  //_STYLE_H

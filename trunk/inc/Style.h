#if !defined(_STYLE_H)
#define _STYLE_H

///
/// @file
/// @brief Declaration of class Style
///

#include "FontWeight.h"
#include "RgbColor.h"


///
/// Font style of a character
/// 
/// This class stores information about the font style of a character
/// in the recognized text. Due to the different design styles in newspapers,
/// a text may contain different kinds of style. That's why we must keep the
/// style of every single character.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-25
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
		Style (unsigned int size, RgbColor color, FontWeight weight);
	
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
		void setSize (unsigned int size);

		///
		/// Returns the font color
		///
		RgbColor getColor () const;
	
		///
		/// Sets the font color
		///
		void setColor (RgbColor color);
	
		///
		/// Sets the font color
		///
		void setColor (double red, double green, double blue);
	
		///
		/// Returns the font weight
		///
		FontWeight getWeight () const;

		///
		/// Sets the font weight
		///
		void setWeight (FontWeight weight);


	private:
	
		///
		/// Size of the character in points
		///
		unsigned int size_;
	
		///
		/// Color of the character
		///
		RgbColor color_;
	
		///
		/// Font weight of the character
		///
		FontWeight weight_;		
};

#endif  //_STYLE_H

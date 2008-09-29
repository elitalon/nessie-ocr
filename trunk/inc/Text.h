#if !defined(_TEXT_H)
#define _TEXT_H

///
/// @file
/// @brief Declaration of class Text
///

#include "WordRate.h"
#include "FontProportionality.h"
#include "Style.h"

#include <string>
#include <vector>
#include <algorithm>
using namespace std;


///
/// Text extracted from the clip by the recognizer
/// 
/// This class stores the text que has been extracted from the press-clip
/// during the recognition process. Besides the text itself, it also keeps
/// some extra information: appearance rate of every word, font style of every
/// character and the font proportionality, among others.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
class Text
{
	public:
		
		///
		/// Constructor
		///
		Text ();
		
		///
		/// Constructor
		///
		Text (string content);
		
		///
		/// Constructor
		///
		Text (string content, vector<Style> styles);
		
		///
		/// Destructor
		///
		~Text ();
		
		///
		/// Adds a character to the text
		///
		void addCharacter (char character);
		
		///
		/// Adds a character to the text
		///
		void addCharacter (char character, Style style);
		
		///
		/// Adds a character to the text
		///
		void addCharacter (char character, unsigned int position);
		
		///
		/// Adds a character to the text
		///
		void addCharacter (char character, Style style, unsigned int position);

		///
		/// Removes a character from the text
		///
		void removeCharacter (unsigned int position);
		
		///
		/// Returns the style of a single character
		///
		Style getCharacterStyle (unsigned int position) const;

		///
		/// Sets the style of a single character
		///
		void setCharacterStyle (unsigned int position, Style style);
				
		///
		/// Returns the text itself
		///
		string content () const;

		///
		/// Sets the text
		///
		void content (string content);
		
		///
		/// Returns the list of text styles
		///
		vector<Style> styles () const;

		///
		/// Sets the list of text styles
		///
		void styles (vector<Style> styles);
		
		///
		/// Returns the text length
		///
		unsigned int length () const;
		
		///
		/// Returns the appearance rates of every single word in text
		///
		vector<WordRate> wordRates () const;
		
		///
		/// Returns the font proportionality in text
		///
		FontProportionality proportionality () const;

		///
		/// Sets the font proportionality in text
		///
		void proportionality (FontProportionality proportionality);


	private:
		
		///
		/// The text itself
		///		
		string content_;
		
		///
		/// A list of every character style
		///
		vector<Style> styles_;
		
		///
		/// The text proportionality
		///
		FontProportionality proportionality_;
		
		///
		/// A list of appearance rates of every single word in text
		///
		vector<WordRate> wordRates_;
		
		///
		/// Builds the vector with every word appearance rate
		///
		void computeWordRates ();
		
		///
		/// Increases by one the number of appearances of a word
		///
		void updateWordRate (string word_);
		
		///
		/// Extracts the words surrounded by default delimiters from text
		///
		void tokenize(vector<string>& tokens_, const string& delimiters_ = " ,.\n\t:;!¡¿?&/()=") const;
};

#endif  //_TEXT_H

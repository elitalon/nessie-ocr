///
/// @file
/// @brief Declaration of class Text
///

#if !defined(_TEXT_H)
#define _TEXT_H


#include "WordRate.h"

#include <string>
#include <vector>


///
/// Text extracted by the recognizer
/// 
/// This class stores the text that has been extracted from the press clip during the recognition process.
/// It also keeps the appearance rate of every word in text.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-04
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
		Text (const std::string &content);
				
		///
		/// Destructor
		///
		~Text ();
		
		///
		/// Adds a character to text
		///
		void addCharacter (const char &character);
		
		///
		/// Adds a character to text
		///
		void addCharacter (const char &character, const unsigned int &position);

		///
		/// Removes a character from text
		///
		void removeCharacter (const unsigned int &position);
				
		///
		/// Returns the text's content
		///
		std::string content () const;

		///
		/// Sets the text's content
		///
		void content (const std::string &content);
		
		///
		/// Returns the text's length
		///
		unsigned int length () const;
		
		///
		/// Returns the appearance rates of every single word in text
		///
		std::vector<WordRate> wordRates () const;

	private:
		///
		/// The text's content
		///		
		std::string content_;
				
		///
		/// A list of appearance rates of every single word in text
		///
		std::vector<WordRate> wordRates_;
		
		///
		/// Builds the vector of appearance rates of every word
		///
		void computeWordRates ();
		
		///
		/// Increases by one the number of appearances of a word
		///
		void updateWordRate (const std::string &word_);
		
		///
		/// Extracts every word surrounded by a set of delimiters
		///
		void tokenize(std::vector<std::string> &tokens_, const std::string &delimiters_ = " ,.\n\t:;!¡¿?&/()=\"'") const;
};

#endif  //_TEXT_H

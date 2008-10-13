///
/// @file
/// @brief Declaration of the class Text
///

#if !defined(_TEXT_H)
#define _TEXT_H


#include "WordRate.hpp"

#include <string>
#include <vector>


///
/// Text extracted by the recognizer
/// 
/// This class stores the text that has been extracted from the press clip during the recognition process.
/// It also keeps the appearance rate of every word in text.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
///
class Text
{
	public:
		
		///
		/// Constructor
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-04
		/// 
		Text ();
		
		
		///
		/// Constructor
		///
		/// @param content Initial text
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-04
		/// 
		Text (const std::string &content);

		
		///
		/// Adds a character to text
		///
		/// @param character	Character to add
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-03
		/// 
		void addCharacter (const char &character);
		
		
		///
		/// Adds a character to text
		///
		/// @param character	Character to add
		/// @param position		Position where adding the character to
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-06
		/// 
		void addCharacter (const char &character, const unsigned int &position);


		///
		/// Removes a character from text
		///
		/// @param position		Position where removing the character from
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-03
		/// 
		void removeCharacter (const unsigned int &position);

				
		///
		/// Returns the text's content
		///
		/// @return The content of the text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const std::string &content () const;


		///
		/// Sets the text's content
		/// 
		/// @param content The content of the text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		void content (const std::string &content);
		
		
		///
		/// Returns the text's length
		///
		/// @return The length of the text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		unsigned int length () const;
		
		
		///
		/// Returns the appearance rates of every single word in text.
		/// 
		/// @return A vector with every different word and their appearance rate
		/// 
		/// @see WordRate
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		const std::vector<WordRate> &wordRates () const;


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
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-04
		/// 
		void computeWordRates ();
		
		
		///
		/// Increases by one the number of appearances of a word
		///
		/// @param word	Word whose appearance rate must be update
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-04
		///
		void updateWordRate (const std::string &word);
		
		
		///
		/// Extracts every word surrounded by a set of delimiters
		///
		/// @param[out]	tokens		Vector where storing the words found to
		/// @param		delimiters	Characters that may delimiter a valid word
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-04
		///
		void tokenize(std::vector<std::string> &tokens, const std::string &delimiters = " ,.\n\t:;!¡¿?&/()=\"'") const;
};



//
// Implementation of inline functions
// 


///
/// @details
///
inline const std::string &Text::content () const
{
	return content_;
};


///
/// @details
/// 
inline void Text::content (const std::string &content)
{
	content_.assign(content);

	// Rebuild the appearance rate of every word in the new text
	computeWordRates();
};


///
/// @details
///
inline unsigned int Text::length () const
{
	return content_.length();
};


///
/// @details
/// 
inline const std::vector<WordRate> &Text::wordRates () const
{
	return wordRates_;
};

#endif  //_TEXT_H

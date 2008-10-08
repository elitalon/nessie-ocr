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
/// @date 2008-10-08
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
		/// @return The content of the text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline std::string content () const
		{
			return content_;
		};


		///
		/// Sets the text's content
		/// 
		/// @param content The content of the text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline void content (const std::string &content)
		{
			content_.assign(content);

			// Rebuild the appearance rate of every word in the new text
			computeWordRates();
		};

		
		///
		/// Returns the text's length
		///
		/// @return The length of the text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline unsigned int length () const
		{
			return content_.length();
		};

		
		///
		/// Returns the appearance rates of every single word in text.
		/// 
		/// @return A vector with every different word and their appearance rate
		/// 
		/// @see WordRate
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline std::vector<WordRate> wordRates () const
		{
			return wordRates_;
		};

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

#if !defined(_TEXT_H)
#define _TEXT_H

///
/// @file
/// @brief Declaration of class Text
///

#include "WordRate.h"

#include <string>
#include <vector>
using namespace std;


///
/// Text extracted from the clip by the recognizer
/// 
/// This class stores the text que has been extracted from the press-clip during the recognition process.
/// It also keeps the appearance rate of every word.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
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
		Text (const string &content);
				
		///
		/// Destructor
		///
		~Text ();
		
		///
		/// Adds a character to the text
		///
		void addCharacter (const char &character);
		
		///
		/// Adds a character to the text
		///
		void addCharacter (const char &character, const unsigned int &position);

		///
		/// Removes a character from the text
		///
		void removeCharacter (const unsigned int &position);
				
		///
		/// Returns the text itself
		///
		string content () const;

		///
		/// Sets the text
		///
		void content (const string &content);
		
		///
		/// Returns the text length
		///
		unsigned int length () const;
		
		///
		/// Returns the appearance rates of every single word in text
		///
		vector<WordRate> wordRates () const;


	private:
		
		///
		/// The text itself
		///		
		string content_;
				
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
		void updateWordRate (const string &word_);
		
		///
		/// Extracts the words surrounded by default delimiters from text
		///
		void tokenize(vector<string>& tokens_, const string& delimiters_ = " ,.\n\t:;!¡¿?&/()=") const;
};

#endif  //_TEXT_H

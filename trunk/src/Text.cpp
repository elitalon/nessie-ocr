///
/// @file
/// @brief Implementation of class Text
///

#include "Text.h"

#include <algorithm>
using namespace std;


///
/// @details Initializes a Text object with no content
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
/// 
Text::Text () : content_(string("")), wordRates_(vector<WordRate>(0))
{
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details Initializes a Text object with the content passed
/// 
/// @param content Initial text
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
/// 
Text::Text (const string &content) : content_(content), wordRates_(vector<WordRate>(0))
{
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details Destroys a Text object
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
Text::~Text ()
{

};


///
/// @details The character is inserted within the text at position passed. If the position passed is over the text total length,
/// the character is appended to the end of the text.
/// 
/// @param character	Character to add
/// @param position		Position where adding the character to
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
/// 
void Text::addCharacter (const char &character, const unsigned int &position)
{
	if(position > content_.length())
		content_.append(1, character);
	else
	{
		if (position < 0)
			content_.insert(0, 1, character);
		else
			content_.insert(position, 1, character);
	}
	
	// Rebuild the appearance rate of every word in text
	computeWordRates();
};


///
/// @details The character passed is appended to the end of the text
///
/// @param character	Character to add
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
/// 
void Text::addCharacter (const char &character)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, length());
}


///
/// @details The character is removed from text at position passed, unless it is over the text total length.
/// In such case, the last character is removed
///
/// @param position		Position where removing the character from
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
/// 
void Text::removeCharacter (const unsigned int &position)
{
	if (position > content_.length())
		content_.erase(content_.end());
	else
	{
		if ( position < 0 )
			content_.erase(content_.begin());
		else
			content_.erase(position, 1);
	}
	
	// Rebuild the appearance rate of every word in text
	computeWordRates();
};



///
/// @return The content of the text
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
string Text::content () const
{
	return content_;
};


///
/// @param content The content of the text
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
/// 
void Text::content (const string &content)
{
	content_.assign(content);

	// Rebuild the appearance rate of every word in the new text
	computeWordRates();
};


///
/// @return The length of the text
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
unsigned int Text::length () const
{
	return content_.length();
};


///
/// @return A vector with every different word and their appearance rate
/// 
/// @see WordRate
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
vector<WordRate> Text::wordRates () const
{
	return wordRates_;
};


///
/// @param word	Word whose appearance rate must be update
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
///
void Text::updateWordRate (const string &word)
{
	// Searches the word in the vector
	vector<WordRate>::iterator wordRates;
	for (wordRates = wordRates_.begin(); wordRates not_eq wordRates_.end(); ++wordRates)
	{
		// Updates its appearance rate
		if ( (*wordRates).first == word )
		{
			(*wordRates).second++;
			return;
		}
	}
	
	// The word was not stored, so here we adds its first appearance
	wordRates_.push_back(WordRate(word, 1));
};


///
/// @details This method must be called every time the content changes,
/// since there is no public method for a class user to make it by itself.
/// By the way, the number of words in text is also computed.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-02
/// 
void Text::computeWordRates ()
{	
	vector<string> words;	// Vector to hold our words after removing spaces
	
	// Extract the words in text
	tokenize(words);
	
	// Update appearance rate of every word extracted
	vector<string>::iterator wordsIterator;
	for (wordsIterator = words.begin(); wordsIterator not_eq words.end(); ++wordsIterator)
		updateWordRate(*wordsIterator);
		
	// This sorting will improve future lookups
	sort (wordRates_.begin(), wordRates_.end());
};


///
/// @param[out] tokens	Vector where storing the words found to
/// @param delimiters	Characters that may delimiter a valid word
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-02
///
void Text::tokenize(vector<string>& tokens, const string& delimiters) const
{
	// Skip delimiters at the beginning of text
	string::size_type lastPos = content_.find_first_not_of(delimiters, 0);
	
	// Find the first "non-delimiter"
	string::size_type pos     = content_.find_first_of(delimiters, lastPos);
	
	// Traverse the content until reaching its end
	while ( (string::npos not_eq pos) or (string::npos not_eq lastPos) )
    {
		// A word has been found, add it to the vector
		tokens.push_back(content_.substr(lastPos, pos - lastPos));
		
		// Skip delimiters again
		lastPos = content_.find_first_not_of(delimiters, pos);
		
		// Find the next "non-delimiter"
        pos = content_.find_first_of(delimiters, lastPos);
    }
};

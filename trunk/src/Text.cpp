///
/// @file
/// @brief Implementation of the class Text
///

#include "Text.hpp"

#include <algorithm>
#include <string>
#include <vector>


///
/// @details Initializes a Text object with no content
///
Text::Text ()
	:	content_(std::string("")),
		wordRates_(std::vector<WordRate>(0))
{
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details Initializes a Text object with the content passed
/// 
Text::Text (const std::string &content) : content_(content), wordRates_(std::vector<WordRate>(0))
{
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details The character is inserted within the text at position passed. If the position passed is over the text total length,
/// the character is appended to the end of the text. If th position passed is less than 0, the character is inserted at the beginning
/// of the text.
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
void Text::addCharacter (const char &character)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, content_.length());
}


///
/// @details The character is removed from text at position passed. If the position passed is over the text total length,
/// the last character is removed. If the position passed is less than 0 the first character is removed.
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
/// @details
///
void Text::updateWordRate (const std::string &word)
{
	// Searches the word in the vector
	std::vector<WordRate>::iterator wordRates;
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
///
void Text::computeWordRates ()
{
	std::vector<std::string> words;	// Vector to hold our words after removing spaces
	
	// Extract the words in text
	tokenize(words);
	
	// Update appearance rate of every word extracted
	std::vector<std::string>::iterator wordsIterator;
	for (wordsIterator = words.begin(); wordsIterator not_eq words.end(); ++wordsIterator)
		updateWordRate(*wordsIterator);
		
	// This sorting will improve future lookups
	std::sort (wordRates_.begin(), wordRates_.end());
};


///
/// @details
///
void Text::tokenize(std::vector<std::string>& tokens, const std::string& delimiters) const
{
	// Skip delimiters at the beginning of text
	std::string::size_type lastPos = content_.find_first_not_of(delimiters, 0);
	
	// Find the first "non-delimiter"
	std::string::size_type pos     = content_.find_first_of(delimiters, lastPos);
	
	// Traverse the content until reaching its end
	while ( (std::string::npos not_eq pos) or (std::string::npos not_eq lastPos) )
    {
		// A word has been found, add it to the vector
		tokens.push_back(content_.substr(lastPos, pos - lastPos));
		
		// Skip delimiters again
		lastPos = content_.find_first_not_of(delimiters, pos);
		
		// Find the next "non-delimiter"
        pos = content_.find_first_of(delimiters, lastPos);
    }
};

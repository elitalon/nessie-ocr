///
/// @file
/// @brief Implementation of the class Text
///

#include "Text.hpp"

#include <utility>
#include "boost/tokenizer.hpp"



///
/// @details Initializes a Text object with no content
///
Text::Text ()
	:	content_(std::string("")),
		wordRates_(std::map<std::string, unsigned int>())
{

};



///
/// @details Initializes a Text object initialized with the content passed
///
Text::Text (const std::string content)
	:	content_(content),
		wordRates_(std::map<std::string, unsigned int>())
{
	// Buld the appearance rate of every word in text
	computeWordRates();
};



///
/// @details
///
unsigned int Text::words () const
{
	unsigned int nWords = 0;
	
	for ( std::map<std::string, unsigned int>::const_iterator it = wordRates_.begin(); it not_eq wordRates_.end(); ++it )
		nWords += (*it).second;
	
	return nWords;
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
	// Convenience typedefs
	typedef std::map<std::string, unsigned int>::iterator wordRatesIterator;
	typedef std::pair<wordRatesIterator, wordRatesIterator> wordRatesIteratorPair;
	
	// Searches the word in the associative map
	wordRatesIteratorPair p = wordRates_.equal_range(word);
	
	if (p.first not_eq p.second)	// Found, just update the rate
		wordRates_[word]++;
	else
		wordRates_.insert(p.first, std::pair<std::string, unsigned int>(word, 1));
};



///
/// @details This method must be called whenever the content changes, since there is no public method for a user to make it.
/// Each time it is called, the previous word rates are cleared and computed again.
///
void Text::computeWordRates (const std::string &delimiters)
{
	// Remove previous rates
	wordRates_.clear();
	
	// Set the delimiters and tokenize the content
	boost::char_separator<char> separators(delimiters.data());
	boost::tokenizer< boost::char_separator<char> > tokenizer(content_, separators);
	
	// Extract each word and update its appearance rate
	for(boost::tokenizer< boost::char_separator<char> >::iterator token=tokenizer.begin(); token not_eq tokenizer.end(); ++token)
		updateWordRate( *token );
};

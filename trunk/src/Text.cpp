///
/// @file
/// @brief Definition of Text class
///

#include "Text.hpp"

#include <utility>
#include <boost/tokenizer.hpp>




Text::Text ()
	:	content_(std::string("")),
		wordRates_(std::map<std::string, unsigned int>())
{

};



Text::Text (const std::string content)
	:	content_(content),
		wordRates_(std::map<std::string, unsigned int>())
{
	// Buld the appearance rate of every word in text
	computeWordRates();
};



unsigned int Text::words () const
{
	unsigned int nWords = 0;
	
	for ( std::map<std::string, unsigned int>::const_iterator it = wordRates_.begin(); it not_eq wordRates_.end(); ++it )
		nWords += (*it).second;
	
	return nWords;
};



///
/// @details If the position passed is above the text total length the character is appended to the end of the text. If the position passed
/// is less than 0, the character is inserted at the beginning of the text.
/// 
void Text::addCharacter (const std::string& character, const unsigned int& position)
{
	if(position > content_.length())
		content_.append(1, character.at(0));
	else
		content_.insert(position, 1, character.at(0));
	
	// Rebuild the appearance rate of every word in text
	computeWordRates();
};



void Text::addCharacter (const std::string& character)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, content_.length());
}



///
/// @details If the position passed is above the text total length the last character is removed.
///
void Text::removeCharacter (const unsigned int& position)
{
	if (position > content_.length())
		content_.erase(content_.end());
	else
		content_.erase(position, 1);
	
	// Rebuild the appearance rate of every word in text
	computeWordRates();
};



void Text::updateWordRate (const std::string& word)
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



void Text::computeWordRates (const std::string& delimiters)
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

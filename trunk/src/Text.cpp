#include "Text.h"

///
/// @file
/// @brief Implementation of class Text
///


///
/// @details Initializes a Text object with empty content and no styles
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
Text::Text () : content_(string("")), styles_(vector<Style>(0)), proportionality_(FONT_PROPORTIONAL), wordRates_(vector<WordRate>(0))
{
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details Initializes a Text object with the content passed in content_ and no styles
/// 
/// @param content Initial text
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
Text::Text (string content) : content_(content), proportionality_(FONT_PROPORTIONAL), wordRates_(vector<WordRate>(0))
{
	// Initialize the vector of styles according to the number of characters in the content
	styles_ = vector<Style>(content.length());
	
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details Initializes a Text object with the content passed in content_ and styles passed in styles_
/// 
/// @param content	Initial text
/// @param styles	Style of every character in text
///
/// @see Style
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
Text::Text (string content, vector<Style> styles) : content_(content), styles_(styles), proportionality_(FONT_PROPORTIONAL), wordRates_(vector<WordRate>(0))
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
/// @details The character is appended to the text at position passed in position_,
/// and with style passed in style_. If no position is passed, the character is appended
/// to the end. Similarly, if no style is passed a default style is assigned to the character.
/// If the position passed is over the text total length, the character is appended to the
/// end of the text.
/// 
/// @param character	Character to add
/// @param style		Style of the character
/// @param position		Position where adding the character to
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
void Text::addCharacter (char character, Style style, unsigned int position)
{
	// The desired position exceeds the content length, so we append to the of the text
	if(position > length())
	{
		content_ += character;
		styles_.push_back(style);
	}
	else
	{
		// Check for a valid position, though a compiler should use a big value when a negative
		// number is assigned to an unsigned int
		if (position < 0)
		{
			position = 0;
		}
				
		// Declare two iterators for pointing to the desired position
		string::iterator contentIterator		= content_.begin();
		vector<Style>::iterator stylesIterator	= styles_.begin();
		
		// Advance the iterators until the desired position
		while (position > 1)
		{
			++contentIterator;
			++stylesIterator;

			--position;
		}
		
		// Insert the character and its style
		content_.insert(contentIterator, character);
		styles_.insert(stylesIterator, style);
	}
	
	// Rebuild the appearance rate of every word in text
	computeWordRates();
};


///
/// @details The character is appended to the text at position passed,
/// with a default style. If the position passed is over the text total length,
/// the character is appended to the end of the text.
///
/// @param character	Character to add
/// @param position		Position where adding the character to
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
void Text::addCharacter (char character, unsigned int position)
{
	// Check for a valid position
	if (position < 0)
	{
		position = 0;
	}
	
	// Call the generic 'addCharacter' function
	addCharacter(character, Style(), position);
}


///
/// @details The character is appended to the end of the text with the style passed.
///
/// @param character	Character to add
/// @param style		Style of the character 
///
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
void Text::addCharacter (char character, Style style)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, style, length());
}


///
/// @details The character passed is appended to the end of the text with a default style.
///
/// @param character	Character to add
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
void Text::addCharacter (char character)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, Style(), length());
}


///
/// @details The character is removed from the position in text passed in position_, unless it is
/// over the text total length. In such case, the last character is removed
///
/// @param position		Position where removing the character from
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
void Text::removeCharacter (unsigned int position)
{
	// Check for a valid position
	if (position > length())
	{
		position = length();
	}
	
	// Declare two iterators for pointing to the desired character and its style
	string::iterator contentIterator		= content_.begin();
	vector<Style>::iterator stylesIterator	= styles_.begin();
	
	// Advance the iterators until the desired position
	while (position > 1)
	{
		++contentIterator;
		++stylesIterator;
		
		--position;
	}
	
	// Remove the character and its style
	content_.erase(contentIterator);
	styles_.erase(stylesIterator);
	
	// Rebuild the appearance rate of every word in text
	computeWordRates();
};



///
/// @details The style of a character at position passed is return unless the position
/// will be over the text length. In this case an empty style is returned.
/// 
/// @param position Position where getting the character style from
/// 
/// @return The style of the character
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
/// 
Style Text::getCharacterStyle (unsigned int position) const
{
	if (position >= length())
		return Style();
	else
		return styles_[position];
};


///
/// @details The character at position position_ in text is set with the style passed.
/// If the position passed in position_ is over the text total length no changes are made.
/// 
/// @param position	Position of the character whose style is going to be modify
/// @param style	New style for the character
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
/// 
void Text::setCharacterStyle (unsigned int position, Style style)
{
	if (position < length())
		styles_[position] = style;
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
/// @date 2008-09-29
/// 
void Text::content (string content)
{
	content_ = content;

	// Rebuild the appearance rate of every word in the new text
	computeWordRates();
};



///
/// @return styles A vector with the styles of every character in text
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
vector<Style> Text::styles () const
{
	return styles_;
};


///
/// @param styles A vector with the styles of every character in text
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
void Text::styles (vector<Style> styles)
{
	styles_ = styles;
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
/// @details The proportionality may be monospaced or proportional
/// 
/// @return Proportionality of the text according to values in FontProportionality
/// 
/// @see FontProportionality
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
FontProportionality Text::proportionality () const
{
	return proportionality_;
};


///
/// @param proportionality	Proportionality of text
/// 
/// @see FontProportionality
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
/// 
void Text::proportionality (FontProportionality proportionality)
{
	proportionality_ = proportionality;
};


///
/// @param word	Word whose appearance rate must be update
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
///
void Text::updateWordRate (string word)
{
	// Searches the word in the vector
	vector<WordRate>::iterator wordRates;
	for (wordRates = wordRates_.begin(); wordRates != wordRates_.end(); ++wordRates)
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
/// @date 2008-09-26
/// 
void Text::computeWordRates ()
{	
	vector<string> words;	// Vector to hold our words after removing spaces
	
	// Extract the words in text
	tokenize(words);
	
	// Update appearance rate of every word extracted
	vector<string>::iterator wordsIterator;
	for (wordsIterator = words.begin(); wordsIterator != words.end(); ++wordsIterator)
		updateWordRate(*wordsIterator);
		
	// This sorting will improve future lookups
	sort (wordRates_.begin(), wordRates_.end());
};


///
/// @param[out] tokens	Vector where storing the words found to
/// @param delimiters	Characters that may delimiter a valid word
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
///
void Text::tokenize(vector<string>& tokens, const string& delimiters) const
{
	// Skip delimiters at the beginning of text
	string::size_type lastPos = content_.find_first_not_of(delimiters, 0);
	
	// Find the first "non-delimiter"
	string::size_type pos     = content_.find_first_of(delimiters, lastPos);
	
	// Traverse the content until reaching its end
	while (string::npos != pos || string::npos != lastPos)
    {
		// A word has been found, add it to the vector
		tokens.push_back(content_.substr(lastPos, pos - lastPos));
		
		// Skip delimiters again
		lastPos = content_.find_first_not_of(delimiters, pos);
		
		// Find the next "non-delimiter"
        pos = content_.find_first_of(delimiters, lastPos);
    }
};

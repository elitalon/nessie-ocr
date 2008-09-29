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
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
void Text::addCharacter (char character, Style style, unsigned int position)
{
	// The desired position exceeds the content length, so we append to the of the text
	if(position > getLength())
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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
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
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
void Text::addCharacter (char character, Style style)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, style, getLength());
}


///
/// @details The character passed is appended to the end of the text with a default style.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
/// 
void Text::addCharacter (char character)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, Style(), getLength());
}


///
/// @details The character is removed from the position in text passed in position_, unless it is
/// over the text total length. In such case, the last character is removed
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
void Text::removeCharacter (unsigned int position)
{
	// Check for a valid position
	if (position > getLength())
	{
		position = getLength();
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
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
/// 
Style Text::getCharacterStyle (unsigned int position) const
{
	if (position >= getLength())
		return Style();
	else
		return styles_[position];
};


///
/// @details The character at position position_ in text is set with the style passed.
/// If the position passed in position_ is over the text total length no changes are made.
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
/// 
void Text::setCharacterStyle (unsigned int position, Style style)
{
	if (position < getLength())
		styles_[position] = style;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
string Text::getContent () const
{
	return content_;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
void Text::setContent (string content)
{
	content_ = content;

	// Rebuild the appearance rate of every word in the new text
	computeWordRates();
};



///
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
vector<Style> Text::getStyles () const
{
	return styles_;
};


///
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
void Text::setStyles (vector<Style> styles)
{
	styles_ = styles;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
unsigned int Text::getLength () const
{
	return content_.length();
};


///
/// @see WordRate
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-23
/// 
vector<WordRate> Text::getWordRates () const
{
	return wordRates_;
};


///
/// @details The proportionality may be monospaced or proportional
/// 
/// @see FontProportionality
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
FontProportionality Text::getProportionality () const
{
	return proportionality_;
};


///
/// @see FontProportionality
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
void Text::setProportionality (FontProportionality proportionality)
{
	proportionality_ = proportionality;
};


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

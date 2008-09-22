#include "Text.h"


///
/// @details Initializes a Text object with empty content and no styles
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
Text::Text () : content(string("")), styles(vector<Style>(0)), proportionality(PROPORTIONAL), wordRates(vector<WordRate>(0))
{
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details Initializes a Text object with the content passed in content_ and no styles
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
Text::Text (string content_) : content(content_), proportionality(PROPORTIONAL), wordRates(vector<WordRate>(0))
{
	// Initialize the vector of styles according to the number of characters in the content
	styles = vector<Style>(content_.length());
	
	// Build the appearance rate of every word in text
	computeWordRates();
};


///
/// @details Initializes a Text object with the content passed in content_ and styles passed in styles_
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
Text::Text (string content_, vector<Style> styles_) : content(content_), styles(styles_), proportionality(PROPORTIONAL), wordRates(vector<WordRate>(0))
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
/// @date 2008-09-22
/// 
void Text::addCharacter (char character, Style style_, unsigned int position_)
{
	// The desired position exceeds the content length, so we append to the of the text
	if(position_ > getLength())
	{
		this->content += character;
		this->styles.push_back(style_);
	}
	else
	{
		// Check for a valid position, though a compiler should use a big value when a negative
		// number is assigned to an unsigned int
		if (position_ < 0)
		{
			position_ = 0;
		}
				
		// Declare two iterators for pointing to the desired position
		string::iterator contentIterator		= this->content.begin();
		vector<Style>::iterator stylesIterator	= this->styles.begin();
		
		// Advance the iterators until the desired position
		while (position_ > 1)
		{
			++contentIterator;
			++stylesIterator;

			--position_;
		}
		
		// Insert the character and its style
		this->content.insert(contentIterator, character);
		this->styles.insert(stylesIterator, style_);
	}
	
	// Rebuild the appearance rate of every word in text
	computeWordRates();
};


///
/// @details The character is appended to the text at position passed in position_,
/// with a default style. If the position passed is over the text total length,
/// the character is appended to the end of the text.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
/// 
void Text::addCharacter (char character, unsigned int position_)
{
	// Check for a valid position
	if (position_ < 0)
	{
		position_ = 0;
	}
	
	// Call the generic 'addCharacter' function
	addCharacter(character, Style(), position_);
}


///
/// @details The character is appended to the end of the text with the style passed in style_.
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
/// 
void Text::addCharacter (char character, Style style_)
{
	// Call the generic 'addCharacter' function
	addCharacter(character, style_, getLength());
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
/// over the text total length.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
/// 
void Text::removeCharacter (unsigned int position_)
{
	// Check for a valid position
	if (position_ > getLength())
	{
		return;
	}
	
	// Declare two iterators for pointing to the desired character and its style
	string::iterator contentIterator		= this->content.begin();
	vector<Style>::iterator stylesIterator	= this->styles.begin();
	
	// Advance the iterators until the desired position
	while (position_ > 1)
	{
		++contentIterator;
		++stylesIterator;
		
		--position_;
	}
	
	// Remove the character and its style
	this->content.erase(contentIterator);
	this->styles.erase(stylesIterator);
	
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
/// @date 2008-09-18
/// 
Style Text::getCharacterStyle (unsigned int position_) const
{
	if (position_ >= getLength())
	{
		return Style();
	}
	else
	{
		return this->styles[position_];
	}
};


///
/// @details The character at position position_ in text is set with the style passed.
/// If the position passed in position_ is over the text total length no changes are made.
/// 
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
void Text::setCharacterStyle (unsigned int position_, Style style_)
{
	if (position_ < getLength())
	{
		this->styles[position_] = style_;
	}
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
string Text::getContent () const
{
	return this->content;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
void Text::setContent (string content_)
{
	this->content = content_;

	// Rebuild the appearance rate of every word in the new text
	computeWordRates();
};



///
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
vector<Style> Text::getStyles () const
{
	return this->styles;
};


///
/// @see Style
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
void Text::setStyles (vector<Style> styles_)
{
	this->styles = styles_;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
unsigned int Text::getLength () const
{
	return this->content.length();
};


///
/// @see WordRate
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
vector<WordRate> Text::getWordRates () const
{
	return this->wordRates;
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
	return this->proportionality;
};


///
/// @see FontProportionality
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
void Text::setProportionality (FontProportionality proportionality_)
{
	this->proportionality = proportionality_;
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
///
void Text::updateWordRate (string word_)
{
	// Searches the word in the vector
	vector<WordRate>::iterator wordRates;
	for (wordRates = this->wordRates.begin(); wordRates != this->wordRates.end(); ++wordRates)
	{
		// Updates its appearance rate
		if ( (*wordRates).first == word_ )
		{
			(*wordRates).second++;
			return;
		}
	}
	
	// The word was not stored, so here we adds its first appearance
	this->wordRates.push_back(WordRate(word_, 1));
};


///
/// @details This method must be called every time the content changes,
/// since there is no public method for a class user to make it by itself.
/// By the way, the number of words in text is also computed.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
/// 
void Text::computeWordRates ()
{	
	vector<string> words;	// Vector to hold our words after removing spaces
	
	// Extract the words in text
	tokenize(words);
	
	// Update appearance rate of every word extracted
	vector<string>::iterator wordsIterator;
	for (wordsIterator = words.begin(); wordsIterator != words.end(); ++wordsIterator)
	{
		updateWordRate(*wordsIterator);
	}
		
	// This sorting will improve future lookups
	sort (this->wordRates.begin(), this->wordRates.end());
};


///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-22
///
void Text::tokenize(vector<string>& tokens_, const string& delimiters_) const
{
	// Skip delimiters at the beginning of text
	string::size_type lastPos = this->content.find_first_not_of(delimiters_, 0);
	
	// Find the first "non-delimiter"
	string::size_type pos     = this->content.find_first_of(delimiters_, lastPos);
	
	// Traverse the content until reaching its end
	while (string::npos != pos || string::npos != lastPos)
    {
		// A word has been found, add it to the vector
		tokens_.push_back(this->content.substr(lastPos, pos - lastPos));
		
		// Skip delimiters again
		lastPos = this->content.find_first_not_of(delimiters_, pos);
		
		// Find the next "non-delimiter"
        pos = this->content.find_first_of(delimiters_, lastPos);
    }
};
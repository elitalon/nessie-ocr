/// @file
/// @brief Definition of Text class

#include "Text.hpp"
#include "NessieException.hpp"


Text::Text ()
	:	content_(std::string(""))
{};


Text::Text (const std::string& content)
	:	content_(content)
{};


void Text::addCharacter (const std::string& character)
{
	addCharacter(character, content_.size());
}


///
/// @todo Design a better mechanism to throw an exception whenever the string passed contains more than one character.
/// The solution is not simple, as any character with accent causes std::string::size() method to return 2 instead of 1.
///
void Text::addCharacter (const std::string& character, const unsigned int& position)
{
	if ( character.size() > 2 )
		throw NessieException("Text::addCharacter() : The string passed cannot contain more than one character.");
	
	if(position > content_.size())
		throw NessieException("Text::addCharacter() : The given position is greater than the size of the text.");
	else
		content_.insert(position, character);
};


void Text::removeCharacter (const unsigned int& position)
{
	if (position > content_.size())
		throw NessieException("Text::addCharacter() : The given position is greater than the size of the text.");
	else
		content_.erase(position, 1);	
};

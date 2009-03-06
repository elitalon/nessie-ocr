/// @file
/// @brief Definition of Text class

#include "Text.hpp"
#include "NessieException.hpp"


Text::Text ()
:	characters_(0)
{};


Text::Text (const std::vector<std::string>& characters)
:	characters_(characters)
{};


Text Text::operator+ (const Text& text) const
{
	std::vector<std::string> characters(0);

	characters.insert(characters.end(), this->characters_.begin(), this->characters_.end());
	characters.insert(characters.end(), text.characters_.begin(), text.characters_.end());

	return Text(characters);
};


std::string Text::content () const
{
	std::string text("");

	for ( std::vector<std::string>::const_iterator i = characters_.begin(); i != characters_.end(); ++i )
		text.append(*i);

	return text;
};


void Text::addCharacter (const std::string& character)
{
	addCharacter(character, characters_.size());
}


void Text::addCharacter (const std::string& character, const unsigned int& position)
{
	if ( character.size() > 2 )
		throw NessieException("Text::addCharacter() : The string passed cannot contain more than one character.");

	if( !(position > characters_.size()) )
		characters_.insert(characters_.begin()+position, character);
};


void Text::removeCharacter (const unsigned int& position)
{
	if ( !(position > characters_.size()) )
		characters_.erase(characters_.begin()+position);	
};


void Text::clear ()
{
	characters_.clear();
};


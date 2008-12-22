/// @file
/// @brief Definition of Text class

#include "Text.hpp"


Text::Text ()
	:	content_(std::wstring(L""))
{};


Text::Text (const std::wstring& content)
	:	content_(content)
{};


unsigned int Text::nWords () const
{
	unsigned int nWords = 0;
	
	return nWords;
};


void Text::addCharacter (const std::wstring& character)
{
	addCharacter(character, content_.length());
}


void Text::addCharacter (const unsigned char& character)
{
	addCharacter(character, content_.length());
}


void Text::addCharacter (const unsigned int& characterAsciiCode)
{
	addCharacter(characterAsciiCode, content_.length());
}


void Text::addCharacter (const std::wstring& character, const unsigned int& position)
{
	if(position > content_.length())
		content_.append(1, character.at(0));
	else
		content_.insert(position, 1, character.at(0));
};


void Text::addCharacter (const unsigned char& character, const unsigned int& position)
{
	std::wstring content(1, character);
	
	if(position > content_.length())
		content_.append(1, content.at(0));
	else
		content_.insert(position, 1, content.at(0));
};


void Text::addCharacter (const unsigned int& characterAsciiCode, const unsigned int& position)
{
	unsigned char character = characterAsciiCode;
	
	addCharacter(character, position);
};


void Text::removeCharacter (const unsigned int& position)
{
	if (position > content_.length())
		content_.erase(content_.end());
	else
		content_.erase(position, 1);	
};

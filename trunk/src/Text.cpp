/// @file
/// @brief Definition of Text class

#include "Text.hpp"
#include "NessieException.hpp"


Text::Text ()
:	content_(""),
	size_(0)
{};


void Text::addCharacter (const std::string& character)
{
	if ( character.size() > 2 || (character.size() == 2 && character.at(0) > 0) )
		throw NessieException("Text::addCharacter() : The string passed cannot contain more than one character.");
	
	content_.append(character);
	size_++;
}


void Text::addCharacter (const std::string& character, const unsigned int& position)
{
	if ( character.size() > 2 || (character.size() == 2 && character.at(0) >= 0) )
		throw NessieException("Text::addCharacter() : The string passed cannot contain more than one character.");

	if( !(position > size_) )
	{
		if ( position == 0 )
			content_.insert(0, character);
		else
		{
			unsigned int i = 0;
			for ( unsigned int j = 0; j < position; ++j )
			{
				if ( static_cast<int>(content_.at(i)) < 0 )	// Wide character
					i += 2;
				else
					++i;
			}

			std::string tmp;
			tmp.append(content_.begin(), content_.begin() + i);
			tmp.append(character);
			tmp.append(content_.begin() + i, content_.end());

			content_ = tmp;
		}
		size_++;
	}
};


void Text::removeCharacter (const unsigned int& position)
{
	if ( !(position > size_) )
	{
		unsigned int i = 0;
		for ( unsigned int j = 0; j < position; ++j )
		{
			if ( static_cast<int>(content_.at(i)) < 0 )	// Wide character
				i += 2;
			else
				++i;
		}
		
		std::string tmp;
		tmp.append(content_.begin(), content_.begin() + i);

		if ( *(content_.begin() + i + 1) < 0 )	// Wide character
			tmp.append(content_.begin() + i + 2, content_.end());
		else
			tmp.append(content_.begin() + i + 1, content_.end());

		content_ = tmp;
		size_--;
	}
};


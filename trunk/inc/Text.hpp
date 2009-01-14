/// @file
/// @brief Declaration of Text class

#if !defined(_TEXT_H)
#define _TEXT_H

#include <string>


///
/// Text extracted during the recognition process.
/// 
/// @details This class stores the text that has been extracted from a press clip during the recognition process.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-30
///
class Text
{
public:

	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	/// 
	Text ();

	///
	/// Returns the text content.
	///
	/// @return A STL string object with the content of the text.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	///
	const std::string& content () const;

	///
	/// Returns the size of the text in number of characters.
	///
	/// @return An integer representing the number of characters in the text.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	///
	unsigned int size () const;	
	
	///
	/// Adds a character at the end of the text.
	///
	/// @param character	A STL string object with a single character to add.
	/// 
	/// @post The character is appended at the end of the text.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	///
	void addCharacter (const std::string& character);
	
	///
	/// Adds a character to the text at given position.
	///
	/// @param character	A STL string object with a single character to add.
	/// @param position		An integer indicating the position where the character will be inserted.
	/// 
	/// @post The character is inserted at given position.
	/// 
	/// @exception If <em>position</em> is greater than the value returned by Text::size().
	/// @exception If <em>character</em> contains more than one character.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	/// 
	void addCharacter (const std::string& character, const unsigned int& position);

	///
	/// Removes a single character from the text.
	///
	/// @param position		An integer indicating the position where the character must be removed.
	/// 
	/// @post The character at given position is removed.
	/// 
	/// @exception If <em>position</em> is greater than the value returned by Text::size().
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	/// 
	void removeCharacter (const unsigned int& position);
	
	///
	/// Allows to sum a pair of Text objects by appending its contents.
	/// 
	/// @param text The text to be appended to the current Text object.
	/// 
	/// @return A Text object as a result of appending both contents.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	///
	Text operator+ (const Text& text) const;
	
private:

	std::string content_;	///< The text content

	///
	/// Constructor.
	/// 
	/// @param text A STL string object with the initial content.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-30
	/// 
	Text (const std::string& text);
};



inline Text Text::operator+ (const Text& text) const
{
	return Text(this->content_ + text.content_);
};


inline const std::string& Text::content () const
{
	return content_;
};


inline unsigned int Text::size () const
{
	return content_.size();
};

#endif  //_TEXT_H

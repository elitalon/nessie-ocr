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
/// @date 2008-10-08
///
class Text
{
public:

	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-04
	/// 
	Text ();


	///
	/// Returns the text content.
	///
	/// @return A STL wstring object with the content of the text.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const std::wstring& content () const;


	///
	/// Returns the size of the text in number of characters.
	///
	/// @return An integer representing the number of characters in the text.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	unsigned int size () const;


	///
	/// Returns the size of the text in number of words.
	///
	/// @return An integer representing the number of words in the text.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	unsigned int nWords () const;


	///
	/// Adds a character at the end of the text.
	/// 
	/// @warning Though typed as string, only the first character of the string passed as parameter is taken.
	///
	/// @param character A STL wstring object with the character to add at the first position.
	/// 
	/// @post The first character in the string passed is appended at the end of the text.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-03
	/// 
	void addCharacter (const std::wstring& character);
	
	
	///
	/// Adds a character at the end of the text.
	///
	/// @param character A single character to add at the first position.
	/// 
	/// @post The character is appended at the end of the text.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-22
	///
	void addCharacter (const unsigned char& character);


	///
	/// Adds a character at the end of the text.
	///
	/// @param characterAsciiCode An integer with the ASCII code of character to add at the first position.
	/// 
	/// @post The character is appended at the end of the text.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-22
	///	
	void addCharacter (const unsigned int& characterAsciiCode);


	///
	/// Adds a character to the text at given position.
	/// 
	/// @warning Though typed as string, only the first character of the string passed as parameter is taken.
	///
	/// @param character	A STL wstring object with the character to add at its first position.
	/// @param position		An integer indicating the position where the character will be inserted.
	/// 
	/// @post The first character in the string passed is inserted at given position.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-03
	/// 
	void addCharacter (const std::wstring& character, const unsigned int& position);
	
	
	///
	/// Adds a character to the text at given position.
	///
	/// @param character	A single character to add.
	/// @param position		An integer indicating the position where the character will be inserted.
	/// 
	/// @post The character is inserted at given position.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-22
	/// 
	void addCharacter (const unsigned char& character, const unsigned int& position);
	
	
	///
	/// Adds a character to the text at given position.
	///
	/// @param characterAsciiCode	An integer with the ASCII code of character to add.
	/// @param position				An integer indicating the position where the character will be inserted.
	/// 
	/// @post The character is inserted at given position.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-22
	/// 
	void addCharacter (const unsigned int& characterAsciiCode, const unsigned int& position);


	///
	/// Removes a single character from the text.
	///
	/// @param position		An integer indicating the position where the character must be removed.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-03
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
	/// @date 2008-12-22
	///
	Text operator+ (const Text& text) const;
	
private:

	std::wstring content_;	///< The text content


	///
	/// Constructor.
	/// 
	/// @param text A STL wstring object with the initial content.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-22
	/// 
	Text (const std::wstring& text);
};



inline Text Text::operator+ (const Text& text) const
{
	return Text(this->content_ + text.content_);
};


inline const std::wstring& Text::content () const
{
	return content_;
};


inline unsigned int Text::size () const
{
	return content_.size();
};

#endif  //_TEXT_H

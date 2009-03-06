/// @file
/// @brief Declaration of Text class

#if !defined(_TEXT_H)
#define _TEXT_H

#include <string>
#include <vector>


/// @brief		Text extracted from a press clip during the recognition process.
///
///	@details	The text that comes in newspaper articles might have characters with accents and, in general, characters that do not belong
///	to the standard ASCII set. By default, the STL <em>string</em> class stores these special characters as if their size were two instead of one (e.g. a vocal plus
///	its accent). That's why this class handles an array of strings, rather than a simple <em>string</em> object.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-30
class Text
{
	public:

		///	@brief	Constructor.
		explicit Text ();

		/// @brief	Allow to sum a pair of Text objects by appending its contents.
		/// 
		/// @param	text	The text to be appended to the current Text object.
		/// 
		/// @return	A Text object as a result of appending both contents.
		Text operator+ (const Text& text) const;

		/// @brief	Get the text content.
		/// 
		/// @return	An array of STL string objects, with one text's character per element.
		const std::vector<std::string>& characters () const;

		///	@brief	Get the size of the text in characters.
		///
		/// @return	Number of characters in the text.
		unsigned int size () const;	

		///	@brief	Get the text content.
		///
		/// @return	A STL string object with the content of the text.
		std::string content () const;

		/// @brief		Add a character at the end of the text.
		/// 
		/// @todo		Design a better mechanism to throw an exception whenever the string passed contains more than one character. The solution is not simple,
		/// as any character with accent causes std::string::size() method to return 2 instead of 1.
		///
		/// @param		character	A STL string object with a single character to add.
		/// 
		/// @post		The character is appended at the end of the text.
		///
		/// @exception	NessieException
		void addCharacter (const std::string& character);

		/// @brief		Adds a character to the text at given position.
		/// 
		/// @todo 		Design a better mechanism to throw an exception whenever the string passed contains more than one character.
		/// The solution is not simple, as any character with accent causes std::string::size() method to return 2 instead of 1.
		///
		/// @param		character	A STL string object with a single character to add.
		/// @param		position	Position where the character will be inserted.
		/// 
		/// @post		The character is inserted at given position.
		/// 
		/// @exception	NessieException
		void addCharacter (const std::string& character, const unsigned int& position);

		/// @brief		Remove a single character from the text.
		///
		/// @param		position		Position where the character must be removed.
		/// 
		/// @post		The character at given position is removed.
		void removeCharacter (const unsigned int& position);

		/// @brief	Remove all the characters in the text, leaving it with a size of 0.
		///
		///	@post	The text becomes empty, no characters at all.
		void clear ();

	private:

		std::vector<std::string>	characters_;	///< The text content.

		///	@brief	Constructor.
		/// 
		/// @param	text	A STL string object with the initial content.
		Text (const std::vector<std::string>& text);
};


inline const std::vector<std::string>& Text::characters () const
{
	return characters_;
};

inline unsigned int Text::size () const
{
	return characters_.size();
};

#endif


/// @file
/// @brief Declaration of Text class

#if !defined(_TEXT_H)
#define _TEXT_H

#include <string>


/// @brief		Text extracted from a press clip during the recognition process.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-30
class Text
{
	public:

		///	@brief	Constructor.
		explicit Text ();

		///	@brief	Get the text content.
		///
		/// @return	A STL string object with the content of the text.
		const std::string& content () const;

		///	@brief	Get the size of the text in characters.
		///
		/// @return	Number of characters in the text.
		const unsigned int& size () const;	

		/// @brief		Add a character at the end of the text.
		/// 
		/// @param		character	A STL string object with a single character to add.
		/// 
		/// @post		The character is appended at the end of the text.
		///
		/// @exception	NessieException
		void addCharacter (const std::string& character);

		/// @brief		Adds a character to the text at given position.
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

		std::string		content_;	///< Characters of text.
		
		unsigned int	size_;		///< Size of text.
};


inline const std::string& Text::content () const
{
	return content_;
};

inline const unsigned int& Text::size () const
{
	return size_;
};

inline void Text::clear ()
{
	content_.clear();
	size_ = 0;
};

#endif


/// @file
/// @brief Declaration of Text class

#if !defined(_TEXT_H)
#define _TEXT_H

#include <string>


/// @brief		Text extracted from a press clip after character recognition.
///
///	@details	This class stores a postprocessed text that has been recognized by NessieOcr and some associated atributes.
///	This text does not match the original text in the newspapers, since all the punctuation sign and miscellaneous characters are removed.
///	Simply put, this text is only composed of words separated by a single white space. This is done since this class is intended to be used
///	by an article classifier in a higher level.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-30
class Text
{
	public:

		///	@brief	Constructor.
		explicit Text ();

		///	@brief	Constructor.
		///
		/// @param	data A STL string object with the content of the text.
		explicit Text (const std::string& data);

		///	@brief	Get the size of the text in number of characters.
		///
		/// @return	Number of characters.
		const unsigned int& size () const;
		
		/// @brief	Remove all the characters in the text.
		///
		///	@post	The text is cleared and size set to zero.
		void clear ();

		/// @brief	Get the character at given position.
		/// 
		/// @param	n	Position within the text.
		/// 
		/// @return	A string object that holds the character at given position.
		const std::string at(const unsigned int& n) const;

		/// @brief	Add a character at the end of the text.
		/// 
		/// @param	character	A STL string object with a single character to add.
		/// 
		/// @post	The character is appended and size is incremented by one.
		void append (const std::string& character);

		///	@brief	Set the text data.
		///
		/// @param	data A STL string object with the content of the text.
		void assign (const std::string& data);
		
		/// @brief	Add a character at given position.
		///
		/// @param	character	A STL string object that holds a single character.
		/// @param	n			Position where the character will be inserted.
		/// 
		/// @post	The character is inserted and size is incremented by one.
		void insert (const std::string& character, const unsigned int& n);

		/// @brief	Remove a single character at given position.
		///
		/// @param	n	Position where the character must be removed.
		/// 
		/// @post	The character is removed and size is decrementeb by one.
		void erase (const unsigned int& n);

		///	@brief	Get the text data.
		///
		/// @return	A STL string object with the content of the text.
		const std::string& data () const;

		/// @brief	Get the average height of characters in pixels.
		/// 
		/// @return	Average height of characters.
		const double& averageCharacterHeight () const;

		/// @brief	Set the average height of characters in pixels.
		/// 
		/// @param	height	Average height of characters.
		void averageCharacterHeight (const double& height);
		
		///	@brief	Get the size of the text in number of words.
		///
		///	@return	Number of words.
		unsigned int nWords () const;

		///	@brief	Get the average word size in number of characters.
		///
		///	@return	Average word size.
		double averageWordSize () const;

	private:

		std::string		data_;						///< Charactersof which the text is composed.
		
		unsigned int	size_;						///< Size of the text.

		double			averageCharacterHeight_;	///< Average character height.
};


inline const std::string& Text::data () const
{
	return data_;
}

inline const unsigned int& Text::size () const
{
	return size_;
}

inline const double& Text::averageCharacterHeight () const
{
	return averageCharacterHeight_;
}

inline void Text::averageCharacterHeight (const double& height)
{
	averageCharacterHeight_ = height;
}

inline void Text::clear ()
{
	data_.clear();
	size_ = 0;
}

#endif


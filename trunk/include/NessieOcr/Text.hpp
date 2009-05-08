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

		///	@brief	Get the size of the text in number of characters.
		///
		/// @return	Number of characters in the text.
		const unsigned int& size () const;
		
		/// @brief	Remove all the characters in the text, leaving it with a size of 0.
		///
		///	@post	The text becomes empty, no characters at all.
		void clear ();

		/// @brief	Get the character at given position.
		/// 
		/// @param	n	Position within the text.
		/// 
		/// @return	A STL string object with the character at given position.
		const std::string at(const unsigned int& n) const;

		/// @brief		Add a character at the end of the text.
		/// 
		/// @param		character	A STL string object with a single character to add.
		/// 
		/// @post		The character is appended at the end of the text.
		///
		/// @exception	NessieException
		void append (const std::string& character);

		///	@brief	Set the text data.
		///
		/// @param	data A STL string object with the content of the text.
		void assign (const std::string& data);
		
		/// @brief		Adds a character to the text at given position.
		///
		/// @param		character	A STL string object with a single character to add.
		/// @param		n			Position where the character will be inserted.
		/// 
		/// @post		The character is inserted at given position.
		/// 
		/// @exception	NessieException
		void insert (const std::string& character, const unsigned int& n);

		/// @brief		Remove a single character from the text.
		///
		/// @param		n	Position where the character must be removed.
		/// 
		/// @post		The character at given position is removed.
		void erase (const unsigned int& n);

		///	@brief	Get the text data.
		///
		/// @return	A STL string object with the content of the text.
		const std::string& data () const;

		/// @brief	Get the average height of characters in text.
		/// 
		/// @return	The average height of characters in pixels.
		const double& averageCharacterHeight () const;

		/// @brief	Set the average height of characters in text.
		/// 
		/// @param	height	Average height of characters in pixels.
		void averageCharacterHeight (const double& height);
		
		///	@brief	Get the size of the text in number of words.
		///
		///	@return	Number of words in the text.
		unsigned int nWords () const;

		///	@brief	Get the average word size.
		///
		///	@return	Average word size in number of characters
		double averageWordSize () const;

	private:

		std::string		data_;						///< Characters of text.
		
		unsigned int	size_;						///< Size of text.

		double			averageCharacterHeight_;	///< Average character height.
};


inline const std::string& Text::data () const
{
	return data_;
};

inline const unsigned int& Text::size () const
{
	return size_;
};

inline const double& Text::averageCharacterHeight () const
{
	return averageCharacterHeight_;
};

inline void Text::averageCharacterHeight (const double& height)
{
	averageCharacterHeight_ = height;
};

inline void Text::clear ()
{
	data_.clear();
	size_ = 0;
};

#endif


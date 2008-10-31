///
/// @file
/// @brief Declaration of Text class
///

#if !defined(_TEXT_H)
#define _TEXT_H



#include <string>
#include <map>


///
/// Text extracted by the recognizer.
/// 
/// @details This class stores the text that has been extracted from the press clip during the recognition process.
/// It also keeps the number of appearances of every word in text.
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
	/// Constructor.
	/// 
	/// @param content The initial content of the text.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-04
	///
	Text (const std::string content);


	///
	/// Appends a text to the current one
	/// 
	/// @param text The text to append
	/// 
	/// @return Text object as a result of appending the content of both texts
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	Text operator+ (const Text& text) const;


	///
	/// Returns the text's content
	///
	/// @return Content of the text
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const std::string& content () const;


	///
	/// Returns the number of appearances of every single word in text.
	/// 
	/// @return An associative map with every different word and their number of appearances.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	const std::map<std::string, unsigned int>& wordRates () const;


	///
	/// Returns the size of the text
	///
	/// @return Size of the text in number of characters
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	unsigned int size () const;


	///
	/// Returns the number words in the text
	///
	/// @return Number of words in the text
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	unsigned int words () const;


	///
	/// Adds a character at the end of the text
	///
	/// @param character	Character to add
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-03
	/// 
	void addCharacter (const char& character);


	///
	/// Adds a character to text at the given position
	///
	/// @param character	Character to add
	/// @param position		Position where adding the character to
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-06
	/// 
	void addCharacter (const char& character, const unsigned int& position);


	///
	/// Removes a character from text
	///
	/// @param position		Position where the character will be removed
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-03
	/// 
	void removeCharacter (const unsigned int& position);


private:

	std::string								content_;	///< The text's content

	std::map<std::string, unsigned int>		wordRates_;	///< A list of appearance rates of every single word in text


	///
	/// Builds the map of number of appearances of every word in the text
	///
	/// @param	delimiters	Characters that delimit a word
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	/// 
	void computeWordRates (const std::string& delimiters = " ,:¡!.;()¿?\"'[]{}<>");


	///
	/// Increases by one the number of appearances of a word
	///
	/// @param word	Word whose appearance rate must be update
	/// 
	/// @post Each time this method is called, the previous word rates are cleared.
	/// 
	/// @warning This method must be called whenever the content changes.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	void updateWordRate (const std::string& word);
};




inline Text Text::operator+ (const Text& text) const
{
	Text temp(this->content() + text.content());

	return temp;
};


inline const std::string& Text::content () const
{
	return content_;
};


inline const std::map<std::string, unsigned int>& Text::wordRates () const
{
	return wordRates_;
};


inline unsigned int Text::size () const
{
	return content_.size();
};


#endif  //_TEXT_H

///
/// @file
/// @brief Declaration of the class Text
///

#if !defined(_TEXT_H)
#define _TEXT_H



#include <string>
#include <map>


///
/// @brief Text extracted by the recognizer.
/// 
/// @details This class stores the text that has been extracted from the press clip during the recognition process.
/// It also keeps the appearance rates of every word in text, i.e. the number of appearances of a single word in the text.
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
	/// @param content The initial content of the text
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-04
	///
	Text (const std::string content);
	
	
	///
	/// Allows the concatenation of two texts
	/// 
	/// @param text A text as the second operand
	/// 
	/// @return A new text as a result of appending the content of both Text objects
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	Text operator+ (const Text& text) const;
	
	
	///
	/// Returns the text's content
	///
	/// @return The content of the text
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const std::string &content () const;
	
	
	///
	/// Returns the appearance rates of every single word in text.
	/// 
	/// @return An associative map with every different word and their appearance rate
	/// 
	/// @see WordRate
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	const std::map<std::string, unsigned int> &wordRates () const;
	
	
	///
	/// Returns the size of the text
	///
	/// @return The size of the text in number of characters
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	unsigned int size () const;
	
	
	///
	/// Returns the number of words in the text
	///
	/// @return The number of words in the text
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	unsigned int words () const;

	
	///
	/// Adds a character to text
	///
	/// @param character	Character to add
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-03
	/// 
	void addCharacter (const char &character);
	
	
	///
	/// Adds a character to text
	///
	/// @param character	Character to add
	/// @param position		Position where adding the character to
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-06
	/// 
	void addCharacter (const char &character, const unsigned int &position);


	///
	/// Removes a character from text
	///
	/// @param position		Position where removing the character from
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-03
	/// 
	void removeCharacter (const unsigned int &position);


private:
	///
	/// The text's content
	///		
	std::string content_;
			
	///
	/// A list of appearance rates of every single word in text
	///
	std::map<std::string, unsigned int> wordRates_;
	
	
	///
	/// Builds the vector of appearance rates of each word in the text
	///
	/// @param		delimiters	Characters that may delimiter a valid word
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	/// 
	void computeWordRates (const std::string &delimiters = " ,:¡!.;()¿?\"'[]{}<>");
	
	
	///
	/// Increases by one the number of appearances of a word
	///
	/// @param word	Word whose appearance rate must be update
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-23
	///
	void updateWordRate (const std::string &word);
};



//
// Implementation of inline functions
// 



///
/// @details
///
inline Text Text::operator+ (const Text& text) const
{
	Text temp(this->content() + text.content());
	
	return temp;
};



///
/// @details
///
inline const std::string &Text::content () const
{
	return content_;
};



///
/// @details
/// 
inline const std::map<std::string, unsigned int> &Text::wordRates () const
{
	return wordRates_;
};



///
/// @details
///
inline unsigned int Text::size () const
{
	return content_.size();
};


#endif  //_TEXT_H

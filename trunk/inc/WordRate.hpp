///
/// @file
/// @brief Declaration of the custom type WordRate
///

#if !defined(_WORDRATE_H)
#define _WORDRATE_H

#include <utility>
#include <string>


///
/// @typedef WordRate
/// 
/// @brief Appearance rate of a word.
/// 
/// @details This pair keeps the number of appearances of a word in a text. The first member represents
/// the word and the second member represents its appearances.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-19
/// 
typedef std::pair<std::string, unsigned int> WordRate;

#endif  //_WORDRATE_H

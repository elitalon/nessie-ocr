///
/// @file
/// @brief Declaration of custom type WordRate
///

#if !defined(_WORDRATE_H)
#define _WORDRATE_H

#include <utility>		// For using 'pair' container
#include <string>


///
/// Appearance rate of a word.
/// 
/// This pair keeps the number of appearances of a word in a text
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-19
/// 
typedef  std::pair<std::string, unsigned int> WordRate;

#endif  //_WORDRATE_H

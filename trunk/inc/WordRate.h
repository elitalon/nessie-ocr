#if !defined(_WORDRATE_H)
#define _WORDRATE_H

#include <iostream>
using namespace std;


///
/// Appearance rate of a word
/// 
/// This structure keeps the number of appearances of a single word
/// in the recognized text from an clip.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
struct WordRate
{
	public:
		
		///
		/// The word itself
		///
		string word;
		
		///
		/// Number of appearances
		///
		unsigned int rate;
		
		
		///
		/// Constructor
		///
		WordRate ();
		
		///
		/// Destructor
		/// 
		~WordRate ();
};

#endif  //_WORDRATE_H

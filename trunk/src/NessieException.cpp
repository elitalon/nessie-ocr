#include "NessieException.h"

///
/// @file
/// @brief Implementation of class NessieException
///


///
/// @details Initializes an exception object with information passed
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
/// 
NessieException::NessieException (string message) : message_(message)
{
	
};
	
		
///
/// @details Destroys a NessieException object
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
NessieException::~NessieException ()
{
	
};


///
/// @details The message is formed using the file name, its line and the explanation
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
string NessieException::what () const
{
	return message_;
};

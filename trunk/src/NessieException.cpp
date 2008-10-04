///
/// @file
/// @brief Implementation of class NessieException
///

#include "NessieException.h"


///
/// @details Initializes an NessieException object with a message
/// 
/// @param what	A message that explains the exception raised
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
/// 
NessieException::NessieException (const std::string &what): what_(what)
{
	
};
	
		
///
/// @details Destroys a NessieException object
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
///
NessieException::~NessieException ()  throw()
{

};


///
/// @details This method overrides the one in class std::exception
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
///
const char* NessieException::what () const throw()
{
	return what_.data();
};

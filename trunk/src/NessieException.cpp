///
/// @file
/// @brief Definition of NessieException class
///

#include "NessieException.hpp"


///
/// @details Initializes a NessieException object with a message.
/// 
NessieException::NessieException (const std::string &what): what_(what)
{
	
};
	
		
///
/// @details Destroys a NessieException object.
///
NessieException::~NessieException () throw()
{

};


///
/// @details This method overrides the one in class std::exception.
/// 
const char* NessieException::what () const throw()
{
	return what_.data();
};

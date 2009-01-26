/// @file
/// @brief Definition of NessieException class

#include "NessieException.hpp"


NessieException::NessieException (const std::string& what)
	:	what_(what)
{};
	
		
NessieException::~NessieException () throw()
{};


const char* NessieException::what () const throw()
{
	return what_.data();
};


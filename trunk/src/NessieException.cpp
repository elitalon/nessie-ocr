/// @file
/// @brief Definition of NessieException class

#include "NessieException.hpp"


NessieException::NessieException (const std::string& what)
:	std::exception(),
	what_(what)
{};


NessieException::~NessieException () throw() {};


const char* NessieException::what () const throw()
{
	return what_.data();
};


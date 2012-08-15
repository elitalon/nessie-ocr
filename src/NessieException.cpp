/// @file
/// @brief Definition of NessieException class

#include "NessieException.hpp"


NessieException::NessieException (const std::string& what)
:	std::exception(),
	what_(what)
{}


NessieException::~NessieException () throw() {}


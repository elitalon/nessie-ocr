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


void NessieException::addInfo (const std::string& info) throw()
{
	this->addInfo(info.data());
};


void NessieException::addInfo (const char* info) throw()
{
	std::string additionalMessage(info);

	what_.append(additionalMessage);
};


/// @file
/// @brief Definition of Dataset class

#include "Dataset.hpp"

Dataset::Dataset ()
:	samples_(0),
	classes_(),
	size_(0),
	features_(0)
{}


Dataset::~Dataset () {}


unsigned int Dataset::code (const std::string& character) const
{
	if ( classes_.empty() )
		return 256;
	
	std::map<std::string, unsigned int>::const_iterator i = classes_.find(character);

	if ( i != classes_.end() )
		return i->second;
	else
		return 256;
}


std::string Dataset::character (const unsigned int& code) const
{
	if ( classes_.empty() )
		return "";

	for ( std::map<std::string, unsigned int>::const_iterator i = classes_.begin(); i != classes_.end(); ++i )
	{
		if ( i->second == code )
			return i->first;
	}

	return "";
}


/// @file
/// @brief Definition of DatasetEngine class

#include "DatasetEngine.hpp"


DatasetEngineType::DatasetEngineType (const unsigned int& type)
:	id_(type)
{}


bool DatasetEngineType::operator== (const DatasetEngineType& engine) const
{
	return this->id_ == engine.id_;
}


DatasetEngine::DatasetEngine (DatasetEngineType type, const std::string& filename)
:	type_(type),
	filename_(filename),
	database_(""),
	username_(""),
	password_("")
{}


DatasetEngine::DatasetEngine (DatasetEngineType type, const std::string& database, const std::string& username, const std::string& password)
:	type_(type),
	filename_(""),
	database_(database),
	username_(username),
	password_(password)
{}


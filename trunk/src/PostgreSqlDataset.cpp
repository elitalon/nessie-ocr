///	@file
///	@brief	Definition of PostgreSqlDataset class

#include "PostgreSqlDataset.hpp"
#include "NessieException.hpp"
#include <pqxx/pqxx>
#include <utility>
#include <sstream>


PostgreSqlDataset::PostgreSqlDataset (const std::string& database, const std::string& username, const std::string& password)
:	Dataset(),
	database_(database),
	username_(username),
	password_(password),
	sampleIds_(0),
	classIds_(),
	featureColumns_()
{
	try
	{
		pqxx::connection connection("dbname=" + database_ + " user=" + username_ + " password=" + password_);
		pqxx::work dbTransaction(connection, "constructorTransaction");
		
		// Get the name of feature columns
		pqxx::result registers = dbTransaction.exec("SELECT column_name\
													FROM information_schema.columns\
													WHERE table_name = 'samples' AND column_name LIKE 'm__'");

		if ( registers.empty() )
			throw NessieException ("The table 'samples' has not any feature column.");
		
		for ( pqxx::result::const_iterator i = registers.begin(); i != registers.end(); ++i )
		{
			std::string column;
			i->at(0).to(column);

			featureColumns_.append(column + ",");
			++features_;
		}
		featureColumns_.erase(featureColumns_.end() - 1);
		

		// Get the classes
		registers = dbTransaction.exec("SELECT * FROM classes");

		typedef std::pair<std::string, unsigned int> asciiCodeRegister;
		typedef std::pair<unsigned int, unsigned int> ClassIdRegister;
		
		for ( pqxx::result::const_iterator i = registers.begin(); i != registers.end(); ++i )
		{
			unsigned int idClass;
			if ( !i->at(0).to(idClass) )
				throw NessieException ("The table 'classes' has an invalid id_class column.");
			
			std::string label;
			if ( !i->at(1).to(label) )
				throw NessieException ("The table 'classes' has an invalid label column.");

			unsigned int asciiCode;
			if ( !i->at(2).to(asciiCode) )
				throw NessieException ("The table 'classes' has an invalid asciiCode column.");

			classes_.insert(asciiCodeRegister(label, asciiCode));
			classIds_.insert(ClassIdRegister(asciiCode, idClass));
		}


		// Get the samples
		registers = dbTransaction.exec("SELECT id_sample, " + featureColumns_ + ", asciiCode\
										FROM samples s, classes c\
										WHERE s.id_class = c.id_class");
		size_ = registers.size();
		samples_.reserve(size_);
		sampleIds_.reserve(size_);
		
		for ( pqxx::result::const_iterator i = registers.begin(); i != registers.end(); ++i )
		{
			unsigned int id_sample;
			if ( !i->at(0).to(id_sample) )
				throw NessieException ("The table 'samples' has an invalid id_sample column.");

			unsigned int asciiCode;
			if ( !i->at(i->size()-1).to(asciiCode) )
				throw NessieException ("The table 'samples' has an invalid asciiCode column.");

			FeatureVector fv(features_);
			for( unsigned int j = 0; j < features_; ++j )
			{
				if ( !i->at(j+1).to(fv.at(j)) )
					throw NessieException ("The table 'samples' has an invalid feature column.");
			}

			sampleIds_.push_back(id_sample);
			samples_.push_back(Sample(fv, asciiCode));
		}
	}
	catch (const std::exception& e)
	{
		samples_.clear();
		sampleIds_.clear();
		classes_.clear();
		classIds_.clear();
		size_ = 0;

		std::string message(e.what());
		throw NessieException ("PostgreSqlDataset::PostgreSqlDataset() : The dataset could not be built from the database. " + message);
	}
}


PostgreSqlDataset::~PostgreSqlDataset () {}


void PostgreSqlDataset::addSample (const Sample& sample)
{
	if ( sample.first.size() != features_ )
		throw NessieException ("PostgreSqlDataset::addSample() : The number of features in the sample is different from the one expected by the dataset.");

	// Build the query section regarding the feature values
	std::string featureValues;
	for( unsigned int i = 0; i < sample.first.size(); ++i )
	{
		std::stringstream value;
		value << sample.first.at(i);
		featureValues.append(value.str() + ", ");
	}
	
	// Get the class ID and its ASCII code
	std::stringstream idClass;
	idClass << classIds_[sample.second];
	
	try
	{
		pqxx::connection connection("dbname=" + database_ + " user=" + username_ + " password=" + password_);
		pqxx::work dbTransaction(connection, "addSampleTransaction");

		pqxx::result registers = dbTransaction.exec("INSERT INTO samples (id_sample, " + featureColumns_ + ", id_class) VALUES\
										(DEFAULT, " + featureValues + idClass.str() + ") RETURNING id_sample");
		
		unsigned int id_sample;
		if ( !registers.front().at(0).to(id_sample) )
			throw NessieException ("The new id_sample could not be retrieved from the database.");

		samples_.push_back(sample);
		sampleIds_.push_back(id_sample);
		size_ = samples_.size();
		
		dbTransaction.commit();
	}
	catch (const std::exception& e)
	{
		std::string message(e.what());
		throw NessieException ("PostgreSqlDataset::addSample() : The sample could not be inserted in the dataset. " + message);
	}
}


void PostgreSqlDataset::removeSample (const unsigned int& n)
{
	try
	{
		std::stringstream id_sample;
		id_sample << sampleIds_.at(n);
		
		pqxx::connection connection("dbname=" + database_ + " user=" + username_ + " password=" + password_);
		pqxx::work dbTransaction(connection, "removeSampleTransaction");
		
		dbTransaction.exec("DELETE FROM samples WHERE id_sample = " + id_sample.str());
		dbTransaction.commit();
	}
	catch (const std::exception& e)
	{
		std::string message(e.what());
		throw NessieException ("PostgreSqlDataset::removeSample() : The sample could not be removed from the dataset. " + message);
	}

	samples_.erase(samples_.begin() + n);
	sampleIds_.erase(sampleIds_.begin() + n);
	size_ = samples_.size();
}


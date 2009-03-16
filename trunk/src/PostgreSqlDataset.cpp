///	@file
///	@brief	Definition of PostgreSqlDataset class

#include "PostgreSqlDataset.hpp"
#include "NessieException.hpp"
#include <utility>
#include <sstream>
#include <exception>


PostgreSqlDataset::PostgreSqlDataset (const std::string& database, const std::string& username, const std::string& password)
:	Dataset(),
	database_(database),
	username_(username),
	password_(password),
	connection_("dbname="+database+" user="+username+" password="+password),
	sampleIds_(0),
	classIds_()
{
	try
	{
		pqxx::work dbTransaction(connection_, "constructorTransaction");
		
		// Get the number of features stored in the database
		pqxx::result registers = dbTransaction.exec("SELECT count(*)\
													FROM information_schema.columns\
													WHERE table_name = 'samples' AND column_name LIKE 'm__'");

		if ( !registers.front().at(0).to(features_) || features_ == 0 )
			throw NessieException ("The table 'samples' has not any features columns.");
		
		// Build the query section regarding the feature columns
		std::string featureFields;
		unsigned int j = 0;
		for( unsigned int i = 0; i < features_; ++i )
		{
			if ( i == 0 )
				featureFields.append("m00, ");
			else
			{
				std::stringstream order;
				order << j;

				featureFields.append("m" + order.str() +"0, ");
				featureFields.append("m0" + order.str() +", ");

				++i;
			}

			++j;
		}

		// Get the classes
		registers = dbTransaction.exec("SELECT * FROM classes");

		typedef std::pair<std::string, unsigned int> asciiCodeRegister;
		typedef std::pair<unsigned int, unsigned int> ClassIdRegister;
		for ( pqxx::result::const_iterator i = registers.begin(); i != registers.end(); ++i )
		{
			pqxx::result::tuple row(*i);

			unsigned int idClass;
			if ( !row.at(0).to(idClass) )
				throw NessieException ("The table 'classes' has an invalid id_class column.");
			
			std::string label;
			if ( !row.at(1).to(label) )
				throw NessieException ("The table 'classes' has an invalid label column.");

			unsigned int asciiCode;
			if ( !row.at(2).to(asciiCode) )
				throw NessieException ("The table 'classes' has an invalid asciiCode column.");

			classes_.insert(asciiCodeRegister(label, asciiCode));
			classIds_.insert(ClassIdRegister(asciiCode, idClass));
		}

		// Get the samples
		registers = dbTransaction.exec("SELECT id_sample, " + featureFields + "asciiCode\
										FROM samples s, classes c\
										WHERE s.id_class = c.id_class");
		size_ = registers.size();
		
		samples_.reserve(size_);
		sampleIds_.reserve(size_);
		for ( pqxx::result::const_iterator i = registers.begin(); i != registers.end(); ++i )
		{
			pqxx::result::tuple row(*i);

			unsigned int id_sample;
			if ( !row.at(0).to(id_sample) )
				throw NessieException ("The table 'samples' has an invalid id_sample column.");

			unsigned int asciiCode;
			if ( !row.at(row.size()-1).to(asciiCode) )
				throw NessieException ("The table 'samples' has an invalid asciiCode column.");

			FeatureVector fv(features_);
			for( unsigned int j = 0; j < features_; ++j )
			{
				if ( !row.at(j+1).to(fv.at(j)) )
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
};


PostgreSqlDataset::~PostgreSqlDataset () {};


void PostgreSqlDataset::addSample (const Sample& sample)
{
	if ( sample.first.size() != features_ )
		throw NessieException ("PostgreSqlDataset::addSample() : The number of features in the sample is different from the one expected by the dataset.");

	// Build the query section regarding the feature columns
	std::string featureFields;
	unsigned int j = 0;
	for( unsigned int i = 0; i < features_; ++i )
	{
		if ( i == 0 )
			featureFields.append("m00, ");
		else
		{
			std::stringstream order;
			order << j;

			featureFields.append("m" + order.str() +"0, ");
			featureFields.append("m0" + order.str() +", ");
			
			++i;
		}
		
		++j;
	}
	
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
		pqxx::work dbTransaction(connection_, "addSampleTransaction");

		pqxx::result registers = dbTransaction.exec("INSERT INTO samples (id_sample, " + featureFields + "id_class) VALUES\
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
};


void PostgreSqlDataset::removeSample (const unsigned int& n)
{
	try
	{
		std::stringstream id_sample;
		id_sample << sampleIds_.at(n);
		
		pqxx::work dbTransaction(connection_, "removeSampleTransaction");
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
};


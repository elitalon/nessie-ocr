///	@file
///	@brief	Definition of PostgreSqlDataset class

#include "PostgreSqlDataset.hpp"
#include "NessieException.hpp"
#include <sstream>
#include <exception>


PostgreSqlDataset::PostgreSqlDataset (const std::string& database, const std::string& username, const std::string& password)
:	Dataset(),
	database_(database),
	username_(username),
	password_(password),
	connection_("dbname="+database+" user="+username+" password="+password),
	sampleIds_(0)
{
	pqxx::work dbTransaction(connection_, "constructorTransaction");

	pqxx::result registers = dbTransaction.exec("SELECT count(*)\
												FROM information_schema.columns\
												WHERE table_name = 'samples' AND column_name LIKE 'm__'");
	registers.front().at(0).to(features_);
	if ( features_ == 0 )
		throw NessieException ("PostgreSqlDataset::postgreSqlDataset() : The table 'samples' has not any features columns.");

	std::string featureFields;
	for( unsigned int i = 0; i < features_; ++i )
	{
		if ( i == 0 )
			featureFields.append("m00, ");
		else
		{
			std::stringstream order;
			order << i;

			featureFields.append("m0" + order.str() +", ");
			featureFields.append("m" + order.str() +"0, ");
		}
	}

	registers = dbTransaction.exec("SELECT id_sample, " + featureFields + "asciiCode\
									FROM samples s, classes c\
									WHERE s.class = c.id_class");
	size_ = registers.size();
	samples_.reserve(size_);
	sampleIds_.reserve(size_);

	for ( pqxx::result::const_iterator i = registers.begin(); i != registers.end(); ++i )
	{
		pqxx::result::tuple row(*i);

		unsigned int id_sample;
		row.at(0).to(id_sample);

		unsigned int asciiCode;
		row.at(row.size()-1).to(asciiCode);

		FeatureVector fv(features_);
		for( unsigned int j = 1; j <= features_; ++i )
			row.at(j).to(fv.at(j-1));

		sampleIds_.push_back(id_sample);
		samples_.push_back(Sample(fv, asciiCode));
	}
};


PostgreSqlDataset::~PostgreSqlDataset () {};


void PostgreSqlDataset::addSample (const Sample& sample)
{
	if ( sample.first.size() != features_ )
		throw NessieException ("PostgreSqlDataset::addSample() : The number of features in the sample is different from the one expected by the dataset.");

	pqxx::work dbTransaction(connection_, "addSampleTransaction");

	// Get the id_class 
	std::stringstream asciiCode;
	asciiCode << sample.second;
	pqxx::result registers = dbTransaction.exec("SELECT id_class FROM classes WHERE asciiCode = " + asciiCode.str());

	unsigned int id_class;
	if ( !registers.front().at(0).to(id_class) )
		throw NessieException ("PostgreSqlDataset::addSample() : No class was found with ASCII code equal to " + asciiCode.str());

	// Build the query columns
	std::string featureFields;
	for( unsigned int i = 0; i < features_; ++i )
	{
		if ( i == 0 )
			featureFields.append("m00, ");
		else
		{
			std::stringstream order;
			order << i;

			featureFields.append("m0" + order.str() +", ");
			featureFields.append("m" + order.str() +"0, ");
		}
	}

	// Insert the new sample
	try
	{
		std::stringstream sampleClass;
		sampleClass << id_class;

		registers = dbTransaction.exec("INSERT INTO samples (id_sample, " + featureFields + "class) VALUES\
										(DEFAULT, " + featureFields + sampleClass.str() + ") RETURNING id_sample");
		dbTransaction.commit();

		unsigned int id_sample;
		if ( !registers.front().at(0).to(id_sample) )
			throw NessieException ("PostgreSqlDataset::addSample() : The new sample ID could not be retrieved from the database.");

		samples_.push_back(sample);
		sampleIds_.push_back(id_sample);
		size_ = samples_.size();
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

		samples_.erase(samples_.begin() + n);
		sampleIds_.erase(sampleIds_.begin() + n);
		size_ = samples_.size();
	}
	catch (const std::exception& e)
	{
		std::string message(e.what());
		throw NessieException ("PostgreSqlDataset::removeSample() : The sample could not be removed from the dataset. " + message);
	}
};


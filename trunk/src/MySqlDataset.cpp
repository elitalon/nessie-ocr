///	@file
///	@brief	Definition of MySqlDataset class

#include "MySqlDataset.hpp"
#include "NessieException.hpp"
#include <mysql++/mysql++.h>
#include <utility>
#include <sstream>
#include <exception>


MySqlDataset::MySqlDataset (const std::string& database, const std::string& username, const std::string& password)
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
		mysqlpp::Connection connection (database_.data(), 0, username_.data(), password_.data());
		mysqlpp::Transaction dbTransaction(connection);

		// Get the number of features stored in the database
		mysqlpp::Query query(&connection);
		mysqlpp::StoreQueryResult registers = query.store("SELECT column_name\
														FROM information_schema.columns\
														WHERE table_name = 'samples' AND column_name LIKE 'm__'");

		if ( !registers )
			throw NessieException ("The table 'samples' has not any feature column.");

		features_ = registers.num_rows();
		if ( features_ == 0 )
			throw NessieException ("The table 'samples' has not any feature column.");

		// Build the query section regarding the feature columns
		for ( size_t i = 0; i < registers.num_rows(); ++i )
		{
			mysqlpp::Row row(registers[i]);

			std::string column(row[0]);
			featureColumns_.append(column + ",");
		}
		featureColumns_.erase(featureColumns_.end() - 1);

		// Get the classes
		query.reset();
		registers = query.store("SELECT * FROM classes");

		if ( !registers )
			throw NessieException ("The table 'classes' could not be accessed.");

		typedef std::pair<std::string, unsigned int> asciiCodeRegister;
		typedef std::pair<unsigned int, unsigned int> ClassIdRegister;
		for ( size_t i = 0; i < registers.num_rows(); ++i )
		{
			mysqlpp::Row row(registers[i]);

			unsigned int idClass = row[0];
			std::string label(row[1]);
			unsigned int asciiCode = row[2];

			classes_.insert(asciiCodeRegister(label, asciiCode));
			classIds_.insert(ClassIdRegister(asciiCode, idClass));
		}

		// Get the samples
		mysqlpp::UseQueryResult useRegisters = query.use("SELECT id_sample, " + featureColumns_ + ", asciiCode\
								FROM samples s, classes c\
								WHERE s.id_class = c.id_class");

		size_ = 0;
		while( mysqlpp::Row row = useRegisters.fetch_row() )
		{
			unsigned int id_sample = row[0];

			unsigned int asciiCode = row[row.size()-1];

			FeatureVector fv(features_);
			for( unsigned int j = 0; j < features_; ++j )
				fv.at(j) = row[j+1];

			sampleIds_.push_back(id_sample);
			samples_.push_back(Sample(fv, asciiCode));
			++size_;
		}

		if ( connection.errnum() )
			throw NessieException ("The table 'samples' could not be accessed.");
	}
	catch (const std::exception& e)
	{
		samples_.clear();
		sampleIds_.clear();
		classes_.clear();
		classIds_.clear();
		size_ = 0;

		std::string message(e.what());
		throw NessieException ("MySqlDataset::MySqlDataset() : The dataset could not be built from the database. " + message);
	}
};


MySqlDataset::~MySqlDataset () {};


void MySqlDataset::addSample (const Sample& sample)
{
	if ( sample.first.size() != features_ )
		throw NessieException ("MySqlDataset::addSample() : The number of features in the sample is different from the one expected by the dataset.");

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
		mysqlpp::Connection connection (database_.data(), 0, username_.data(), password_.data());
		mysqlpp::Transaction dbTransaction(connection);

		mysqlpp::Query query(connection.query("INSERT INTO samples (id_sample, " + featureColumns_ + ", id_class) VALUES\
											(DEFAULT, " + featureValues + idClass.str() + ")"));
		mysqlpp::SimpleResult registers = query.execute();

		if ( !registers )
			throw NessieException("");

		samples_.push_back(sample);
		sampleIds_.push_back(registers.insert_id());
		size_ = samples_.size();

		dbTransaction.commit();
	}
	catch (const std::exception& e)
	{
		std::string message(e.what());
		throw NessieException ("MySqlDataset::addSample() : The sample could not be inserted in the dataset. " + message);
	}
};


void MySqlDataset::removeSample (const unsigned int& n)
{
	try
	{
		std::stringstream id_sample;
		id_sample << sampleIds_.at(n);

		mysqlpp::Connection connection (database_.data(), 0, username_.data(), password_.data());
		mysqlpp::Transaction dbTransaction(connection);

		mysqlpp::Query query(connection.query("DELETE FROM samples WHERE id_sample = " + id_sample.str()));
		if ( !query.exec() )
			throw NessieException("");

		dbTransaction.commit();
	}
	catch (const std::exception& e)
	{
		std::string message(e.what());
		throw NessieException ("MySqlDataset::removeSample() : The sample could not be removed from the dataset. " + message);
	}

	samples_.erase(samples_.begin() + n);
	sampleIds_.erase(sampleIds_.begin() + n);
	size_ = samples_.size();
};


Dataset* MySqlDataset::clone () const
{
	return new MySqlDataset(*this);
};


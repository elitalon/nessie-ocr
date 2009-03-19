///	@file
///	@brief	Declaration of PostgreSqlDataset class

#if !defined(_POSTGRE_SQL_DATASET_H)
#define _POSTGRE_SQL_DATASET_H

#include "Dataset.hpp"
#include <string>
#include <map>
#include <boost/noncopyable.hpp>


///	@brief		Dataset built by retrieving the data from a PostgreSQL database.
///
///	@see		Dataset
///
///	@author Eliezer Talón (elitalon@gmail.com)
///	@date 2009-02-13
class PostgreSqlDataset : public Dataset, private boost::noncopyable
{
	public:
	
		///	@brief		Constructor.
		///
		///	@param		database	Name of the database to connect.
		///	@param		username	Username to use in the database connection.
		///	@param		password	User password.
		///
		///	@post		A connection with the PostgreSQL database is stablished using the given parameters.
		///
		///	@exception	NessieException
		explicit PostgreSqlDataset (const std::string& database, const std::string& username, const std::string& password);

		///	@brief	Destructor.
		virtual ~PostgreSqlDataset ();

		///	@brief		Add a sample to the dataset.
		///
		///	@param		sample Sample to add.
		///
		///	@post		The sample is appended to the end of the dataset.
		///
		///	@exception	NessieException
		void addSample (const Sample& sample);

		///	@brief		Remove a sample from the dataset.
		///
		///	@param		n	Row in the dataset where remove the sample.
		///
		///	@exception	NessieException
		void removeSample (const unsigned int& n);

	private:
		
		std::string								database_;		///< Name of the database to connect.

		std::string								username_;		///< User name to use in the database connection.

		std::string								password_;		///< User password.

		std::vector<unsigned int>				sampleIds_;		///< Array of integers to store the id_sample field of samples table in the database.
		
		std::map<unsigned int, unsigned int>	classIds_;		///< Map that associates a class ID with its code.
};

#endif


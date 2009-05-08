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
///	@details	The database must contain two tables named <em>samples</em> and <em>classes</em>. The table <em>classes</em> stores the characters
///	that can be recognized. It must contain three columns: id_class, label and asciiCode. The <em>id_class</em> column must be an integer
///	and will act as the primary key. The <em>label</em> column must be a variable-length array of two characters. Finally, the <em>asciiCode</em> column
///	must be an integer. A posible definition for this table is acomplished with the following SQL statement:
///
///	@code
///		CREATE TABLE classes (
///			id_class	serial		PRIMARY KEY,
///			label		varchar(2)	NOT NULL,
///			asciiCode	integer		NOT NULL
///		);
///	@endcode
///
///	The table <em>samples</em> stores the features of every trained sample using the classifier. It must contain a column named <em>id_sample</em>,
///	an integer which will act as the primary key, a foreign key named <em>id_class</em> which points to the 'classes' table, and a variable number of
///	feature columns, which are numbers whose only constraint is that their name must have the letter <em>m</em> and two digits from 0 to 9. A posible
///	definition for this table is acomplished with the following SQL statement:
///
///	@code
///		CREATE TABLE samples (
///			id_sample	serial	PRIMARY KEY,
///			m00			numeric	NOT NULL DEFAULT 0.0,
///			m10			numeric	NOT NULL DEFAULT 0.0,
///			m01			numeric	NOT NULL DEFAULT 0.0,
///			m20			numeric	NOT NULL DEFAULT 0.0,
///			m02			numeric	NOT NULL DEFAULT 0.0,
///			id_class	integer	REFERENCES classes
///		);
///	@endcode
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
		
		std::string								database_;			///< Name of the database to connect.

		std::string								username_;			///< User name to use in the database connection.

		std::string								password_;			///< User password.

		std::vector<unsigned int>				sampleIds_;			///< Array of integers to store the id_sample field of samples table in the database.
		
		std::map<unsigned int, unsigned int>	classIds_;			///< Map that associates a class ID with its code.
		
		std::string								featureColumns_;	///< Name of the columns that holds the features to include on a query.
};

#endif


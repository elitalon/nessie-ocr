///	@file
///	@brief	Declaration of MySqlDataset class

#if !defined(_MYSQL_DATASET_H)
#define _MYSQL_DATASET_H

#include "Dataset.hpp"
#include <string>
#include <map>


///	@brief		Dataset built by retrieving the data from a MySQL database.
///
///	@details	The database must contain two tables named <em>samples</em> and <em>classes</em>. The table <em>classes</em> stores the characters
///	that can be recognized. It must contain three columns: id_class, label and asciiCode. The <em>id_class</em> column must be an integer
///	and will act as the primary key. The <em>label</em> column must be a variable-length array of two characters. Finally, the <em>asciiCode</em> column
///	must be an integer. A posible definition for this table is acomplished with the following SQL statement:
///
///	@code
///		CREATE TABLE IF NOT EXISTS classes (
///			id_class	smallint unsigned	AUTO_INCREMENT PRIMARY KEY,
///			label		varchar(2)			NOT NULL DEFAULT ' ',
///			asciiCode	smallint unsigned	NOT NULL DEFAULT 32
///		)
///		ENGINE=InnoDB;
///	@endcode
///
///	The table <em>samples</em> stores the features of every trained sample using the classifier. It must contain a column named <em>id_sample</em>,
///	an integer which will act as the primary key, a foreign key named <em>id_class</em> which points to the 'classes' table, and a variable number of
///	feature columns, which are numbers whose only constraint is that their name must have the letter <em>m</em> and two digits from 0 to 9. A posible
///	definition for this table is acomplished with the following SQL statement:
///
///	@code
///		CREATE TABLE samples (
///			id_sample	int unsigned		AUTO_INCREMENT PRIMARY KEY,
///			m00			double				NOT NULL DEFAULT 0.0,
///			m10			double				NOT NULL DEFAULT 0.0,
///			m01			double				NOT NULL DEFAULT 0.0,
///			m20			double				NOT NULL DEFAULT 0.0,
///			m02			double				NOT NULL DEFAULT 0.0,
///			id_class	smallint unsigned	REFERENCES classes(id_class) ON DELETE CASCADE ON UPDATE CASCADE,
///			INDEX		class(id_class)
///		)
///		ENGINE=InnoDB;
///	@endcode
///
///	@see		Dataset
///
///	@author Eliezer Talón (elitalon@gmail.com)
///	@date 2009-02-13
class MySqlDataset : public Dataset
{
	public:
	
		///	@brief		Constructor.
		///
		///	@param		database	Name of the database to connect.
		///	@param		username	Username to use in the database connection.
		///	@param		password	User password.
		///
		///	@post		A connection with the MySQL database is stablished using the given parameters.
		///
		///	@exception	NessieException
		explicit MySqlDataset (const std::string& database, const std::string& username, const std::string& password);

		///	@brief	Destructor.
		virtual ~MySqlDataset ();

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


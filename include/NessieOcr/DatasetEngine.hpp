/// @file
/// @brief Declaration of DatasetEngine class

#if !defined(_DATASET_ENGINE_H)
#define _DATASET_ENGINE_H

#include <string>


///	@brief		Identifier of the engine that is used to manage the dataset.
///
///	@details	This class provides a simple ID mechanism to identify the type of the dataset engine whose initialization information is stored in
///	a DatasetEngine object.
///
///	@see		DatasetEngine
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-06-10
class DatasetEngineType
{
	public:

		///	@brief Get the unique identifier of a plain-text-based dataset engine.
		static DatasetEngineType PlainText () { return DatasetEngineType(1); };
		
		///	@brief Get the unique identifier of a MySQL-based dataset engine.
		static DatasetEngineType MySql () { return DatasetEngineType(2); };
	
		///	@brief Get the unique identifier of a PostgreSQL-based dataset engine.
		static DatasetEngineType PostgreSql () { return DatasetEngineType(3); };

		///	@brief Equality operator overloading.
		///
		///	@param	engine	DatasetEngineType object to compare with.
		///
		///	@return True if both identifiers are equal, false otherwise.
		bool operator== (const DatasetEngineType& engine) const;

	private:

		///	@brief Constructor.
		///
		///	@param	type	Identifier of the engine type.
		explicit DatasetEngineType (const unsigned int& type);


		unsigned int id_;	///< Engine type identifier.
};



///	@brief		Engine that is used to manage the dataset.
///
///	@details	This class provides a simple way to specify which dataset engine must be used in the classification stage of NessieOcr. It is intended to be
///	used as a parameter of several methods of NessieOcr class, either NessieOcr::recognize() o NessieOcr::train(). Its members are used internally in that
///	class to define a particular Dataset object associated with the engine, since such classes should not be accessible from a client program.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-06-10
class DatasetEngine
{
	public:

		///	@brief	Get a plain-text-based dataset engine.
		///
		///	@param	filename	Filename of the plain text file that stores the dataset.
		///
		///	@return A DatasetEngine object properly initialized.
		static DatasetEngine PlainText (const std::string& filename) { return DatasetEngine(DatasetEngineType::PlainText(), filename); };

		///	@brief	Get a MySQL-based dataset engine.
		///
		///	@param	database	Database where the dataset is stored.
		///	@param	username	Name of the user who has access to the database.
		///	@param	password	Password of the user who has access to the database.
		///
		///	@return A DatasetEngine object properly initialized.
		static DatasetEngine MySql (const std::string& database, const std::string& username, const std::string& password)
		{
			return DatasetEngine(DatasetEngineType::MySql(), database, username, password);
		};

		///	@brief	Get a PostgreSQL-based dataset engine.
		///
		///	@param	database	Database where the dataset is stored.
		///	@param	username	Name of the user who has access to the database.
		///	@param	password	Password of the user who has access to the database.
		///
		///	@return A DatasetEngine object properly initialized.
		static DatasetEngine PostgreSql (const std::string& database, const std::string& username, const std::string& password)
		{
			return DatasetEngine(DatasetEngineType::PostgreSql(), database, username, password);
		};

		///	@brief	Get the unique identifier of the dataset engine.
		///
		///	@return	A DatasetEngineType object with its associated ID.
		DatasetEngineType type () const;

		///	@brief	Get the name of the file where the dataset is stored.
		///
		///	@return A STL string with the filename.
		const std::string& filename () const;
		
		///	@brief	Get the name of the database where the dataset is stored.
		///
		///	@return A STL string with the database name.
		const std::string& database () const;
		
		///	@brief	Get the name of the user who has access a database-based dataset.
		///
		///	@return A STL string with the username.
		const std::string& username () const;
		
		///	@brief	Get the password of the user who has access a database-based dataset.
		///
		///	@return A STL string with the password.
		const std::string& password () const;
	
	private:

		///	@brief	Constructor.
		///
		///	@param	type		Identifier of the engine.
		///	@param	filename	Filename of the plain text file that stores the dataset.
		explicit DatasetEngine (DatasetEngineType type, const std::string& filename);
		
		///	@brief	Constructor.
		///
		///	@param	type		Identifier of the engine.
		///	@param	database	Database where the dataset is stored.
		///	@param	username	Name of the user who has access to the database.
		///	@param	password	Password of the user who has access to the database.
		explicit DatasetEngine (DatasetEngineType type, const std::string& database, const std::string& username, const std::string& password);


		DatasetEngineType	type_;		///< Engine type

		std::string			filename_;	///< File name when the engine is PlainText.

		std::string			database_;	///< Database name when the engine is a database, e.g. MySql.

		std::string			username_;	///< Database user.

		std::string			password_;	///< Database password.
};


inline DatasetEngineType DatasetEngine::type () const
{
	return type_;
}

inline const std::string& DatasetEngine::filename () const
{
	return filename_;
}

inline const std::string& DatasetEngine::database () const
{
	return database_;
}

inline const std::string& DatasetEngine::username () const
{
	return username_;
}

inline const std::string& DatasetEngine::password () const
{
	return password_;
}
	
#endif

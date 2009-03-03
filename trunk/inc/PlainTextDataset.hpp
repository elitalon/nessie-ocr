/// @file
/// @brief Declaration of PlainTextDataset class

#if !defined(_PLAIN_TEXT_DATASET_H)
#define _PLAIN_TEXT_DATASET_H

#include "Dataset.hpp"
#include <string>
#include <boost/noncopyable.hpp>


///	@brief		Dataset built by retrieving the data from a plain text file in the filesystem.
///
///	@see		Dataset
///
///	@author Eliezer Talón (elitalon@gmail.com)
///	@date 2009-02-13
class PlainTextDataset : public Dataset, private boost::noncopyable
{
	public:

		///	@brief		Constructor.
		///
		/// @param		filename	Path in the filesystem to the file containing the dataset.
		///
		/// @pre		The file passed must have the number of features in its first line.
		///
		///	@exception	NessieException
		explicit PlainTextDataset (const std::string& filename);

		///	@brief	Destructor.
		virtual ~PlainTextDataset ();

		///	@brief		Adds a sample to the dataset.
		///
		///	@param		sample Sample to add.
		///
		///	@post		The sample is appended to the end of the dataset.
		///
		///	@exception	NessieException
		void addSample (const Sample& sample);

		///	@brief	Removes a sample from the dataset.
		///
		///	@param	n	Row in the dataset where remove the sample.
		///
		///	@post	The sample is removed from given position.
		void removeSample (const unsigned int& n);

	private:

		std::string	filename_;	///< File path where the data set is stored in the filesystem.
};

#endif

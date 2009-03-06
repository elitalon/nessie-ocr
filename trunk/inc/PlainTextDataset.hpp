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
		/// @details	This constructor loads a dataset from a file, which must have the following format:
		///
		/// The <em>first line</em> defines the number of features in every sample of the data set.
		///
		/// The <em>following lines</em> are the samples (one sample per line). Every line has a number of fields according to the definition in the first line,
		///	which constitutes a feature vector, and one additional field that tells the class of the feature vector. An example of a valid data set may be:
		///
		/// 4<br>
		/// 0.1 0.3 1.3 2.4 3<br>
		/// 1.5 2.8 6.2 2.4 1<br>
		/// 3.3 1.2 0.9 1.1 3<br>
		/// . . .<br>
		///
		/// The <em>feature</em> fields must have a floating point format: both the integer and decimal parts are required and separated by a point.
		///	The <em>class</em> field must be an integer.
		///
		/// @param		filename	Path in the filesystem to the file containing the dataset.
		///
		/// @pre		The file passed must have the number of features in its first line.
		///
		///	@exception	NessieException
		explicit PlainTextDataset (const std::string& filename);

		///	@brief	Destructor.
		virtual ~PlainTextDataset ();

		///	@brief		Addsa sample to the dataset.
		///
		///	@param		sample Sample to add.
		///
		///	@post		The sample is appended to the end of the dataset.
		///
		///	@exception	NessieException
		void addSample (const Sample& sample);

		///	@brief	Remove a sample from the dataset.
		///
		///	@param	n	Row in the dataset where remove the sample.
		void removeSample (const unsigned int& n);

	private:

		std::string	filename_;	///< File path where the data set is stored in the filesystem.
};

#endif

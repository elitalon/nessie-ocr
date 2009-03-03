/// @file
/// @brief Definition of PlainTextDataset class

#include "PlainTextDataset.hpp"
#include "NessieException.hpp"
#include <fstream>
#include <sstream>
#include <sys/stat.h>


/// @details This constructor loads a dataset from a file, which must have the following format:
///
/// The <em>first line</em> defines the number of features in every sample of the data set.
///
/// The <em>following lines</em> are the samples (one sample per line). Every line has a number of fields according to the definition in the first line, which constitutes
///	a feature vector, and one additional field that tells the class of the feature vector. An example of a valid data set may be:
///
/// 4<br>
/// 0.1 0.3 1.3 2.4 3<br>
/// 1.5 2.8 6.2 2.4 1<br>
/// 3.3 1.2 0.9 1.1 3<br>
/// . . .<br>
///
/// The <em>feature</em> fields must have a floating point format: both the integer and decimal parts are required and separated by a point. The <em>class</em> field must be an integer.
PlainTextDataset::PlainTextDataset (const std::string& filename)
:	Dataset(),
	filename_(filename)
{
	struct stat fileInfo;
	int fileStatus = stat(filename.data(), &fileInfo);

	if ( fileStatus != 0 )
		throw NessieException ("PlainTextDataset::PlainTextDataset() : File " + filename + " does not exist.");

	if ( not S_ISREG(fileInfo.st_mode) )
		throw NessieException ("PlainTextDataset::PlainTextDataset() : File " + filename + " exists but it is not a regular file.");

	std::ifstream stream( filename_.data() );
	if ( not stream.is_open() or not stream.good() )
	{
		stream.close();
		throw NessieException ("PlainTextDataset::PlainTextDataset() : File " + filename + " could not be open.");
	}

	// Read the number of features from the first line
	std::string line;
	getline(stream, line);
	std::stringstream lineStream( line );

	if ( (lineStream >> features_).fail() )
	{
		stream.close();
		throw NessieException ("PlainTextDataset::PlainTextDataset() : The number of features read has not a valid format.");
	}

	if ( features_ == 0 )
	{
		stream.close();
		throw NessieException ("PlainTextDataset::PlainTextDataset() : The number of features read is zero.");
	}

	// Read samples from the following lines
	unsigned int currentLineInt = 1;
	getline(stream, line);
	++currentLineInt;
	while ( stream.good() )
	{
		if ( line.empty() )
		{
			getline(stream, line);
			++currentLineInt;
			continue;
		}

		std::string field;
		std::vector<std::string> fields;
		std::stringstream lineStream(line);

		while ( lineStream >> field )
			fields.push_back(field);

		if ( fields.size() - 1 not_eq features_ )
		{
			stream.close();
			std::stringstream currentLineStr;
			currentLineStr << currentLineInt;
			throw NessieException ("PlainTextDataset::PlainTextDataset() : An invalid sample has been found at line " + currentLineStr.str() + "; the number of features found is inconsistent.");
		}

		FeatureVector features(features_);
		for ( unsigned int i = 0; i < features_; ++i )
		{
			std::stringstream featureStream( fields.at(i) );
			if ( (featureStream >> features.at(i)).fail() )
			{
				stream.close();
				std::stringstream currentLineStr;
				currentLineStr << currentLineInt;
				throw NessieException ("PlainTextDataset::PlainTextDataset() : An invalid sample has been found at line " + currentLineStr.str() + "; a feature had not a valid format.");
			}
		}

		unsigned int label;
		std::stringstream labelStream( fields.back() );
		if ( (labelStream >> label).fail() )
		{
			stream.close();
			std::stringstream currentLineStr;
			currentLineStr << currentLineInt;
			throw NessieException ("PlainTextDataset::PlainTextDataset() : An invalid sample has been found at line " + currentLineStr.str() + "; the label had not a valid format.");
		}
		samples_.push_back( Sample(features, label) );

		getline(stream, line);
		++currentLineInt;
	}

	stream.close();
	size_ = samples_.size();
};


PlainTextDataset::~PlainTextDataset ()
{
	try
	{
		std::ofstream stream( filename_.data(), std::ios::trunc );
		if ( not stream.is_open() or not stream.good() )
		{
			stream.close();
			return;
		}

		stream << features_ << std::endl;

		for ( unsigned int i = 0; i < size_; ++i )
		{
			FeatureVector features	= samples_.at(i).first;
			unsigned int label		= samples_.at(i).second;

			for ( unsigned int j = 0; j < features.size(); ++j )
				stream << features.at(j) << " ";

			stream << label << std::endl;
		}
	}
	catch (...) {}	// Bad luck if the dataset could not be dumped to disk.
};


void PlainTextDataset::addSample (const Sample& sample)
{
	if ( sample.first.size() != features_ )
		throw NessieException ("PlainTextDataset::addSample() : The number of features in the sample is different from the one expected by the dataset.");
	else
	{
		samples_.push_back(sample);
		size_ = samples_.size();
	}
};


void PlainTextDataset::removeSample (const unsigned int& n)
{
	samples_.erase(samples_.begin() + n);
	size_ = samples_.size();
};

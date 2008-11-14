///
/// @file
/// @brief Definition of DataSet class
///


#include "DataSet.hpp"

#include <fstream>
#include <sstream>

#include <sys/stat.h>



///
/// @details This constructor is intended to read a data set from a file. The source file where the data set is read from must have the following
/// format:
/// 
/// The <strong>first line</strong> defines the number of features in every sample of the data set.
/// 
/// The <strong>following lines</strong> are the samples, with one sample per line. Every line has a number of fields up to the number of features
/// defined in the first line plus one. Each field is separated by a whitespace. The last field represents the category of the sample. An example
/// of a valid data set may be:
/// 
/// <em>4</em>
/// 
/// <em>0.1 0.3 1.3 2.4</em> <strong>3</strong>
/// 
/// <em>1.5 2.8 6.2 2.4</em> <strong>1</strong>
/// 
/// <em>3.3 1.2 0.9 1.1</em> <strong>3</strong>
/// 
/// <em>. . .</em>
/// 
/// The fields representing the features must have a <em>float</em> format: both the integer and decimal parts are required and separated by a decimal
/// point (not a comma). The field representing the category of the sample must be an integer.
///
DataSet::DataSet (const std::string& sourceFile)
	:	samples_(std::deque<Sample>(0)),
		size_(0),
		nFeatures_(0),
		sourceFile_(sourceFile)
{
	// Check the source file attributes
	struct stat fileInfo;
	int fileStatus = stat(sourceFile.data(), &fileInfo);
	
	if ( fileStatus not_eq 0 )
		throw NessieException ("DataSet::DataSet() : The given file does not exist.");

	if ( not S_ISREG(fileInfo.st_mode) )
		throw NessieException ("DataSet::DataSet() : The given file exists but it is not a regular file.");
		
	
	// Associate the file with a stream
	std::ifstream stream( sourceFile_.data() );
	if ( not stream.is_open() or not stream.good() )
	{
		stream.close();
		throw NessieException ("DataSet::DataSet() : The file could not be open.");
	}


	// Read the number of features per sample from the first line
	std::string line;
	getline(stream, line);
	std::stringstream lineStream( line );
	
	if ( (lineStream >> nFeatures_).fail() )
	{
		stream.close();
		throw NessieException ("DataSet::DataSet() : The number of features read from file has not a valid format.");
	}
	
	if ( nFeatures_ == 0 )
	{
		stream.close();
		throw NessieException ("DataSet::DataSet() : The number of features read from file are zero.");
	}


	// Read the samples from the following lines
	getline(stream, line);
	while ( stream.good() )
	{
		// Discard empty lines
		if ( line.empty() )
		{
			getline(stream, line);
			continue;
		}
		
		// Extract the fields in the line
		std::string buffer;
		std::vector<std::string> tokens;
		std::stringstream lineStream(line);
		
		while ( lineStream >> buffer )
			tokens.push_back(buffer);
			
		// Test the fields found are consistent
		if ( tokens.size() - 1 not_eq nFeatures_ )
		{
			stream.close();
			throw NessieException ("DataSet::DataSet() : At least one sample in the data set is not valid, the number of features found is inconsistent.");
		}
				
		// Extract each feature
		FeatureVector features(nFeatures_);
		for ( unsigned int i = 0; i < nFeatures_; ++i )
		{
			std::stringstream featureStream( tokens.at(i) );
			if ( (featureStream >> features(i)).fail() )
			{
				stream.close();
				throw NessieException ("DataSet::DataSet() : At least one sample in the data set is not valid. An invalid feature has been found.");
			}
		}
		
		// Extract the category
		unsigned int category;
		std::stringstream categoryStream( tokens.back() );
		if ( (categoryStream >> category).fail() )
		{
			stream.close();
			throw NessieException ("DataSet::DataSet() : At least one sample in the data set is not valid. An invalid category has been found.");
		}
		samples_.push_back( Sample(features, category) );
		
		// Read new line from file
		getline(stream, line);
	}

	// Close the file
	stream.close();
	
	
	// Update size of data set
	size_ = samples_.size();
};




///
/// @details This constructor is intended to create an empty data set where only new samples will be added and previous samples in the source file,
/// if any, are automatically discarded. Thus, the previous content will be cleared and updated to the new samples added.
/// 
DataSet::DataSet (const std::string& sourceFile, const unsigned int& nFeatures)
	:	samples_(std::deque<Sample>(0)),
		size_(0),
		nFeatures_(nFeatures),
		sourceFile_(sourceFile)
{
	// Test the number of features requested
	if ( nFeatures == 0 )
		throw NessieException ("DataSet::DataSet() : The number of features cannot be zero.");
	
	
	struct stat fileInfo;
	int fileStatus = stat(sourceFile.data(), &fileInfo);
	
	if ( fileStatus not_eq 0 )	// The file does not exist
		return;

	if ( not S_ISREG(fileInfo.st_mode) )
		throw NessieException ("DataSet::DataSet() : The given file exists but is not a regular file.");		
};



DataSet::~DataSet ()
{
	// Associate the file with a stream
	std::ofstream stream( sourceFile_.data(), std::ios::trunc );
	if ( not stream.is_open() or not stream.good() )
	{
		stream.close();
		return;
	}
	
	// Write the number of features
	stream << nFeatures_ << std::endl;
	
	// Write the samples
	for ( unsigned int i = 0; i < size_; ++i )
	{
		FeatureVector features	= samples_.at(i).first;
		unsigned int category	= samples_.at(i).second;
		
		for ( unsigned int j = 0; j < features.size(); ++j )
			stream << features(j) << " ";
		
		stream << category << std::endl;
	}
};

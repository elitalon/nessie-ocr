/// @file
/// @brief Definition of PlainTextDataset class

#include "PlainTextDataset.hpp"
#include "NessieException.hpp"
#include <utility>
#include <fstream>
#include <sstream>
#include <sys/stat.h>


PlainTextDataset::PlainTextDataset (const std::string& filename)
:	Dataset(),
	filename_(filename)
{
	// Open the samples input file
	struct stat fileInfo;
	int fileStatus = stat(filename.data(), &fileInfo);

	if ( fileStatus != 0 )
		throw NessieException ("PlainTextDataset::PlainTextDataset() : File " + filename + " does not exist.");

	if ( not S_ISREG(fileInfo.st_mode) )
		throw NessieException ("PlainTextDataset::PlainTextDataset() : File " + filename + " exists but it is not a regular file.");

	std::ifstream inputFile( filename_.data() );
	if ( not inputFile.is_open() or not inputFile.good() )
		throw NessieException ("PlainTextDataset::PlainTextDataset() : File " + filename + " could not be opened.");

	// Read the number of features stored from file's first line
	if ( (inputFile >> features_).fail() )
		throw NessieException ("PlainTextDataset::PlainTextDataset() : The number of features read has not a valid format.");

	if ( features_ == 0 )
		throw NessieException ("PlainTextDataset::PlainTextDataset() : The number of features read is zero.");

	// Read every sample from the following lines
	std::string line;
	getline(inputFile, line);
	unsigned int lineNo = 2;
	while ( inputFile.good() )
	{
		if ( !line.empty() )
		{
			std::stringstream lineStream(line);
			
			while ( !lineStream.eof() )
			{
				FeatureVector features(features_);
				for ( unsigned int i = 0; i < features_; ++i )
				{
					if ( (lineStream >> features.at(i)).fail() )
					{
						std::stringstream lineNoAsString;
						lineNoAsString << lineNo;
						throw NessieException ("PlainTextDataset::PlainTextDataset() : An invalid sample has been found at line " + lineNoAsString.str() + ".");
					}
				}
			
				unsigned int code;
				if ( (lineStream >> code).fail() )
				{
					std::stringstream lineNoAsString;
					lineNoAsString << lineNo;
					throw NessieException ("PlainTextDataset::PlainTextDataset() : An invalid sample has been found at line " + lineNoAsString.str() + ".");
				}
			
				samples_.push_back( Sample(features, code) );
			} 
		}

		getline(inputFile, line);
		++lineNo;
	}
	inputFile.close();
	size_ = samples_.size();

	// Generate the character/code map
	typedef std::pair<std::string, unsigned int> Register;

	for ( unsigned char c = 'A'; c <= 'Z'; ++c )
	{
		std::string character(1, c);
		classes_.insert(Register(character, static_cast<unsigned int>(c)));
	}

    for ( unsigned char c = 'a'; c <= 'z'; ++c )
	{
		std::string character(1, c);
		classes_.insert(Register(character, static_cast<unsigned int>(c)));
	}
    
    for ( unsigned char c = '0'; c <= '9'; ++c )
	{
		std::string character(1, c);
		classes_.insert(Register(character, static_cast<unsigned int>(c)));
	}

	for (unsigned char c = '#'; c <= '/'; ++c)
	{
		std::string character(1, c);
		classes_.insert(Register(character, static_cast<unsigned int>(c)));
	}

	for (unsigned char c = ':'; c <= '@'; ++c)
	{
		std::string character(1, c);
		classes_.insert(Register(character, static_cast<unsigned int>(c)));
	}

	classes_.insert(Register(" ", static_cast<unsigned int>(' ')));
	classes_.insert(Register("{", static_cast<unsigned int>('{')));
	classes_.insert(Register("}", static_cast<unsigned int>('}')));
	classes_.insert(Register("!", static_cast<unsigned int>('!')));
	classes_.insert(Register("[", static_cast<unsigned int>('[')));
	classes_.insert(Register("]", static_cast<unsigned int>(']')));
	
	classes_.insert(Register("Ñ", 209));
	classes_.insert(Register("Ç", 199));
	classes_.insert(Register("Á", 193));
	classes_.insert(Register("É", 201));
	classes_.insert(Register("Í", 205));
	classes_.insert(Register("Ó", 211));
	classes_.insert(Register("Ú", 218));
	classes_.insert(Register("Ü", 220));
	classes_.insert(Register("ñ", 241));
	classes_.insert(Register("ç", 231));
	classes_.insert(Register("á", 225));
	classes_.insert(Register("é", 233));
	classes_.insert(Register("í", 237));
	classes_.insert(Register("ó", 243));
	classes_.insert(Register("ú", 250));
	classes_.insert(Register("ü", 252));
	classes_.insert(Register("¡", 161));
	classes_.insert(Register("¿", 191));
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
			unsigned int code		= samples_.at(i).second;

			for ( unsigned int j = 0; j < features.size(); ++j )
				stream << features.at(j) << " ";

			stream << code << std::endl;
		}
	}
	catch (...) {}
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

///
/// @file
/// @brief Declaration of DataSet class
///


#if !defined(_DATASET_H)
#define _DATASET_H


#include <string>
#include <utility>
#include <list>


#include "FeatureVector.hpp"
#include "NessieException.hpp"




///
/// Data set of character samples encoded as feature vectors.
/// 
/// This class stores a set of feature vectors that represents different characters. Every feature vector belongs to a category, i.e. a character.
/// You can read a bunch of data, work with it and update it (adding new samples o deleting any of them).
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-11-10
///
class DataSet
{
public:
	
	///
	/// @typedef Sample
	/// 
	/// @brief Sample of a data set.
	///
	/// @details This pair keeps the feature vector and the category that defines every sample in a data set.
	/// 
	/// @see FeatureVector
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	typedef std::pair<FeatureVector, unsigned int> Sample;
	
	
	///
	/// Constructor.
	/// 
	/// @param sourceFile	File path in the filesystem where the data set is stored.
	/// @param nFeatures	Number of features of the data set
	/// 
	/// @post The content in the file is loaded into the internal data structure.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	DataSet (const std::string& sourceFile, const unsigned int& nFeatures);
	
	
	///
	/// Destructor.
	/// 
	/// @post The changes made to the data set are written to disk. The output file is truncated
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	~DataSet ();
	
	
	///
	/// Adds a sample to the data set.
	/// 
	/// @param sample The sample to add
	/// 
	/// @post #samples_ is modified by adding the new sample.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	void addSample (const Sample& sample);
	
	
	///
	/// Removes a sample from the data set.
	/// 
	/// @param sample Position in the data set of the sample to remove.
	/// 
	/// @post #samples_ is modified by removing the sample at given position.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	void removeSample (const unsigned int& sample);


	///
	/// Gets a sample from the data set.
	/// 
	/// @param sample Position in the data set of the sample to get
	/// 
	/// @return The sample at given position
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	const Sample& getSample (const unsigned int& sample) const;


	///
	/// Returns the number of samples in the data set
	/// 
	/// @return The number of samples in the data set
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	const unsigned int& size () const;


	///
	/// Returns the number of features in every sample of the data set.
	/// 
	/// @return The number of features in every sample of the data set.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	const unsigned int& nFeatures () const;


	///
	/// Returns the file path where the data set is stored in the filesystem.
	/// 
	/// @return A string with the file path where the data set is stored in the filesystem.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	const std::string& sourceFile () const;


private:
	
	std::list<Sample>	samples_;		///< Samples of the data set
	
	unsigned int		size_;			///< Number of samples in the data set
	
	unsigned int		nFeatures_;		///< Number of features in every sample of the data set
	
	std::string			sourceFile_;	///< File path where the data set is stored in the filesystem
};




inline void DataSet::addSample (const Sample& sample)
{
	if ( sample.first.size() not_eq this->nFeatures_ )
		throw NessieException ("DataSet::addSample() : The number of features in the sample is different from the one in data set.");
	else
	{
		samples_.push_back(sample);
		size_ = samples_.size();
	}		
};


inline void DataSet::removeSample (const unsigned int& sample)
{
	if ( sample >= size_ )
		throw NessieException ("DataSet::removeSample() : The given position is out of bounds or the data set is empty.");
	else
	{
		std::list<Sample>::iterator j = samples_.begin();
		for ( unsigned int i = 1; i < size_ and i < sample; ++i )
			advance (j, 1);
			
		samples_.erase(j);
		size_ = samples_.size();
	}
};


inline const DataSet::Sample& DataSet::getSample (const unsigned int& sample) const
{
	if ( samples_.empty() )
		throw NessieException ("DataSet::getSample() : The data set is empty");
	else
	{
		std::list<Sample>::const_iterator j = samples_.begin();
		for ( unsigned int i = 1; i < size_ and i < sample; ++i )
			advance (j, 1);

		return (*j);
	}
};


inline const unsigned int& DataSet::size () const
{
	return size_;
};


inline const unsigned int& DataSet::nFeatures () const
{
	return nFeatures_;
};


inline const std::string& DataSet::sourceFile () const
{
	return sourceFile_;
};

#endif  //_DATASET_H

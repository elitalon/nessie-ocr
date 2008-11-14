///
/// @file
/// @brief Declaration of DataSet class
///


#if !defined(_DATASET_H)
#define _DATASET_H


#include <string>
#include <utility>
#include <deque>


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
	/// @param sourceFile	Path in the filesystem to the file containing the data set.
	/// 
	/// @pre The source file must contain at least the number of features in its first line.
	/// 
	/// @post The content in the file is loaded into #samples_.
	/// @post #nFeatures_ is set to the number of features per sample.
	/// @post #size_ is set to the number of samples read.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-13
	///
	DataSet (const std::string& sourceFile);
	
		
	///
	/// Constructor.
	/// 
	/// @param sourceFile	File path in the filesystem where the data set will be stored.
	/// @param nFeatures	Number of features of the data set
	/// 
	/// @post An empty data set is created, with #size_ set to zero and #nFeatures_ set to the number passed.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	DataSet (const std::string& sourceFile, const unsigned int& nFeatures);
	
	
	///
	/// Destructor.
	/// 
	/// @post The changes made to the data set are written to disk. The output file is truncated and rewritten
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
	/// Gets a sample from the data set.
	/// 
	/// @param iSample Position in the data set of the sample to get
	/// 
	/// @return The sample at given position
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	const Sample& getSample (const unsigned int& iSample) const;


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
	
	std::deque<Sample>	samples_;		///< Samples of the data set
	
	unsigned int		size_;			///< Number of samples in the data set
	
	unsigned int		nFeatures_;		///< Number of features in every sample of the data set
	
	std::string			sourceFile_;	///< File path where the data set is stored in the filesystem
	
	
	///
	/// Private constructor.
	/// 
	/// @details This declaration is intended to avoid creating an empty DataSet object.
	/// 
	/// @warning Do not define this method.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-14
	///
	DataSet ();
};




inline void DataSet::addSample (const Sample& sample)
{
	if ( sample.first.size() not_eq nFeatures_ )
		throw NessieException ("DataSet::addSample() : The number of features in the sample is different from the one in data set.");
	else
	{
		samples_.push_back(sample);
		size_ = samples_.size();
	}		
};


inline const DataSet::Sample& DataSet::getSample (const unsigned int& iSample) const
{
	return samples_.at(iSample);
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

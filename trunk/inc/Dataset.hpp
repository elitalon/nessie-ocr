/// @file
/// @brief Declaration of Dataset class

#if !defined(_DATASET_H)
#define _DATASET_H

#include <utility>
#include <vector>
#include "FeatureVector.hpp"


/// @typedef	Sample.
/// @brief		Internal representation of a sample in a dataset.
/// @author		Eliezer Talón (elitalon@gmail.com)
/// @date		2009-02-12
/// @see		FeatureVector
typedef std::pair<FeatureVector, unsigned int> Sample;


///	@brief		Data set of character samples encoded as feature vectors.
///
///	@details	This abstract base class provides an interface for a classification dataset, i.e. a set of samples that represents different characteristics of
///	previously recognized characters. A sample is composed of two fields: a feature vector and its label. The label indicates the class where the feature vector
///	belongs to. Any sample in the dataset can be read, and adding or deleting samples is also supported.
///
///	@see		FeatureVector
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-12
class Dataset
{
	public:

		///	@brief	Constructor.
		explicit Dataset ();

		///	@brief	Destructor.
		virtual ~Dataset ();

		///	@brief	Allows read-only access to a sample in the dataset.
		///
		/// @param	n	Row in the dataset where the required sample is.
		///
		/// @return	Sample at given position.
		virtual const Sample&  at(const unsigned int& n) const;

		///	@brief	Returns the number of samples in the dataset.
		///
		///	@return	Number of samples in the dataset.
		virtual const unsigned int& size () const;

		///	@brief	Returns the number of features per sample.
		///
		/// @return	Number of features per sample.
		virtual const unsigned int& features () const;

		///	@brief	Adds a sample to the dataset.
		///
		///	@param	sample Sample to add.
		///
		///	@post	The sample is appended to the end of the dataset.
		///
		///	@exception	NessieException	The number of features per sample in the dataset does not match with the sample passed.
		virtual void addSample (const Sample& sample) = 0;

		///	@brief	Removes a sample from the dataset.
		///
		///	@param	n	Row in the dataset where remove the sample.
		///
		///	@post	The sample is removed from given position.
		virtual void removeSample (const unsigned int& n) = 0;

	protected:

		std::vector<Sample>	samples_;	///< Samples of the dataset.

		unsigned int		size_;		///< Number of samples.

		unsigned int		features_;	///< Number of features per sample.
};


inline const Sample& Dataset::at (const unsigned int& n) const
{
	return samples_.at(n);
};

inline const unsigned int& Dataset::size () const
{
	return size_;
};

inline const unsigned int& Dataset::features () const
{
	return features_;
};

#endif

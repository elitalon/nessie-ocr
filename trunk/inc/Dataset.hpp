/// @file
/// @brief Declaration of Dataset class

#if !defined(_DATASET_H)
#define _DATASET_H

#include <utility>
#include <vector>
#include <string>
#include <map>
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
///	previously recognized characters. A sample is composed of two fields: a feature vector and its code. The code is a numeric identifier that indicates the class
/// where the feature vector belongs to. Any sample in the dataset can be read, and adding or deleting samples is also supported.
///
///	@see		FeatureVector, Sample
///
///	@todo		Implement a mechanism to condense the dataset by eliminating useless samples during training.
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

		///	@brief	Allow read-only access to a sample in the dataset.
		///
		/// @param	n	Row in the dataset where the required sample is.
		///
		/// @return	Sample at given position.
		virtual const Sample&  at(const unsigned int& n) const;

		///	@brief	Get the number of samples in the dataset.
		///
		///	@return	Number of samples in the dataset.
		virtual const long unsigned int& size () const;

		///	@brief	Get the number of features per sample.
		///
		/// @return	Number of features per sample.
		virtual const unsigned int& features () const;

		/// @brief	Get the code associated to the character passed.
		/// 
		/// @param	character	A valid character.
		/// 
		/// @return The code associated to the character or 256 if there is no association.
		virtual unsigned int code (const std::string& character) const;

		/// @brief	Get the character associated to the code passed.
		/// 
		/// @param	code	A valid code.
		/// 
		/// @return The character associated to the code or an empty string if there is no association.
		virtual std::string character (const unsigned int& code) const;

		///	@brief	Add a sample to the dataset.
		///
		///	@param	sample Sample to add.
		///
		///	@post	The sample is appended to the end of the dataset.
		///
		///	@exception	NessieException	The number of features per sample in the dataset does not match with the sample passed.
		virtual void addSample (const Sample& sample) = 0;

		///	@brief	Remove a sample from the dataset.
		///
		///	@param	n	Row in the dataset where remove the sample.
		virtual void removeSample (const unsigned int& n) = 0;

	protected:

		std::vector<Sample>					samples_;	///< Samples of the dataset.

		std::map<std::string, unsigned int>	classes_;	///< Map of classes that associates a character with its code.

		long unsigned int					size_;		///< Number of samples.

		unsigned int						features_;	///< Number of features per sample.
};


inline const Sample& Dataset::at (const unsigned int& n) const
{
	return samples_.at(n);
};

inline const long unsigned int& Dataset::size () const
{
	return size_;
};

inline const unsigned int& Dataset::features () const
{
	return features_;
};

#endif

/// @file
/// @brief Declaration of FeatureVector class

#if !defined(_FEATUREVECTOR_H)
#define _FEATUREVECTOR_H


#include <vector>
#include "NessieException.hpp"


///	@brief		Array of characteristic features that identifies a pattern.
/// 
/// @details	This class stores a set of features computed from a pattern where a character's shape has been mapped.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-04
///
class FeatureVector
{
	public:

		///	@brief	Constructor.
		/// 
		/// @param	nFeatures Number of features to hold.
		FeatureVector (const unsigned int& nFeatures);

		/// @brief	Allows read-and-write access to a certain feature.
		///
		/// @param	index	Position inside the vector where the feature is.
		/// 
		/// @return A reference to the feature at given position.
		double& operator() (const unsigned int& index);

		///	@brief	Allows read-only access to a certain feature.
		///
		/// @param	index	Position inside the vector where the feature is.
		/// 
		/// @return Feature at given position.
		double operator() (const unsigned int& index) const;

		/// @brief	Computes the sum of two feature vectors.
		/// 
		/// @param	featureVector	Feature vector to sum.
		/// 
		/// @return A FeatureVector object as a result of summing both feature vectors.
		FeatureVector operator+ (const FeatureVector& featureVector) const;

		///	@brief	Computes the subtraction of two feature vectors.
		/// 
		/// @param	featureVector	Feature vector to subtract.
		/// 
		/// @return A FeatureVector object as a result of subtracting both feature vectors.
		FeatureVector operator- (const FeatureVector& featureVector) const;

		/// @brief	Computes the dot product of two feature vectors.
		/// 
		/// @param	featureVector	Feature vector to multiplicate.
		/// 
		/// @return The result of multiplicating both feature vectors.
		double operator* (const FeatureVector& featureVector) const;

		/// @brief	Returns the number of features held.
		/// 
		/// @return Number of features held.
		const unsigned int& size () const;

	private:

		std::vector<double>	features_;	///< Characteristic features of the pattern.

		unsigned int		size_;		///< Number of features.

		// Explicitly disallowed compiler-generated methods. DO NOT IMPLEMENT THEM!!
		FeatureVector ();
};


inline double& FeatureVector::operator() (const unsigned int &index)
{
	return features_.at(index);
};


inline double FeatureVector::operator() (const unsigned int &index) const
{
	return features_.at(index);
};


inline FeatureVector FeatureVector::operator+ (const FeatureVector& featureVector) const
{
	// Check if vectors have the same size
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator+() : Size of vectors to sum must be equal");

	FeatureVector temp(this->size_);

	for ( unsigned int i = 0; i < this->size_; ++i )
		temp.features_.at(i) = this->features_.at(i) + featureVector.features_.at(i);

	return temp;
};


inline FeatureVector FeatureVector::operator- (const FeatureVector& featureVector) const
{
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator-() : Size of vectors to subtract must be equal");

	FeatureVector temp(this->size_);

	for ( unsigned int i = 0; i < this->size_; ++i )
		temp.features_.at(i) = this->features_.at(i) - featureVector.features_.at(i);

	return temp;
};


inline double FeatureVector::operator* (const FeatureVector& featureVector) const
{
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator*() : Size of vectors to multiply must be equal");

	double result = 0.0;

	for ( unsigned int i = 0; i < this->size_; ++i )
		result += this->features_.at(i) * featureVector.features_.at(i);

	return result;
};


inline const unsigned int& FeatureVector::size () const
{
	return size_;
};

#endif  //_FEATUREVECTOR_H


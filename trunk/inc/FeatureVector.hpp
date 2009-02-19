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
class FeatureVector
{
	public:

		///	@brief	Constructor.
		///
		///	@post	An empty feature vector of zero size is initialized. 
		FeatureVector ();
		
		///	@brief	Constructor.
		/// 
		/// @param	n Number of features to store in the vector.
		///
		///	@post	An empty feature vector of size <em>n</em> is initialized to 0.0. 
		explicit FeatureVector (const unsigned int& n);

		/// @brief	Allows read-and-write access to a certain feature.
		///
		/// @param	n	Position inside the vector where the feature is.
		/// 
		/// @return A reference to the feature at given position.
		double& at (const unsigned int& n);

		///	@brief	Allows read-only access to a certain feature.
		///
		/// @param	n	Position inside the vector where the feature is.
		/// 
		/// @return Feature at given position.
		const double& at (const unsigned int& n) const;

		/// @brief		Computes the sum of two feature vectors.
		/// 
		/// @param		featureVector	Feature vector to sum.
		/// 
		/// @return		A FeatureVector object as a result of summing both feature vectors.
		/// 
		///	@exception	NessieException
		FeatureVector operator+ (const FeatureVector& featureVector) const;

		///	@brief		Computes the subtraction of two feature vectors.
		/// 
		/// @param		featureVector	Feature vector to subtract.
		/// 
		/// @return		A FeatureVector object as a result of subtracting both feature vectors.
		/// 
		///	@exception	NessieException
		FeatureVector operator- (const FeatureVector& featureVector) const;

		/// @brief		Computes the dot product of two feature vectors.
		/// 
		/// @param		featureVector	Feature vector to multiplicate.
		/// 
		/// @return		The result of multiplicating both feature vectors.
		/// 
		///	@exception	NessieException
		double operator* (const FeatureVector& featureVector) const;

		/// @brief	Returns the number of features held.
		/// 
		/// @return Number of features held.
		const unsigned int& size () const;

	private:

		std::vector<double>	features_;	///< Characteristic features of the pattern.

		unsigned int		size_;		///< Number of features.
};


inline double& FeatureVector::at (const unsigned int &n)
{
	return features_.at(n);
};


inline const double& FeatureVector::at (const unsigned int &n) const
{
	return features_.at(n);
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

#endif


///
/// @file
/// @brief Declaration of FeatureVector class
///

#if !defined(_FEATUREVECTOR_H)
#define _FEATUREVECTOR_H


#include <vector>

#include "NessieException.hpp"




///
/// Vector of features that defines a character in an image.
/// 
/// This class stores a number of features, computed from the moments of an image where the character's shape has been extracted. Each feature represents
/// an image moment.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-11-10
///
class FeatureVector
{
public:
	
	///
	/// Constructor.
	/// 
	/// @param nFeatures NUmber of features to store
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	FeatureVector (const unsigned int& nFeatures=7);
	
	
	///
	/// Destructor.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	~FeatureVector ();
	
	
	///
	/// Allows read-and-write access to a feature in the vector.
	///
	/// @param feature		Position in the vector where the feature is at.
	/// 
	/// @return A reference to the feature at given position.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	double& operator() (const unsigned int& feature);


	///
	/// Allows read-only access to a pixel in the clip.
	///
	/// @param feature		Position in the vector where the feature is at.
	/// 
	/// @return Feature at given location.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	double operator() (const unsigned int& feature) const;
	
	
	///
	/// Makes the sum of two feature vectors.
	/// 
	/// @param featureVector	Feature vector to sum
	/// 
	/// @return FeatureVector object as a result of summing both vectors
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	FeatureVector operator+ (const FeatureVector& featureVector) const;
	
	
	///
	/// Makes the subtraction of two feature vectors.
	/// 
	/// @param featureVector	Feature vector to subtract
	/// 
	/// @return FeatureVector object as a result of subtracting both vectors
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	FeatureVector operator- (const FeatureVector& featureVector) const;
	
	
	///
	/// Makes the multiplication of two feature vectors.
	/// 
	/// @param featureVector	Feature vector to multiplicate
	/// 
	/// @return FeatureVector object as a result of multiplicating both vectors
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	double operator* (const FeatureVector& featureVector) const;
		
	
	///
	/// Returns the number of features stored in the vector.
	/// 
	/// @return Number of features stored in the vector.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-10
	///
	const unsigned int& size () const;
	
	
private:
	
	std::vector<double>	features_;	///< Features of the character
	
	unsigned int		size_;		///< Number of features
	
};



inline double& FeatureVector::operator() (const unsigned int &feature)
{
	return features_.at(feature);
};


inline double FeatureVector::operator() (const unsigned int &feature) const
{
	return features_.at(feature);
};


inline FeatureVector FeatureVector::operator+ (const FeatureVector& featureVector) const
{
	// Check if vectors have the same size
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator+() : Size of vectors to sum must be equal");


	FeatureVector temp;
	
	for ( unsigned int i = 0; i < this->size_; ++i )
		temp.features_.at(i) = this->features_.at(i) + featureVector.features_.at(i);
	
	return temp;
};


inline FeatureVector FeatureVector::operator- (const FeatureVector& featureVector) const
{
	// Check if vectors have the same size
	if ( this->size_ not_eq featureVector.size_ )
		throw NessieException ("FeatureVector::operator-() : Size of vectors to subtract must be equal");

	FeatureVector temp;
	temp.features_.reserve(this->size_);

	for ( unsigned int i = 0; i < this->size_; ++i )
		temp.features_.at(i) = this->features_.at(i) - featureVector.features_.at(i);
		
	return temp;
};


inline double FeatureVector::operator* (const FeatureVector& featureVector) const
{
	// Check if vectors have the same size
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

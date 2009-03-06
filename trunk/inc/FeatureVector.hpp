/// @file
/// @brief Declaration of FeatureVector class

#if !defined(_FEATUREVECTOR_H)
#define _FEATUREVECTOR_H

#include <vector>


///	@brief		Array of characteristic features that identifies a pattern.
/// 
/// @details	This class stores a set of features computed from a pattern where the character's pixels has been mapped.
///
/// @todo		Implement another method to compute distance between vectors (e.g. the Mahalanobis distance).
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

		/// @brief	Allow read-and-write access to a certain feature.
		///
		/// @param	n	Position inside the vector where the feature is.
		/// 
		/// @return The feature at given position.
		double& at (const unsigned int& n);

		///	@brief	Allow read-only access to a certain feature.
		///
		/// @param	n	Position inside the vector where the feature is.
		/// 
		/// @return The feature at given position.
		const double& at (const unsigned int& n) const;

		/// @brief		Compute the sum of two feature vectors.
		/// 
		/// @param		featureVector	Feature vector to sum.
		/// 
		/// @return		A FeatureVector object as a result of summing both feature vectors.
		/// 
		///	@exception	NessieException
		FeatureVector operator+ (const FeatureVector& featureVector) const;

		///	@brief		Compute the subtraction of two feature vectors.
		/// 
		/// @param		featureVector	Feature vector to subtract.
		/// 
		/// @return		A FeatureVector object as a result of subtracting both feature vectors.
		/// 
		///	@exception	NessieException
		FeatureVector operator- (const FeatureVector& featureVector) const;

		/// @brief		Compute the dot product of two feature vectors.
		/// 
		/// @param		featureVector	Feature vector to multiplicate.
		/// 
		/// @return		The result of multiplicating both feature vectors.
		/// 
		///	@exception	NessieException
		double operator* (const FeatureVector& featureVector) const;

		/// @brief	Get the number of features held.
		/// 
		/// @return Number of features held.
		const unsigned int& size () const;
		
		/// @brief	Clear the vector content.
		///
		///	@post	The features are removed and the size becomes 0.
		void clear ();
		
		/// @brief	Reset the vector content.
		///
		///	@post	The features are set to 0.0 but the vector size remains equal.
		void reset ();
		
		/// @brief	Resize the vector to the specified size.
		/// 
		/// @param	n Number of features to store in the vector.
		///
		///	@post	The previous features are removed and an new vector of size <em>n</em> is initialized to 0.0.
		void resize (const unsigned int& n);

		///	@brief	Compute the Euclidean distance with the input vector.
		///
		///	@param	featureVector	Feature vector of reference.
		///
		///	@return	The Euclidean distance between this vector and the input vector.
		double computeEuclideanDistance (const FeatureVector& featureVector) const;

	private:

		std::vector<double>	features_;	///< Characteristic features of the pattern.
		
		unsigned int		size_;		///< Size of the vector.
};


inline double& FeatureVector::at (const unsigned int &n)
{
	return features_.at(n);
};

inline const double& FeatureVector::at (const unsigned int &n) const
{
	return features_.at(n);
};

inline const unsigned int& FeatureVector::size () const
{
	return size_;
};

inline void FeatureVector::clear ()
{
	features_.clear();
	size_ = 0;
};

inline void FeatureVector::reset ()
{
	for ( std::vector<double>::iterator i = features_.begin(); i != features_.end(); ++i )
		*i = 0.0;
};

inline void FeatureVector::resize (const unsigned int& n)
{
	features_.clear();
	features_.assign(n, 0.0);
	
	size_ = n;
};

#endif


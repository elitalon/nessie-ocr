/// @file
/// @brief Declaration of Classifier class

#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H


#include "DataSet.hpp"
#include "FeatureVector.hpp"
class Shape;

#include <string>
#include <deque>
#include <utility>



/// Classifier of the OCR process.
/// 
/// This class encapsulates all the methods related to the classification stage of the OCR process. Its task
/// is to match every shape found in the segmentation stage to a valid character.
/// 
/// @see Shape, FeatureVector
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-11-06
///
class Classifier
{
public:
	
	/// Constructor.
	/// 
	/// @param dataset A data set to use in the classification process.
	Classifier (const DataSet& dataset);
	
	
	/// Destructor.
	~Classifier ();
	
	
	/// Matchs a shape to a character.
	/// 
	/// @param shape Shape that represents a character
	/// 
	/// @return The character if found, otherwise an empty string indicating a failure.
	std::string matchShape (const Shape& shape);
	
	
	/// Returns the elapsed time while matching a shape to a character.
	/// 
	/// @return Elpased time while matching a shape to a character.
	const double& matchingShapeTime ();


private:
	
	DataSet			dataset_;			///< Data set where the classification samples are stored.
	
	FeatureVector	sample_;			///< A sample that represents a shape.
	
	double			matchingShapeTime_;	///< Elapsed time while matching a shape into a character.
	
	
	Classifier ();
	
	///
	/// Builds a feature vector from a shape.
	/// 
	/// @param shape	The source shape where the information is taken to build the feature vector.
	void buildFeatureVector (const Shape& shape);
};



inline const double& Classifier::matchingShapeTime ()
{
	return matchingShapeTime_;
};

#endif  //_CLASSIFIER_H


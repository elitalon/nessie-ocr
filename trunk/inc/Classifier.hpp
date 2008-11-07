///
/// @file
/// @brief Declaration of Classifier class
///


#if !defined(_CLASSIFIER_H)
#define _CLASSIFIER_H


#include "FeatureVector.hpp"
class Shape;

#include <string>
#include <deque>
#include <utility>




///
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
	
	///
	/// Constructor.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-07
	///
	Classifier ();
	
	
	///
	/// Matchs a shape to a character.
	/// 
	/// @param shape Shape that represents a character
	/// 
	/// @return The character if found, otherwise an empty string indicating a failure.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-07
	///
	std::string matchShape (const Shape& shape);
	
	
	///
	/// Returns the elapsed time while matching a shape to a character.
	/// 
	/// @return Elpased time while matching a shape to a character.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-07
	///
	float matchingShapeTime ();


private:
	
	///
	/// @typedef DatasetElement
	/// 
	/// @brief Element of a data set.
	///
	/// @details This pair keeps the feature vector and the category that defines every sample in a data set.
	/// 
	/// @see FeatureVector
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-07
	///
	typedef std::pair<FeatureVector, unsigned int> DatasetElement;
	
	
	std::deque<DatasetElement>	dataset_;			///< Data set where the classification samples are stored.
	
	FeatureVector				sample_;			///< A sample that represents a shape.
	
	float						matchingShapeTime_;	///< Elapsed time while matching a shape into a character.
	
	std::string					datasetFilename;	///< The file path where the data set is stored in the filesystem.
	
	
	///
	/// Builds a feature vector from a shape.
	/// 
	/// @param shape	The source shape where the information is taken to build the feature vector.
	/// 
	/// @post #sample_ is initialized according to the values calculated.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-07
	///
	void buildFeatureVector (const Shape& shape);


	///
	/// Reads a dataset from a file in the filesystem.
	/// 
	/// @post #dataset_ is set with the contents of the file.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-07
	///
	void readDataset ();
	
	
	///
	/// Writes a dataset to a file in the filesystem.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-11-07
	///
	void writeDataset () const;
	
};

#endif  //_CLASSIFIER_H

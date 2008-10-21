///
/// @file
/// @brief Declaration of the class Segmenter
///

#if !defined(_SEGMENTER_H)
#define _SEGMENTER_H

#include <vector>

#include "Shape.hpp"
class Clip;


///
/// Segmenter of the OCR process.
/// 
/// This class encapsulates all the methods related to segmentation stage. Its task
/// is to isolate every shape within a clip that represents a character, storing them in a data structure
/// for further classification.
/// 
/// @see Clip, Shape, Pixel
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-13 
///
class Segmenter
{
public:
	///
	/// Constructor.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	Segmenter ();
	
	///
	/// Returns the elapsed time while applying the thresholding algorithm.
	/// 
	/// @return The elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const double &thresholdingTime () const;
	
	
	///
	/// Returns the elapsed time while finding the shapes.
	/// 
	/// @return The elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const double &shapesFindingTime () const;
	
	
	///
	/// Returns the shapes found in the last segmentation process
	/// 
	/// @return A vector of Shape objects
	/// 
	/// @see Shape
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const std::vector<Shape> &shapes () const;
	
	
	
	///
	/// Returns the gray level that represents the ink used in characters
	/// 
	/// @return Either a value of 0 or 255
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-18
	///
	const unsigned char &inkValue () const;
	
	
	///
	/// Applies the threshold algorithm.
	/// 
	/// @param	clip				Press clip
	/// @param	threshold			Threshold value to differentiate between back- and foreground pixels
	/// @param	backgroundReference	Background reference gray level
	/// 
	/// @post Every pixel has either a gray level of 0 or 255.
	/// @post The #inkValue_ member is initialized to the gray level that represents the ink's gray level
	/// 
	/// @see Clip
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	void applyThreshold (Clip &clip, const unsigned char &threshold, const unsigned char &backgroundReference);
	
	
	///
	/// Finds the shapes in the clip by searching connected pixels
	/// 
	/// @pre The clip MUST be thresholded by calling applyThreshold() method before.
	/// 
	/// @post The #shapes_ member is initialized with the shapes that represents character within the clip.
	/// 
	/// @param clip	The press clip
	/// 
	/// @see Clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	void findShapes (const Clip &clip);
	

private:
	///
	/// Gray level value of the pixels that have ink
	///
	unsigned char inkValue_;
	
	///
	/// A set of shapes that represents every character found within the press clip
	///
	std::vector<Shape> shapes_;

	///
	/// Elapsed time while applying the thresholding algorithm
	///
	double thresholdingTime_;
	
	///
	/// Elapsed time while applying the flood fill algorithm
	///
	double shapesFindingTime_;

	
	// void splitShape();
	// void joinShapes();
	// void sortShapes();
};



//
// Implementation of inline functions
// 


/// 
/// @details
///
inline const double &Segmenter::thresholdingTime () const
{
	return thresholdingTime_;
};



/// 
/// @details
///
inline const double &Segmenter::shapesFindingTime () const
{
	return shapesFindingTime_;
};



///
/// @details
///
inline const std::vector<Shape> &Segmenter::shapes() const
{
	return shapes_;
};



///
/// @details
///
inline const unsigned char &Segmenter::inkValue () const
{
	return inkValue_;
};

#endif  //_SEGMENTER_H

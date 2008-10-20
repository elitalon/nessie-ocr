///
/// @file
/// @brief Declaration of the class Segmenter
///

#if !defined(_SEGMENTER_H)
#define _SEGMENTER_H

#include <vector>
#include <list>


#include "Pixel.hpp"
#include "Shape.hpp"
#include "Clip.hpp"


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
	/// Returns the elapsed time while applying the flood fill algorithm.
	/// 
	/// @return The elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const double &floodFillingTime () const;
	
	
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
	/// Returns the seeds found in the last segmentation process
	/// 
	/// @return A list of Pixel objects
	/// 
	/// @see Pixel
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-17
	///
	const std::list<Pixel> &seeds () const;
	
	
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
	/// Applies the flood fill algorithm.
	/// 
	/// @pre The clip MUST be thresholded by calling applyThreshold() method before.
	/// 
	/// @post The #seeds_ member is initialized with the pixels that generates each shape found.
	/// @post The #shapes_ member is initialized with the shapes that represents character within the clip.
	/// 
	/// @param clip	Press clip
	/// 
	/// @see Clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	void applyFloodFill (const Clip &clip);
	
	
	
	

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
	double floodFillingTime_;
	
	///
	/// A set of ink pixels from where the flood fill method find the shapes
	///
	std::list<Pixel> seeds_;
	

	///
	/// Finds all the ink pixels within a clip that may grow up as a shape
	/// 
	/// @pre The clip MUST be thresholded by calling applyThreshold() method before.
	/// 
	/// @post The #seeds_ member is initialized with all the ink pixels within the clip
	/// 
	/// @param clip	The press clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-17
	///
	void findSeeds (const Clip &clip);
	
	
	///
	/// Returns true if the pixel belongs to the vector of seeds.
	/// 
	/// @param pixel A pixel of the clip
	/// 
	/// @return True if the pixel is a seed
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-18
	///
	bool isSeed (const Pixel& pixel) const;
	

	///
	/// Makes a recursive exploration searching for ink pixels that are neighbours of the pixel passed building a Shape
	/// 
	/// @post A new Shape object is added to #shapes_.
	/// @post The pixels that belongs to the new Shape object are removed from #seeds_.
	/// 
	/// @param seed The pixel where starting the exploration from
	/// @param clip	The clip where doing the exploration
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-18
	///
	void exploreSeedNeighbourhood (const Pixel &seed, const Clip &clip);



	// void removeSeed(Pixel seed);
	// void addShape(Shape shape);
	// void removeShape(unsigned int shape);
	// void splitShape(Shape shape);
	// void joinShapes(Shape leftShape, Shape rightShape);
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
inline const double &Segmenter::floodFillingTime () const
{
	return floodFillingTime_;
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
inline const std::list<Pixel> &Segmenter::seeds() const
{
	return seeds_;
};


///
/// @details
///
inline const unsigned char &Segmenter::inkValue () const
{
	return inkValue_;
};

#endif  //_SEGMENTER_H

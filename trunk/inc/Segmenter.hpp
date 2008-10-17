///
/// @file
/// @brief Declaration of the class Segmenter
///

#if !defined(_SEGMENTER_H)
#define _SEGMENTER_H

#include <vector>


#include "Pixel.hpp"
#include "Shape.hpp"
class Clip;	// Forward declaration


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
		/// @post The #seeds_ member is initialized to a vector of pixels that generates each shape found.
		/// @post The #shapes_ member is initialized to a vector of shapes that represents character within the clip.
		/// 
		/// @param clip	Press clip
		/// 
		/// @see Clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-13
		///
		void applyFloodFill (const Clip &clip);
		
		
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
		/// @return A vector of Pixel objects
		/// 
		/// @see Pixel
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-17
		///
		const std::vector<Pixel> &seeds () const;
		

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
		std::vector<Pixel> seeds_;
		

		///
		/// Finds all the ink pixels within a clip that may grow up as a shape
		/// 
		/// @post The #seeds_ member is initialized
		/// 
		/// @param clip	The press clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-17
		///
		void findSeeds (const Clip &clip);
		
		
		// void addSeed(Pixel seed);
		// Pixel selectRandomSeed();
		// void exploreSeedNeighbourhood(Pixel seed);
		// bool isSeed(Pixel pixel);
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
inline const std::vector<Pixel> &Segmenter::seeds() const
{
	return seeds_;
};

#endif  //_SEGMENTER_H

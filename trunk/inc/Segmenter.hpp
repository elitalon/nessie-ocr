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
		const std::vector<Shape> &shapes() const;
		

	private:
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
		

		// void findSeeds(Clip clip);
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

#endif  //_SEGMENTER_H

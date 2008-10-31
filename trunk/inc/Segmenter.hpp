///
/// @file
/// @brief Declaration of Segmenter class
///

#if !defined(_SEGMENTER_H)
#define _SEGMENTER_H


#include <deque>
#include <list>
#include <utility>


#include "Shape.hpp"
class Clip;




///
/// Segmenter of the OCR process.
/// 
/// This class encapsulates all the methods related to segmentation stage of the OCR process. Its task
/// is to isolate every shape in a clip that represents a character, storing them in a data structure
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
	/// Returns the gray level that represents the ink used in characters
	/// 
	/// @return A value of 0 or 255
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-18
	///
	const unsigned char& inkValue () const;
	
	
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
	const std::list<Shape>& shapes () const;
	
	
	///
	/// Returns the elapsed time while applying the thresholding algorithm.
	/// 
	/// @return The elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& thresholdingTime () const;
	
	
	///
	/// Returns the elapsed time while finding the shapes.
	/// 
	/// @return The elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& shapesFindingTime () const;
	
	
	///
	/// Applies a thresholding algorithm.
	/// 
	/// @param	clip				A press clip.
	/// @param	threshold			A threshold value to differentiate between background and foreground pixels.
	/// @param	backgroundReference	Background reference gray level.
	/// 
	/// @post Every pixel in the clip has either a gray level of 0 or 255.
	/// @post The #inkValue_ member is initialized to the gray level that represents the ink's gray level of the press clip.
	/// 
	/// @see Clip
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	void applyThreshold (Clip& clip, const unsigned char& threshold, const unsigned char& backgroundReference);
	
	
	///
	/// Finds a list of isolated shapes in the press clip by joining connected pixels
	/// 
	/// @pre The clip MUST be thresholded by calling applyThreshold() method before.
	/// 
	/// @post The #seeds_ member is initialized with the seeds that grew into the shapes.
	/// @post The #visited_ member is initialized with the positions of the seeds set to true.
	/// @post The #shapes_ member is initialized with the shapes that represents character within the clip.
	/// 
	/// @param clip	The press clip
	/// 
	/// @see Clip
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	void findShapes (const Clip& clip);
	

private:
	
	///
	/// @typedef LineMarker
	/// 
	/// @brief Limits of a line of shapes.
	///
	/// @details This pair keeps the rows of a press clip that delimits a single line of shapes. The first member representes the row of pixels
	/// at the top of the line, while the second member represents the row of pixels at the bottom of the line.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-24
	/// 
	typedef std::pair<unsigned int, unsigned int> LineMarker;
	
	
	///
	/// @typedef LineMarkerIterator
	/// 
	/// @brief An iterator to a list of LineMarker objects.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-31
	///
	typedef std::list<LineMarker>::iterator LineMarkerIterator;
	
	
	///
	/// @typedef ShapeIterator
	/// 
	/// @brief An iterator to a list of Shape objects.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-30
	///
	typedef std::list<Shape>::iterator ShapeIterator;
	
	
	unsigned char			inkValue_;				///< Gray level value of the pixels that have ink

	std::deque<Pixel> 		seeds_;					///< A list with the coordinates of every pixel that has a gray level equal to #inkValue_
	
	std::deque<bool>		visited_;				///< A list of "visited/non visited" status for the pixels in the press clip
	
	std::list<Shape>		shapes_;				///< A list of shapes that represents every character found within the press clip
	
	std::list<LineMarker>	lineMarkers_;			///< A list of integer pairs that defines the limits of every line of characters in a press clip

	float					thresholdingTime_;		///< Elapsed time while applying the thresholding algorithm
	
	float					shapesFindingTime_;		///< Elapsed time while applying the shapes finding algorithm
	
		
	///
	/// Find the seeds where the shapes will grow up from.
	/// 
	/// @param clip	The press clip where finding the seeds
	/// 
	/// @pre The press clip must come thresholded in two values, one of them being equal to #inkValue_.
	/// 
	/// @post #seeds_ contains every pixel that has a gray level equal to #inkValue_.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-24
	///
	void findSeeds (const Clip& clip);


	///
	/// Builds a list of shapes founded in a clip by growing seeds into isolated shapes.
	/// 
	/// @param	clip	The press clip where the shape will be found from the seeds.
	/// 
	/// @pre #seeds_ must be initialized by calling findSeeds() method. Their coordinates must be consistent with the clip dimensions.
	/// 
	/// @post #shapes_ member contains the initial shapes that represents characters in the clip.
	/// @post #visited_ member is updated by setting to true the position of those pixels that become part of a shape.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-24
	///
	void growSeedsIntoInitialShapes (const Clip& clip);
	
	
	///
	/// Finds the pairs of rows that delimit every line of shapes in a press clip.
	/// 
	/// @param clip The press clip
	/// 
	/// @post The #lineMarkers_ member contains pairs of numbers that delimits every isolated line of shapes.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-24
	///
	void findLineMarkers (const Clip& clip);
	

	///
	/// Joins two shapes that are vertically overlapped.
	/// 
	/// @param s1	First shape to join
	/// @param s2	Second shape to join
	/// 
	/// @pre #shapes_ cannot be empty.
	/// 
	/// @post A new Shape object is inserted into #shapes_ by joining s1 and s2. Both s1 and s2 are then removed from #shapes_.
	/// @post The iterator s1 is updated by pointing to the next shape in #shapes_.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-27
	///
	void joinVerticallyOverlappedShapes (ShapeIterator& s1, ShapeIterator& s2);
	
	
	///
	/// Finds a shape that is vertically overlapped to the shape passed, both being in the same line of shapes.
	/// 
	/// @param lineTop		Row that delimits the top of the line
	/// @param lineBottom	Column that delimits the bottom of the line
	/// @param shape		Shape for which a vertically overlapped shape has to be found
	/// 
	/// @pre #shapes_ cannot be empty.
	/// 
	/// @return If found, an iterator to a shape that is vertically overlapped to the shape passed. Otherwise, an iterator to the shape passed.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-30
	///
	ShapeIterator findVerticallyOverlappedShape (const unsigned int& lineTop, const unsigned int& lineBottom, const ShapeIterator& shape);

};




inline const unsigned char& Segmenter::inkValue () const
{
	return inkValue_;
};


inline const std::list<Shape>& Segmenter::shapes() const
{
	return shapes_;
};


inline const float& Segmenter::thresholdingTime () const
{
	return thresholdingTime_;
};


inline const float& Segmenter::shapesFindingTime () const
{
	return shapesFindingTime_;
};

#endif  //_SEGMENTER_H

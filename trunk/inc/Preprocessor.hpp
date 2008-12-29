///
/// @file
/// @brief Declaration of Preprocessor class
///

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H


#include "Clip.hpp"
#include "Shape.hpp"
#include <deque>
#include <list>
#include <utility>


///
/// Preprocessor of the OCR process.
///
/// This class encapsulates all the algorithms related to preprocessing stage of the OCR process. Its task
/// is to enhance the image quality by applying some techniques of image processing theory and compute
/// a number of parameters such as the optimal thresolding value or the background reference gray level.
///
/// @see Clip
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-11
///
class Preprocessor
{
public:
	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-08
	///
	Preprocessor (const Clip& pressClip);


	///
	/// Returns the optimal threshold found in the last clip used.
	///
	/// @return Optimal threshold computed from the last clip used.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned char& optimalThreshold () const;


	///
	/// Sets the optimal threshold to use in algorithms.
	///
	/// @param threshold Value between 0 and 255 that stablishes the optimal threshold of a clip.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-08
	///
	void optimalThreshold (const unsigned char& threshold);


	///
	/// Returns the background reference gray level in the last clip used.
	///
	/// @return Reference background gray level in the last clip used
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned char& backgroundReferenceGrayLevel () const;


	///
	/// Sets the background reference gray level in the last clip used.
	///
	/// @param grayLevel Value between 0 and 255 that stablishes the reference background gray level in the clip
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-15
	///
	void backgroundReferenceGrayLevel (const unsigned char& grayLevel);


	///
	/// Returns the elapsed time while applying the 'isolated noise removal' algorithm
	///
	/// @return Elapsed time when applying the 'isolated noise removal' algorithm
	///
	/// @see removeIsolatedNoise()
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const double& noiseRemovalTime () const;


	///
	/// Returns the elapsed time while founding the optimal threshold within the clip
	///
	/// @return Elapsed time while founding the optimal threshold within the clip
	///
	/// @see computeOptimalThreshold()
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const double& optimalThresholdComputingTime () const;


	///
	/// Returns the elapsed time while computing the background reference gray level within the clip
	///
	/// @return Elapsed time while computing the background reference gray level
	///
	/// @see findBackgroundReferenceGrayLevel()
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const double& backgroundReferenceGrayLevelFindingTime () const;


	///
	/// Computes the optimal threshold value in a clip following the Sonka's technique.
	///
	/// @pre	You MUST call findBackgroundReferenceGrayLevel() method before calling this one, since it sets internal attributes.
	///
	/// @post	The #optimalThresholdComputingTime_ member is modified.
	/// @post	The #optimalThreshold_ member is initialized to the threshold found
	///
	/// @param clip			The clip where applying the algorithm over
	///
	/// @see Clip
	///
	/// @return The optimal threshold of the clip
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-20
	///
	const unsigned char& computeOptimalThreshold ();


	///
	/// Computes the background reference gray level value within a clip.
	///
	/// @post	The #backgroundReferenceGrayLevelFindingTime_ member is modified.
	///
	/// @param	clip							The clip where applying the algorithm over
	/// @param	referenceGrayLevelNeighbours	Number of neighbours of the more frequent gray level to explore on each direction
	///
	/// @see Clip
	///
	/// @return The reference gray level of the background
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const unsigned char& findBackgroundReferenceGrayLevel (const unsigned int& referenceGrayLevelNeighbours = 2);


	///
	/// Applies the 'isolated noise removal' algorithm.
	///
	/// @pre	You MUST call computeOptimalThreshold() and findBackgroundReferenceGrayLevel() methods before calling this one,
	/// since they set internal attributes.
	///
	/// @post	The clip may be modified if any noise is found.
	///
	/// @param[in,out]	clip					The clip where applying the algorithm over
	/// @param			isolationCoefficient	The maximum noisy neighbours for a pixel to consider it as isolated
	///
	/// @see Clip
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-11
	///
	void removeIsolatedNoise (const unsigned int& isolationCoefficient = 0);


	///
	/// Applies a thresholding algorithm.
	///
	/// @param	clip				A press clip.
	/// @param	threshold			A threshold value to differentiate between background and foreground pixels.
	/// @param	backgroundReference	Background reference gray level.
	///
	/// @post Every pixel in the clip has either a gray level of 0 or 1.
	/// @post The #inkValue_ member is initialized to the gray level that represents the ink's gray level of the press clip.
	///
	/// @see Clip
	///
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	void applyThreshold (const unsigned char& threshold, const unsigned char& backgroundReference);


    ///
	/// Finds a list of isolated shapes in the press clip by joining connected pixels
	///
	/// @pre The clip MUST be thresholded by calling applyThreshold() method before.
	///
	/// @post #seeds_ contains the seeds that grew into the shapes.
	/// @post #visited_ contains the positions of the seeds set to true.
	/// @post #shapes_ contains the shapes that represents character within the clip.
	/// @post #shapes_ is sorted according with the position of characters in text
	///
	/// @param clip	The press clip
	///
	/// @see Clip
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-21
	///
	void findShapes (const Clip& clip);

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
	/// Finds every position in the list of shapes where a blank space must be inserted when building the text.
	///
	/// @pre #shapes_ must be sorted according with the position of characters in text.
	///
	/// @post #spaceLocations_ contains indexes to #shapes_.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-31
	///
	void findSpaceLocations ();
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

    std::deque<Pixel> 			seeds_;					///< A list with the coordinates of every pixel that has a gray level equal to #inkValue_

	std::deque<bool>			visited_;				///< A list of "visited/non visited" status for the pixels in the press clip

	std::list<Shape>			shapes_;				///< A list of shapes that represents every character found within the press clip

	std::list<LineMarker>		lineMarkers_;			///< A list of integer pairs that defines the limits of every line of characters in a press clip
    
	Clip            clip;

	unsigned char	optimalThreshold_;							///< Optimal threshold value within the clip

	unsigned char	backgroundReferenceGrayLevel_;				///< Background reference gray level

	double			noiseRemovalTime_;							///< Elapsed time when applying the 'isolated noise removal' algorithm

	double			optimalThresholdComputingTime_;				///< Elapsed time when converting the image to a grayscale colorspace

	double			backgroundReferenceGrayLevelFindingTime_;	///< Elapsed time when computing the background gray level

	double						thresholdingTime_;		///< Elapsed time while applying the thresholding algorithm

	double						shapesFindingTime_;		///< Elapsed time while applying the shapes finding algorithm

	unsigned char				inkValue_;				///< Gray level value of the pixels that have ink


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
	/// @post #lineMarkers_ contains pairs of numbers that delimits every isolated line of shapes.
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





inline const std::list<Shape>& Preprocessor::shapes() const
{
	return shapes_;
};

inline const unsigned char& Preprocessor::optimalThreshold () const
{
	return optimalThreshold_;
};


inline void Preprocessor::optimalThreshold (const unsigned char& threshold)
{
	optimalThreshold_ = threshold;
};


inline const unsigned char& Preprocessor::backgroundReferenceGrayLevel () const
{
	return backgroundReferenceGrayLevel_;
};


inline void Preprocessor::backgroundReferenceGrayLevel (const unsigned char& grayLevel)
{
	backgroundReferenceGrayLevel_ = grayLevel;
};


inline const double& Preprocessor::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};


inline const double& Preprocessor::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


inline const double& Preprocessor::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


#endif  //_PREPROCESSOR_H

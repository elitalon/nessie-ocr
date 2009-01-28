/// @file
/// @brief Declaration of Preprocessor class

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H


#include "Clip.hpp"
#include "Statistics.hpp"
#include "Region.hpp"
#include "Pattern.hpp"
#include <list>
#include <vector>
#include <utility>



/// Preprocessor of the OCR process.
///
/// This class encapsulates all the algorithms related to preprocessing stage of the OCR process. Its task
/// is to extract the regions of interest from a press clip, enhance them and clean the result by smoothing
/// and noise removal. In the very end of the process, a list of patterns is available through the
///	Preprocessor::patterns() method.
///
///	For an optimal preprocessing, it is strongly recommended that the following algorithms
/// will be executed:
///	
///	-# Global gray level thresholding
///	-# Smoothing and noise removal
///	-# Patterns extraction and isolation
///	-# Slant detection and correction
///	-# Character normalization
///	-# Thinning (skeleton construction)
///
/// @see Clip, Pattern, Statistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-08
///
class Preprocessor
{
public:

	/// Constructor.
	/// 
	/// @param pressClip A press clip over which apply all the preprocessing algorithms.
	/// 
	/// @see Clip
	explicit Preprocessor (const Clip& pressClip);

	/// Applies a global thresholding algorithm over the press clip.
	///
	/// @post Every pixel in the press clip belonging to the background has a gray level value of 0, while
	/// every pixel of ink has a gray level of 1.
	void applyGlobalThresholding ();

	///	Applies four 3x3 matching templates over the press clip to remove noise and smooth character borders.
	///
	///	@pre The press clip must have been converted to binary mode, i.e. 0 for background pixels and 1 for ink pixels.
	///
	///	@post The noise in the image is removed and the borders of characters are smoothed.
	void applyTemplateFilters ();

	/// Applies an averaging filter mask (linear filtering) over the press clip to remove noise and smooth character borders.
	///
	///	@pre The press clip must be in grayscale mode.
	///
	///	@post The noise in the image is removed and the borders of characters are blurred.
	void applyAveragingFilters ();
	
	/// Applies a segmentation process over the press clip to isolate every region of ink pixels.
	///
	///	@pre The press clip must have been converted to binary mode, i.e. 0 for background pixels and 1 for ink pixels.
	void extractRegions ();

	///	Corrects the slanting of every region extracted from press clip.
	///
	///	@pre The internal list of regions must have been initialized by calling Preprocessor::extractRegions.
	void correctSlanting ();

	///
	///
	///	@pre
	///
	///	@post
	void normalizeCharacters ();
	
	///
	///
	///	@pre
	///
	///	@post
	void applyThinning ();

	/// Finds every position in the list of patterns where a blank space must be inserted when building the text.
	void findSpaceLocations ();

	/// Returns the patterns found, if any, in the last segmentation process
	///
	/// @return An array of Pattern objects
	///
	/// @see Pattern
	const std::vector<Pattern>& patterns () const;

	/// Returns the statistics about the preprocessing stage regarding algorithms execution.
	/// 
	/// @return A PreprocessorStatistics object with all the data gathered until the moment of execution.
	/// 
	/// @see PreprocessorStatistics
	const PreprocessorStatistics& statistics () const;

private:

	Clip					clip_;			///< The press clip over which the preprocessing algorithms are applied.
	
	PreprocessorStatistics	statistics_;	///< Statistics about the execution of algorithms.

	std::list<Region>		regions_;		///< A list of regions that represents every set of ink pixels found in the press clip.
	
	std::vector<Pattern>	patterns_;		///< An array of patterns that represents every character shape found in the press clip.

	/// @typedef	LineDelimiter.
	/// @brief		Internal representation of a pair of x-axis coordinates that delimits a row of regions as if they were characters in a text.
	/// @author		Eliezer Talón (elitalon@gmail.com)
	/// @date		2009-01-19
	typedef std::pair<unsigned int, unsigned int> LineDelimiter;

	/// @brief Computes the optimal threshold value in a press clip following the Sonka's algorithm.
	/// 
	/// @return A unsigned char with the optimal threshold value in a scale of [0,255].
	unsigned char computeSonkaOptimalThreshold () const;

	/// @brief Computes the optimal threshold value in a press clip following the Otsu's algorithm.
	///
	///	@return	A unsigned char with the optimal threshold value in a scale of [0,255].
	unsigned char computeOtsuOptimalThreshold () const;

	/// Finds every pair of rows that delimits a line of regions as if they were characters in a text.
	///
	///	@param		visited		A vector of boolean values that tell which pixels have been visited during the regions extraction process.
	/// @param[out] delimiters	A list of LineDelimiter objects to store the result.
	void findLineDelimiters (const std::vector<bool>& visited, std::list<LineDelimiter>& delimiters) const;

	/// @brief Merge every pair of regions that are vertically overlapped, assuming they are accents isolated from their characters.
	/// 
	/// @param delimiters A list of text line delimiters.
	void mergeVerticallyOverlappedRegions (const std::list<LineDelimiter>& delimiters);
	
	
	// Explicitly disallowed compiler-generated functions. DO NOT IMPLEMENT THEM!!
	Preprocessor ();
	Preprocessor (const Preprocessor&);
	Preprocessor& operator= (const Preprocessor&);
};


inline const PreprocessorStatistics& Preprocessor::statistics () const
{
	return statistics_;
};


inline const std::vector<Pattern>& Preprocessor::patterns() const
{
	return patterns_;
};

#endif  //_PREPROCESSOR_H


/// @file
/// @brief Declaration of Preprocessor class

#if !defined(_PREPROCESSOR_H)
#define _PREPROCESSOR_H

#include <Magick++.h>
#include "Region.hpp"
#include "PreprocessorStatistics.hpp"
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <list>
#include <utility>
class Pattern;


/// @brief		Preprocessor of NessieOcr.
///
/// @details	This class encapsulates all the algorithms related to the preprocessing stage of the OCR process. Its task is to extract the characters
///	from a press clip, enhance them and clean the result by smoothing and noise removal. In the very end of the process, an array of patterns is available
///	through the patterns() method.
///
///	@details	For an optimal preprocessing, it is strongly recommended that the following algorithms will be executed in this order:
///	
///		-# Smoothing and noise removal using the averaging filter.
///		-# Global gray level thresholding.
///		-# Smoothing and noise removal using the template matching filter.
///		-# Regions extraction and isolation.
///		-# Patterns building.
///		-# Skeletonization of patterns.
///		-# Slant detection and correction.
///
/// @see	Pattern, PreprocessorStatistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-08
class Preprocessor
{
	public:

		/// @brief	Constructor.
		///
		/// @param	page		Underlying image representing a newspaper page.
		/// @param	x			X-axis coordinate of the row where the top leftmost pixel of the press clip is.
		/// @param	y			Y-axis coordinate of the column where the top leftmost pixel of the press clip is.
		/// @param	height		Height of the press clip in pixels.
		/// @param	width		Width of the press clip in pixels.
		///
		///	@post	The Image object is copied into an internal structure.
		explicit Preprocessor (const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width);

		/// @brief	Get the patterns found, if any, in the last segmentation process.
		///
		/// @return An array of Pattern objects.
		const std::vector<Pattern>& patterns () const;

		///	@brief	Get the statistics regarding the preprocessing stage.
		/// 
		/// @return A PreprocessorStatistics object with all the statistics gathered at the time of calling.
		const PreprocessorStatistics& statistics () const;

		/// @brief		Apply an averaging filter over the press clip to remove noise and smooth character borders.
		///
		///	@details	This method follows a linear filtering approach to remove noise and smooth the press clip, in which the value of
		///	an output pixel is a linear combination of the values of the pixels in the input pixel's neighbourhood. A pixel's neighbourhood
		///	is a set of pixels defined by their locations relative to that pixel. Normally, this algorithm should be applied a predefined
		///	number of times, otherwise all the important features could disappear.
		///
		///	@pre		The press clip must be in grayscale mode.
		void removeNoiseByLinearFiltering ();
	
		/// @brief		Apply a global thresholding algorithm over the press clip.
		///
		/// @details	The algorithm uses the Otsu's method to find automatically the optimal threshold for the press clip. Then, it compares each pixel
		/// gray level with that threshold and transforms the source clip into a binary image. As a result, the final histogram is bimodal. 
		///
		/// @post		Every pixel in the press clip belonging to the background has a gray level value of 0, while every pixel of ink has a gray level of 1.
		void applyGlobalThresholding ();

		///	@brief		Apply four 3x3 templates over the press clip to remove additional noise and smooth character borders.
		///
		///	@details	This method passes over the templates over the entire clip, and this process is repeated until there is no change. These masks
		///	begin scanning in the lower right corner of the image and process each row movin upward row by row. The pixel in the center of the mask is
		///	the target. If the pixels in its neighbourhood do not match the template, the pixel is removed.
		///
		///	@pre		The press clip must have been converted to binary mode by calling applyGlobalThresholding().
		void removeNoiseByTemplateMatching ();

		/// @brief		Apply a segmentation process over the press clip to isolate every region of ink pixels.
		///
		/// @details	This method isolates every region of ink pixels in a press clip following a flooding algorithm. Starting from an arbitrary pixel of ink,
		///	the algorithm explores the neighbourhood adding new ink pixels to the region until a boundary of background pixels is found. Then, the algorithm
		///	selects another pixel and begins the process, until every ink pixel has been assigned to a region. As a result, a list of regions is built.
		///
		///	The list of regions is post-processed in order to find disconnected region that must be merged, e.g. accents and other punctuation signs to their characters.
		///	Finally, the list is sorted by lines and columns, so that traversing the list from the beginning is equivalent to reading the text from left to right
		///	and from up to down.
		///
		/// @return		An array of integers, each one represents the position where a blank space must be inserted when building the text in further post-processing.
		///
		///	@pre		The press clip must have been thresholded by calling applyGlobalThresholding().
		std::vector<unsigned int> isolateRegions ();

		/// @brief	Build an array of normalized patterns using the regions of ink pixels extracted from the press clip.
		///
		///	@pre	There must be a list of regions available by calling isolateRegions().
		void buildPatterns ();

		/// @brief		Reduce the patterns to their fundamental skeleton using the Zhang-Suen algorithm.
		///
		///	@details	This algorithm has two steps, which are successively applied to the patterns. In each step contour points of the pattern
		///	that can be deleted are identified. Contour points are defined as points that have ink, and they have at least one 8-neighbour pixel
		///	value equal to the background.
		///
		///	In the first step every contour point that can be deleted is flagged only if four conditions are satisfied. In the second step additional
		///	pixels are flagged if another four conditions are satisfied. A pixel is not removed until a whole step has been applied. Both steps
		///	are repeated until there is no change in the image.
		///
		///	@pre		There must be an array of patterns available by calling buildPatterns().
		void skeletonizePatterns();

		///	@brief		Correct the slanting of every region extracted from press clip.
		///
		///	@details	This method corrects the slanting by computing the angle for which the input pattern presents at least one column
		/// with more ink pixels than any column in the original pattern.
		///
		///	@pre		There must be an array of patterns available by calling buildPatterns().
		///
		///	@post		The regions that present slanting are rotated as much as possible to be aligned with the Y-axis.
		void correctSlanting ();

		/// @brief	Get the average character height.
		/// 
		/// @return	Average character height in pixels.
		const double& averageCharacterHeight () const;

		/// @brief		Create a new image in the filesystem using Magick++ facilities, reflecting the current state of the press clip.
		///
		/// @param		outputFile		A string with the image name in the filesystem.
		/// @param		scalingFactor	Top limit of the source image color scale to use in the output image (i.e. 1 for [0..1], 255 for [0..255], etc.).
		///
		/// @post		A new image file is created in the filesystem. The image type is assigned according to the file extension provided in the
		///	filename (e.g. "foo.png" selects PNG as the image type). Otherwise the image type is Magick++'s implementation-dependent.
		void writeClipToOutputImage (const std::string& outputFile, const double& scalingFactor = 1.0) const;


	private:

		/// @typedef	LineDelimiter.
		/// @brief		A pair of x-axis coordinates that delimits a row of regions as if they were characters in a text.
		/// @author		Eliezer Talón (elitalon@gmail.com)
		/// @date		2009-01-19
		typedef std::pair<unsigned int, unsigned int> LineDelimiter;

		///	@typedef	LineDelimiterIterator.
		///	@brief		Iterator to a LineDelimiter object within a list of LineDelimiters objects.
		///	@author		Eliezer Talón (elitalon@gmail.com)
		///	@date		2009-05-26
		typedef std::list<LineDelimiter>::iterator LineDelimiterIterator;

		///	@typedef	RegionIterator.
		///	@brief		Iterator to a Region object within a list of Region objects.
		///	@author		Eliezer Talón (elitalon@gmail.com)
		///	@date		2009-05-26
		typedef std::list<Region>::iterator RegionIterator;

		///	@typedef	RegionLines.
		///	@brief		Organization of regions in lines, where each line is composed of an identifier and a list of iterators to regions.
		///	@author		Eliezer Talón (elitalon@gmail.com)
		///	@date		2009-06-01
		typedef std::map<unsigned int, std::list<RegionIterator> > RegionLines;


		std::vector<unsigned char>	clip_;							///< Press clip over which the preprocessing algorithms are applied.
		
		unsigned int				clipHeight_;					///< Clip's height in pixels.

		unsigned int				clipWidth_;						///< Clip's width in pixels.

		PreprocessorStatistics		statistics_;					///< Statistics about the execution of algorithms.

		std::list<Region>			regions_;						///< Stores every region of ink pixels found in the press clip.
	
		std::list<LineDelimiter>	delimiters_;					///< Stores the limits of every line of characters.
	
		RegionLines					inlineRegions_;					///< Organizes the regions in lines.

		std::vector<Pattern>		patterns_;						///< Stores the patterns suitable for feature extraction.
		
		double						averageCharacterHeight_;		///< Average character's height in pixels.
		
		double						averageCharacterWidth_;			///< Average character's width in pixels.

		double						averageSpaceBetweenCharacters_;	///< Average space in pixels between characters.
		

		/// @brief	Find every pair of x-axis coordinates that delimits a line of regions as if they were characters in a text.
		///
		///	@param	visited		A vector of boolean values that tell which pixels have been visited during the regions extraction process.
		void findLineDelimiters (const std::deque<bool>& visited);

		/// @brief		Arrange every region into its line according to the delimiters found.
		///
		///	@pre		A list of line delimiters must be available by calling findLineDelimiters().
		///
		///	@post		For each line, a list of iterators pointing to the appropiate regions is built.
		///
		///	@warning	The implementation must not modify the list of Region objects, since iterators to that list are used later.
		void organizeRegionsIntoLines();

		/// @brief	Merge every pair of regions that are vertically overlapped, assuming they are accents isolated from their characters.
		///
		///	@pre	A map of regions arranged into lines must have been built by calling organizeRegionsIntoLines().
		///
		///	@post	Merged regions are removed from the list of regions. The new regions built are added to the list of regions.
		void mergeVerticallyOverlappedRegions ();

		///	@brief	Sort the regions within a line using the insertion sort algorithm.
		///
		///	@param	regions	List of iterators to the regions that must be sorted.
		///
		///	@pre	A map of regions arranged into lines must have been built by calling organizeRegionsIntoLines().
		///
		///	@post	The list of regions is sorted using the insertion sorting algorithm.
		void sortRegions (std::list<RegionIterator>& regions);

		/// @brief	Scan the list of regions detecting spaces between words.
		/// 
		/// @return An array of numbers, each one represents the position where a blank space must be inserted when building the text in further post-processing.
		std::vector<unsigned int> findSpacesBetweenWords ();

		// Do not implement these methods, as they are only declared here to prevent objects to be copied. 
		Preprocessor (const Preprocessor&);
		Preprocessor& operator= (const Preprocessor&);
};


inline const PreprocessorStatistics& Preprocessor::statistics () const
{
	return statistics_;
}

inline const std::vector<Pattern>& Preprocessor::patterns() const
{
	return patterns_;
}

inline const double& Preprocessor::averageCharacterHeight () const
{
	return averageCharacterHeight_;
}

#endif


/// @file
/// @brief Declaration of FeatureExtractor class

#if !defined(_FEATURE_EXTRACTOR_H)
#define _FEATURE_EXTRACTOR_H


#include "Statistics.hpp"
#include "Region.hpp"
#include "Pattern.hpp"
#include <list>
#include <vector>


/// @brief		FeatureExtractor of the OCR process.
///
/// @details	This class encapsulates all the algorithms related to feature extraction stage of the OCR process. Its task is ...
///	In the very end of the process, a vector of
///	patterns is available through the FeatureExtractor::patterns() method.
///
/// @see		Region, FeatureExtractorStatistics, Pattern
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-02
///
class FeatureExtractor
{
	public:

		/// @brief	Constructor.
		/// 
		/// @param	regions A list of regions over which apply all the feature extraction algorithms.
		explicit FeatureExtractor (const std::list<Region>& regions);

		/// @brief	Returns the patterns built from the regions passed in constructor.
		///
		/// @return A list of Pattern objects
		const std::vector<Pattern>& patterns () const;

		///	@brief	Returns the statistics about the feature extraction stage.
		/// 
		/// @return A FeatureExtractorStatistics object with all the data gathered.
		const FeatureExtractorStatistics& statistics () const;

	private:

		std::list<Region>				regions_;		///< A list of regions that represents every set of ink pixels found in the press clip.

		FeatureExtractorStatistics		statistics_;	///< Statistics about the execution of algorithms.

		std::vector<Pattern>			patterns_;		///< An array of patterns arranged for further classification.

		// Explicitly disallowed compiler-generated methods. DO NOT IMPLEMENT THEM!!
		FeatureExtractor ();
		FeatureExtractor (const FeatureExtractor&);
		FeatureExtractor& operator= (const FeatureExtractor&);
};


inline const FeatureExtractorStatistics& FeatureExtractor::statistics () const
{
	return statistics_;
};


inline const std::vector<Pattern>& FeatureExtractor::patterns() const
{
	return patterns_;
};

#endif  //_FEATURE_EXTRACTOR_H


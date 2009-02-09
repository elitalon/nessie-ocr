/// @file
/// @brief Declaration of FeatureExtractor class

#if !defined(_FEATURE_EXTRACTOR_H)
#define _FEATURE_EXTRACTOR_H


class Region;
#include "Statistics.hpp"
#include "Pattern.hpp"
#include "FeatureVector.hpp"
#include <list>
#include <vector>


/// @brief		FeatureExtractor of the OCR process.
///
/// @details	This class encapsulates all the algorithms related to feature extraction stage of the OCR process. Its task is to capture the
///	distinctive characteristics of the digitized characters for recognition, i.e. the measurement of those attributes of patterns that are most
///	pertinent to a given classification task. In the very end of the process, an array of patterns is available through the
///	FeatureExtractor::patterns() method, and an array of feature vectors through the method FeatureExtractor::featureVectors() method.
///
/// @see		Region, FeatureExtractorStatistics, Pattern, FeatureVector
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
		/// @return An array of Pattern objects.
		const std::vector<Pattern>& patterns () const;

		///	@brief	Returns the feature vectors built from the patterns.
		///
		///	@return	An array of FeatureVector objects.
		const std::vector<FeatureVector>& featureVectors () const;

		///	@brief	Returns the statistics about the feature extraction stage.
		/// 
		/// @return A FeatureExtractorStatistics object with all the data gathered.
		const FeatureExtractorStatistics& statistics () const;

		///	@brief	Compute a number of image moments from the internal patterns.
		void computeMoments ();

	private:

		FeatureExtractorStatistics		statistics_;		///< Statistics about the execution of algorithms.

		std::vector<Pattern>			patterns_;			///< An array of patterns from which compute characteristic features.

		std::vector<FeatureVector>		featureVectors_;	///< An array of feature vectors arranged for further classification.

		// Explicitly disallowed compiler-generated methods. DO NOT IMPLEMENT THEM!!
		FeatureExtractor ();
		FeatureExtractor (const FeatureExtractor&);
		FeatureExtractor& operator= (const FeatureExtractor&);
};


inline const std::vector<Pattern>& FeatureExtractor::patterns() const
{
	return patterns_;
};


inline const std::vector<FeatureVector>& FeatureExtractor::featureVectors () const
{
	return featureVectors_;
};


inline const FeatureExtractorStatistics& FeatureExtractor::statistics () const
{
	return statistics_;
};

#endif  //_FEATURE_EXTRACTOR_H


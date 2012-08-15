/// @file
/// @brief Declaration of FeatureExtractor class

#if !defined(_FEATURE_EXTRACTOR_H)
#define _FEATURE_EXTRACTOR_H

class FeatureVector;
class Pattern;
#include "FeatureExtractorStatistics.hpp"
#include <vector>


/// @brief		FeatureExtractor of the OCR process.
///
/// @details	This class encapsulates all the algorithms related to feature extraction stage of the OCR process. Its task is to capture the
///	distinctive characteristics of the digitized characters for recognition, i.e. the measurement of those attributes of patterns that are most
///	pertinent to a given classification task. In the very end of the process, an array of patterns is available through the
///	FeatureExtractor::patterns() method, and an array of feature vectors through the method FeatureExtractor::featureVectors() method.
///
/// @see		FeatureExtractorStatistics, Pattern, FeatureVector
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-02
class FeatureExtractor
{
	public:

		/// @brief	Constructor.
		explicit FeatureExtractor ();

		///	@brief	Get the feature vectors built from the patterns.
		///
		///	@return	An array of FeatureVector objects.
		const std::vector<FeatureVector>& featureVectors () const;

		///	@brief	Get the statistics about the feature extraction stage.
		/// 
		/// @return A FeatureExtractorStatistics object with all the statistics gathered.
		const FeatureExtractorStatistics& statistics () const;

		///	@brief	Compute the image moments from the internal patterns.
		/// 
		/// @param	patterns An array of patterns over which apply all the feature extraction algorithms.
		///
		///	@post	An array of feature vectors becomes available through the FeatureExtractor::featureVectors() method.
		void computeMoments (const std::vector<Pattern>& patterns);

	private:

		FeatureExtractorStatistics		statistics_;		///< Statistics about the execution of algorithms.

		std::vector<FeatureVector>		featureVectors_;	///< An array of feature vectors arranged for further classification.
};


inline const std::vector<FeatureVector>& FeatureExtractor::featureVectors () const
{
	return featureVectors_;
}

inline const FeatureExtractorStatistics& FeatureExtractor::statistics () const
{
	return statistics_;
}

#endif


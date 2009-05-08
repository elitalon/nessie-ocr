/// @file
/// @brief Declaration of FeatureExtractor class

#if !defined(_FEATURE_EXTRACTOR_H)
#define _FEATURE_EXTRACTOR_H

class Pattern;
#include "FeatureExtractorStatistics.hpp"
#include "FeatureVector.hpp"
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
		/// 
		/// @param	patterns An array of patterns over which apply all the feature extraction algorithms.
		explicit FeatureExtractor (const std::vector<Pattern>& patterns);

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
		///	@param	n	Maximum number of moments to compute.
		///
		///	@post	An array of feature vectors becomes available through the FeatureExtractor::featureVectors() method.
		void computeMoments (const unsigned int& n);

	private:

		FeatureExtractorStatistics		statistics_;		///< Statistics about the execution of algorithms.

		std::vector<Pattern>			patterns_;			///< An array of patterns from which compute characteristic features.

		std::vector<FeatureVector>		featureVectors_;	///< An array of feature vectors arranged for further classification.

		///	@brief	Compute the standard image moment of order (p + q) of a pattern.
		///
		/// @param	pattern	Input pattern.
		/// @param	p		Order in the x-axis.
		/// @param	q		Order in the y-axis.
		///	@param	xc		X-axis coordinate of the pattern's centroid.
		///	@param	yc		Y-axis coordinate of the pattern's centroid.
		/// 
		/// @return	The result of computing the moment of order (n + m).
		double imageMoment (const Pattern& pattern, const unsigned int& p, const unsigned int& q, const double& xc=0.0, const double& yc=0.0) const;
		
		// Do not implement these methods, as they are only declared here to prevent objects to be copied. 
		FeatureExtractor (const FeatureExtractor&);
		FeatureExtractor& operator= (const FeatureExtractor&);
};


inline const std::vector<FeatureVector>& FeatureExtractor::featureVectors () const
{
	return featureVectors_;
};

inline const FeatureExtractorStatistics& FeatureExtractor::statistics () const
{
	return statistics_;
};

#endif


/// @file
/// @brief Definition of FeatureExtractor class

#include "FeatureExtractor.hpp"
#include <boost/timer.hpp>


FeatureExtractor::FeatureExtractor (const std::list<Region>& regions)
:	regions_(regions),
	statistics_(FeatureExtractorStatistics()),
	patterns_(std::vector<Pattern>(0))
{
};


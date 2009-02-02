/// @file
/// @brief Definition of FeatureExtractor class

#include "FeatureExtractor.hpp"
#include <boost/timer.hpp>
#include <string>
#include <sstream>


FeatureExtractor::FeatureExtractor (const std::list<Region>& regions)
:	regions_(regions),
	statistics_(FeatureExtractorStatistics()),
	patterns_(std::vector<Pattern>(0, Pattern(Region())))
{
	patterns_.reserve(regions_.size());
	unsigned int patternNo = 0;
	for ( std::list<Region>::iterator i = regions_.begin(); i != regions_.end(); ++i )
	{
		boost::timer timer;
		timer.restart();
		
		(*i).normalizeCoordinates();
		patterns_.push_back( Pattern(*i) );

		statistics_.patternsBuildingTime(timer.elapsed());

		std::string filename("pattern");
		std::ostringstream ostr;
		ostr << patternNo;
		filename.append(ostr.str());
		filename.append(".bmp");
		//patterns_.back().writeToOutputImage(filename);
		++patternNo;
	}
};


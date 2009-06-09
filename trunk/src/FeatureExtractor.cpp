/// @file
/// @brief Definition of FeatureExtractor class

#include "FeatureExtractor.hpp"
#include "Pattern.hpp"
#include "FeatureVector.hpp"
#include <boost/timer.hpp>
#include <cmath>


FeatureExtractor::FeatureExtractor ()
:	statistics_(),
	featureVectors_(0)
{}


void FeatureExtractor::computeMoments (const std::vector<Pattern>& patterns)
{
	boost::timer timer;
	timer.restart();

	featureVectors_.reserve(patterns.size());
	for ( std::vector<Pattern>::const_iterator i = patterns.begin(); i != patterns.end(); ++i )
	{
		FeatureVector fv(14);	// Initial value set to zero

		std::pair<unsigned int, unsigned int> centroid = i->centroid();

		fv.at(0) = centroid.first;
		fv.at(1) = centroid.second;
		
		for ( unsigned int j = 0; j < i->height(); ++j )
		{
			double tj2 = pow(j-centroid.first, 1);	// p = 1
			double tj3 = pow(j-centroid.first, 2);	// p = 2
			double tj4 = pow(j-centroid.first, 0);	// p = 0
			double tj5 = pow(j-centroid.first, 2);	// p = 2
			double tj6 = pow(j-centroid.first, 1);	// p = 1
			double tj7 = pow(j-centroid.first, 2);	// p = 2
			double tj8 = pow(j-centroid.first, 3);	// p = 3
			double tj9 = pow(j-centroid.first, 0);	// p = 0
			double tj10 = pow(j-centroid.first, 3);	// p = 3
			double tj11 = pow(j-centroid.first, 1);	// p = 1
			double tj12 = pow(j-centroid.first, 3);	// p = 3
			double tj13 = pow(j-centroid.first, 2);	// p = 2

			for (unsigned int k = 0; k < i->width(); ++k )
			{
				fv.at(2)	+= tj2	* pow(k-centroid.second, 1) * i->at(j,k);	// q = 1
				fv.at(3)	+= tj3	* pow(k-centroid.second, 0) * i->at(j,k);	// q = 0
				fv.at(4)	+= tj4	* pow(k-centroid.second, 2) * i->at(j,k);	// q = 2
				fv.at(5)	+= tj5	* pow(k-centroid.second, 1) * i->at(j,k);	// q = 1
				fv.at(6)	+= tj6	* pow(k-centroid.second, 2) * i->at(j,k);	// q = 2
				fv.at(7)	+= tj7	* pow(k-centroid.second, 2) * i->at(j,k);	// q = 2
				fv.at(8)	+= tj8	* pow(k-centroid.second, 0) * i->at(j,k);	// q = 0
				fv.at(9)	+= tj9	* pow(k-centroid.second, 3) * i->at(j,k);	// q = 3
				fv.at(10)	+= tj10	* pow(k-centroid.second, 1) * i->at(j,k);	// q = 1
				fv.at(11)	+= tj11	* pow(k-centroid.second, 3) * i->at(j,k);	// q = 3
				fv.at(12)	+= tj12	* pow(k-centroid.second, 2) * i->at(j,k);	// q = 2
				fv.at(13)	+= tj13	* pow(k-centroid.second, 3) * i->at(j,k);	// q = 3
			}
		}

		double area = i->area();
		if ( area == 0.0 )
			area = 1.0;

		fv.at(2) /= pow(area, ((1+1)/2) + 1);
		fv.at(3) /= pow(area, ((2+0)/2) + 1);
		fv.at(4) /= pow(area, ((0+2)/2) + 1);
		fv.at(5) /= pow(area, ((2+1)/2) + 1);
		fv.at(6) /= pow(area, ((1+2)/2) + 1);
		fv.at(7) /= pow(area, ((2+2)/2) + 1);
		fv.at(8) /= pow(area, ((3+0)/2) + 1);
		fv.at(9) /= pow(area, ((0+3)/2) + 1);
		fv.at(10) /= pow(area, ((3+1)/2) + 1);
		fv.at(11) /= pow(area, ((1+3)/2) + 1);
		fv.at(12) /= pow(area, ((3+2)/2) + 1);
		fv.at(13) /= pow(area, ((2+3)/2) + 1);

		featureVectors_.push_back(fv);
	}

	statistics_.momentsComputingTime(timer.elapsed());
}


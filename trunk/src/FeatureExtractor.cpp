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
		double xc = centroid.first;
		double yc = centroid.second;

		fv.at(0) = xc;
		fv.at(1) = yc;
		
		for ( unsigned int j = 0; j < i->height(); ++j )
		{
			double tj2 = pow(j-xc, 1);	// p = 1
			double tj3 = pow(j-xc, 2);	// p = 2
			double tj4 = pow(j-xc, 0);	// p = 0
			double tj5 = pow(j-xc, 2);	// p = 2
			double tj6 = pow(j-xc, 1);	// p = 1
			double tj7 = pow(j-xc, 2);	// p = 2
			double tj8 = pow(j-xc, 3);	// p = 3
			double tj9 = pow(j-xc, 0);	// p = 0
			double tj10 = pow(j-xc, 3);	// p = 3
			double tj11 = pow(j-xc, 1);	// p = 1
			double tj12 = pow(j-xc, 3);	// p = 3
			double tj13 = pow(j-xc, 2);	// p = 2

			for (unsigned int k = 0; k < i->width(); ++k )
			{
				double tk2 = pow(k-yc, 1);	// q = 1
				double tk3 = pow(k-yc, 0);	// q = 0
				double tk4 = pow(k-yc, 2);	// q = 2
				double tk5 = pow(k-yc, 1);	// q = 1
				double tk6 = pow(k-yc, 2);	// q = 2
				double tk7 = pow(k-yc, 2);	// q = 2
				double tk8 = pow(k-yc, 0);	// q = 0
				double tk9 = pow(k-yc, 3);	// q = 3
				double tk10 = pow(k-yc, 1);	// q = 1
				double tk11 = pow(k-yc, 3);	// q = 3
				double tk12 = pow(k-yc, 2);	// q = 2
				double tk13 = pow(k-yc, 3);	// q = 3

				fv.at(2)	+= tj2	* tk2	* i->at(j,k);
				fv.at(3)	+= tj3	* tk3	* i->at(j,k);
				fv.at(4)	+= tj4	* tk4	* i->at(j,k);
				fv.at(5)	+= tj5	* tk5	* i->at(j,k);
				fv.at(6)	+= tj6	* tk6	* i->at(j,k);
				fv.at(7)	+= tj7	* tk7	* i->at(j,k);
				fv.at(8)	+= tj8	* tk8	* i->at(j,k);
				fv.at(9)	+= tj9	* tk9	* i->at(j,k);
				fv.at(10)	+= tj10	* tk10	* i->at(j,k);
				fv.at(11)	+= tj11	* tk11	* i->at(j,k);
				fv.at(12)	+= tj12	* tk12	* i->at(j,k);
				fv.at(13)	+= tj13	* tk13	* i->at(j,k);
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


/// @file
/// @brief Definition of FeatureExtractor class

#include "FeatureExtractor.hpp"
#include "Pattern.hpp"
#include "FeatureVector.hpp"
#include <boost/timer.hpp>
#include <cmath>


FeatureExtractor::FeatureExtractor (const std::vector<Pattern>& patterns)
:	statistics_(),
	patterns_(patterns),
	featureVectors_(0)
{};


void FeatureExtractor::computeMoments ()
{
	boost::timer timer;
	timer.restart();

	featureVectors_.reserve(patterns_.size());
	for ( std::vector<Pattern>::iterator i = patterns_.begin(); i != patterns_.end(); ++i )
	{
		FeatureVector fv(27);

		double area = imageMoment(*i, 0, 0);
		if ( area == 0.0 )
			area = 1.0;

		std::pair<unsigned int, unsigned int> centroid = i->centroid();
		double xc = centroid.first;
		double yc = centroid.second;

		double eta11 = imageMoment(*i, 1, 1, xc, yc) / pow(area, ((1+1)/2) + 1);
		double eta20 = imageMoment(*i, 2, 0, xc, yc) / pow(area, ((2+0)/2) + 1);
		double eta02 = imageMoment(*i, 0, 2, xc, yc) / pow(area, ((0+2)/2) + 1);
		double eta21 = imageMoment(*i, 2, 1, xc, yc) / pow(area, ((2+1)/2) + 1);
		double eta12 = imageMoment(*i, 1, 2, xc, yc) / pow(area, ((1+2)/2) + 1);
		double eta22 = imageMoment(*i, 2, 2, xc, yc) / pow(area, ((2+2)/2) + 1);
		double eta30 = imageMoment(*i, 3, 0, xc, yc) / pow(area, ((3+0)/2) + 1);
		double eta03 = imageMoment(*i, 0, 3, xc, yc) / pow(area, ((0+3)/2) + 1);
		double eta31 = imageMoment(*i, 3, 1, xc, yc) / pow(area, ((3+1)/2) + 1);
		double eta13 = imageMoment(*i, 1, 3, xc, yc) / pow(area, ((1+3)/2) + 1);
		double eta32 = imageMoment(*i, 3, 2, xc, yc) / pow(area, ((3+2)/2) + 1);
		double eta23 = imageMoment(*i, 2, 3, xc, yc) / pow(area, ((2+3)/2) + 1);
		double eta33 = imageMoment(*i, 3, 3, xc, yc) / pow(area, ((3+3)/2) + 1);
		//double eta40 = imageMoment(*i, 4, 0, xc, yc) / pow(area, ((4+0)/2) + 1);
		//double eta04 = imageMoment(*i, 0, 4, xc, yc) / pow(area, ((0+4)/2) + 1);
		//double eta50 = imageMoment(*i, 5, 0, xc, yc) / pow(area, ((5+0)/2) + 1);
		//double eta05 = imageMoment(*i, 0, 5, xc, yc) / pow(area, ((0+5)/2) + 1);

		fv.at(0) = 0.0;	// m00
		fv.at(1) = xc;		// m10
		fv.at(2) = yc;		// m01
		fv.at(3) = eta11;	// m11
		fv.at(4) = eta20;	// m20
		fv.at(5) = eta02;	// m02
		fv.at(6) = eta21;	// m21
		fv.at(7) = eta12;	// m12
		fv.at(8) = eta22;	// m22
		fv.at(9) = 0.0;	// m30
		fv.at(10) = 0.0;	// m03
		fv.at(11) = 0.0;	// m31
		fv.at(12) = 0.0;	// m13
		fv.at(13) = eta32;	// m32
		fv.at(14) = eta23;	// m23
		fv.at(15) = 0.0;	// m33

		featureVectors_.push_back(fv);
	}

	try
	{
		statistics_.momentsComputingTime(timer.elapsed());
	}
	catch(...) {}
};


double FeatureExtractor::imageMoment (const Pattern& pattern, const unsigned int& p, const unsigned int& q, const double& xc, const double& yc) const
{
	double t = 0.0;
	for ( unsigned int i = 0; i < pattern.height(); ++i )
	{
		double ti = pow(i-xc, p);

		for (unsigned int j = 0; j < pattern.width(); ++j )
		{
			double tj = pow(j-yc, q);

			t += ti * tj * pattern.at(i,j);
		}
	}
	return t;
};

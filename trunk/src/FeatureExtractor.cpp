/// @file
/// @brief Definition of FeatureExtractor class

#include "FeatureExtractor.hpp"
#include "Pattern.hpp"
#include <boost/timer.hpp>
#include <cmath>


FeatureExtractor::FeatureExtractor (const std::vector<Pattern>& patterns)
:	statistics_(),
	patterns_(patterns),
	featureVectors_(0)
{
};


void FeatureExtractor::computeMoments (const unsigned int& n)
{
	boost::timer timer;
	timer.restart();

	featureVectors_.reserve(patterns_.size());
	for ( std::vector<Pattern>::iterator i = patterns_.begin(); i != patterns_.end(); ++i )
	{
		FeatureVector fv(n);

		double area = imageMoment(*i, 0, 0);

		double xc = imageMoment(*i, 1, 0) / area;
		double yc = imageMoment(*i, 0, 1) / area;
		
		double eta22 = imageMoment(*i, 2, 2, xc, yc) / pow(area, ((2+2)/2) + 1);
		double eta20 = imageMoment(*i, 2, 0, xc, yc) / pow(area, ((2+0)/2) + 1);
		double eta02 = imageMoment(*i, 0, 2, xc, yc) / pow(area, ((0+2)/2) + 1);
		double eta21 = imageMoment(*i, 2, 1, xc, yc) / pow(area, ((2+1)/2) + 1);
		double eta12 = imageMoment(*i, 1, 2, xc, yc) / pow(area, ((1+2)/2) + 1);
		double eta30 = imageMoment(*i, 3, 0, xc, yc) / pow(area, ((3+0)/2) + 1);
		double eta03 = imageMoment(*i, 0, 3, xc, yc) / pow(area, ((0+3)/2) + 1);
		double eta40 = imageMoment(*i, 4, 0, xc, yc) / pow(area, ((4+0)/2) + 1);
		double eta04 = imageMoment(*i, 0, 4, xc, yc) / pow(area, ((0+4)/2) + 1);

		fv.at(0) = eta22;
		fv.at(1) = eta20;
		fv.at(2) = eta02;
		fv.at(3) = eta21;
		fv.at(4) = eta12;
		fv.at(5) = eta30;
		fv.at(6) = eta03;
		fv.at(7) = eta40;
		fv.at(8) = eta04;
		
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

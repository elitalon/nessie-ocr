/// @file
/// @brief Definition of FeatureExtractor class

#include "FeatureExtractor.hpp"
#include "Region.hpp"
#include <boost/timer.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <cmath>


/// @brief	Auxiliary function for computing the scaled Tchebichef polynomial.
double beta (const unsigned int& n, const unsigned int& N)
{
	double a = boost::math::factorial<double>(2*n);
	double b = boost::math::binomial_coefficient<double>(N+n, 2*n+1);

	return sqrt(a*b);
};


///	@brief	Computes the expression of the modified Pochhammer symbol, suitable for simplifying the notation of other equations.
double modifiedPochhammerSymbol (const unsigned& a, const unsigned& k)
{
	if ( k == 0 )
		return 1.0;

	double tmp = a;
	for ( unsigned int i = 1; i <= (k+1); ++i )
		tmp = tmp * (tmp - i);

	return tmp;
};


///	@brief	Computes the discrete scaled Tchebichef polynomial of order n.
double scaledTchebichefPolynomial(const unsigned int& n, const unsigned int& x, const unsigned int& N)
{
	double t = 0.0;
	for ( unsigned int k = 0; k <= n; ++k )
	{
		double num = boost::math::factorial<double>(n+k);
		double den = boost::math::factorial<double>(n-k) * pow(boost::math::factorial<double>(k), 2);
		double B = (num / den) * modifiedPochhammerSymbol(n-N, n-k);

		t += B * modifiedPochhammerSymbol(x, k);
	}
	return t / beta(n, N);
};


///	@brief	Computes the standard 2D Tchebichef moment of order (n + m) of a pattern.
double tchebichefMoment (const Pattern& pattern, const unsigned int& n, const unsigned int& m)
{
	double t = 0.0;
	for ( unsigned int i = 0; i < pattern.height(); ++i )
	{
		double ti = scaledTchebichefPolynomial(n, i, pattern.height()) / beta(n, pattern.height());
		
		for (unsigned int j = 0; j < pattern.width(); ++j )
		{
			double tj = scaledTchebichefPolynomial(m, j, pattern.width()) / beta(m, pattern.width());

			t += ti * tj * pattern(i,j);
		}
	}
	return t;
};


FeatureExtractor::FeatureExtractor (const std::list<Region>& regions)
:	statistics_(),
	patterns_(0),
	featureVectors_(0)
{
	boost::timer timer;
	timer.restart();

	patterns_.reserve(regions.size());

	for ( std::list<Region>::const_iterator i = regions.begin(); i != regions.end(); ++i )
	{
		Region region(*i);
		region.normalizeCoordinates();
		patterns_.push_back( Pattern(region) );
	}

	try
	{
		statistics_.patternsBuildingTime(timer.elapsed());
	}
	catch(...) {}
};


void FeatureExtractor::computeMoments (const unsigned int& n)
{
	boost::timer timer;
	timer.restart();

	featureVectors_.reserve(patterns_.size());
	for ( std::vector<Pattern>::iterator i = patterns_.begin(); i != patterns_.end(); ++i )
	{
		FeatureVector fv(n);

		for( unsigned int j = 0; j < n; ++j )
		{
			if ( j == 0 )
				fv.at(j) = imageMoment(*i, j, j);
			else
			{
				unsigned int order = floor((j + 1.0) / 2.0);
				
				if ( j%2 == 1 )
				{
					if ( order == 1 )
						fv.at(j) = imageMoment(*i, order, 0) / fv.at(0);
					else
						fv.at(j) = imageMoment(*i, order, 0, fv.at(1), fv.at(2));
				}
				else
				{
					if ( order == 1 )
						fv.at(j) = imageMoment(*i, 0, order) / fv.at(0);
					else
						fv.at(j) = imageMoment(*i, 0, order, fv.at(1), fv.at(2));
				}
			}
		}
		
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

			t += ti * tj * pattern(i,j);
		}
	}
	return t;
};


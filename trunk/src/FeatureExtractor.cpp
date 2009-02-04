/// @file
/// @brief Definition of FeatureExtractor class

#include "FeatureExtractor.hpp"
#include <boost/timer.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <cmath>
#include <string>
#include <sstream>


/// @brief	Prints every pattern that has been built.
static void printPatterns (const std::vector<Pattern>& patterns)
{
	unsigned int patternNo = 0;
	for ( std::vector<Pattern>::const_iterator i = patterns.begin(); i != patterns.end(); ++i )
	{
		std::ostringstream ostr;
		ostr << patternNo++;
		std::string filename("pattern");
		filename.append(ostr.str().append(".bmp"));
		(*i).writeToOutputImage(filename,true);
	}
};


/// @brief	Auxiliary function for computing the scaled Tchebichef polynomials.
static double beta (const unsigned int& n, const unsigned int& N)
{
	using namespace boost::math;

	double tmp	= factorial<unsigned int>(n+N) / (factorial<unsigned int>(2*n + 1) * factorial<unsigned int>((n+N) - (2*n+1)));
	double ro	= factorial<unsigned int>(2*n) * tmp;	// Equation (8)

	return sqrt(ro);	// Equation (11)
};


///	@brief	Computes the expression of the modified Pochhammer symbol, suitable for simplifying the notation of other equations.
static double modifiedPochhammerSymbol (const unsigned& a, const unsigned& k)
{
	if ( k == 0 )
		return 1.0;

	double tmp = a;
	for ( unsigned int i = 1; i < (k+2); ++i )	// Equation (4)
		tmp *= tmp - i;

	return tmp;
};


///	@brief	Computes the discrete scaled Tchebichef polynomials of order n.
static double scaledTchebichefPolynomial(const unsigned int& n, const unsigned int& x, const unsigned int& N)
{
	using namespace boost::math;

	double t = 0.0;
	for ( unsigned int k = 0; k <= n; ++k )
	{
		double a = modifiedPochhammerSymbol(x,k);

		double B = modifiedPochhammerSymbol(n-N, n-k);
		double tmp = factorial<unsigned int>(n+k) / static_cast<double>(factorial<unsigned int>(n-k) * pow(factorial<unsigned int>(k),2));
		B = tmp * B;	// Equation (6)

		t += B * a;	// Equation (5)
	}

	return t / beta(n, N);	// Equation (9)
};


///	@brief	Computes the standard 2D Tchebichef moment of order (n + m) of a pattern.
static double tchebichefMoment (const Pattern& pattern, const unsigned int& n, const unsigned int& m)
{
	double t = 0.0;
	for ( unsigned int i = 0; i < pattern.height(); ++i )
	{
		for (unsigned int j = 0; j < pattern.width(); ++j )
		{
			double ti = scaledTchebichefPolynomial(n, i, pattern.height()) / beta(n, pattern.height());
			double tj = scaledTchebichefPolynomial(m, j, pattern.width()) / beta(m, pattern.width());

			t += ti * tj * pattern(i,j);	// Equation (12)
		}
	}
	return t;
};


FeatureExtractor::FeatureExtractor (const std::list<Region>& regions)
:	regions_(regions),
	statistics_(FeatureExtractorStatistics()),
	patterns_(std::vector<Pattern>(0, Pattern(Region()))),
	featureVectors_(std::vector<FeatureVector>(0, FeatureVector(9)))
{
	boost::timer timer;
	timer.restart();

	patterns_.reserve(regions_.size());

	for ( std::list<Region>::iterator i = regions_.begin(); i != regions_.end(); ++i )
	{
		(*i).normalizeCoordinates();
		patterns_.push_back( Pattern(*i) );
	}
	statistics_.patternsBuildingTime(timer.elapsed());
	printPatterns(this->patterns_);
};


void FeatureExtractor::computeMoments ()
{
	boost::timer timer;
	timer.restart();

	for ( std::vector<Pattern>::iterator k = patterns_.begin(); k != patterns_.end(); ++k )
	{
		double area = tchebichefMoment(*k, 0, 0);

		// Centroid coordinates
		unsigned int x0 = round(tchebichefMoment(*k, 1, 0) / area);	// x-axis
		unsigned int y0 = round(tchebichefMoment(*k, 0, 1) / area);	// y-axis

		// Variance
		tchebichefMoment(*k, 2, 0);
		tchebichefMoment(*k, 0, 2);

		// Skewness
		tchebichefMoment(*k, 0, 3);
		tchebichefMoment(*k, 3, 0);

		// Kurtosis
		tchebichefMoment(*k, 0, 4);
		tchebichefMoment(*k, 4, 0);
	}

	statistics_.momentsComputingTime(timer.elapsed());
};


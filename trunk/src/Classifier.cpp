///
/// @file
/// @brief Definition of Classifier class
///


#include "Classifier.hpp"
#include "Shape.hpp"

#include <cmath>
#include <algorithm>
#include <utility>
#include <boost/timer.hpp>
#include <iostream>




Classifier::Classifier (const DataSet& dataset)
	:	dataset_(dataset),
		sample_(FeatureVector(dataset.nFeatures())),
		matchingShapeTime_(0.0)
{
	
};



Classifier::~Classifier ()
{
	
};



std::string Classifier::matchShape (const Shape& shape)
{
	// Start timing
	boost::timer timer;
	timer.restart();
	
	this->buildFeatureVector(shape);
	
	// Compute euclidean distances with every sample in the training set
	std::deque< std::pair<double, unsigned int> > euclideanDistances(dataset_.size());
	
	for ( unsigned int i = 0; i < dataset_.size(); ++i )
	{
		DataSet::Sample referenceSample = dataset_.getSample(i);
		
		FeatureVector difference;
		difference = referenceSample.first - sample_;

		double term = 0.0;
		for ( unsigned int j = 0; j < dataset_.nFeatures(); ++j )
			term += pow(difference(j), 2);

		term = sqrt(term);
		
		euclideanDistances.at(i) = std::pair<double, unsigned int>(term, i);
	}
	std::cout << (*std::max_element(euclideanDistances.begin(), euclideanDistances.end())).first << std::endl;
	std::cout << (*std::max_element(euclideanDistances.begin(), euclideanDistances.end())).second << std::endl;
	//std::sort(euclideanDistances.begin(), euclideanDistances.end());
	
	
	// Compute the probability of classify a shape into a category
	unsigned int k = 5;
	std::deque<unsigned int> categoryFrequencies(256, 0);
	for ( unsigned int i = 0; i < k; ++i )
	{
		unsigned int category = euclideanDistances.at(i).second;	// Index within the data set of a k-neighbour
		
		categoryFrequencies.at(category) += 1.0;
	}
	
	// Get the most probably category (its ASCII code)
	std::deque<unsigned int>::iterator mostFrequentCategory = std::max_element(categoryFrequencies.begin(), categoryFrequencies.end());
	unsigned int categoryMatched = 0;
	
	std::deque<unsigned int>::iterator i = categoryFrequencies.begin();
	while ( i not_eq mostFrequentCategory )
	{
		++categoryMatched;
		++i;
	}
		
	// Gather elapsed time
	matchingShapeTime_ = timer.elapsed();
	
	
	std::cout << "Character matched: " << categoryMatched << std::endl;
	unsigned char asciiCode = categoryMatched;
	return std::string(1, asciiCode);
};



///
/// Computes the lambda factor to use in several equations related to image moments
/// 
/// @param p Order of the moment to use in rows
/// @param q Order of the moment to use in columns
/// 
/// @return (p+q/2) + 1
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-16
///
static double lambda (const unsigned int& p, const unsigned int& q)
{
	return 1.0 + ( (static_cast<double>(p+q)) / 2.0);
};



///
/// Computes the central moment of a shape
/// 
/// @param shape	Shape where get the pixels
/// @param p		Order of the moment to use in rows
/// @param q		Order of the moment to use in columns
/// @param x		Barycenter's X coordinate
/// @param y		Barycenter's Y coordinate
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-16
///
static double computeCentralMoment (const Shape& shape, const unsigned int& p, const unsigned int& q, const unsigned int& x, const unsigned int& y)
{
	double centralMoment = 0.0;

	for ( unsigned int i = 0; i < shape.size(); ++i )
		centralMoment += pow(shape(i).first - x, p) * pow(shape(i).second - y, q);
	
	return centralMoment;
};


void Classifier::buildFeatureVector (const Shape& shape)
{
	//
	// Compute the shape's barycenter coordinates
	//
	double m00 = 0.0;
	double m01 = 0.0;
	double m10 = 0.0;

	for ( unsigned int i = 0; i < shape.size(); ++i )
	{
		m00 += pow(shape(i).first, 0) * pow(shape(i).second, 0);
		m01 += pow(shape(i).first, 0) * pow(shape(i).second, 1);
		m10 += pow(shape(i).first, 1) * pow(shape(i).second, 0);
	}
	
	double barycenterXCoordinate = m10 / m00;
	double barycenterYCoordinate = m01 / m00;	
	
	
	//
	// Compute the normalized un-scaled central moments 
	//
	double u00 = computeCentralMoment(shape, 0, 0, barycenterXCoordinate, barycenterYCoordinate);
	double v20 = computeCentralMoment(shape, 2, 0, barycenterXCoordinate, barycenterYCoordinate) / pow(u00, lambda(2,0));
	double v02 = computeCentralMoment(shape, 0, 2, barycenterXCoordinate, barycenterYCoordinate) / pow(u00, lambda(0,2));
	double v11 = computeCentralMoment(shape, 1, 1, barycenterXCoordinate, barycenterYCoordinate) / pow(u00, lambda(1,1));
	double v12 = computeCentralMoment(shape, 1, 2, barycenterXCoordinate, barycenterYCoordinate) / pow(u00, lambda(1,2));
	double v21 = computeCentralMoment(shape, 2, 1, barycenterXCoordinate, barycenterYCoordinate) / pow(u00, lambda(2,1));
	double v03 = computeCentralMoment(shape, 0, 3, barycenterXCoordinate, barycenterYCoordinate) / pow(u00, lambda(0,3));
	double v30 = computeCentralMoment(shape, 3, 0, barycenterXCoordinate, barycenterYCoordinate) / pow(u00, lambda(3,0));
	
	
	//
	// Compute the final seven invariant moments
	// 
	double p1 = v20 + v02;
	std::cout << "I(1)                         : " << p1 << std::endl;
	
	double p2 = pow(v20 - v02, 2) + 4 * pow(v11, 2);
	std::cout << "I(2)                         : " << p2 << std::endl;
	
	double p3 = pow(v30 - 3 * v12, 2) + pow(3 * v21 - v03, 2);
	std::cout << "I(3)                         : " << p3 << std::endl;
	
	double p4 = pow(v30 + v12, 2) + pow(v21 + v03, 2);
	std::cout << "I(4)                         : " << p4 << std::endl;
	
	double p5 = (v30 - 3 * v12) * (v30 + v12) * (pow(v30 + v12, 2) - 3*pow(v21 + v03, 2)) +\
				(3 * v21 - v03) * (v21 + v03) * (3 * pow(v30 + v12, 2) - pow(v21 + v03, 2));
	std::cout << "I(5)                         : " << p5 << std::endl;
	
	double p6 = (v20 - v02) * (pow(v30 + v12, 2) - pow(v21 + v03, 2)) + 4 * v11 * (v30 + v12) * (v21 + v03);
	std::cout << "I(6)                         : " << p6 << std::endl;
	
	double p7 = (3 * v21 - v03) * (v30 + v12) * (pow(v30 + v12, 2) - 3*pow(v21 + v03, 2)) -\
				(v30 - 3 * v12) * (v21 + v03) * (3 * pow(v30 + v12, 2) - pow(v21 + v03, 2));
	std::cout << "I(7)                         : " << p7 << std::endl << std::endl;;
	
	switch (sample_.size())
	{
		case 1:
		{
			sample_(0) = p1;
			break;
		}
		case 2:
		{
			sample_(0) = p1;
			sample_(1) = p2;
			break;
		}
		case 3:
		{
			sample_(0) = p1;
			sample_(1) = p2;
			sample_(2) = p3;
			break;
		}
		case 4:
		{
			sample_(0) = p1;
			sample_(1) = p2;
			sample_(2) = p3;
			sample_(3) = p4;
			break;
		}
		case 5:
		{
			sample_(0) = p1;
			sample_(1) = p2;
			sample_(2) = p3;
			sample_(3) = p4;
			sample_(4) = p5;
			break;
		}
		case 6:
		{
			sample_(0) = p1;
			sample_(1) = p2;
			sample_(2) = p3;
			sample_(3) = p4;
			sample_(4) = p5;
			sample_(5) = p6;
			break;
		}
		default:
		{
			sample_(0) = p1;
			sample_(1) = p2;
			sample_(2) = p3;
			sample_(3) = p4;
			sample_(4) = p5;
			sample_(5) = p6;
			sample_(6) = p7;
			break;
		}
	}
};

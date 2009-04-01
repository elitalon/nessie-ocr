/// @file
/// @brief Definition of ClassifierStatistics class

#include "ClassifierStatistics.hpp"
#include <iostream>
#include <iomanip>


ClassifierStatistics::ClassifierStatistics ()
:	Statistics(),	// Invoke base class copy constructor.
	classificationTime_(0),
	hitRate_(0),
	missRate_(0)
{};


ClassifierStatistics::ClassifierStatistics (const ClassifierStatistics& statistics)
:	Statistics(),	// Invoke base class copy constructor.
	classificationTime_(0),
	hitRate_(0),
	missRate_(0)
{
	if ( statistics.classificationTime_.get() != 0 )
		classificationTime_.reset( new double (*statistics.classificationTime_.get() ));

	if ( statistics.hitRate_.get() != 0 )
		hitRate_.reset( new double (*statistics.hitRate_.get() ));

	if ( statistics.missRate_.get() != 0 )
		missRate_.reset( new double (*statistics.missRate_.get() ));
};


ClassifierStatistics::~ClassifierStatistics () {};


ClassifierStatistics& ClassifierStatistics::operator= (const ClassifierStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.classificationTime_.get() != 0 )
		classificationTime_.reset( new double (*statistics.classificationTime_.get() ));

	if ( statistics.hitRate_.get() != 0 )
		hitRate_.reset( new double (*statistics.hitRate_.get() ));

	if ( statistics.missRate_.get() != 0 )
		missRate_.reset( new double (*statistics.missRate_.get() ));

	return *this;
};


void ClassifierStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Classification stage statistics" << std::endl;

	if ( classificationTime_.get() != 0 )
		std::cout << "  - Classification time           : " << *classificationTime_.get() << " s" << std::endl;

	if ( hitRate_.get() != 0 )
		std::cout << "  - Hit rate                      : " << std::setprecision(2) << std::fixed << *hitRate_.get() << " %" << std::endl;

	if ( missRate_.get() != 0 )
		std::cout << "  - Miss rate                     : " << std::setprecision(2) << std::fixed << *missRate_.get() << " %" << std::endl;

	std::cout << "  - Total elapsed time            : " << totalTime_ << " s" << std::endl;
};


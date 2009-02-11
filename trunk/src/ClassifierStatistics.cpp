/// @file
/// @brief Definition of ClassifierStatistics class

#include "ClassifierStatistics.hpp"
#include <iostream>


ClassifierStatistics::ClassifierStatistics ()
:	Statistics(),	// Invoke base class copy constructor.
	charactersFound_(0),
	classificationTime_(0)
{};


ClassifierStatistics::ClassifierStatistics (const ClassifierStatistics& statistics)
:	Statistics(),	// Invoke base class copy constructor.
	charactersFound_(0),
	classificationTime_(0)
{
	if ( statistics.charactersFound_ != 0 )
		charactersFound_ = new unsigned int(*statistics.charactersFound_);

	if ( statistics.classificationTime_ != 0 )
		classificationTime_ = new double(*statistics.classificationTime_);
};


ClassifierStatistics::~ClassifierStatistics ()
{
	delete charactersFound_;
	delete classificationTime_;
};


ClassifierStatistics& ClassifierStatistics::operator= (const ClassifierStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.charactersFound_ != 0 )
	{
		unsigned int* tmp = new unsigned int(*statistics.charactersFound_);
		delete charactersFound_;
		charactersFound_ = tmp;
	}

	if ( statistics.classificationTime_ != 0 )
	{
		double* tmp = new double(*statistics.classificationTime_);
		delete classificationTime_;
		classificationTime_ = tmp;
	}

	return *this;
};


void ClassifierStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Classification stage statistics" << std::endl;

	if ( charactersFound_ != 0 )
		std::cout << "  - Characters found             : " << *charactersFound_ << std::endl;

	if ( classificationTime_ != 0 )
		std::cout << "  - Classification time          : " << *classificationTime_ << std::endl;

	std::cout << "  - Total elapsed time           : " << totalTime_ << std::endl;
};


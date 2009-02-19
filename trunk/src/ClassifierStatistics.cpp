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
	if ( statistics.charactersFound_.get() != 0 )
		charactersFound_.reset( new unsigned int (*statistics.charactersFound_.get() ));
	
	if ( statistics.classificationTime_.get() != 0 )
		classificationTime_.reset( new double (*statistics.classificationTime_.get() ));
};


ClassifierStatistics::~ClassifierStatistics () {};


ClassifierStatistics& ClassifierStatistics::operator= (const ClassifierStatistics& statistics)
{
	Statistics::operator=(statistics);	// Assign base class parts

	if ( statistics.charactersFound_.get() != 0 )
		charactersFound_.reset( new unsigned int (*statistics.charactersFound_.get() ));
	
	if ( statistics.classificationTime_.get() != 0 )
		classificationTime_.reset( new double (*statistics.classificationTime_.get() ));

	return *this;
};


void ClassifierStatistics::print () const
{
	std::cout << std::endl;
	std::cout << "Classification stage statistics" << std::endl;

	if ( charactersFound_.get() != 0 )
		std::cout << "  - Characters found             : " << *charactersFound_.get() << std::endl;

	if ( classificationTime_.get() != 0 )
		std::cout << "  - Classification time          : " << *classificationTime_.get() << std::endl;

	std::cout << "  - Total elapsed time           : " << totalTime_ << std::endl;
};


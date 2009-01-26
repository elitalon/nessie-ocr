/// @file
/// @brief Definition of Region class

#include "Region.hpp"
#include <algorithm>


Region::Region ()
	:	coordinates_(std::vector<PixelCoordinates>(0)),
		size_(0)
{};


unsigned int Region::height () const
{
	std::vector<unsigned int> rowCoordinates(0);
	rowCoordinates.reserve(size_);

	for ( std::vector<PixelCoordinates>::const_iterator i = coordinates_.begin(); i not_eq coordinates_.end(); ++i )
		rowCoordinates.push_back((*i).first);

	std::sort(rowCoordinates.begin(), rowCoordinates.end());
	return rowCoordinates.back() - rowCoordinates.front() + 1;
};


unsigned int Region::width () const
{
	std::vector<unsigned int> columnCoordinates(0);
	columnCoordinates.reserve(size_);

	for ( std::vector<PixelCoordinates>::const_iterator i = coordinates_.begin(); i not_eq coordinates_.end(); ++i )
		columnCoordinates.push_back((*i).second);

	std::sort(columnCoordinates.begin(), columnCoordinates.end());
	return columnCoordinates.back() - columnCoordinates.front() + 1;
};


void Region::addCoordinates (const PixelCoordinates& coordinates)
{
	coordinates_.push_back( coordinates );
	size_ = coordinates_.size();
};


PixelCoordinates Region::topLeftmostPixelCoordinates () const
{
	std::vector<unsigned int> rowCoordinates(0);
	std::vector<unsigned int> columnCoordinates(0);
	rowCoordinates.reserve(size_);
	columnCoordinates.reserve(size_);

	for ( std::vector<PixelCoordinates>::const_iterator i = coordinates_.begin(); i not_eq coordinates_.end(); ++i )
	{
		rowCoordinates.push_back((*i).first);
		columnCoordinates.push_back((*i).second);
	}

	std::sort(rowCoordinates.begin(), rowCoordinates.end());
	std::sort(columnCoordinates.begin(), columnCoordinates.end());
	
	return PixelCoordinates(rowCoordinates.front(), columnCoordinates.front());
};


void Region::normalizeCoordinates ()
{
	unsigned int x0 = topLeftmostPixelCoordinates().first;
	unsigned int y0 = topLeftmostPixelCoordinates().second;
		
	for ( std::vector<PixelCoordinates>::iterator i = coordinates_.begin(); i not_eq coordinates_.end(); ++i )
	{
		(*i).first	= (*i).first	- x0;
		(*i).second	= (*i).second	- y0;
	}
};


bool Region::operator< (const Region& region) const
{
	// Compute the top pixel row of "this" region.
	std::vector<unsigned int> thisRowCoordinates(0);
	thisRowCoordinates.reserve(this->size_);

	for ( std::vector<PixelCoordinates>::const_iterator i = this->coordinates_.begin(); i not_eq this->coordinates_.end(); ++i )
		thisRowCoordinates.push_back((*i).first);

	std::sort(thisRowCoordinates.begin(), thisRowCoordinates.end());

	// Compute the bottom pixel coordinates of input region.
	std::vector<unsigned int> inputRowCoordinates(0);
	inputRowCoordinates.reserve(region.size_);

	for ( std::vector<PixelCoordinates>::const_iterator i = region.coordinates_.begin(); i not_eq region.coordinates_.end(); ++i )
		inputRowCoordinates.push_back((*i).first);

	std::sort(inputRowCoordinates.begin(), inputRowCoordinates.end());

	if ( thisRowCoordinates.back() < inputRowCoordinates.front() )
		return true;
	else
		return (this->topLeftmostPixelCoordinates().second < region.topLeftmostPixelCoordinates().second);
};


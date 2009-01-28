/// @file
/// @brief Definition of Region class

#include "Region.hpp"
#include <algorithm>


Region::Region ()
	:	coordinates_(std::vector<PixelCoordinates>(0)),
		height_(0),
		width_(0),
		size_(0),
		topLeftmostPixelCoordinates_(PixelCoordinates(0,0)),
		topBorderRow_(0),
		bottomBorderRow_(0),
		leftBorderColumn_(0),
		rightBorderColumn_(0)
{};


void Region::addCoordinates (const PixelCoordinates& coordinates)
{
	coordinates_.push_back( coordinates );
	size_ = coordinates_.size();

	if ( size_ > 1 )
	{
		topBorderRow_		= std::min( topBorderRow_, coordinates.first );
		bottomBorderRow_	= std::max( bottomBorderRow_, coordinates.first );
		leftBorderColumn_	= std::min( leftBorderColumn_, coordinates.second );
		rightBorderColumn_	= std::max( rightBorderColumn_, coordinates.second );
	}
	else
	{
		topBorderRow_		= coordinates.first;
		bottomBorderRow_	= coordinates.first;
		leftBorderColumn_	= coordinates.second;
		rightBorderColumn_	= coordinates.second;
	}

	height_ = bottomBorderRow_ - topBorderRow_ + 1;
	width_	= rightBorderColumn_ - leftBorderColumn_ + 1;

	topLeftmostPixelCoordinates_ = PixelCoordinates(topBorderRow_, leftBorderColumn_);
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


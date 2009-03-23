/// @file
/// @brief Definition of Region class

#include "Region.hpp"
#include <algorithm>


Region::Region ()
:	coordinates_(0),
	height_(0),
	width_(0),
	size_(0),
	topLeftmostPixelCoordinates_(0,0),
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
	unsigned int x0 = topLeftmostPixelCoordinates_.first;
	unsigned int y0 = topLeftmostPixelCoordinates_.second;

	for ( std::vector<PixelCoordinates>::iterator i = coordinates_.begin(); i != coordinates_.end(); ++i )
	{
		i->first	= i->first	- x0;
		i->second	= i->second	- y0;
	}

	if ( size_ > 1 )
	{
		std::vector<unsigned int> rowCoordinates(0);
		rowCoordinates.reserve(size_);

		std::vector<unsigned int> columnCoordinates(0);
		columnCoordinates.reserve(size_);

		for ( std::vector<PixelCoordinates>::iterator i = coordinates_.begin(); i != coordinates_.end(); ++i )
		{
			rowCoordinates.push_back(i->first);
			columnCoordinates.push_back(i->second);
		}

		std::sort(rowCoordinates.begin(), rowCoordinates.end());
		std::sort(columnCoordinates.begin(), columnCoordinates.end());

		topBorderRow_		= rowCoordinates.front();
		bottomBorderRow_	= rowCoordinates.back();
		leftBorderColumn_	= columnCoordinates.front();
		rightBorderColumn_	= columnCoordinates.back();
	}
	else
	{
		topBorderRow_		= coordinates_.front().first;
		bottomBorderRow_	= coordinates_.front().first;
		leftBorderColumn_	= coordinates_.front().second;
		rightBorderColumn_	= coordinates_.front().second;
	}

	height_ = bottomBorderRow_ - topBorderRow_ + 1;
	width_	= rightBorderColumn_ - leftBorderColumn_ + 1;
	size_	= coordinates_.size();

	topLeftmostPixelCoordinates_ = PixelCoordinates(topBorderRow_, leftBorderColumn_);
};


Region Region::operator+ (const Region& region) const
{
	Region temp;

	for ( std::vector<PixelCoordinates>::const_iterator i = this->coordinates_.begin(); i != coordinates_.end(); ++i )
		temp.addCoordinates(*i);

	for ( std::vector<PixelCoordinates>::const_iterator i = region.coordinates_.begin(); i != region.coordinates_.end(); ++i )
		temp.addCoordinates(*i);

	return temp;
};


bool Region::operator< (const Region& region) const
{
	if ( this->bottomBorderRow_ < region.topBorderRow_ )
		return true;
	else
	{
		if ( region.bottomBorderRow_ < this->topBorderRow_ )
			return false;
		else
			return ( this->topLeftmostPixelCoordinates_.second < region.topLeftmostPixelCoordinates_.second );
	}
};


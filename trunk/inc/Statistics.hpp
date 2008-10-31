///
/// @file
/// @brief Declaration of Statistics class
///

#if !defined(_STATISTICS_H)
#define _STATISTICS_H



///
/// Statistical data regarding the text recognition process.
/// 
/// This class stores a various statistical information regarding the elapsed time during the text recognition process,
/// accumulated internally mostly in algorithms.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-08
/// 
class Statistics
{
public:
	///
	/// Constructor.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-04
	///
	Statistics ();


	///
	/// Allows the sum of times stored in two different statistics.
	/// 
	/// @param statistics A set of statistical data as the second operand.
	/// 
	/// @return A new set of statistical data as a result of summing the time parameters of both objects each other
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-22
	///
	Statistics operator+ (const Statistics& statistics) const;


	///
	/// Allows the subtraction of two different statistics.
	/// 
	/// @param statistics A set of statistical data as the second operand.
	/// 
	/// @return A new set of statistical data as a result of subtracting the time parameters of both objects each other
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-22
	///
	Statistics operator- (const Statistics& statistics) const;


	///
	/// Returns the elapsed time in the reference gray level of the background finding algorithm
	///
	/// @return Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& backgroundReferenceGrayLevelFindingTime () const;


	///
	/// Returns the elapsed time in the optimal threshold computing algorithm
	///
	/// @return Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& optimalThresholdComputingTime () const;


	///
	/// Returns the elapsed time in the noise removal algorithm
	///
	/// @return Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& noiseRemovalTime () const;		


	///
	/// Returns the total elapsed time within the preprocessing stage
	///
	/// @return Total elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& preprocessingTime () const;


	///
	/// Returns the elapsed time while applying the thresholding algorithm.
	/// 
	/// @return Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& thresholdingTime () const;


	///
	/// Returns the elapsed time while finding the shapes in a clip
	/// 
	/// @return Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& shapesFindingTime () const;


	///
	/// Returns the total elapsed time within the segmentation stage
	///
	/// @return Total elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	const float& segmentationTime () const;


private:

	friend class	Recognizer;									///< Declares the class Recognizer as friend
	
	float			backgroundReferenceGrayLevelFindingTime_;	///< Elapsed time in the reference gray level of the background finding algorithm
	
	float			optimalThresholdComputingTime_;				///< Elapsed time in the optimal threshold computing algorithm

	float			noiseRemovalTime_;							///< Elapsed time in the noise removal algorithm

	float			preprocessingTime_;							///< Total elapsed time within the preprocessing stage

	float			thresholdingTime_;							///< Elapsed time while applying the thresholding algorithm

	float			shapesFindingTime_;							///< Elapsed time while finding the shapes in a clip

	float			segmentationTime_;							///< Total elapsed time within the segmentation stage


	///
	/// Sets the elapsed time in the reference gray level of the background finding algorithm.
	/// 
	/// @param	time	Elapsed time in seconds
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-06
	///
	void backgroundReferenceGrayLevelFindingTime (const float& time);


	///
	/// Sets the elapsed time in the optimal threshold computing algorithm
	///
	/// @param	time	Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-06
	///
	void optimalThresholdComputingTime (const float& time);


	///
	/// Sets the elapsed time in the noise removal algorithm
	///
	/// @param	time	Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-06
	///
	void noiseRemovalTime (const float& time);


	///
	/// Sets the elapsed time in the thresholding algorithm
	///
	/// @param	time	Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	void thresholdingTime (const float& time);


	///
	/// Sets the elapsed time in the shapes finding algorithm
	///
	/// @param	time	Elapsed time in seconds
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-10-13
	///
	void shapesFindingTime (const float& time);
};




inline Statistics Statistics::operator+ (const Statistics& statistics) const
{
	Statistics temp;

	temp.backgroundReferenceGrayLevelFindingTime_	= this->backgroundReferenceGrayLevelFindingTime_	+ statistics.backgroundReferenceGrayLevelFindingTime_;
	temp.optimalThresholdComputingTime_				= this->optimalThresholdComputingTime_				+ statistics.optimalThresholdComputingTime_;
	temp.noiseRemovalTime_							= this->noiseRemovalTime_	+ statistics.noiseRemovalTime_;
	temp.preprocessingTime_							= this->preprocessingTime_	+ statistics.preprocessingTime_;
	temp.thresholdingTime_							= this->thresholdingTime_	+ statistics.thresholdingTime_;
	temp.shapesFindingTime_							= this->shapesFindingTime_	+ statistics.shapesFindingTime_;
	temp.segmentationTime_							= this->segmentationTime_	+ statistics.segmentationTime_;

	return (temp);
};


inline Statistics Statistics::operator- (const Statistics& statistics) const
{
	Statistics temp;

	temp.backgroundReferenceGrayLevelFindingTime_	= this->backgroundReferenceGrayLevelFindingTime_	- statistics.backgroundReferenceGrayLevelFindingTime_;
	temp.optimalThresholdComputingTime_				= this->optimalThresholdComputingTime_				- statistics.optimalThresholdComputingTime_;
	temp.noiseRemovalTime_							= this->noiseRemovalTime_	- statistics.noiseRemovalTime_;
	temp.preprocessingTime_							= this->preprocessingTime_	- statistics.preprocessingTime_;
	temp.thresholdingTime_							= this->thresholdingTime_	- statistics.thresholdingTime_;
	temp.shapesFindingTime_							= this->shapesFindingTime_	- statistics.shapesFindingTime_;
	temp.segmentationTime_							= this->segmentationTime_	- statistics.segmentationTime_;

	return (temp);
};


inline const float& Statistics::backgroundReferenceGrayLevelFindingTime () const
{
	return backgroundReferenceGrayLevelFindingTime_;
};


inline const float& Statistics::optimalThresholdComputingTime () const
{
	return optimalThresholdComputingTime_;
};


inline const float& Statistics::noiseRemovalTime () const
{
	return noiseRemovalTime_;
};


inline const float& Statistics::preprocessingTime () const
{
	return preprocessingTime_;
};


inline const float& Statistics::thresholdingTime () const
{
	return thresholdingTime_;
};


inline const float& Statistics::shapesFindingTime () const
{
	return shapesFindingTime_;
};


inline const float& Statistics::segmentationTime () const
{
	return segmentationTime_;
};

inline void Statistics::backgroundReferenceGrayLevelFindingTime (const float& time)
{
	backgroundReferenceGrayLevelFindingTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


inline void Statistics::optimalThresholdComputingTime (const float& time)
{
	optimalThresholdComputingTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


inline void Statistics::noiseRemovalTime (const float& time)
{
	noiseRemovalTime_ = time;
	
	preprocessingTime_ = backgroundReferenceGrayLevelFindingTime_ + optimalThresholdComputingTime_ + noiseRemovalTime_;
};


inline void Statistics::thresholdingTime (const float& time)
{
	thresholdingTime_ = time;
	
	segmentationTime_ = thresholdingTime_ + shapesFindingTime_;
};


inline void Statistics::shapesFindingTime (const float& time)
{
	shapesFindingTime_ = time;
	
	segmentationTime_ = thresholdingTime_ + shapesFindingTime_;
};


#endif  //_STATISTICS_H

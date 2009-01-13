/// @file
/// @brief Declaration of Statistics class

#if !defined(_STATISTICS_H)
#define _STATISTICS_H



///
/// Statistical data regarding the text recognition process.
///
/// This abstract base class provides a common interface for every stage of the recognition process, allowing the redefinition of the class
/// so that derived classes can be customized according to the stage the belong. The statitical data is gathered mostly in internal algorithms,
/// and provides the elapsed time among other parameters.
/// 
/// @see PreprocessorStatistics, FeatureExtractionStatistics, ClassificationStatistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class Statistics
{
public:
	
	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	explicit Statistics ();
	
	
	///
	/// Destructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	virtual ~Statistics ();
	
	
	///
	/// Prints the statistical data gathered during the text recognition process.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	virtual const void print () const = 0;
		
protected:

	double totalTime_;	///< Total elapsed time during stage execution.
	
	
	///
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	virtual const void updateTotalTime () = 0;
};



///
/// Statistical data regarding the preprocessing stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class PreprocessorStatistics : public Statistics
{
public:
	
	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	explicit PreprocessorStatistics ();
	
	
	///
	/// Destructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	virtual ~PreprocessorStatistics ();
	
	
	///
	/// Prints the statistical data gathered.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	const void print () const;
	
	
	///
	/// Sets the press clip size in number of pixels.
	/// 
	/// @param nPixels A number representing the number of pixels.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	const void clipSize (const unsigned int& nPixels);
	
	
	///
	/// Sets the elapsed time while executing the global thresholding algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	const void globalThresholdingTime (const double& elapsedTime);
	
private:
	
	unsigned int	clipSize_;					///< Press clip size in number of pixels.
	
	double			globalThresholdingTime_;	///< Elapsed time during execution of global thresholding algorithm.
	
	///
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	const void updateTotalTime ();
};

inline const void PreprocessorStatistics::updateTotalTime ()
{
	totalTime_ = globalThresholdingTime_;
};

inline const void PreprocessorStatistics::clipSize (const unsigned int& nPixels)
{
	clipSize_ = nPixels;
};

inline const void PreprocessorStatistics::globalThresholdingTime (const double& elapsedTime)
{
	globalThresholdingTime_ = elapsedTime;
	updateTotalTime();
};



///
/// Statistical data regarding the feature extraction stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class FeatureExtractionStatistics : public Statistics
{
public:
	
	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	explicit FeatureExtractionStatistics ();
	
	
	///
	/// Destructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	virtual ~FeatureExtractionStatistics ();
	
	
	///
	/// Prints the statistical data gathered.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	const void print () const;

private:
	
	///
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	const void updateTotalTime ();
};

inline const void FeatureExtractionStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;
};



///
/// Statistical data regarding the classification stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class ClassificationStatistics : public Statistics
{
public:
	
	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	explicit ClassificationStatistics ();
	
	
	///
	/// Destructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	virtual ~ClassificationStatistics ();
	
	
	///
	/// Prints the statistical data gathered.
	/// 
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	const void print () const;
	
private:
	
	///
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	const void updateTotalTime ();
};

inline const void ClassificationStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;
};

#endif  //_STATISTICS_H

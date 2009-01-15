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
	virtual void print () const = 0;
		
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
	virtual void updateTotalTime () = 0;
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
	void print () const;
	
	///
	/// Sets the press clip size in number of pixels.
	/// 
	/// @param nPixels A number representing the number of pixels.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	void clipSize (const unsigned int& nPixels);
	
	///
	/// Sets the optimal threshold used to binrize the press clip.
	/// 
	/// @param threshold A number representing the threshold gray level.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	void optimalThreshold (const unsigned char& threshold);
	
	///
	/// Sets the elapsed time while executing the global thresholding algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	void globalThresholdingTime (const double& elapsedTime);
	
	///
	/// Sets the elapsed time while executing the template filtering algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	void templateFilteringTime (const double& elapsedTime);
	
	///
	/// Sets the elapsed time while executing the averaging filtering algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	void averagingFilteringTime (const double& elapsedTime);

	///
	/// Sets the elapsed time while executing the skewness correction algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-15
	///
	void skewnessCorrectionTime (const double& elapsedTime);

private:
	
	unsigned int	clipSize_;					///< Press clip size in number of pixels.
	
	unsigned char	optimalThreshold_;			///< Optimal threshold to binarize the press clip.
	
	double			globalThresholdingTime_;	///< Elapsed time during execution of global thresholding algorithm.
	
	double			templateFilteringTime_;		///< Elapsed time while smoothing and noise removal by applying the template filtering algorithm.
	
	double			averagingFilteringTime_;	///< Elapsed time while smoothing and noise removal by applying the averaging filtering algorithm.
	
	double			skewnessCorrectionTime_;	///< Elapsed time while correcting the skewness of the text lines in a press clip.
	
	///
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	void updateTotalTime ();
};


inline void PreprocessorStatistics::updateTotalTime ()
{
	totalTime_ = globalThresholdingTime_ + templateFilteringTime_ + averagingFilteringTime_;
};


inline void PreprocessorStatistics::clipSize (const unsigned int& nPixels)
{
	clipSize_ = nPixels;
};


inline void PreprocessorStatistics::optimalThreshold (const unsigned char& threshold)
{
	optimalThreshold_ = threshold;
};


inline void PreprocessorStatistics::globalThresholdingTime (const double& elapsedTime)
{
	globalThresholdingTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::templateFilteringTime (const double& elapsedTime)
{
	templateFilteringTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::averagingFilteringTime (const double& elapsedTime)
{
	averagingFilteringTime_ = elapsedTime;
	updateTotalTime();
};

inline void PreprocessorStatistics::skewnessCorrectionTime (const double& elapsedTime)
{
	skewnessCorrectionTime_ = elapsedTime;
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
	void print () const;

private:
	
	///
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	void updateTotalTime ();
};


inline void FeatureExtractionStatistics::updateTotalTime ()
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
	void print () const;
	
private:
	
	///
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	/// 
	/// @author	Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-13
	///
	void updateTotalTime ();
};


inline void ClassificationStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;
};

#endif  //_STATISTICS_H

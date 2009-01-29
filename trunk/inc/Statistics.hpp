/// @file
/// @brief Declaration of Statistics class

#if !defined(_STATISTICS_H)
#define _STATISTICS_H


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
	
	/// Constructor.
	explicit Statistics ();
	
	/// Destructor.
	virtual ~Statistics ();
	
	/// Prints the statistical data gathered during the text recognition process.
	virtual void print () const = 0;
		
protected:

	double totalTime_;	///< Total elapsed time during stage execution.
	
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	virtual void updateTotalTime () = 0;
};



/// Statistical data regarding the preprocessing stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class PreprocessorStatistics : public Statistics
{
public:
	
	/// Constructor.
	explicit PreprocessorStatistics ();
	
	/// Destructor.
	virtual ~PreprocessorStatistics ();
	
	/// Prints the statistical data gathered.
	void print () const;
	
	/// Sets the press clip size in number of pixels.
	/// 
	/// @param nPixels A number representing the number of pixels.
	void clipSize (const unsigned int& nPixels);
	
	/// Sets the optimal threshold used to binrize the press clip.
	/// 
	/// @param threshold A number representing the threshold gray level.
	void optimalThreshold (const unsigned char& threshold);
	
	/// Sets the elapsed time while executing the global thresholding algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	void globalThresholdingTime (const double& elapsedTime);
	
	/// Sets the elapsed time while executing the template filtering algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	void templateFilteringTime (const double& elapsedTime);
	
	/// Sets the elapsed time while executing the averaging filtering algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	void averagingFilteringTime (const double& elapsedTime);

	/// Sets the elapsed time while executing the regions extraction algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	void regionsExtractionTime (const double& elapsedTime);

	/// Sets the number of regions found before merging the accents while executing the regions extraction algorithm.
	/// 
	/// @param nRegions Number of regions found.
	void nRegionsBeforeMerging (const unsigned int& nRegions);

	/// Sets the number of regions found after merging the accents while executing the regions extraction algorithm.
	/// 
	/// @param nRegions Number of regions found.
	void nRegionsAfterMerging (const unsigned int& nRegions);
	
	/// Sets the number of line delimiters found while executing the regions extraction algorithm.
	/// 
	/// @param nDelimiters Number of line delimiters found.
	void nLineDelimiters (const unsigned int& nDelimiters);

	/// Sets the slant angle estimation used to correct the slanting of every region found after executing the regions extraction algorithm.
	/// 
	/// @param angle Angle estimation in degrees.
	void slantAngleEstimation (const double& angle);

	/// Sets the elapsed time while executing the slanting correction algorithm.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	void slantingCorrectionTime (const double& elapsedTime);

	/// Sets the number of spaces between words found in text after post-processing the list of regions.
	///
	///	@param nSpaces A number representing the spaces found.
	void spacesBetweenWords (const unsigned int& nSpaces);
	
	/// Sets the mean interregion space found in text after post-processing the list of regions.
	///
	///	@param nPixels A number representing the mean value found.
	void meanInterRegionSpace (const double& nPixels);

	/// Sets the elapsed time while finding the spaces location in text.
	/// 
	/// @param elapsedTime A number representing the elapsed time in seconds.
	void spacesLocationFindingTime (const double& elapsedTime);

private:
	
	unsigned int	clipSize_;					///< Press clip size in number of pixels.
	
	unsigned char	optimalThreshold_;			///< Optimal threshold to binarize the press clip.
	
	double			globalThresholdingTime_;	///< Elapsed time during execution of global thresholding algorithm.
	
	double			templateFilteringTime_;		///< Elapsed time while smoothing and noise removal by applying the template filtering algorithm.
	
	double			averagingFilteringTime_;	///< Elapsed time while smoothing and noise removal by applying the averaging filtering algorithm.
	
	double			regionsExtractionTime_;		///< Elapsed time while extracting the regions of ink pixels applying a segmentation process over the press clip.
	
	unsigned int	nRegionsBeforeMerging_;		///< Number of regions of pixels found before merging accents while applying a segmentation process over the clip.
	
	unsigned int	nRegionsAfterMerging_;		///< Number of regions of pixels found after merging accents while applying a segmentation process over the clip.
	
	unsigned int	nLineDelimiters_;			///< Number of line delimiters found while applying a segmentation process over the clip.
	
	double			slantAngleEstimation_;		///< Angle estimation in degrees to correct the slanting in characters.
	
	double			slantingCorrectionTime_;	///< Elapsed time while correcting the slanting of every region found after the region extraction algorithm.

	unsigned int	spacesBetweenWords_;		///< Number of spaces between words found in text after post-processing the list of regions.

	double			meanInterRegionSpace_;		///< Mean interregion space found in text after post-processing the list of regions.

	double			spacesLocationFindingTime_;	///< Elapsed time while finding the spaces location in text.

	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	void updateTotalTime ();
};


inline void PreprocessorStatistics::updateTotalTime ()
{
	totalTime_ = globalThresholdingTime_ + templateFilteringTime_ + averagingFilteringTime_ + regionsExtractionTime_ + slantingCorrectionTime_\
				 + spacesLocationFindingTime_;
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


inline void PreprocessorStatistics::regionsExtractionTime (const double& elapsedTime)
{
	regionsExtractionTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::nRegionsBeforeMerging (const unsigned int& nRegions)
{
	nRegionsBeforeMerging_ = nRegions;
};


inline void PreprocessorStatistics::nRegionsAfterMerging (const unsigned int& nRegions)
{
	nRegionsAfterMerging_ = nRegions;
};


inline void PreprocessorStatistics::nLineDelimiters (const unsigned int& nDelimiters)
{
	nLineDelimiters_ = nDelimiters;
};


inline void PreprocessorStatistics::slantAngleEstimation (const double& angle)
{
	slantAngleEstimation_ = angle;
};


inline void PreprocessorStatistics::slantingCorrectionTime (const double& elapsedTime)
{
	slantingCorrectionTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::spacesBetweenWords (const unsigned int& nSpaces)
{
	spacesBetweenWords_ = nSpaces;
};


inline void PreprocessorStatistics::meanInterRegionSpace (const double& nPixels)
{
	meanInterRegionSpace_ = nPixels;
};


inline void PreprocessorStatistics::spacesLocationFindingTime (const double& elapsedTime)
{
	spacesLocationFindingTime_ = elapsedTime;
	updateTotalTime();
};



/// Statistical data regarding the feature extraction stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class FeatureExtractionStatistics : public Statistics
{
public:
	
	/// Constructor.
	explicit FeatureExtractionStatistics ();	
	
	/// Destructor.
	virtual ~FeatureExtractionStatistics ();
	
	/// Prints the statistical data gathered.
	void print () const;

private:
	
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	void updateTotalTime ();
};


inline void FeatureExtractionStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;
};



/// Statistical data regarding the classification stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class ClassificationStatistics : public Statistics
{
public:
	
	/// Constructor.
	explicit ClassificationStatistics ();	
	
	/// Destructor.
	virtual ~ClassificationStatistics ();
	
	/// Prints the statistical data gathered.
	void print () const;
	
private:
	
	/// Updates the total elapsed time attribute.
	/// 
	/// @post #totalTime_ is set by summing all the timers attributes within the class.
	void updateTotalTime ();
};


inline void ClassificationStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;
};

#endif  //_STATISTICS_H


/// @file
/// @brief Declaration of Statistics class

#if !defined(_STATISTICS_H)
#define _STATISTICS_H


/// @brief	Statistical data gathered during the text recognition process.
///
/// @details	This abstract base class provides a common interface for every stage of the recognition process, allowing its redefinition
/// so that derived classes can be customized according to the stage they belong. The statitical data is gathered mostly in internal algorithms,
/// and provides time results among other parameters.
/// 
/// @see	PreprocessorStatistics, FeatureExtractionStatistics, ClassificationStatistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class Statistics
{
	public:

		/// @brief	Constructor.
		explicit Statistics ();

		/// @brief	Destructor.
		virtual ~Statistics ();

		/// @brief	Prints the statistical data gathered during the text recognition process.
		virtual void print () const = 0;

	protected:

		double totalTime_;	///< Total elapsed time during stage execution.

		/// @brief	Updates the stage total elapsed time.
		/// 
		/// @post	#totalTime_ is set by summing all the individual timers.
		virtual void updateTotalTime () = 0;
};




///	@brief	Statistical data gathered during the preprocessing stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class PreprocessorStatistics : public Statistics
{
	public:

		///	@brief	Constructor.
		explicit PreprocessorStatistics ();

		///	@brief	Copy constructor.
		PreprocessorStatistics (const PreprocessorStatistics& statistics);

		///	@brief	Destructor.
		virtual ~PreprocessorStatistics ();

		/// @brief Assignment operator.
		PreprocessorStatistics& operator= (const PreprocessorStatistics& statistics);

		///	@brief	Prints the statistical data gathered.
		void print () const;

		/// @brief	@brief	Stores the press clip size in number of pixels.
		///
		///	@post	The internal member is set to <em>nPixels</em>.
		/// 
		/// @param	nPixels	Number of pixels in the press clip.
		void clipSize (const unsigned int& nPixels);

		/// @brief	@brief	Stores the optimal threshold used to binarize the press clip.
		///
		///	@post	The internal member is set to <em>threshold</em>.
		///
		/// @param	threshold A gray level.
		void optimalThreshold (const unsigned char& threshold);

		/// @brief	Stores the elapsed time while executing the global thresholding algorithm.
		/// 
		///	@post	The internal member is set to <em>elapsedTime</em>.
		/// 
		/// @param	elapsedTime Elapsed time in seconds.
		void globalThresholdingTime (const double& elapsedTime);

		/// @brief	Stores the elapsed time while executing the template filtering algorithm.
		/// 
		///	@post	The internal member is set to <em>elapsedTime</em>.
		/// 
		/// @param	elapsedTime Elapsed time in seconds.
		void templateFilteringTime (const double& elapsedTime);

		/// @brief	Stores the elapsed time while executing the averaging filtering algorithm.
		/// 
		///	@post	The internal member is set to <em>elapsedTime</em>.
		/// 
		/// @param	elapsedTime Elapsed time in seconds.
		void averagingFilteringTime (const double& elapsedTime);

		///	@brief	Stores the elapsed time while executing the thinning algorithm.
		///
		///	@post	The internal member is set to <em>elapsedTime</em>.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void thinningTime (const double& elapsedTime);

		/// @brief	Stores the elapsed time while executing the regions extraction algorithm.
		/// 
		///	@post	The internal member is set to <em>elapsedTime</em>.
		/// 
		/// @param	elapsedTime Elapsed time in seconds.
		void regionsExtractionTime (const double& elapsedTime);

		/// @brief	Stores the number of regions found before merging the accents while executing the regions extraction algorithm.
		/// 
		///	@post	The internal member is set to <em>nRegions</em>.
		/// 
		/// @param	nRegions Number of regions found.
		void nRegionsBeforeMerging (const unsigned int& nRegions);

		/// @brief	Stores the number of regions found after merging the accents while executing the regions extraction algorithm.
		/// 
		///	@post	The internal member is set to <em>nRegions</em>.
		/// 
		/// @param	nRegions Number of regions found.
		void nRegionsAfterMerging (const unsigned int& nRegions);

		/// @brief	Stores the number of line delimiters found while executing the regions extraction algorithm.
		/// 
		///	@post	The internal member is set to <em>nDelimiters</em>.
		/// 
		/// @param	nDelimiters Number of line delimiters found.
		void nLineDelimiters (const unsigned int& nDelimiters);

		/// @brief	Stores the slant angle estimation used to correct the slanting of every region found after executing the regions extraction algorithm.
		/// 
		///	@post	The internal member is set to <em>angle</em>.
		/// 
		/// @param	angle Angle estimation in degrees.
		void slantAngleEstimation (const double& angle);

		/// @brief	Stores the elapsed time while executing the slanting correction algorithm.
		/// 
		///	@post	The internal member is set to <em>elapsedTime</em>.
		/// 
		/// @param	elapsedTime Elapsed time in seconds.
		void slantingCorrectionTime (const double& elapsedTime);

		/// @brief	Stores the number of spaces between words found in text after post-processing the list of regions.
		///
		///	@post	The internal member is set to <em>nSpaces</em>.
		/// 
		///	@param	nSpaces	Number of spaces found.
		void spacesBetweenWords (const unsigned int& nSpaces);

		/// @brief	Stores the mean interregion space found in text after post-processing the list of regions.
		///
		///	@post	The internal member is set to <em>nPixels</em>.
		/// 
		///	@param	nPixels	Mean space width in pixels.
		void meanInterRegionSpace (const double& nPixels);

		/// @brief	Stores the elapsed time while finding the spaces location in text.
		/// 
		///	@post	The internal member is set to <em>elapsedTime</em>.
		/// 
		/// @param	elapsedTime Elapsed time in seconds.
		void spacesLocationFindingTime (const double& elapsedTime);

	private:

		unsigned int*	clipSize_;					///< Press clip size in number of pixels.

		unsigned char*	optimalThreshold_;			///< Optimal threshold to binarize the press clip.

		double*			globalThresholdingTime_;	///< Elapsed time during execution of global thresholding algorithm.

		double*			templateFilteringTime_;		///< Elapsed time while smoothing and noise removal by applying the template filtering algorithm.

		double*			averagingFilteringTime_;	///< Elapsed time while smoothing and noise removal by applying the averaging filtering algorithm.

		double*			thinningTime_;				///< Elapsed time while executing the thinning algorithm.

		double*			regionsExtractionTime_;		///< Elapsed time while extracting the regions of ink pixels applying a segmentation process over the press clip.

		unsigned int*	nRegionsBeforeMerging_;		///< Number of regions of pixels found before merging accents while applying a segmentation process over the clip.

		unsigned int*	nRegionsAfterMerging_;		///< Number of regions of pixels found after merging accents while applying a segmentation process over the clip.

		unsigned int*	nLineDelimiters_;			///< Number of line delimiters found while applying a segmentation process over the clip.

		double*			slantAngleEstimation_;		///< Angle estimation in degrees to correct the slanting in characters.

		double*			slantingCorrectionTime_;	///< Elapsed time while correcting the slanting of every region found after the region extraction algorithm.

		unsigned int*	spacesBetweenWords_;		///< Number of spaces between words found in text after post-processing the list of regions.

		double*			meanInterRegionSpace_;		///< Mean interregion space found in text after post-processing the list of regions.

		double*			spacesLocationFindingTime_;	///< Elapsed time while finding the spaces location in text.

		/// @brief	Updates the total elapsed time.
		/// 
		/// @post #totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void PreprocessorStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( globalThresholdingTime_ != 0 )
		totalTime_ += *globalThresholdingTime_;

	if ( templateFilteringTime_ != 0 )
		totalTime_ += *templateFilteringTime_;

	if ( averagingFilteringTime_ != 0 )
		totalTime_ += *averagingFilteringTime_;

	if ( thinningTime_ != 0 )
		totalTime_ += *thinningTime_;

	if ( regionsExtractionTime_ != 0 )
		totalTime_ += *regionsExtractionTime_;

	if ( slantingCorrectionTime_ != 0 )
		totalTime_ += *slantingCorrectionTime_;

	if ( spacesLocationFindingTime_ != 0 )
		totalTime_ += *spacesLocationFindingTime_;
};


inline void PreprocessorStatistics::clipSize (const unsigned int& nPixels)
{
	if ( clipSize_ == 0 )
		clipSize_ = new unsigned int;

	*clipSize_ = nPixels;
};


inline void PreprocessorStatistics::optimalThreshold (const unsigned char& threshold)
{
	if ( optimalThreshold_ == 0 )
		optimalThreshold_ = new unsigned char;

	*optimalThreshold_ = threshold;
};


inline void PreprocessorStatistics::globalThresholdingTime (const double& elapsedTime)
{
	if ( globalThresholdingTime_ == 0 )
		globalThresholdingTime_ = new double;

	*globalThresholdingTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::templateFilteringTime (const double& elapsedTime)
{
	if ( templateFilteringTime_ == 0 )
		templateFilteringTime_ = new double;

	*templateFilteringTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::thinningTime (const double& elapsedTime)
{
	if ( thinningTime_ == 0 )
		thinningTime_ = new double;

	*thinningTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::averagingFilteringTime (const double& elapsedTime)
{
	if ( averagingFilteringTime_ == 0 )
		averagingFilteringTime_ = new double;

	*averagingFilteringTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::regionsExtractionTime (const double& elapsedTime)
{
	if ( regionsExtractionTime_ == 0 )
		regionsExtractionTime_ = new double;

	*regionsExtractionTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::nRegionsBeforeMerging (const unsigned int& nRegions)
{
	if ( nRegionsBeforeMerging_ == 0 )
		nRegionsBeforeMerging_ = new unsigned int;

	*nRegionsBeforeMerging_ = nRegions;
};


inline void PreprocessorStatistics::nRegionsAfterMerging (const unsigned int& nRegions)
{
	if ( nRegionsAfterMerging_ == 0 )
		nRegionsAfterMerging_ = new unsigned int;

	*nRegionsAfterMerging_ = nRegions;
};


inline void PreprocessorStatistics::nLineDelimiters (const unsigned int& nDelimiters)
{
	if ( nLineDelimiters_ == 0 )
		nLineDelimiters_ = new unsigned int;

	*nLineDelimiters_ = nDelimiters;
};


inline void PreprocessorStatistics::slantAngleEstimation (const double& angle)
{
	if ( slantAngleEstimation_ == 0 )
		slantAngleEstimation_ = new double;

	*slantAngleEstimation_ = angle;
};


inline void PreprocessorStatistics::slantingCorrectionTime (const double& elapsedTime)
{
	if ( slantingCorrectionTime_ == 0 )
		slantingCorrectionTime_ = new double;

	*slantingCorrectionTime_ = elapsedTime;
	updateTotalTime();
};


inline void PreprocessorStatistics::spacesBetweenWords (const unsigned int& nSpaces)
{
	if ( spacesBetweenWords_ == 0 )
		spacesBetweenWords_ = new unsigned int;

	*spacesBetweenWords_ = nSpaces;
};


inline void PreprocessorStatistics::meanInterRegionSpace (const double& nPixels)
{
	if ( meanInterRegionSpace_ == 0 )
		meanInterRegionSpace_ = new double;

	*meanInterRegionSpace_ = nPixels;
};


inline void PreprocessorStatistics::spacesLocationFindingTime (const double& elapsedTime)
{
	if ( spacesLocationFindingTime_ == 0 )
		spacesLocationFindingTime_ = new double;

	*spacesLocationFindingTime_ = elapsedTime;
	updateTotalTime();
};




/// @brief	Statistical data gathered during the feature extraction stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class FeatureExtractionStatistics : public Statistics
{
	public:

		/// @brief	Constructor.
		explicit FeatureExtractionStatistics ();	

		/// @brief	Destructor.
		virtual ~FeatureExtractionStatistics ();

		/// @brief	Prints the statistical data gathered.
		void print () const;

	private:

		/// @brief	Updates the total elapsed time.
		/// 
		/// @post	#totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void FeatureExtractionStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;
};




/// @brief	Statistical data gathered during the classification stage of the text recognition process.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
///
class ClassificationStatistics : public Statistics
{
	public:

		/// @brief	Constructor.
		explicit ClassificationStatistics ();	

		/// @brief	Destructor.
		virtual ~ClassificationStatistics ();

		/// @brief	Prints the statistical data gathered.
		void print () const;

	private:

		/// @brief	Updates the total elapsed time.
		/// 
		/// @post	#totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void ClassificationStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;
};

#endif  //_STATISTICS_H


/// @file
/// @brief Declaration of PreprocessorStatistics class

#if !defined(_PREPROCESSOR_STATISTICS_H)
#define _PREPROCESSOR_STATISTICS_H

#include "Statistics.hpp"
#include <memory>


///	@brief	Statistics gathered during the preprocessing stage of the text recognition process.
///
///	@see	Statistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-01-12
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

		///	@brief	Print the statistical data gathered.
		void print () const;

		/// @brief	@brief	Set the press clip size in number of pixels.
		///
		/// @param	n	Number of pixels in the press clip.
		void clipSize (const unsigned int& n);

		/// @brief	@brief	Set the optimal threshold used to binarize the press clip.
		///
		/// @param	threshold A gray level.
		void optimalThreshold (const unsigned char& threshold);

		/// @brief	Set the elapsed time while executing the global thresholding algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void globalThresholdingTime (const double& elapsedTime);

		/// @brief	Set the elapsed time while executing the template filtering algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void templateFilteringTime (const double& elapsedTime);

		/// @brief	Set the elapsed time while executing the averaging filtering algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void averagingFilteringTime (const double& elapsedTime);

		///	@brief	Set the elapsed time while executing the thinning algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void thinningTime (const double& elapsedTime);

		/// @brief	Set the number of regions found before merging the accents while executing the regions extraction algorithm.
		///
		/// @param	n Number of regions found.
		void nRegionsBeforeMerging (const unsigned int& n);

		/// @brief	Set the number of line delimiters found while executing the regions extraction algorithm.
		///
		/// @param	n Number of line delimiters found.
		void nLineDelimiters (const unsigned int& n);

		/// @brief	Set the number of regions found after merging the accents while executing the regions extraction algorithm.
		///
		/// @param	n Number of regions found.
		void nRegionsAfterMerging (const unsigned int& n);

		/// @brief	Set the elapsed time while executing the regions extraction algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void regionsExtractionTime (const double& elapsedTime);

		/// @brief	Set the slant angle estimation used to correct the slanting of every region found after executing the regions extraction algorithm.
		///
		/// @param	angle Angle estimation in degrees.
		void slantAngleEstimation (const double& angle);

		/// @brief	Set the elapsed time while executing the slanting correction algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void slantingCorrectionTime (const double& elapsedTime);

		/// @brief	Set the number of spaces between words found in text after post-processing the list of regions.
		///
		///	@param	n	Number of spaces found.
		void spacesBetweenWords (const unsigned int& n);

		/// @brief	Set the mean interregion space found in text after post-processing the list of regions.
		///
		///	@param	n	Mean space width in pixels.
		void meanInterRegionSpace (const double& n);

		/// @brief	Set the elapsed time while finding the spaces location in text.
		///
		/// @param	elapsedTime Elapsed time in seconds.		
		void spacesLocationFindingTime (const double& elapsedTime);

	private:

		std::auto_ptr<unsigned int>		clipSize_;					///< Press clip size in number of pixels.

		std::auto_ptr<unsigned char>	optimalThreshold_;			///< Optimal threshold to binarize the press clip.

		std::auto_ptr<double>			globalThresholdingTime_;	///< Elapsed time when executing the global thresholding algorithm.

		std::auto_ptr<double>			templateFilteringTime_;		///< Elapsed time when executing the template filtering algorithm.

		std::auto_ptr<double>			averagingFilteringTime_;	///< Elapsed time when executing the averaging filtering algorithm.

		std::auto_ptr<double>			thinningTime_;				///< Elapsed time when executing the thinning algorithm.

		std::auto_ptr<unsigned int>		nRegionsBeforeMerging_;		///< Number of regions of pixels found before merging accents when segmenting the clip.

		std::auto_ptr<unsigned int>		nLineDelimiters_;			///< Number of line delimiters found when segmenting the clip.

		std::auto_ptr<unsigned int>		nRegionsAfterMerging_;		///< Number of regions of pixels found after merging accents when segmenting the clip.

		std::auto_ptr<double>			regionsExtractionTime_;		///< Elapsed time when executing the segmentation algorithm.

		std::auto_ptr<double>			slantAngleEstimation_;		///< Angle estimation in degrees to correct the slanting in characters.

		std::auto_ptr<double>			slantingCorrectionTime_;	///< Elapsed time when correcting the slanting in characters.

		std::auto_ptr<unsigned int>		spacesBetweenWords_;		///< Number of spaces between words found in text after post-processing the list of regions.

		std::auto_ptr<double>			meanInterRegionSpace_;		///< Mean interregion space in text after post-processing the list of regions.

		std::auto_ptr<double>			spacesLocationFindingTime_;	///< Elapsed time when finding the spaces location in text.

		/// @brief	Update the total elapsed time.
		///
		/// @post #totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void PreprocessorStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( globalThresholdingTime_.get() != 0 )
		totalTime_ += *globalThresholdingTime_.get();

	if ( templateFilteringTime_.get() != 0 )
		totalTime_ += *templateFilteringTime_.get();

	if ( averagingFilteringTime_.get() != 0 )
		totalTime_ += *averagingFilteringTime_.get();

	if ( thinningTime_.get() != 0 )
		totalTime_ += *thinningTime_.get();

	if ( regionsExtractionTime_.get() != 0 )
		totalTime_ += *regionsExtractionTime_.get();

	if ( slantingCorrectionTime_.get() != 0 )
		totalTime_ += *slantingCorrectionTime_.get();

	if ( spacesLocationFindingTime_.get() != 0 )
		totalTime_ += *spacesLocationFindingTime_.get();
};

inline void PreprocessorStatistics::clipSize (const unsigned int& n)
{
	clipSize_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::optimalThreshold (const unsigned char& threshold)
{
	optimalThreshold_.reset(new unsigned char(threshold));
};

inline void PreprocessorStatistics::globalThresholdingTime (const double& elapsedTime)
{
	globalThresholdingTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::templateFilteringTime (const double& elapsedTime)
{
	templateFilteringTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::thinningTime (const double& elapsedTime)
{
	thinningTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::averagingFilteringTime (const double& elapsedTime)
{

	averagingFilteringTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::nRegionsBeforeMerging (const unsigned int& n)
{
	nRegionsBeforeMerging_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::nLineDelimiters (const unsigned int& n)
{
	nLineDelimiters_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::nRegionsAfterMerging (const unsigned int& n)
{
	nRegionsAfterMerging_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::regionsExtractionTime (const double& elapsedTime)
{
	regionsExtractionTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::slantAngleEstimation (const double& angle)
{
	slantAngleEstimation_.reset(new double(angle));
};

inline void PreprocessorStatistics::slantingCorrectionTime (const double& elapsedTime)
{
	slantingCorrectionTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::spacesBetweenWords (const unsigned int& n)
{
	spacesBetweenWords_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::meanInterRegionSpace (const double& n)
{
	meanInterRegionSpace_.reset(new double(n));
};

inline void PreprocessorStatistics::spacesLocationFindingTime (const double& elapsedTime)
{
	spacesLocationFindingTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

#endif


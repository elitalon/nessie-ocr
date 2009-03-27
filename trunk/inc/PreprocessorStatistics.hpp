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

		/// @brief	Set the press clip size in number of pixels.
		///
		/// @param	n	Number of pixels in the press clip.
		void clipSize (const unsigned int& n);

		/// @brief	Set the optimal threshold used to binarize the press clip.
		///
		/// @param	threshold A gray level.
		void optimalThreshold (const unsigned char& threshold);

		/// @brief	Set the number of regions found after merging the accents.
		///
		/// @param	n Number of characters found.
		void nCharacters (const unsigned int& n);

		/// @brief	Set the number of lines found.
		///
		/// @param	n Number of lines found.
		void nLines (const unsigned int& n);

		/// @brief	Set the slant angle estimation used to correct the slant of characters.
		///
		/// @param	angle Angle estimation in degrees.
		void slantAngle (const double& angle);

		/// @brief	Set the average intercharacter space found in text.
		///
		///	@param	n	Average space in pixels.
		void averageInterCharacterSpace (const double& n);

		/// @brief	Set the average character height found in text.
		///
		///	@param	n	Average height in pixels.
		void averageCharacterHeight (const double& n);

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

		/// @brief	Set the elapsed time while executing the regions extraction algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void segmentationTime (const double& elapsedTime);

		///	@brief	Set the elapsed time while executing the thinning algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void thinningTime (const double& elapsedTime);

		/// @brief	Set the elapsed time while executing the slanting correction algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void slantingCorrectionTime (const double& elapsedTime);

		///	@brief	Print the statistical data gathered.
		void print () const;

	private:

		std::auto_ptr<unsigned int>		clipSize_;						///< Press clip size in number of pixels.

		std::auto_ptr<unsigned char>	optimalThreshold_;				///< Optimal threshold to binarize the press clip.

		std::auto_ptr<unsigned int>		nCharacters_;					///< Number of characters found after merging accents.

		std::auto_ptr<unsigned int>		nLines_;						///< Number of lines found in the press clip.

		std::auto_ptr<double>			slantAngle_;					///< Angle estimation in degrees to correct the slant in characters.

		std::auto_ptr<double>			averageInterCharacterSpace_;	///< Average intercharacter space.

		std::auto_ptr<double>			averageCharacterHeight_;		///< Average character height.

		std::auto_ptr<double>			globalThresholdingTime_;		///< Elapsed time when executing the global thresholding algorithm.

		std::auto_ptr<double>			templateFilteringTime_;			///< Elapsed time when executing the template filtering algorithm.

		std::auto_ptr<double>			averagingFilteringTime_;		///< Elapsed time when executing the averaging filtering algorithm.

		std::auto_ptr<double>			segmentationTime_;				///< Elapsed time when executing the segmentation algorithm.

		std::auto_ptr<double>			thinningTime_;					///< Elapsed time when executing the thinning algorithm.

		std::auto_ptr<double>			slantingCorrectionTime_;		///< Elapsed time when correcting the slant in characters.

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

	if ( segmentationTime_.get() != 0 )
		totalTime_ += *segmentationTime_.get();

	if ( slantingCorrectionTime_.get() != 0 )
		totalTime_ += *slantingCorrectionTime_.get();
};

inline void PreprocessorStatistics::clipSize (const unsigned int& n)
{
	clipSize_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::optimalThreshold (const unsigned char& threshold)
{
	optimalThreshold_.reset(new unsigned char(threshold));
};

inline void PreprocessorStatistics::nCharacters (const unsigned int& n)
{
	nCharacters_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::nLines (const unsigned int& n)
{
	nLines_.reset(new unsigned int(n));
};

inline void PreprocessorStatistics::slantAngle (const double& angle)
{
	slantAngle_.reset(new double(angle));
};

inline void PreprocessorStatistics::averageInterCharacterSpace (const double& n)
{
	averageInterCharacterSpace_.reset(new double(n));
};

inline void PreprocessorStatistics::averageCharacterHeight (const double& n)
{
	averageCharacterHeight_.reset(new double(n));
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

inline void PreprocessorStatistics::averagingFilteringTime (const double& elapsedTime)
{
	averagingFilteringTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::segmentationTime (const double& elapsedTime)
{
	segmentationTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::thinningTime (const double& elapsedTime)
{
	thinningTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

inline void PreprocessorStatistics::slantingCorrectionTime (const double& elapsedTime)
{
	slantingCorrectionTime_.reset(new double(elapsedTime));
	updateTotalTime();
};

#endif


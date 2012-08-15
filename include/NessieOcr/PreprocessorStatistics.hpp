/// @file
/// @brief Declaration of PreprocessorStatistics class

#if !defined(_PREPROCESSOR_STATISTICS_H)
#define _PREPROCESSOR_STATISTICS_H

#include "Statistics.hpp"
#include <memory>


///	@brief		Preprocessing stage statistics of NessieOcr.
///
///	@details	This class stores all the statistical data gathered during execution of methods of the preprocessing stage. Data can be write or read,
///	although a client program should be only interested in reading values. The statistical data	is automatically set whenever a method from a
///	Preprocessor object is called, but only the fields that method uses.
///
///	@see		Statistics, Preprocessor
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

		/// @brief	Assignment operator.
		PreprocessorStatistics& operator= (const PreprocessorStatistics& statistics);

		/// @brief	Set the press clip size in number of pixels.
		///
		/// @param	n	Number of pixels in the press clip.
		void clipSize (const unsigned int& n);

		/// @brief	Get the press clip size in number of pixels.
		///
		/// @return	Number of pixels in the press clip.
		unsigned int clipSize () const;

		/// @brief	Set the optimal threshold used to binarize the press clip.
		///
		/// @param	threshold A gray level.
		void optimalThreshold (const unsigned char& threshold);

		/// @brief	Get the optimal threshold used to binarize the press clip.
		///
		/// @return A gray level.
		unsigned char optimalThreshold () const;

		/// @brief	Set the number of regions found after merging the accents.
		///
		/// @param	n Number of characters found.
		void nRegions (const unsigned int& n);

		/// @brief	Get the number of regions found after merging the accents.
		///
		/// @return Number of characters found.
		unsigned int nRegions () const;

		/// @brief	Set the number of lines found.
		///
		/// @param	n Number of lines found.
		void nLines (const unsigned int& n);

		/// @brief	Get the number of lines found.
		///
		/// @return Number of lines found.
		unsigned int nLines () const;

		/// @brief	Set the average intercharacter space found in text.
		///
		///	@param	n	Average space in pixels.
		void averageSpaceBetweenCharacters (const double& n);

		/// @brief	Get the average intercharacter space found in text.
		///
		///	@return	Average space in pixels.
		double averageSpaceBetweenCharacters () const;

		/// @brief	Set the average character height found in text.
		///
		///	@param	n	Average height in pixels.
		void averageCharacterHeight (const double& n);

		/// @brief	Get the average character height found in text.
		///
		///	@return	Average height in pixels.
		double averageCharacterHeight () const;

		/// @brief	Set the average character width found in text.
		///
		///	@param	n	Average width in pixels.
		void averageCharacterWidth (const double& n);

		/// @brief	Get the average character width found in text.
		///
		///	@return	Average width in pixels.
		double averageCharacterWidth () const;

		/// @brief	Set the elapsed time while executing the averaging filtering algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void averagingFilteringTime (const double& elapsedTime);

		/// @brief	Get the elapsed time while executing the averaging filtering algorithm.
		///
		/// @return Elapsed time in seconds.
		double averagingFilteringTime () const;

		/// @brief	Set the elapsed time while executing the global thresholding algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void globalThresholdingTime (const double& elapsedTime);

		/// @brief	Get the elapsed time while executing the global thresholding algorithm.
		///
		/// @return Elapsed time in seconds.
		double globalThresholdingTime () const;

		/// @brief	Set the elapsed time while executing the template filtering algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void templateFilteringTime (const double& elapsedTime);

		/// @brief	Get the elapsed time while executing the template filtering algorithm.
		///
		/// @return Elapsed time in seconds.
		double templateFilteringTime () const;

		/// @brief	Set the elapsed time while executing the regions extraction algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void segmentationTime (const double& elapsedTime);

		/// @brief	Get the elapsed time while executing the regions extraction algorithm.
		///
		/// @return Elapsed time in seconds.
		double segmentationTime () const;

		/// @brief	Set the elapsed time while building an array of patterns from a list of regions.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void patternsBuildingTime (const double& elapsedTime);

		/// @brief	Get the elapsed time while building an array of patterns from a list of regions.
		///
		/// @return Elapsed time in seconds.
		double patternsBuildingTime () const;

		///	@brief	Set the elapsed time while executing the skeletonization algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void skeletonizationTime (const double& elapsedTime);

		///	@brief	Get the elapsed time while executing the skeletonization algorithm.
		///
		/// @return Elapsed time in seconds.
		double skeletonizationTime () const;

		/// @brief	Set the elapsed time while executing the slanting correction algorithm.
		///
		/// @param	elapsedTime Elapsed time in seconds.
		void slantingCorrectionTime (const double& elapsedTime);

		/// @brief	Get the elapsed time while executing the slanting correction algorithm.
		///
		/// @return Elapsed time in seconds.
		double slantingCorrectionTime () const;

		///	@brief	Print the statistical data gathered to the standard output.
		void print () const;

	private:

		std::auto_ptr<unsigned int>		clipSize_;						///< Press clip size in number of pixels.

		std::auto_ptr<unsigned char>	optimalThreshold_;				///< Optimal threshold to binarize the press clip.

		std::auto_ptr<unsigned int>		nRegions_;						///< Number of regions of ink found after merging accents.

		std::auto_ptr<unsigned int>		nLines_;						///< Number of lines found in the press clip.

		std::auto_ptr<double>			averageSpaceBetweenCharacters_;	///< Average space between characters.

		std::auto_ptr<double>			averageCharacterHeight_;		///< Average character height.

		std::auto_ptr<double>			averageCharacterWidth_;			///< Average character width.

		std::auto_ptr<double>			averagingFilteringTime_;		///< Elapsed time when executing the averaging filtering algorithm.

		std::auto_ptr<double>			globalThresholdingTime_;		///< Elapsed time when executing the global thresholding algorithm.

		std::auto_ptr<double>			templateFilteringTime_;			///< Elapsed time when executing the template filtering algorithm.

		std::auto_ptr<double>			segmentationTime_;				///< Elapsed time when executing the segmentation algorithm.

		std::auto_ptr<double>			patternsBuildingTime_;			///< Elapsed time while building an array of patterns.

		std::auto_ptr<double>			skeletonizationTime_;			///< Elapsed time when executing the skeletonization algorithm.

		std::auto_ptr<double>			slantingCorrectionTime_;		///< Elapsed time when executing the slanting correction algorithm.

		/// @brief	Update the total elapsed time.
		///
		/// @post #totalTime_ is set by summing all the individual timers.
		void updateTotalTime ();
};


inline void PreprocessorStatistics::updateTotalTime ()
{
	totalTime_ = 0.0;

	if ( averagingFilteringTime_.get() != 0 )
		totalTime_ += *averagingFilteringTime_;

	if ( globalThresholdingTime_.get() != 0 )
		totalTime_ += *globalThresholdingTime_;

	if ( templateFilteringTime_.get() != 0 )
		totalTime_ += *templateFilteringTime_;

	if ( segmentationTime_.get() != 0 )
		totalTime_ += *segmentationTime_;

	if ( patternsBuildingTime_.get() != 0 )
		totalTime_ += *patternsBuildingTime_;

	if ( skeletonizationTime_.get() != 0 )
		totalTime_ += *skeletonizationTime_;

	if ( slantingCorrectionTime_.get() != 0 )
		totalTime_ += *slantingCorrectionTime_;
}

inline void PreprocessorStatistics::clipSize (const unsigned int& n)
{
	clipSize_.reset(new unsigned int(n));
}

inline unsigned int PreprocessorStatistics::clipSize () const
{
	return *clipSize_;
}

inline void PreprocessorStatistics::optimalThreshold (const unsigned char& threshold)
{
	optimalThreshold_.reset(new unsigned char(threshold));
}

inline unsigned char PreprocessorStatistics::optimalThreshold () const
{
	return *optimalThreshold_;
}

inline void PreprocessorStatistics::nRegions (const unsigned int& n)
{
	nRegions_.reset(new unsigned int(n));
}

inline unsigned int PreprocessorStatistics::nRegions () const
{
	return *nRegions_;
}

inline void PreprocessorStatistics::nLines (const unsigned int& n)
{
	nLines_.reset(new unsigned int(n));
}

inline unsigned int PreprocessorStatistics::nLines () const
{
	return *nLines_;
}

inline void PreprocessorStatistics::averageSpaceBetweenCharacters (const double& n)
{
	averageSpaceBetweenCharacters_.reset(new double(n));
}

inline double PreprocessorStatistics::averageSpaceBetweenCharacters () const
{
	return *averageSpaceBetweenCharacters_;
}

inline void PreprocessorStatistics::averageCharacterHeight (const double& n)
{
	averageCharacterHeight_.reset(new double(n));
}

inline double PreprocessorStatistics::averageCharacterHeight () const
{
	return *averageCharacterHeight_;
}

inline void PreprocessorStatistics::averageCharacterWidth (const double& n)
{
	averageCharacterWidth_.reset(new double(n));
}

inline double PreprocessorStatistics::averageCharacterWidth () const
{
	return *averageCharacterWidth_;
}

inline void PreprocessorStatistics::averagingFilteringTime (const double& elapsedTime)
{
	averagingFilteringTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double PreprocessorStatistics::averagingFilteringTime () const
{
	return *averagingFilteringTime_;
}

inline void PreprocessorStatistics::globalThresholdingTime (const double& elapsedTime)
{
	globalThresholdingTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double PreprocessorStatistics::globalThresholdingTime () const
{
	return *globalThresholdingTime_;
}

inline void PreprocessorStatistics::templateFilteringTime (const double& elapsedTime)
{
	templateFilteringTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double PreprocessorStatistics::templateFilteringTime () const
{
	return *templateFilteringTime_;
}

inline void PreprocessorStatistics::segmentationTime (const double& elapsedTime)
{
	segmentationTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double PreprocessorStatistics::segmentationTime () const
{
	return *segmentationTime_;
}

inline void PreprocessorStatistics::patternsBuildingTime (const double& elapsedTime)
{
	patternsBuildingTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double PreprocessorStatistics::patternsBuildingTime () const
{
	return *patternsBuildingTime_;
}

inline void PreprocessorStatistics::skeletonizationTime (const double& elapsedTime)
{
	skeletonizationTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double PreprocessorStatistics::skeletonizationTime () const
{
	return *skeletonizationTime_;
}

inline void PreprocessorStatistics::slantingCorrectionTime (const double& elapsedTime)
{
	slantingCorrectionTime_.reset(new double(elapsedTime));
	updateTotalTime();
}

inline double PreprocessorStatistics::slantingCorrectionTime () const
{
	return *slantingCorrectionTime_;
}

#endif


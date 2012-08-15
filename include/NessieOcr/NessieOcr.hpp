/// @file
/// @brief Declaration of NessieOcr class

#if !defined(_NESSIE_OCR_H)
#define _NESSIE_OCR_H

class Classifier;
class Pattern;
class FeatureVector;
class Statistics;
#include <Magick++.h>
#include "Text.hpp"
#include <vector>
#include <string>
#include <memory>


/// @brief		Manager of the optical character recognition process.
///
/// @details	A pattern recognition system typically involves four stages: preprocessing, feature extraction, classification and postprocessing. This class
///	inhibits a client program to manage the execution and outcomes of every stage. Instead, a common set of operations are provided to satisfy most clients. If it's not
///	enough for your needs, a client can always use directly each one of the subsystems that compose NessieOcr: preprocessing, feature extraction, classification and
/// postprocessing.
///
/// @details	As the first important step, image and data <em>preprocessing</em> serves the purpose of extracting regions of interest, enhancing and cleaning up
/// the images, so that they can be directly and efficiently processed by the feature extraction stage. This subsystem is managed through the Preprocessor class.
///
///	@details	The purpose of <em>feature extraction</em> is the measurement of those attributes of patterns that are most pertinent to a given classification
///	task, producing a feature vector for each pattern extracted in the preprocessing stage. This subsystem is managed through the FeatureExtractor class.
///
///	@details	The <em>classification</em> stage processes the feature vectors to identify the characters. The feature vectors of input patterns are mapped onto
///	points in a feature space. Depending on the location of these points the patterns are classified as one character or another. This subsystem is managed through
/// the Classifier class and its derived classes. As you can see below, a Classifier object is actually a parameter you should specify in NessieOcr's constructor.
///
///	@details	In the end, <em>postprocessing</em> builds a meaningful text by inserting blank spaces between characters to separate the words. Management of this
///	subsystem is not supported currently.
///
/// @see		Statistics, Preprocessor, FeatureExtractor, Classifier
///
///	@todo		Improve the usability of supervised training methods.
///	@todo		Create a namespace and avoid access to private classes.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
class NessieOcr
{
	public:

		/// @brief	Constructor.
		explicit NessieOcr ();

		///	@brief	Destructor.
		~NessieOcr ();

		/// @brief		Extract the text from a press clip.
		///	@details	This method executes sequentially every recognition stage: preprocessing, feature extraction, classification and
		/// postprocessing.
		///
		/// @param		page		Underlying image representing a newspaper page.
		/// @param		x			X-axis coordinate of the row where the top leftmost pixel of the press clip is in the page.
		/// @param		y			Y-axis coordinate of the column where the top leftmost pixel of the press clip is in the page.
		/// @param		height		Height of the press clip in pixels.
		/// @param		width		Width of the press clip in pixels.
		///	@param		classifier	Classifier that must be used in the classification stage.
		///
		///	@return		A Text object with the extracted text.
		///
		///	@warning	<em>classifier</em> is not copied but only used internally. Be careful when using threads.
		const Text& recognize (const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width, const std::auto_ptr<Classifier>& classifier);

		/// @brief		Train a classifier according to a reference set of characters.
		///	@details	This method performs an automatic training of a classifier, comparing the set of characters previously extracted from a press clip
		///	with a reference text.
		/// 
		///	@param		classifier	Classifier that must be used in the classification stage. The KNN classifier with K=1 is the default option.
		/// @param		page		Underlying image representing a newspaper page.
		/// @param		x			X-axis coordinate of the row where the top leftmost pixel of the press clip is in the page.
		/// @param		y			Y-axis coordinate of the column where the top leftmost pixel of the press clip is in the page.
		/// @param		height		Height of the press clip in pixels.
		/// @param		width		Width of the press clip in pixels.
		/// @param		text		A text to compare with the classification results.
		/// 
		///	@post		The dataset handled by <em>classifier</em> is updated according to the training decisions.
		///	@warning	<em>classifier</em> is not copied but only used internally. Be careful when using threads.
		void train (const std::auto_ptr<Classifier>& classifier, const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width, const std::string& text);

		/// @brief		Train a classifier according to a reference pattern and its ASCII code.
		///	@details	This method performs an automatic training of a classifier, comparing a single pattern with an ASCII code. The pattern must have
		///	Pattern:planeSize() height and width, and must have been previously extracted from a press clip, probably calling NessieOcr::recognize and then
		///	NessieOcr::exportPatternImages.
		/// 
		///	@param		classifier	Classifier that must be used in the classification stage. The KNN classifier with K=1 is the default option.
		/// @param		pattern		Underlying image representing a pattern.
		/// @param		asciiCode	Reference ASCII code to compare with the classification result.
		/// 
		///	@pre		The input image must be in binary mode, i.e. a gray level of 0 means ink and a gray level of 1 means background.
		///	@pre		The input image must have the dimensions expected by the Pattern class, as returned by Pattern::planeSize() method.
		///	@post		The dataset handled by <em>classifier</em> is updated according to the training decisions.
		///	@warning	<em>classifier</em> is not copied but only used internally. Be careful when using threads.
		void train (const std::auto_ptr<Classifier>& classifier, const Magick::Image& pattern, const unsigned int& asciiCode);


		///	@brief		Export the patterns that have been built after a recognition or training stage.
		///	@details	For each pattern found in the preprocessing stage, this method creates a new BMP image in the filesystem, using the Magick++ library support.
		void exportPatternImages () const;

		/// @brief	Print statistical data to standard output.
		void printStatistics () const;


	private:

		std::vector<unsigned int>	spaceLocations_;				///< Array of space locations in text obtained after the preprocessing stage.
		
		std::vector<Pattern>		patterns_;						///< Array of patterns obtained after the preprocessing stage.

		std::vector<FeatureVector>	featureVectors_;				///< Array of feature vectors obtained after the feature extraction stage.
		
		std::vector<std::string>	characters_;					///< Array of strings that keeps the characters found after the classification stage.

		Text						text_;							///< Text produced after the whole recognition process.

		std::auto_ptr<Statistics>	preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		std::auto_ptr<Statistics>	featureExtractionStatistics_;	///< Statistics gathered during the feature extraction stage.

		std::auto_ptr<Statistics>	classificationStatistics_;		///< Statistics gathered during the classification stage.


		/// @brief	Execute the preprocessing stage.
		/// 
		/// @param	page		Underlying image representing a newspaper page.
		/// @param	x			X-axis coordinate of the row where the top leftmost pixel of the press clip is in the page.
		/// @param	y			Y-axis coordinate of the column where the top leftmost pixel of the press clip is in the page.
		/// @param	height		Height of the press clip in pixels.
		/// @param	width		Width of the press clip in pixels.
		///
		///	@post	An array of patterns becomes available through <em>patterns_</em> member.
		///	@post	An array of positions where spaces must be inserted when building the text becomes available through <em>spaceLocations_</em> member.
		void doPreprocessing (const Magick::Image& page, const unsigned int& x, const unsigned int& y, const unsigned int& height, const unsigned int& width);
		
		/// @brief	Execute the feature extraction stage.
		///
		///	@pre	doPreprocessing() must have been previously executed.
		///	@post	An array of feature vectors becomes available through <em>featureVectors_</em> member.
		void doFeatureExtraction ();

		/// @brief	Execute the classification stage. 
		///
		///	@param	classifier	Classifier that must be used in the classification stage. The KNN classifier with K=1 is the default option.
		///
		///	@pre	doFeatureExtraction() must have been previously executed. 
		///	@post	An array of characters becomes available through <em>characters_</em> member.
		void doClassification (const std::auto_ptr<Classifier>& classifier);

		/// @brief	Execute the postprocessing stage.
		///
		///	@pre	doClassification() must have been previously executed. 
		///	@post	A Text object with the result becomes available through <em>text_</em> member.
		void doPostprocessing ();
};

#endif


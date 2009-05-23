/// @file
/// @brief Declaration of NessieOcr class

#if !defined(_NESSIE_OCR_H)
#define _NESSIE_OCR_H


class Clip;
class Classifier;
class Pattern;
class FeatureVector;
class Statistics;
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
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
class NessieOcr
{
	public:

		/// @brief		Constructor.
		explicit NessieOcr ();

		///	@brief	Destructor.
		~NessieOcr ();

		/// @brief		Recognize the text present on a press clip.
		///	@details	This method executes sequentially all the recognition stages: preprocessing, feature extraction, classification and postprocessing.
		///
		/// @param		pressClip	Press clip to be processed.
		///	@param		classifier	Classifier that must be used in the classification stage. The KNN classifier with K=1 is the default option.
		///
		///	@return		A Text object with the text recognized.
		///
		///	@post		<em>classifier</em> is copied internally, so it can be safely deleted from the outside.
		const Text& recognize (const Clip& pressClip, const std::auto_ptr<Classifier>& classifier);

		/// @brief		Train a classifier according to a reference set of characters.
		///	@details	This methods performs an automatic training of a classifier, comparing the set of characters previously extracted from a press clip
		///	with a reference text.
		/// 
		///	@param		classifier	Classifier that must be used in the classification stage. The KNN classifier with K=1 is the default option.
		/// @param		pressClip	Press clip to be processed.
		/// @param		text		A text to compare with the classification results.
		/// 
		///	@post		The internal Dataset object handled by <em>classifier</em> is updated according to the training decisions.
		///	@post		<em>classifier</em> is copied internally, so it can be safely deleted from the outside.
		void train (const std::auto_ptr<Classifier>& classifier, const Clip& pressClip, const std::string& text);

		///	@brief		Export the patterns that have been built after a recognition or training stage.
		///	@details	This methods creates a new image in the filesystem (BMP by default) for each pattern, using Magick++ library support.
		void exportPatternImages () const;

		/// @brief		Print statistical data to standard output.
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


		/// @brief		Execute the preprocessing stage.
		/// 
		/// @param		pressClip	Press clip to be processed.
		///
		///	@post		An array of patterns becomes available through <em>patterns_</em> attribute.
		///	@post		The position of blank spaces becomes available through <em>spaceLocations_</em> attribute.
		void doPreprocessing (const Clip& pressClip);
		
		/// @brief		Execute the feature extraction stage.
		///
		///	@pre		The NessieOcr::doPreprocessing() method must have been previously executed. 
		///	@post		An array of FeatureVector objects becomes available through <em>featureVectors_</em> attribute.
		void doFeatureExtraction ();

		/// @brief		Execute the classification stage. 
		///
		///	@param		classifier	Classifier that must be used in the classification stage. The KNN classifier with K=1 is the default option.
		///
		///	@pre		The NessieOcr::doFeatureExtraction() method must have been previously executed. 
		///	@post		An array of characters becomes available through characters_ attribute.
		void doClassification (const std::auto_ptr<Classifier>& classifier);

		/// @brief		Execute the postprocessing stage.
		///
		///	@pre		The NessieOcr::doClassification() method must have been previously executed. 
		///	@post		A Text object with the result becomes available through text_ attribute.
		void doPostprocessing ();
};

#endif


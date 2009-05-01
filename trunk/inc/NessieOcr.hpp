/// @file
/// @brief Declaration of NessieOcr class

#if !defined(_NESSIE_OCR_H)
#define _NESSIE_OCR_H


class Clip;
class ClassificationAlgorithm;
class Pattern;
class FeatureVector;
#include "Text.hpp"
#include "PreprocessorStatistics.hpp"
#include "FeatureExtractorStatistics.hpp"
#include "ClassifierStatistics.hpp"
#include <vector>
#include <memory>


/// @brief		Manager of the optical character recognition process.
///
/// @details	A pattern recognition system typically involves four stages: preprocessing, feature extraction, classification and postprocessing. This class
///	allows to manage the execution and outcomes of every stage, or apply a global character recognition over an input press clip. The execution of any stage
///	produces some statistical data that might be of interest.
///
/// @details	As the first important step, image and data <em>preprocessing</em> serves the purpose of extracting regions of interest, enhancing and cleaning up
/// the images, so that they can be directly and efficiently processed by the feature extraction stage.
///
///	@details	The purpose of <em>feature extraction</em> is the measurement of those attributes of patterns that are most pertinent to a given classification
///	task, producing a feature vector for each pattern extracted in the preprocessing stage.
///
///	@details	The <em>classification</em> stage processes the feature vectors to identify the characters. The feature vectors of input patterns are mapped onto
///	points in a feature space. Depending on the location of these points the patterns are classified as one character or another.
///
///	@details	In the end, <em>postprocessing</em> builds a meaningful text by inserting blank spaces between characters to separate the words.
///
/// @see		Text, Statistics, ClassificationAlgorithm, Clip, Pattern, FeatureVector
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

		/// @brief	Get an array of patterns built in the last feature extraction stage executed.
		///
		/// @return An array of Pattern objects.
		std::vector<Pattern> patterns () const;

		///	@brief	Get the feature vectors found in the last feature extraction stage executed.
		///
		///	@return	An array of FeatureVector objects.
		std::vector<FeatureVector> featureVectors () const;

		/// @brief	Get the text found, either in the last classification stage or the last postprocessing stage.
		///
		/// @return A Text object with the recognized characters forming a meaningful content.
		const Text& text () const;

		/// @brief		Execute the preprocessing stage.
		/// @details	Image and data <em>preprocessing</em> enhances and cleans the press clip up, and extracts the regions of interest.
		/// 
		/// @param		pressClip	Press clip to be processed.
		///
		///	@post		An array of patterns becomes available through the NessieOcr::patterns() method.
		///	@post		The position of blank spaces becomes available through the NessieOcr::spaceLocations() method.
		void doPreprocessing (const Clip& pressClip);
		
		/// @brief		Execute the feature extraction stage.
		///	@details	The <em>feature extraction</em> measures the attributes of patterns that are most pertinent to a given classification task.
		///
		///	@pre		The NessieOcr::doPreprocessing() method must have been previously executed. 
		///	@post		An array of FeatureVector objects becomes available through the NessieOcr::featureVectors() method.
		void doFeatureExtraction ();

		/// @brief		Execute the classification stage. 
		///	@details	The feature vectors of input patterns are mapped onto points in a feature space and assigned to a class of characters.
		///
		/// @param		algorithm	Algorithm that must be used to classify the patterns.
		///
		///	@pre		The NessieOcr::doFeatureExtraction() method must have been previously executed. 
		///	@post		An array of characters becomes available through the NessieOcr::characters() method.
		///	@post		The ClassificationAlgorithm object is released.
		void doClassification (std::auto_ptr<ClassificationAlgorithm>& algorithm);

		/// @brief		Execute the postprocessing stage.
		///	@details	Characters <em>postprocessing</em> builds a meaningful text by inserting blank spaces between characters to separate the words.
		///
		///	@pre		The NessieOcr::doClassification() method must have been previously executed. 
		///	@post		A Text object with the result becomes available through the NessieOcr::text() method.
		void doPostprocessing ();

		/// @brief		Extract the text from a press clip.
		///	@details	This method executes sequentially all the recognition stages: preprocessing, feature extraction, classification and postprocessing.
		///
		/// @param		pressClip	Press clip to be processed.
		///	@param		algorithm	Algorithm that must be used to classify the patterns found in the press clip.
		///
		///	@post		A Text object with the result becomes available through the NessieOcr::text() method.
		///	@post		The ClassificationAlgorithm object is released.
		void extractText (const Clip& pressClip, std::auto_ptr<ClassificationAlgorithm>& algorithm);

		/// @brief	Execute an automatic training of the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param	pressClip		Press clip to be processed.
		/// @param	text			A text to compare with the classification results character by character.
		/// @param	algorithm		Algorithm that must be used to classify the patterns found in the press clip.
		/// 
		///	@post	The internal dataset is updated according to the user responses, e.g. new samples might be added.
		///	@post	The ClassificationAlgorithm object is released.
		void trainClassifier (const Clip& pressClip, const std::string& text, std::auto_ptr<ClassificationAlgorithm>& algorithm);

		/// @brief	Print detailed statistical data about every stage of the recognition process.
		///
		///	@post	The data is printed using the standard output.
		void printStatistics () const;

	private:

		std::vector<unsigned int>	spaceLocations_;				///< Array of space locations in text, useful in the postprocessing stage.

		std::vector<Pattern>		patterns_;						///< Array of patterns obtained after the feature extraction stage.

		std::vector<FeatureVector>	featureVectors_;				///< Array of feature vectors obtained after the feature extraction stage.
		
		std::vector<std::string>	characters_;					///< Array of strings that holds the characters found after the classification stage.

		Text						text_;							///< Text obtained after the recognition process.

		PreprocessorStatistics		preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		FeatureExtractorStatistics	featureExtractorStatistics_;	///< Statistics gathered during the feature extraction stage.

		ClassifierStatistics		classifierStatistics_;			///< Statistics gathered during the classification stage.
};


inline std::vector<Pattern> NessieOcr::patterns () const
{
	return patterns_;
};

inline std::vector<FeatureVector> NessieOcr::featureVectors () const
{
	return featureVectors_;
};

inline const Text& NessieOcr::text () const
{
	return text_;
};

#endif


/// @file
/// @brief Declaration of Recognizer class

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H


class Clip;
class Dataset;
#include "ClassificationParadigm.hpp"
#include "Pattern.hpp"
#include "FeatureVector.hpp"
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
/// @see		Dataset, Text, Statistics, Clip, ClassificationParadigm, Pattern, Region, FeatureVector
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
class Recognizer
{
	public:

		/// @brief		Constructor.
		///	@details	<em>dataset</em> is not copied by allocating new memory, but owned internally. Thus, it's released and set to null.
		///
		///	@param		dataset	The dataset to be used in classification and training.
		///
		///	@pre		<em>dataset</em> must not be a null pointer.
		///
		///	@post		The input dataset is released and set to null. The Dataset object is managed internally and destroyed with the Recognizer object.
		///
		///	@exception	NessieException
		explicit Recognizer (std::auto_ptr<Dataset>& dataset);
		
		/// @brief		Constructor.
		///
		///	@param		dataset	The dataset to be used in classification and training.
		///
		///	@pre		<em>dataset</em> must not be a null pointer.
		///
		///	@post		The input pointer is set to null. The Dataset object is managed internally and destroyed with the Recognizer object.
		///
		///	@exception	NessieException
		explicit Recognizer (Dataset* dataset);

		///	@brief	Destructor.
		///
		///	@post	The dataset is also destroyed and its memory deallocated.
		~Recognizer ();

		/// @brief	Get the dataset that is being used in classification and training.
		/// 
		/// @return	A pointer's constant reference to the internal Dataset object.
		const std::auto_ptr<Dataset>& dataset () const;
		
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

		/// @brief	Set the dataset that will be used in classification and training.
		/// 
		/// @param	dataset	A pointer's reference to the internal Dataset object.
		void dataset (std::auto_ptr<Dataset>& dataset);

		/// @brief		Execute the preprocessing stage.
		/// @details	Image and data <em>preprocessing</em> enhances and cleans the press clip up, and extracts the regions of interest.
		/// 
		/// @param		pressClip	Press clip to be processed.
		///
		///	@post		An array of patterns becomes available through the Recognizer::patterns() method.
		///	@post		The position of blank spaces becomes available through the Recognizer::spaceLocations() method.
		void doPreprocessing (const Clip& pressClip);
		
		/// @brief		Execute the feature extraction stage.
		///	@details	The <em>feature extraction</em> measures the attributes of patterns that are most pertinent to a given classification task.
		///
		///	@pre		The Recognizer::doPreprocessing() method must have been previously executed. 
		///	@post		An array of FeatureVector objects becomes available through the Recognizer::featureVectors() method.
		void doFeatureExtraction ();

		/// @brief		Execute the classification stage. 
		///	@details	The feature vectors of input patterns are mapped onto points in a feature space and assigned to a class of characters.
		///
		/// @param		paradigm	Paradigm that must be used to classify the patterns.
		///
		///	@pre		The Recognizer::doFeatureExtraction() method must have been previously executed. 
		///	@post		An array of characters becomes available through the Recognizer::characters() method.
		void doClassification (const ClassificationParadigm& paradigm=ClassificationParadigm::knn());

		/// @brief		Execute the postprocessing stage.
		///	@details	Characters <em>postprocessing</em> builds a meaningful text by inserting blank spaces between characters to separate the words.
		///
		///	@pre		The Recognizer::doClassification() method must have been previously executed. 
		///	@post		A Text object with the result becomes available through the Recognizer::text() method.
		void doPostprocessing ();

		/// @brief		Extract the text from a press clip.
		///	@details	This method executes sequentially all the recognition stages: preprocessing, feature extraction, classification and postprocessing.
		///
		/// @param		pressClip	Press clip to be processed.
		///	@param		paradigm	Paradigm that must be used to classify the patterns found in the press clip.
		///
		///	@post		A Text object with the result becomes available through the Recognizer::text() method.
		void extractText (const Clip& pressClip, const ClassificationParadigm& paradigm=ClassificationParadigm::knn());

		/// @brief	Execute an automatic training of the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param	pressClip		Press clip to be processed.
		/// @param	text			A text to compare with the classification results character by character.
		/// @param	paradigm		Paradigm that must be used to classify the patterns found in the press clip.
		/// 
		///	@post	The internal dataset is updated according to the user responses, e.g. new samples might be added.
		void trainClassifier (const Clip& pressClip, const std::string& text, const ClassificationParadigm& paradigm=ClassificationParadigm::knn());

		/// @brief	Print detailed statistical data about every stage of the recognition process.
		///
		///	@post	The data is printed using the standard output.
		void printStatistics () const;

	private:

		std::auto_ptr<Dataset>		dataset_;						///< Dataset to be used during the classification stage.

		std::vector<unsigned int>	spaceLocations_;				///< Array of space locations in text, useful in the postprocessing stage.

		std::vector<Pattern>		patterns_;						///< Array of patterns obtained after the feature extraction stage.

		std::vector<FeatureVector>	featureVectors_;				///< Array of feature vectors obtained after the feature extraction stage.
		
		std::vector<std::string>	characters_;					///< Array of strings that holds the characters found after the classification stage.

		Text						text_;							///< Text obtained after the recognition process.

		PreprocessorStatistics		preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		FeatureExtractorStatistics	featureExtractorStatistics_;	///< Statistics gathered during the feature extraction stage.

		ClassifierStatistics		classifierStatistics_;			///< Statistics gathered during the classification stage.

		// Do not implement these methods, as they are only declared here to prevent objects to be copied. 
		Recognizer (const Recognizer&);
		Recognizer& operator= (const Recognizer&);
};


inline const std::auto_ptr<Dataset>& Recognizer::dataset () const
{
	return dataset_;
};

inline void Recognizer::dataset (std::auto_ptr<Dataset>& dataset)
{
	dataset_ = dataset;
};

inline std::vector<Pattern> Recognizer::patterns () const
{
	return patterns_;
};

inline std::vector<FeatureVector> Recognizer::featureVectors () const
{
	return featureVectors_;
};

inline const Text& Recognizer::text () const
{
	return text_;
};

#endif


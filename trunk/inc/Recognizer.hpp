/// @file
/// @brief Declaration of Recognizer class

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H


class Clip;
class Statistics;
class Dataset;
class ClassificationParadigm;
#include <list>
#include <vector>
#include "Region.hpp"
#include "Pattern.hpp"
#include "FeatureVector.hpp"
#include "Text.hpp"
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
		///	@exception	NessieException
		explicit Recognizer (std::auto_ptr<Dataset>& dataset);
		
		/// @brief		Constructor.
		///
		///	@param		dataset	The dataset to be used in classification and training.
		///
		///	@pre		<em>dataset</em> must not be a null pointer.
		///
		///	@warning	<em>dataset</em> is not copied by allocating new memory, but owned internally. Thus, be careful with deallocating the memory using
		///	external pointer. However, also notice that when a Recognizer object is destroyed, the internal dataset is also destroyed and its memory deallocated.
		///
		///	@exception	NessieException
		explicit Recognizer (Dataset* const dataset);

		///	@brief	Destructor.
		~Recognizer ();

		/// @brief	Get the dataset that is being used in classification and training.
		/// 
		/// @return	A pointer's constant reference to the internal Dataset object.
		const std::auto_ptr<Dataset>& dataset () const;
		
		/// @brief	Set the dataset that will be used in classification and training.
		/// 
		/// @param	dataset	A pointer's reference to the internal Dataset object.
		void dataset (std::auto_ptr<Dataset>& dataset);

		/// @brief	Get the regions found in the last preprocessing stage executed.
		///
		/// @return A list of Region objects.
		std::list<Region> regions () const;

		/// @brief	Get the positions of blank spaces found in the last preprocessing stage executed.
		///
		/// @return An array of integers, each one representing the position where a blank space must be inserted when building the text in postprocessing.
		std::vector<unsigned int> spaceLocations () const;

		/// @brief	Get an array with the patterns built in the last feature extraction stage executed.
		///
		/// @return An array of Pattern objects.
		std::vector<Pattern> patterns () const;

		///	@brief	Get the feature vectors found in the last feature extraction stage executed.
		///
		///	@return	An array of FeatureVector objects.
		std::vector<FeatureVector> featureVectors () const;

		/// @brief	Get the characters found in the last classification stage executed.
		/// 
		/// @return An array of strings, where each string constitutes a single character.
		std::vector<std::string> characters () const;

		/// @brief	Get the text found, either in the last classification stage or the last postprocessing stage.
		///
		/// @return A Text object with the recognized characters forming a meaningful content.
		const Text& text () const;

		/// @brief		Execute the preprocessing stage.
		/// @details	Image and data <em>preprocessing</em> enhances and cleans the press clip up, and extracts the regions of interest.
		/// 
		/// @param		pressClip	Press clip to be processed.
		///
		///	@post		A list of regions becomes available through the Recognizer::regions() method.
		///	@post		The position of blank spaces becomes available through the Recognizer::spaceLocations() method.
		void doPreprocessing (const Clip& pressClip);
		
		/// @brief		Execute the feature extraction stage.
		///	@details	The <em>feature extraction</em> measures the attributes of patterns that are most pertinent to a given classification task.
		///
		///	@pre		The Recognizer::doPreprocessing() method must have been previously executed. 
		///	@post		An array of FeatureVector objects becomes available through the Recognizer::featureVectors() method.
		void doFeatureExtraction ();

		/// @brief		Execute the feature extraction stage.
		///	@details	The <em>feature extraction</em> measures the attributes of patterns that are most pertinent to a given classification task.
		/// 
		/// @param		regions	A list of regions from which extract the patterns and its feature vectors.
		///
		///	@post		An array of FeatureVector objects becomes available through the Recognizer::featureVectors() method.
		void doFeatureExtraction (const std::list<Region>& regions);

		/// @brief		Execute the classification stage. 
		///	@details	The feature vectors of input patterns are mapped onto points in a feature space and assigned to a class of characters.
		///
		/// @param		paradigm	Paradigm that must be used to classify the patterns.
		///
		///	@pre		The Recognizer::doFeatureExtraction() method must have been previously executed. 
		///	@post		An array of characters becomes available through the Recognizer::characters() method.
		void doClassification (const ClassificationParadigm& paradigm);

		/// @brief		Execute the classification stage.
		///	@details	The feature vectors of input patterns are mapped onto points in a feature space and assigned to a class of characters.
		/// 
		/// @param		featureVectors	An array of feature vectors that identifies characters to be classified.
		/// @param		paradigm		Paradigm that must be used to classify the patterns found in the press clip.
		/// 
		///	@post		An array of characters becomes available through the Recognizer::characters() method.
		void doClassification (const std::vector<FeatureVector>& featureVectors, const ClassificationParadigm& paradigm);

		/// @brief		Execute the postprocessing stage.
		///	@details	Characters <em>postprocessing</em> builds a meaningful text by inserting blank spaces between characters to separate the words.
		///
		///	@pre		The Recognizer::doClassification() method must have been previously executed. 
		///	@post		A Text object with the result becomes available through the Recognizer::text() method.
		void doPostprocessing ();

		/// @brief		Execute the postprocessing stage.
		///	@details	Characters <em>postprocessing</em> builds a meaningful text by inserting blank spaces between characters to separate the words.
		/// 
		/// @param		characters		An array of characters to be postprocessed to build the final text.
		/// @param		spaceLocations	Positions in the text where blanks spaces should be inserted.
		/// 
		///	@post		A Text object with the result becomes available through the Recognizer::text() method.
		void doPostprocessing (const std::vector<std::string>& characters, const std::vector<unsigned int>& spaceLocations);

		/// @brief		Extract the text from a press clip.
		///	@details	This method executes sequentially all the recognition stages: preprocessing, feature extraction, classification and postprocessing.
		///
		/// @param		pressClip	Press clip to be processed.
		///	@param		paradigm	Paradigm that must be used to classify the patterns found in the press clip.
		///
		///	@post		A Text object with the result becomes available through the Recognizer::text() method.
		void extractText (const Clip& pressClip, const ClassificationParadigm& paradigm);

		/// @brief	Execute an interactive training of the classifier, prompting the user to confirm each classification decision.
		/// 
		/// @param	pressClip	Press clip to be processed.
		/// @param	paradigm	Paradigm that must be used to classify the patterns found in the press clip.
		/// 
		///	@post	The internal dataset is updated according to the user responses, e.g. new samples might be added.
		void trainClassifier (const Clip& pressClip, const ClassificationParadigm& paradigm);

		/// @brief	Execute an automatic training of the classifier, comparing each classification decision with a reference text.
		/// 
		/// @param	pressClip		Press clip to be processed.
		/// @param	text			A text to compare with the classification results character by character.
		/// @param	paradigm		Paradigm that must be used to classify the patterns found in the press clip.
		/// 
		///	@post	The internal dataset is updated according to the user responses, e.g. new samples might be added.
		void trainClassifier (const Clip& pressClip, const std::string& text, const ClassificationParadigm& paradigm);

		/// @brief	Print detailed statistical data about every stage of the recognition process.
		///
		///	@post	The data is printed using the standard output.
		void printStatistics () const;

	private:

		std::auto_ptr<Dataset>		dataset_;						///< Dataset to be used during the classification stage.

		std::list<Region>			regions_;						///< List of regions obtained after the preprocessing stage.

		std::vector<unsigned int>	spaceLocations_;				///< Array of space locations in text, useful in the postprocessing stage.

		std::vector<Pattern>		patterns_;						///< Array of patterns obtained after the feature extraction stage.

		std::vector<FeatureVector>	featureVectors_;				///< Array of feature vectors obtained after the feature extraction stage.
		
		std::vector<std::string>	characters_;					///< Array of strings that holds the characters found after the classification stage.

		Text						text_;							///< Text obtained after the recognition process.

		std::auto_ptr<Statistics>	preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		std::auto_ptr<Statistics>	featureExtractorStatistics_;	///< Statistics gathered during the feature extraction stage.

		std::auto_ptr<Statistics>	classifierStatistics_;			///< Statistics gathered during the classification stage.

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

inline std::list<Region> Recognizer::regions () const
{
	return regions_; 
};

inline std::vector<unsigned int> Recognizer::spaceLocations () const
{
	return spaceLocations_;
};

inline std::vector<Pattern> Recognizer::patterns () const
{
	return patterns_;
};

inline std::vector<FeatureVector> Recognizer::featureVectors () const
{
	return featureVectors_;
};

inline std::vector<std::string> Recognizer::characters () const
{
	return characters_;
};

inline const Text& Recognizer::text () const
{
	return text_;
};

#endif


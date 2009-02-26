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


/// @brief		Manager of the whole OCR process.
///
/// @details	This class encapsulates all the stages related to the optical character recognition process of
/// every clip within a newspaper's page. For each image provided representing a press clip, you can obtain
/// its text and a number of statistics regarding the recognition process.
///
/// @see		Dataset, Text, Statistics, Clip, ClassificationParadigm, Pattern, Region, FeatureVector
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
class Recognizer
{
	public:

		/// @brief		Constructor.
		///
		///	@param		dataset	The dataset to be used during the classification stage.
		///
		///	@pre		The dataset argument must not be a null pointer.
		///
		///	@warning	The dataset object is not copied, be careful with deleting it from the client until the Recognizer object becomes is destroyed.
		///
		///	@exception	NessieException
		explicit Recognizer (const Dataset* dataset);

		///	@brief	Destructor.
		~Recognizer ();

		/// @brief	Extracts the text from a single press clip.
		///
		/// @param	pressClip	Press clip to be processed.
		///	@param	paradigm	Paradigm that must be used to classify the patterns found in the press clip.
		///
		///	@post	The text recognized from the pressClip is available through the Recognizer::text() method.
		void extractText (const Clip& pressClip, const ClassificationParadigm& paradigm);

		/// @brief	Executes the preprocessing stage.
		/// 
		/// @param	pressClip	Press clip to be processed.
		void doPreprocessing (const Clip& pressClip);

		/// @brief	Executes the feature extraction stage assuming the internal members were already set. 
		///
		///	@pre	The preprocessing stage must have been previously executed. 
		void doFeatureExtraction ();

		/// @brief	Executes the feature extraction stage. 
		/// 
		/// @param	regions	A list of regions from which extract the patterns and its feature vectors.
		void doFeatureExtraction (const std::list<Region>& regions);

		/// @brief	Executes the classification stage assuming the internal members were already set. 
		///
		/// @param	paradigm		Paradigm that must be used to classify the patterns found in the press clip.
		///
		///	@pre	The feature extraction stage must have been previously executed. 
		void doClassification (const ClassificationParadigm& paradigm);

		/// @brief	Executes the classification stage.
		/// 
		/// @param	featureVectors	An array of feature vectors that identifies characters to be classified.
		/// @param	paradigm		Paradigm that must be used to classify the patterns found in the press clip.
		void doClassification (const std::vector<FeatureVector>& featureVectors, const ClassificationParadigm& paradigm);

		/// @brief	Executes the postprocessing stage assuming the internal members were already set. 
		///
		///	@pre	The classification stage must have been previously executed. 
		void doPostprocessing ();

		/// @brief	Executes the postprocessing stage.
		/// 
		/// @param	text			Text to be postprocessed.
		/// @param	spaceLocations	Positions in the text where blanks spaces should be inserted.
		void doPostprocessing (const Text& text, const std::vector<unsigned int>& spaceLocations);

		/// @brief	Returns the regions found, if any, in the last preprocessing stage executed.
		///
		/// @return A list of Region objects
		std::list<Region> regions () const;

		/// @brief	Returns the positions of blank spaces found in the last preprocessing stage executed.
		///
		/// @return An array of numbers, each one represents the position where a blank space should be inserted when building the text in postprocessing.
		std::vector<unsigned int> spaceLocations () const;

		/// @brief	Returns an array with the patterns built in the last feature extraction stage executed.
		///
		/// @return An array of Pattern objects.
		std::vector<Pattern> patterns () const;

		///	@brief	Returns the feature vectors found in the last feature extraction stage executed.
		///
		///	@return	An array of FeatureVector objects.
		std::vector<FeatureVector> featureVectors () const;

		/// @brief	Returns the text found, either in the last classification stage or the last postprocessing stage.
		///
		/// @return A Text object with information about the recognized text.
		const Text& text () const;

		/// @brief	Prints detailed statistics about the text recognition process.
		///
		///	@post	Every stage statistical data is printed using the standard output.
		void printStatistics () const;

		/// @brief	Executes a classifier interactive training using the input array of patterns.
		/// 
		/// @param	regions		A list of regions to classify.
		/// @param	paradigm	Paradigm that must be used to classify the patterns found in the press clip.
		void trainClassifier (const std::list<Region>& regions, const ClassificationParadigm& paradigm);

		/// @brief	Executes a classifier automatic training, comparing the input patterns with a reference text.
		/// 
		/// @param	regions		A list of regions to classify.
		/// @param	referenceText	A text to compare with the classification results character by character.
		/// @param	paradigm		Paradigm that must be used to classify the patterns found in the press clip.
		void trainClassifier (const std::list<Region>& regions, const std::vector<std::string>& referenceText, const ClassificationParadigm& paradigm);

	private:

		const Dataset*				dataset_;						///< Dataset to be used during the classification stage.

		std::list<Region>			regions_;						///< List of regions obtained after the preprocessing stage.

		std::vector<unsigned int>	spaceLocations_;				///< Array of space locations in text, useful in the postprocessing stage.

		std::vector<Pattern>		patterns_;						///< Array of patterns obtained after the feature extraction stage.

		std::vector<FeatureVector>	featureVectors_;				///< Array of feature vectors obtained after the feature extraction stage.
		
		Text						text_;							///< Text obtained after the recognition process.

		std::auto_ptr<Statistics>	preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		std::auto_ptr<Statistics>	featureExtractorStatistics_;	///< Statistics gathered during the feature extraction stage.

		std::auto_ptr<Statistics>	classifierStatistics_;			///< Statistics gathered during the classification stage.

		// Do not implement these methods, as they are only declared here to prevent objects to be copied. 
		Recognizer (const Recognizer&);
		Recognizer& operator= (const Recognizer&);
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

inline const Text& Recognizer::text () const
{
	return text_;
};

#endif


/// @file
/// @brief Declaration of Recognizer class

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H


class Clip;
class Statistics;
class Dataset;
class ClassificationParadigm;
#include "Text.hpp"


/// @brief		Manager of the whole OCR process.
///
/// @details	This class encapsulates all the stages related to the optical character recognition process of
/// every clip within a newspaper's page. For each image provided representing a press clip, you can obtain
/// its text and a number of statistics regarding the recognition process.
///
/// @see		Dataset, Text, Statistics, Clip
///
///	@warning	The Dataset object passed in constructor will destroyed when the Recognizer object is destroyed.
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
///
class Recognizer
{
	public:

		/// @brief	Constructor.
		///
		///	@param	dataset	The dataset to be used during the classification stage.
		///
		///	@warning	The Dataset object passed in constructor will destroyed when the Recognizer object is destroyed.
		explicit Recognizer (Dataset* dataset);

		/// @brief	Destructor.
		~Recognizer ();

		/// @brief	Extracts the text from a single press clip.
		///
		/// @param	pressClip	Press clip to be processed.
		///	@param	paradigm	Paradigm that must be used to classify the patterns found in the press clip.
		///
		///	@post	The internal members are set so that recognized text is available through Text::text() method.
		void extractText (const Clip& pressClip, const ClassificationParadigm& paradigm);

		/// @brief	Returns the text found in a press clip after the recognition process.
		///
		/// @return A Text object with data about the recognized text.
		const Text& text () const;

		/// @brief	Prints detailed statistics about the text recognition process gathered during its execution.
		void printStatistics () const;

	private:

		Dataset*	dataset_;						///< Dataset to be used during the classification stage.

		Text		text_;							///< Text obtained after the recognition process.

		Statistics*	preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		Statistics*	featureExtractorStatistics_;	///< Statistics gathered during the feature extraction stage.

		Statistics*	classifierStatistics_;			///< Statistics gathered during the classification stage.

		// Explicitly disallowed compiler-generated methods. DO NOT IMPLEMENT THEM!!
		Recognizer ();
		Recognizer (const Recognizer&);
		Recognizer& operator= (const Recognizer&);
};


inline const Text& Recognizer::text () const
{
	return text_;
};

#endif


/// @file
/// @brief Declaration of Recognizer class

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H


class Clip;
class Statistics;
class Dataset;
class ClassificationParadigm;
#include "Text.hpp"
#include <memory>


/// @brief		Manager of the whole OCR process.
///
/// @details	This class encapsulates all the stages related to the optical character recognition process of
/// every clip within a newspaper's page. For each image provided representing a press clip, you can obtain
/// its text and a number of statistics regarding the recognition process.
///
/// @see		Dataset, Text, Statistics, Clip, ClassificationParadigm
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
		explicit Recognizer (Dataset* dataset);

		///	@brief	Destructor.
		~Recognizer ();

		/// @brief	Extracts the text from a single press clip.
		///
		/// @param	pressClip	Press clip to be processed.
		///	@param	paradigm	Paradigm that must be used to classify the patterns found in the press clip.
		///
		///	@post	The text recognized from the pressClip is available through the Recognizer::text() method.
		void extractText (const Clip& pressClip, const ClassificationParadigm& paradigm);

		/// @brief	Returns the text found in a press clip after the recognition process.
		///
		/// @return A Text object with information about the recognized text.
		const Text& text () const;

		/// @brief	Prints detailed statistics about the text recognition process.
		///
		///	@post	Every stage statistical data is printed using the standard output.
		void printStatistics () const;

	private:

		Dataset*					dataset_;						///< Dataset to be used during the classification stage.

		Text						text_;							///< Text obtained after the recognition process.

		std::auto_ptr<Statistics>	preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		std::auto_ptr<Statistics>	featureExtractorStatistics_;	///< Statistics gathered during the feature extraction stage.

		std::auto_ptr<Statistics>	classifierStatistics_;			///< Statistics gathered during the classification stage.

		// Do not implement these methods, as they are only declared here to prevent objects to be copied. 
		Recognizer (const Recognizer&);
		Recognizer& operator= (const Recognizer&);
};


inline const Text& Recognizer::text () const
{
	return text_;
};

#endif


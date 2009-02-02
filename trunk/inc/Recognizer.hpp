/// @file
/// @brief Declaration of the class Recognizer

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H


class Clip;
#include "Text.hpp"
#include "Statistics.hpp"


/// @brief		Manager of the whole OCR process.
///
/// @details	This class encapsulates all the stages related to the optical character recognition process of
/// every clip within a newspaper's page. For each image provided representing a press clip, you can obtain
/// its text and a number of statistics regarding the recognition process.
///
/// @see		Clip, Text, Statistics
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
///
class Recognizer
{
	public:

		/// @brief	Constructor.
		explicit Recognizer ();

		/// @brief	Destructor.
		~Recognizer ();

		/// @brief	Extracts the text from a single press clip.
		///
		/// @param	pressClip	A Clip object with a press clip previously loaded.
		///
		///	@post	The internal members are set so that recognized text is available through Text::text() method.
		void extractText (const Clip& pressClip);

		/// @brief	Returns the text found in a press clip after the recognition process.
		///
		/// @return A Text object with data about the recognized text.
		const Text& text () const;

		/// @brief	Prints detailed statistics about the text recognition process gathered during its execution.
		void printStatistics () const;

	private:

		Text		text_;							///< Text obtained after the recognition process.

		Statistics*	preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.

		Statistics*	featureExtractionStatistics_;	///< Statistics gathered during the feature extraction stage.

		Statistics*	classificationStatistics_;		///< Statistics gathered during the classification stage.

		// Explicitly disallowed compiler-generated methods. DO NOT IMPLEMENT THEM!!
		Recognizer (const Recognizer&);
		Recognizer& operator= (const Recognizer&);
};


inline const Text& Recognizer::text () const
{
	return text_;
};


inline void Recognizer::printStatistics () const
{
	if ( preprocessingStatistics_ != 0 )
		preprocessingStatistics_->print();

	if ( featureExtractionStatistics_ != 0 )
		featureExtractionStatistics_->print();

	if ( classificationStatistics_ != 0 )
		classificationStatistics_->print();
};

#endif  //_RECOGNIZER_H


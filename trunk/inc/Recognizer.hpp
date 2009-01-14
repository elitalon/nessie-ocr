/// @file
/// @brief Declaration of the class Recognizer

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H


class Clip;
#include "Text.hpp"
#include "Statistics.hpp"


///
/// Manager of the whole OCR process.
///
/// This class encapsulates all the stages related to the optical character recognition process of
/// every clip within a newspaper's page. For each image provided representing a press clip, you can obtain
/// its text and a number of statistics regarding the recognition process.
///
/// @see Text, Statistics, Clip
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
///
class Recognizer
{
public:

	///
	/// Constructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	explicit Recognizer ();
	
	///
	/// Destructor.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	~Recognizer ();

	///
	/// Extracts the text within a single press clip.
	///
	/// @param pressClip	A Clip object representing the press clip previously loaded.
	///
	/// @see Clip
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	void extractText (const Clip& pressClip);

	///
	/// Returns the text found in a press clip after the recognition process.
	///
	/// @return A Text object with the data about the text recognized.
	///
	/// @see Text
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2008-12-29
	///
	const Text& text () const;

	///
	/// Prints detailed statistics about the text recognition process gathered during execution.
	///
	/// @author Eliezer Talón (elitalon@gmail.com)
	/// @date 2009-01-12
	///
	void printStatistics () const;

private:

	Text		text_;							///< Text obtained after the recognition process.

	Statistics*	preprocessingStatistics_;		///< Statistics gathered during the preprocessing stage.
	
	Statistics*	featureExtractionStatistics_;	///< Statistics gathered during the feature extraction stage.
	
	Statistics*	classificationStatistics_;		///< Statistics gathered during the classification stage.

	// Explicitly disallowed compiler-generated functions. DO NOT IMPLEMENT THEM!!
	Recognizer (const Recognizer&);
	Recognizer& operator= (const Recognizer&);
};


inline const Text& Recognizer::text () const
{
	return text_;
};


inline void Recognizer::printStatistics () const
{
	if ( preprocessingStatistics_ not_eq 0 )
		preprocessingStatistics_->print();
	
	if ( featureExtractionStatistics_ not_eq 0 )
		featureExtractionStatistics_->print();
		
	if ( classificationStatistics_ not_eq 0 )
		classificationStatistics_->print();
};

#endif  //_RECOGNIZER_H

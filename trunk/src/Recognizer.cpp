/// @file
/// @brief Implementation of the class Recognizer

#include "Recognizer.hpp"
#include "Clip.hpp"



Recognizer::Recognizer ()
	:	text_(Text()),
		statistics_(Statistics())
{};


///
/// @details This method executes the recognition process in four stages: preprocessing, feature extraction, classification and postprocessing.
///
void Recognizer::extractText (const Clip& pressClip)
{
	//
	// Preprocessing stage
	//
	pressClip.writeToOutputImage("foo.jpg");

	//
	// Feature extraction stage
	//


	//
	// Classification stage
	//


	//
	// Postprocessing stage
	//
};

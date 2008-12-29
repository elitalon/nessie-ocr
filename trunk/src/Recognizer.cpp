/// @file
/// @brief Implementation of the class Recognizer

#include "Recognizer.hpp"
#include "Clip.hpp"



///
/// @details Creates an empty Recognizer object with neither text nor statistics set.
///
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

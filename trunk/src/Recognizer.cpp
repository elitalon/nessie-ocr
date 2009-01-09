/// @file
/// @brief Implementation of the class Recognizer

#include "Recognizer.hpp"
#include "Clip.hpp"
#include "Preprocessor.hpp"



Recognizer::Recognizer ()
	:	text_(),
		statistics_()
{};


///
/// @details This method executes the recognition process in four stages: preprocessing, feature extraction, classification and postprocessing.
///
/// As the first important step, image and data <em>preprocessing</em> serve the purpose of extracting regions of interest, enhancing and cleaning up
/// the images, so that they can be directly and efficiently processed by the feature extraction stage.
///
void Recognizer::extractText (const Clip& pressClip)
{
	//
	// Preprocessing stage
	//	1. Global gray level thresholding (otsu's and sonka's method, background gray level detection)
	//	2. Smoothing and noise removal (filtering)
	//	3. Skew detection and correction (future work)
	//	4. Slant detection and correction
	//	5. Character normalization
	//	6. Thinning (skeleton construction)
	//
	Preprocessor preprocessor(pressClip);
	preprocessor.applyGlobalThresholding();


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

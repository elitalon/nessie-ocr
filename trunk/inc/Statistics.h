#if !defined(_STATISTICS_H)
#define _STATISTICS_H

///
/// @file
/// @brief Declaration of struct Statistics
///

#include "WordRate.h"

#include <vector>
using namespace std;



///
/// Statistics about a text and its recognition process.
/// 
/// This struct stores a number of statistic data regarding the recognition process
/// and the text produced.
/// 
/// First, it stores the elapsed time on every stage, accumulated internally in the
/// critical processes (mostly, image processing algorithms). Second, it also stores
/// the number of words in the text and the appearance rate of every single word.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-18
/// 
struct Statistics
{
	public:
		
		///
		/// Number of words in the recognized text
		///
		unsigned int nWords;
		
		///
		/// List of appearance rates of every word in the recognized text
		///
		vector<WordRate> wordRates;
		
		///
		/// Elapsed time in the noise removal stage
		///
		double noiseRemovalTime;
		
		///
		/// Elapsed time in the grayscale conversion stage
		///
		double grayscaleConversionTime;
		
		///
		/// Elapsed time in the flood filling stage
		///
		double floodFillingTime;
		
		///
		/// Elapsed time in the thresholding stage
		///
		double thresholdingTime;
		
		///
		/// Elapsed time in the feature vectors building stage
		///
		double featureVectorsBuildingTime;
		
		///
		/// Elapsed time in the characters extraction stage
		///
		double charactersExtractionTime;
		
		///
		/// Returns the total time within the classification stage
		/// 
		double classificationTime;
		
		///
		/// Returns the total time within the segmentation stage
		/// 
		double segmentationTime;
		
		///
		/// Returns the total time within the preprocessing stage
		/// 
		double preprocessingTime;
		
		
		///
		/// Constructor
		/// 
		Statistics ();
		
		///
		/// Destructor
		/// 
		~Statistics ();
};

#endif  //_STATISTICS_H

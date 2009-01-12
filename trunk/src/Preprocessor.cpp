/// @file
/// @brief Definition of Preprocessor class

#include "Preprocessor.hpp"
#include <boost/timer.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>



Preprocessor::Preprocessor (const Clip& pressClip)
	:	clip_(pressClip),
		statistics_(PreprocessorStatistics())
{
	statistics_.clipSize(pressClip.size());
};


///
/// @details The algorithm uses the Otsu's method to find automatically the optimal threshold for the press clip. Then, it compares each pixel
/// gray level with that threshold and transforms the source clip into a binary image. As a result, the final histogram is bimodal.
///
void Preprocessor::applyGlobalThresholding ()
{
	unsigned char threshold = computeOtsuOptimalThreshold();
};


///
/// @details The strategy proposed by N. Otsu in "A Threshold Selection Method from Gray-Level Histograms" (1979) maximises the likelihood that the
/// threshold is chosen so as to split the image between and object and its background. An optimal threshold is selected by the discriminant
/// criterion, namely, so as to maximize the separability of the resultant classes in gray levels. The procedure is very simple, utilizing only the
/// zeroth- and the first-order cumulative moments of the gray-level histogram.
///
unsigned char Preprocessor::computeOtsuOptimalThreshold () const
{
	// Compute the normalized clip histogram 
	std::deque<double> histogram(256, 0.0);
	
	for ( unsigned int i = 0; i < clip_.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip_.width(); ++j )
		{
			unsigned int grayLevel = static_cast<unsigned int>(clip_(i,j));
			
			histogram.at(grayLevel) += 1.0;
		}
	}
	std::transform (histogram.begin(), histogram.end(), histogram.begin(), std::bind2nd(std::divides<double>(), clip_.size()) );
	
	
	// Compute the total mean gray level of the clip
	double totalMeanGrayLevel = 0.0;
	for ( unsigned int i = 1; i <= histogram.size(); ++i )
		totalMeanGrayLevel += histogram.at(i-1) * static_cast<double>(i);
		
	
	// Compute the zeroth- and first-order cumulative moments, i.e. the probabilities of class occurrence and the
	// class mean levels up to level i-th.
	std::deque<double> zerothOrderMoment(256, 0.0);
	std::deque<double> firstOrderMoment(256, 0.0);
	for ( unsigned int i = 0; i < histogram.size(); ++i )
	{
		for ( unsigned int j = 0; j < i; ++j )
		{
			zerothOrderMoment.at(i)	+= histogram.at(j);
			firstOrderMoment.at(i)	+= static_cast<double>(j+1) * histogram.at(j);
		}
	}
	
	
	// Compute the between-class variance, according to the criterion measurements used in the discriminant analysis
	std::deque<double> betweenClassVariance(256, 0.0);
	for ( unsigned int i = 0; i < histogram.size(); ++i )
	{
		double numerator = pow(totalMeanGrayLevel * zerothOrderMoment.at(i) - firstOrderMoment.at(i), 2);
		double denominator = zerothOrderMoment.at(i) * (1 - zerothOrderMoment.at(i));
		
		if ( std::isnan(numerator / denominator) )
			betweenClassVariance.at(i) = 0.0;
		else
			betweenClassVariance.at(i) = numerator / denominator;
	}
	
	
	// Find the gray level that maximizes the between-class variance
	std::deque<double>::iterator maximumVariance = std::max_element(betweenClassVariance.begin(), betweenClassVariance.end());
	std::deque<double>::iterator i = betweenClassVariance.begin();
	unsigned char optimalThreshold = 0;

	while ( i not_eq maximumVariance )
	{
		++i;
		++optimalThreshold;
	}
	
	return optimalThreshold;
};


///
/// @details The strategy proposed by M. Sonka, V. Hlavac and R. Boyle in "Image Processing, Analysis and Machine Vision" (2008) is to find a mean
/// value between the mean value of background's gray level and the mean value of objects' gray level, starting from an initial threshold that is
/// computed from the four corners of the press clip. 
///
unsigned char Preprocessor::computeSonkaOptimalThreshold () const
{
	// Start with an initial threshold
	unsigned char optimalThreshold = (clip_(0,0) + clip_(0, clip_.width()-1) + clip_(0, clip_.height()-1) + clip_(clip_.height()-1,clip_.width()-1)) / 4;
	unsigned char currentThreshold = ~optimalThreshold;

	// Loop as many times as needed to find the optimal threshold by averaging the pixel gray levels
	while (currentThreshold not_eq optimalThreshold)
	{
		double backgroundMeanValue = 0.0, objectsMeanValue = 0.0;
		unsigned int nSamples = 0;

		// Count the pixels that belong to objects and the pixels that belong to background
		for ( unsigned int i = 0; i < clip_.height(); ++i )
		{
			for ( unsigned int j = 0; j < clip_.width(); ++j )
			{
				unsigned char grayLevel = clip_(i, j);

				if ( grayLevel >= optimalThreshold )
				{
					backgroundMeanValue += static_cast<double>(grayLevel);
					nSamples++;
				}
				else
					objectsMeanValue += static_cast<double>(grayLevel);
			}
		}
		backgroundMeanValue = round(backgroundMeanValue / static_cast<double>(nSamples));
		objectsMeanValue = round(objectsMeanValue / static_cast<double>(clip_.size() - nSamples));

		// Update the optimal threshold keeping the last one
		currentThreshold = optimalThreshold;
		optimalThreshold = static_cast<unsigned char>( round((objectsMeanValue + backgroundMeanValue) / 2.0) );
	}
	
	return optimalThreshold;
};



// /
// / @details To find the reference gray level of the background it is assumed that there are more pixels belonging to the
// / background than belonging to the foreground. Then, we search the more frequent gray level and its neighbours. Finally, we compute
// / a gray level weighted mean using all those values.
// /
// / @bug There are cases where the reference gray level found does not match with the real background gray level, because the assumption made about
// / the background's number of pixels is false. An alternative may be to find two reference gray levels; if the classification process does not work,
// / everything must be undone and start again with the second reference gray level.
// /
//const unsigned char& Preprocessor::findBackgroundReferenceGrayLevel (const unsigned int& referenceGrayLevelNeighbours)
// {
// 	// Start timing
// 	boost::timer timer;
// 	timer.restart();
// 
// 
// 	// Compute clip's histogram
// 	std::vector<unsigned int> histogram(256, 0);
// 	for ( unsigned int i = 0; i < clip_.height(); ++i )
// 	{
// 		for ( unsigned int j = 0; j < clip_.width(); ++j )
// 		{
// 			histogram[static_cast<unsigned int>(clip_(i, j))] += 1;
// 		}
// 	}
// 
// 
// 	// Search the more frequent level of gray
// 	std::vector<unsigned int>::iterator histogramIterator;
// 	unsigned int moreFrequentGrayLevel = 0;
// 	unsigned int maximumAppearances	= histogram[0];
// 
// 	for ( unsigned int l = 1; l < 256; ++l )
// 	{
// 		if ( histogram[l] > maximumAppearances )
// 		{
// 			moreFrequentGrayLevel	= l;
// 			maximumAppearances		= histogram[l];
// 		}
// 	}
// 	unsigned int referenceGrayLevel = moreFrequentGrayLevel * histogram[moreFrequentGrayLevel];
// 
// 
// 	// Search the neighbours of the more frequent level of gray
// 	std::vector<unsigned int>::reverse_iterator histogramReverseIterator( std::find (histogram.rbegin(), histogram.rend(), histogram[moreFrequentGrayLevel])++ );
// 	histogramIterator = histogramReverseIterator.base()++;
// 	unsigned int nFrequencies = histogram[moreFrequentGrayLevel];
// 
// 	for ( unsigned int i = 1; i <= referenceGrayLevelNeighbours; ++i )
// 	{
// 		// Search forwards
// 		if ( histogramIterator not_eq histogram.end() )
// 		{
// 			referenceGrayLevel	+= (moreFrequentGrayLevel + i) * histogram[moreFrequentGrayLevel + i];
// 			nFrequencies		+= histogram[moreFrequentGrayLevel + i];
// 
// 			++histogramIterator;
// 		}
// 
// 		// Search backwards
// 		if ( histogramReverseIterator not_eq histogram.rend() )
// 		{
// 			referenceGrayLevel	+= (moreFrequentGrayLevel - i) * histogram[moreFrequentGrayLevel - i];
// 			nFrequencies		+= histogram[moreFrequentGrayLevel - i];
// 
// 			++histogramReverseIterator;
// 		}
// 	}
// 
// 	// Set the background reference gray level found
// 	backgroundReferenceGrayLevel_ = static_cast<unsigned char>( round(referenceGrayLevel / nFrequencies) );
// 
// 	// Gather elapsed time
// 	backgroundReferenceGrayLevelFindingTime_ = timer.elapsed();
// 
// 	return backgroundReferenceGrayLevel_;
// };


///
/// @details The 'isolated noise removal' algorithm tries to eliminate isolated noisy pixels from an clip. The isolationCoefficient parameter
/// defines how much isolated should be a noisy pixel to be removed. That means a noisy pixel will be removed whenever it has as much neighbours
/// whose gray level is over a threshold value as isolationCoefficient
///
void Preprocessor::removeIsolatedNoise (const unsigned int& isolationCoefficient)
{
	// // Start timing
	// boost::timer timer;
	// timer.restart();
	// 
	// 
	// // Loop over the clip to remove every noisy isolated pixel
	// for (unsigned int i=0; i < clip_.height(); ++i)
	// {
	// 	for (unsigned int j=0; j < clip_.width(); ++j)
	// 	{
	// 		unsigned char pixelGrayLevel = clip_(i, j);
	//
	// 		// Comparison values to avoid pixels that clearly belong to the background
	// 		bool backgroundPixelOnWhite = (backgroundReferenceGrayLevel_ > optimalThreshold_) and (pixelGrayLevel >= backgroundReferenceGrayLevel_);
	// 		bool backgroundPixelOnBlack = (backgroundReferenceGrayLevel_ < optimalThreshold_) and (pixelGrayLevel <= backgroundReferenceGrayLevel_);
	// 
	// 		if ( not backgroundPixelOnBlack and not backgroundPixelOnWhite )
	// 		{
	// 			unsigned int nBackgroundPixels = 0, nPixels = 0;
	// 
	// 			// Explore the pixel neighbourhood
	// 			for(int p = i-1; p < static_cast<int>(i+2); p++)
	// 			{
	// 				for(int q = j-1; q < static_cast<int>(j+2); q++)
	// 				{
	// 					// Comparison values to avoid step outside the image and the central pixel
	// 					bool heightOverflow	= (p < 0) or (p >= static_cast<int>(clip_.height()));
	// 					bool widthOverflow	= (q < 0) or (q >= static_cast<int>(clip_.width()));
	// 					bool isCentralPixel = (p == static_cast<int>(i)) and (q == static_cast<int>(j));
	// 
	// 					if ( not heightOverflow and not widthOverflow and not isCentralPixel )
	// 					{
	// 						// Update pixels counter
	// 						nPixels++;
	// 
	// 						// Get neighbour pixel gray level
	// 						unsigned char neighbourPixelGrayLevel = clip_(p, q);
	// 
	// 						// When background gray level is close to white but not the pixel, update the noisy neighbours counter
	// 						if ( (backgroundReferenceGrayLevel_ >= optimalThreshold_) and (neighbourPixelGrayLevel >= optimalThreshold_) )
	// 							nBackgroundPixels++;
	// 						else
	// 						{
	// 							// When background gray level is close to black but not the pixel, update the noisy neighbours counter
	// 							if ( (backgroundReferenceGrayLevel_ < optimalThreshold_) and (neighbourPixelGrayLevel <= optimalThreshold_) )
	// 								nBackgroundPixels++;
	// 						}
	// 					}
	// 				}
	// 			}
	// 
	// 			// Clear the noisy pixel if it is isolated
	// 			if (nBackgroundPixels >= (nPixels - isolationCoefficient))
	// 				clip_(i, j) = backgroundReferenceGrayLevel_;
	// 		}
	// 	}
	// }
	// 
	// // Gather elapsed time
	// noiseRemovalTime_ = timer.elapsed();
};



///
/// @details This method isolates every shape in a press clip by connecting pixels of ink that are located together in a 3x3 neighbourhood. The shapes
/// may contain a subset of shapes, since further processing is applied to join accents and other punctuation signs to their characters. The final list
/// of shapes is sorted by lines and columns, so that traversing the list is equivalent to read the text from left to right and from up to down.
///
// void Preprocessor::findShapes (const Clip& clip)
// {
// 	// Start timing
// 	boost::timer timer;
// 	timer.restart();
// 
// 
// 	// Find the seeds where the flooding process will start from
// 	findSeeds(clip);
// 	std::cout << "Seeds                        : " << seeds_.size() << std::endl;
// 
// 
// 	// Obtain the initial shapes
// 	growSeedsIntoInitialShapes(clip);
// 	std::cout << "Initial shapes               : " << shapes_.size() << std::endl;
// 
// 
// 	// Find the markers that delimit the lines
// 	findLineMarkers(clip);
// 	std::cout << "Lines of text                : " << lineMarkers_.size() << std::endl;
// 
// 
// 	// Join accents to their vocals in a line of characters
// 	for ( LineMarkerIterator i = lineMarkers_.begin(); i not_eq lineMarkers_.end(); ++i )
// 	{
// 		unsigned int lineTop	= (*i).first;
// 		unsigned int lineBottom	= (*i).second;
// 
// 		// Iterator to the list of shapes
// 		ShapeIterator iShape = shapes_.begin();
// 
// 		// Traverse the list of shapes,. For each shape it is searched another shape that is vertically overlapped
// 		while ( iShape not_eq shapes_.end() )
// 		{
// 			bool shapeIsAboveTheLine = ((*iShape).topPixel().first < lineTop) and ((*iShape).bottomPixel().first < lineTop);
// 			bool shapeIsBelowTheLine = ((*iShape).topPixel().first > lineBottom) and ((*iShape).bottomPixel().first > lineBottom);
// 
// 			// Avoid processing a shape that is outside the line borders
// 			if ( shapeIsAboveTheLine or shapeIsBelowTheLine )
// 				advance (iShape, 1);
// 			else
// 			{
// 				ShapeIterator jShape = findVerticallyOverlappedShape(lineTop, lineBottom, iShape);
// 
// 				if ( jShape not_eq iShape )
// 					joinVerticallyOverlappedShapes( iShape, jShape );
// 				else
// 					advance(iShape, 1);
// 			}
// 		}
// 	}
// 
// 
// 	// Sort the shapes by lines and columns
// 	shapes_.sort();
// 
// 
// 	// Gather elapsed time
// 	shapesFindingTime_ = timer.elapsed();
// };



///
/// @details A seed is a pixel that has a gray level equal to the gray level of characters in the clip. Thus, the seeds founded by this method
/// are actually all the pixels that do not belong to the background in the clip.
///
void Preprocessor::findSeeds (const Clip& clip)
{
	// Traverse the clip searching the seeds
	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			if ( clip(i, j) == inkValue_ )
				seeds_.push_back( Pixel(i,j) );
		}
	}
};



///
/// @details The initial shapes are a set of shapes that are inconsistent with the real characters in the press clip. That is because
/// a further processing is necessary to join accents to vocals, split shapes that represents two characters joined, etc.
///
/// This method follows a strategy similar to the 'flood fill' algorithm. The main target is to isolate every shape in a clip that represents
/// a character. Every shape is built starting from an ink pixel (a seed) and exploring its neighbourhood looking for connected pixels. The process
/// ends when there are not more seeds to explore and the shapes are completely isolated.
///
void Preprocessor::growSeedsIntoInitialShapes (const Clip& clip)
{
	// Initialize the visited_ deque
	visited_ = std::deque<bool>(clip.size(), false);

	// Explore the neighbourhood of each seed. For each pixel explored, the vector above tells if it has already been explored
	for ( std::deque<Pixel>::iterator seedsIterator = seeds_.begin(); seedsIterator not_eq seeds_.end(); ++seedsIterator )
	{
		int row	= (*seedsIterator).first;
		int column	= (*seedsIterator).second;

		if ( not visited_.at(row * clip.width() + column) )	// This seed has not already been visited
		{
			visited_.at(row * clip.width() + column) = true;

			// This seed begins a new shape
			shapes_.push_back(Shape());
			shapes_.back().addPixel( Pixel(row, column) );


			// Explore the seed's neighbourhood
			for ( int i = row-1; (i <= row+1) and (i < static_cast<int>(clip.height())); ++i )
			{
				for ( int j = column-1; (j <= column+1) and (j < static_cast<int>(clip.width())); ++j )
				{
					// Test clip borders are not passed
					if ( i >= 0 and j >= 0 )
					{
						// Add this neighbour if has ink and has already not been visited
						if ( clip(i,j) == inkValue_ and not visited_.at(i * clip.width() + j) )
						{
							visited_.at(i * clip.width() + j) = true;
							shapes_.back().addPixel( Pixel(i, j) );
						}
					}
				}
			}


			// Explore the neighbours of the neighbours of the seed.
			unsigned int lastPixelPosition = 1;
			while ( shapes_.back().size() > lastPixelPosition )
			{
				Pixel pixel( shapes_.back()(lastPixelPosition) );

				// Explore the neighbour's neighbourhood
				for ( int i = pixel.first-1; (i <= static_cast<int>(pixel.first+1)) and (i < static_cast<int>(clip.height())); ++i )
				{
					for ( int j = pixel.second-1; (j <= static_cast<int>(pixel.second+1)) and (j < static_cast<int>(clip.width())); ++j )
					{
						// Test clip borders are not passed
						if ( i >= 0 and j >= 0 )
						{
							// Add this neighbour if has ink and has already not been visited
							if ( clip(i,j) == inkValue_ and not visited_.at(i * clip.width() + j) )
							{
								visited_.at(i * clip.width() + j) = true;
								shapes_.back().addPixel( Pixel(i, j) );
							}
						}
					}
				}

				// Update the pixel's counter
				lastPixelPosition++;
			}
		}
	}
};



///
/// @details Each row is isolated by searching horizontal blank lines between characters. Every time a row with no pixels of ink is found following
/// a row with some pixels of ink a top marker is set. Then, the following rows are explored until a new blank line is found. The line before
/// that last blank line is set as the bottom marker of the line.
///
void Preprocessor::findLineMarkers (const Clip& clip)
{
	unsigned int topRow = 0;
	bool rowHasInk = false, previousRowHasInk;

	// Traverse the clip searching non-visited pixels
	for ( unsigned int i = 0; i < clip.height(); ++i )
	{
		previousRowHasInk	= rowHasInk;
		rowHasInk			= false;

		unsigned int nVisitedPixels = 0;
		for ( unsigned int j = 0; j < clip.width(); ++j )
		{
			if ( visited_.at(i * clip.width() + j) )
				nVisitedPixels++;
		}

		// A line with less than three pixels of ink is assumed as a blank line
		if ( nVisitedPixels > 2 )
			rowHasInk = true;

		// Check if a new line border has been found
		if ( rowHasInk )
		{
			if (not previousRowHasInk)
		    	topRow = i;
		}
		else
		{
			if ( previousRowHasInk )
				lineMarkers_.push_back( LineMarker(topRow, i-1) );
			else
				topRow = i;
		}
	}

	// Check the last line ends with the image border
    if ( rowHasInk and previousRowHasInk )
		lineMarkers_.push_back( LineMarker(topRow, clip.height()-1) );


	// Compute the mean shape height
	double meanShapeHeight = 0.0;

	for ( ShapeIterator iShape = shapes_.begin(); iShape not_eq shapes_.end(); ++iShape )
		meanShapeHeight += (*iShape).height();

	meanShapeHeight = meanShapeHeight / static_cast<double>(shapes_.size());


	// Point iterators to the first two elements
	LineMarkerIterator previousLineMarkerIterator	= lineMarkers_.begin();
	LineMarkerIterator currentLineMarkerIterator	= lineMarkers_.begin();
	advance( currentLineMarkerIterator, 1 );

	// Search for lines that are too close to each other, probably because there are characters with accents in a single line
	while ( currentLineMarkerIterator not_eq lineMarkers_.end() )
	{
		// An accent is as much as three times smaller than the mean shape height
		if ( (*currentLineMarkerIterator).first - ((*previousLineMarkerIterator).second + 1) >= meanShapeHeight )
		//if ( ((*previousLineMarkerIterator).second - (*previousLineMarkerIterator).first + 1) >= round(meanShapeHeight / 4.0) )
		{
			// This is not an accent
			advance( currentLineMarkerIterator, 1 );
			advance( previousLineMarkerIterator, 1 );
		}
		else
		{
			// A new line marker representing the union of the two line markers that are being handled is inserted
			// and the two old line markers are removed from the list

			lineMarkers_.insert( previousLineMarkerIterator, LineMarker((*previousLineMarkerIterator).first, (*currentLineMarkerIterator).second) );

			LineMarkerIterator newLineMarkerIterator = previousLineMarkerIterator;
			advance ( newLineMarkerIterator, -1 );

			// Delete the first line marker
			lineMarkers_.erase( previousLineMarkerIterator );

			// Delete the second line marker
			previousLineMarkerIterator = currentLineMarkerIterator;
			advance( currentLineMarkerIterator, 1 );
			lineMarkers_.erase( previousLineMarkerIterator );

			// Point to the new element inserted
			previousLineMarkerIterator = newLineMarkerIterator;
		}
	}
};



void Preprocessor::joinVerticallyOverlappedShapes (ShapeIterator& s1, ShapeIterator& s2)
{
	// Join shapes into a new one and insert it before the current shape
	shapes_.push_back(*s1 + *s2);

	// Delete the second shape
	shapes_.erase(s2);

	// Update iterators
	s2 = s1;
	advance(s2, 1);

	// Delete the first shape
	shapes_.erase(s1);
	s1 = s2;
};



///
/// @details The list of shapes is traversed in order to find a shape that is vertically overlapped with the shape passed. A shape is considered
/// as overlapped when at least one pixel is overlapped with the shape of interest. This minimum criteria is necessary because of characters that
/// are too small.
///
Preprocessor::ShapeIterator Preprocessor::findVerticallyOverlappedShape (const unsigned int& lineTop, const unsigned int& lineBottom, const ShapeIterator& shape)
{
	for ( ShapeIterator i = shapes_.begin(); i not_eq shapes_.end(); ++i )
	{
		// Avoid processing a shape against itself
		if ( shape == i )
			continue;

		bool candidateShapeIsAboveShapeOfInterest = ((*i).topPixel().first < lineTop) and ((*i).bottomPixel().first <= lineTop);
		bool candidateShapeIsBelowShapeOfInterest = ((*i).topPixel().first >= lineBottom) and ((*i).bottomPixel().first > lineBottom);

		// Avoid processing a shape that is outside the line borders
		if ( candidateShapeIsAboveShapeOfInterest or candidateShapeIsBelowShapeOfInterest )
			continue;

		unsigned int overlappedPixels	= 0;

		// Count the overlapped pixels that the shape has with the shape of interest
		for ( unsigned int j = 0; j < (*i).size(); ++j )
		{
			if ( ((*i)(j).second > (*shape).leftPixel().second) and ((*i)(j).second < (*shape).rightPixel().second) )
				overlappedPixels++;
		}

		// Check if the shape is overlapped with the shape of interest
		if ( overlappedPixels >= 1)
			return i;
	}
	return shape;
};


///
/// @details In order to find th spaces between words it is assumed that the mean inter-character space is always less than the mean inter-word space.
/// Once the mean inter-character space is computed, a simple searching for each line gives the location of every space between words.
///
void Preprocessor::findSpaceLocations ()
{
	// Compute the mean inter-character space
	ShapeIterator iShape = shapes_.begin();
	advance (iShape, 1);

	ShapeIterator jShape = shapes_.begin();

	double meanIntercharacterSpace = 0.0;
	while ( iShape not_eq shapes_.end() )
	{
		if ( (*iShape).leftPixel().second >= (*jShape).rightPixel().second )
			meanIntercharacterSpace += (*iShape).leftPixel().second - (*jShape).rightPixel().second;

		advance (iShape, 1);
		advance (jShape, 1);
	}
	meanIntercharacterSpace = round(meanIntercharacterSpace / shapes_.size());
	std::cout << "Mean intercharacter space    : " << meanIntercharacterSpace << std::endl;


	// Count the number of spaces within a text
	iShape = shapes_.begin();
	advance (iShape, 1);

	jShape = shapes_.begin();

	double spaces = 0;
	while ( iShape not_eq shapes_.end() )
	{
		if ( (*iShape).leftPixel().second < (*jShape).rightPixel().second )	// end-of-line
			spaces++;
		else
		{
			unsigned int distanceBetweenCharacters = (*iShape).leftPixel().second - (*jShape).rightPixel().second;

			if ( distanceBetweenCharacters > meanIntercharacterSpace )
				spaces++;
		}
		advance (iShape, 1);
		advance (jShape, 1);
	}
	std::cout << "Spaces found                 : " << spaces << std::endl;
};

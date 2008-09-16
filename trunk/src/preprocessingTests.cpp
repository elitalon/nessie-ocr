#include <list> 
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

#include <Magick++.h>
using namespace Magick;


/**
 * @fn threshold(Image* image, double threshold)
 * @brief Apply thresholding over an image.
 *
 *	This method applies a threshold over each pixel on image.
 *
 *	@author: Eliezer Talón
 *	@date: 29/09/2008
 */
void threshold(Image* image, double threshold);



/** @file main.cpp
 * @brief Main program
 *
 * Detailed description
 */
int main (int argc, char const *argv[])
{
	Image img;			/**< Magick++ object */
	string outputFile;	/**< Output file path */
	string inputFile;	/**< Input file path */

	// Check for filename
	if( argv[1] == NULL )
	{
		cout<< "There's no input file" << endl;
		return 1;
	}


	// Create output file name
	try
	{
		int dotPosition;

		// Assign the file name
		outputFile = argv[1];

		// Search the dot position
		dotPosition = outputFile.find('.');

		// Append a suffix
		outputFile.insert(dotPosition, "_SingleNoise");

		// Search the new dot position
		dotPosition = outputFile.find('.');

		// Change the file extension
		outputFile.replace(dotPosition+1, outputFile.size(), "png");

		cout<< "Input file: " << argv[1] << endl;
		cout<< "Output file: " << outputFile << endl;
	}
	catch ( std::exception &error_ )
	{
		cout << "Caught exception: " << error_.what() << endl;
		return 1;
	}


	// Open the image, average it and write the results to another file
	try
	{
		// Read image from file
		img.read( argv[1] );

		// Change image colormap to gray scale
		img.type( GrayscaleType );
		
		// Calculate threshold
		//double T = 155.0 / 255.0;
		//cout << "Threshold: " << T << endl;
				
		// Apply simple threshold
		//threshold( &img, T);
		
		// Apply adaptive threshold
		//img.adaptiveThreshold(35,70);

		// Write results to a new file
		//img.write( outputFile );

		// Show results in console
		cout << endl <<"Pixels: " << (img.rows() * img.columns()) << endl;
	}
	catch ( Exception &error_ )
	{
		cout << "Caught exception: " << error_.what() << endl;
		return 1;
	}

	return 0;
}	


void threshold(Image *image, double threshold)
{
	try
	{
		PixelPacket *originPixel, *pixel;

		// Allocate pixel frame
		Pixels frame(*image);
		originPixel = frame.get(0, 0, (*image).columns(), (*image).rows());

		// Apply averaging
		for ( unsigned int row = 0; row < frame.rows() ; row++ )
		{
			for ( unsigned int column = 0; column < frame.columns() ; column++ )
			{
				// Get pixel intensity
				pixel = originPixel + (row * frame.columns()) + column;
				ColorGray brightness( *pixel );

				// Update the pixel count
				if ( brightness.shade() > threshold )
					*pixel = ColorGray(1.0);
				else
					*pixel = ColorGray(0.0);
			}
		}

		// Write the image to a file
		frame.sync();
	}
	catch ( Exception &error_ )
	{
		cout << "Caught exception: " << error_.what() << endl;
	}
}



/*
	Isolated noise elimination
	
		int main (int argc, char const *argv[])
		{
			Image img;
			string outputFile;
			string inputFile;

			// Check for filename
			if( argv[1] == NULL )
			{
				cout<< "There's no input file" << endl;
				return 1;
			}


			// Create output file name
			try
			{
				int dotPosition;

				// Assign the file name
				outputFile = argv[1];

				// Search the dot position
				dotPosition = outputFile.find('.');

				// Append a suffix
				outputFile.insert(dotPosition, "_SingleNoise");

				// Search the new dot position
				dotPosition = outputFile.find('.');

				// Change the file extension
				outputFile.replace(dotPosition+1, outputFile.size(), "png");

				cout<< "Input file: " << argv[1] << endl;
				cout<< "Output file: " << outputFile << endl;
			}
			catch ( std::exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}


			// Open the image, average it and write the results to another file
			try
			{
				clock_t referenceTime, elapsedTime;
				double averagingTime;

				PixelPacket *pixels, *rotatingPixel, *originPixel;

				// Read image from file
				img.read( argv[1] );

				// Change image colormap to gray scale
				img.type( GrayscaleType );

				// Ensure that there is only one reference to underlying image.
				// If this is not done, then image pixels will not be modified.
				img.modifyImage();

				// Set averaging time reference
				referenceTime = clock();

				// Allocate pixel frame
				Pixels frame(img);
				pixels = frame.get(0, 0, img.columns(), img.rows());
				originPixel = pixels;

				// Declare static thresholding values
				double intensityThreshold = 80 / (double) 255;
				int pixelCountThreshold = 6;

				// Apply averaging
				for (unsigned int row = 0; row < frame.rows() ; row++ )
				{
					for (unsigned int column = 0; column < frame.columns() ; column++ )
					{
						unsigned int backgroundPixels = 0, nPixels = 0;

						for(int i = row-1; i < row+2; i++)
						{
							for(int j = column-1; j < column+2; j++)
							{
								// Check image borders
								if ( (i < 0 || i >= frame.rows()) || (j < 0 || j >= frame.columns()) )
									continue;

								nPixels++;

								// Get neighbour pixel intensity
								rotatingPixel = originPixel + (i * frame.columns()) + j;
								ColorGray brightness(*rotatingPixel);

								// Update the pixel count
								if (brightness.shade() > intensityThreshold)
									backgroundPixels += 1;
							}
						}

						unsigned int realPixelCountThreshold = nPixels - 8 + pixelCountThreshold;

						// Delete the noisy pixel if it is relatively isolated
						if (backgroundPixels >= realPixelCountThreshold)
							*pixels = ColorGray(1.0);

						pixels++;
					}
				}

				// Get the averaging time
				elapsedTime = clock();
				averagingTime = (elapsedTime - referenceTime) / (float) CLOCKS_PER_SEC;

				// Write the image to a file
				frame.sync();
				img.write( outputFile );

				// Show results in console
				cout << endl <<"Pixels: " << (img.rows() * img.columns()) << endl << "Averaging time: " << averagingTime << endl;
			}
			catch ( Exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}

			return 0;
		}	
*/

/*
	Loop for cross averaging, poor results
	
		struct Neighbour
		{
			int i;
			int j;
		};
		
		int main (int argc, char const *argv[])
		{
			Image img;
			string outputFile;
			string inputFile;

			// Check for filename
			if( argv[1] == NULL )
			{
				cout<< "There's no input file" << endl;
				return 1;
			}


			// Create output file name
			try
			{
				int dotPosition;

				// Assign the file name
				outputFile = argv[1];

				// Search the dot position
				dotPosition = outputFile.find('.');

				// Append a suffix
				outputFile.insert(dotPosition, "_Averaged");

				// Search the new dot position
				dotPosition = outputFile.find('.');

				// Change the file extension
				outputFile.replace(dotPosition+1, outputFile.size(), "png");

				cout<< "Input file: " << argv[1] << endl;
				cout<< "Output file: " << outputFile << endl;
			}
			catch ( std::exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}


			// Open the image, average it and write the results to another file
			try
			{
				clock_t referenceTime, elapsedTime;
				double averagingTime;

				PixelPacket *pixels, *rotatingPixel, *originPixel;

				// Read image from file
				img.read( argv[1] );

				// Change image colormap to gray scale
				img.type( GrayscaleType );

				// Ensure that there is only one reference to underlying image.
				// If this is not done, then image pixels will not be modified.
				img.modifyImage();

				// Set averaging time reference
				referenceTime = clock();

				// Allocate pixel frame
				Pixels frame(img);
				pixels = frame.get(0, 0, img.columns(), img.rows());
				originPixel = pixels;

				// Apply averaging
				for (unsigned int row = 0; row < frame.rows() ; row++ )
				{
					for (unsigned int column = 0; column < frame.columns() ; column++ )
					{
						int selectedMask = 8;		// The pixel itself by default
						Neighbour neighbours[5];	// Neighbours coordinates
						int nPixels;				// Number of pixels averaged

						double dispersionReference = 500.0;
						double maskAverageBrightness[9], pixelNeighbourBrightness[5];
						double standardDeviation;

						// Calculate standard deviation for every rotated mask
						for(unsigned int thisMask = 0; thisMask < 9; thisMask++)
						{
							ColorGray brightness;

							switch(thisMask)
							{
								case 0:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row - 1;
									neighbours[1].j = column + 1;
									neighbours[2].i = row + 1;
									neighbours[2].j = column + 1;
									neighbours[3].i = row;
									neighbours[3].j = column + 1;
									neighbours[4].i = row;
									neighbours[4].j = column + 2;
									break;
								}
								case 1:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row - 2;
									neighbours[1].j = column;
									neighbours[2].i = row - 1;
									neighbours[2].j = column + 1;
									neighbours[3].i = row - 2;
									neighbours[3].j = column + 2;
									neighbours[4].i = row;
									neighbours[4].j = column + 2;
									break;
								}
								case 2:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row - 1;
									neighbours[1].j = column + 1;
									neighbours[2].i = row - 1;
									neighbours[2].j = column - 1;
									neighbours[3].i = row - 1;
									neighbours[3].j = column;
									neighbours[4].i = row - 2;
									neighbours[4].j = column;
									break;
								}
								case 3:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row - 2;
									neighbours[1].j = column;
									neighbours[2].i = row ;
									neighbours[2].j = column - 2;
									neighbours[3].i = row - 1;
									neighbours[3].j = column - 1;
									neighbours[4].i = row - 2;
									neighbours[4].j = column - 2;
									break;
								}
								case 4:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row;
									neighbours[1].j = column - 1;
									neighbours[2].i = row;
									neighbours[2].j = column - 2;
									neighbours[3].i = row + 1;
									neighbours[3].j = column - 1;
									neighbours[4].i = row - 1;
									neighbours[4].j = column - 1;
									break;
								}
								case 5:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row + 2;
									neighbours[1].j = column;
									neighbours[2].i = row + 2;
									neighbours[2].j = column - 2;
									neighbours[3].i = row;
									neighbours[3].j = column - 2;
									neighbours[4].i = row + 1;
									neighbours[4].j = column - 1;
									break;
								}
								case 6:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row + 1;
									neighbours[1].j = column;
									neighbours[2].i = row + 2;
									neighbours[2].j = column;
									neighbours[3].i = row + 1;
									neighbours[3].j = column - 1;
									neighbours[4].i = row + 1;
									neighbours[4].j = column + 1;
									break;
								}
								case 7:
								{
									neighbours[0].i = row;
									neighbours[0].j = column;
									neighbours[1].i = row + 2;
									neighbours[1].j = column;
									neighbours[2].i = row + 2;
									neighbours[2].j = column + 2;
									neighbours[3].i = row;
									neighbours[3].j = column + 2;
									neighbours[4].i = row + 1;
									neighbours[4].j = column + 1;
									break;
								}
								default:	// 8
								{
									neighbours[0].i = row ;
									neighbours[0].j = column;
									neighbours[1].i = row + 1;
									neighbours[1].j = column;
									neighbours[2].i = row - 1;
									neighbours[2].j = column;
									neighbours[3].i = row;
									neighbours[3].j = column + 1;
									neighbours[4].i = row;
									neighbours[4].j = column - 1;
									break;
								}
							}


							// Inspect every pixel in mask
							maskAverageBrightness[thisMask] = 0.0;
							nPixels = 0;
							for(unsigned int n = 0; n < 5; n++)
							{
								int i = neighbours[n].i;
								int j = neighbours[n].j;

								// Check image borders
								if ( i < 0 || i >= frame.rows() )
									continue;
								if ( j < 0 || j >= frame.columns() )
									continue;

								// Store brightness value
								rotatingPixel = originPixel + (i * frame.columns()) + j;
								brightness = ColorGray(*rotatingPixel);

								maskAverageBrightness[thisMask] += brightness.shade();
								pixelNeighbourBrightness[nPixels] =  brightness.shade();
								nPixels++;
							}
							maskAverageBrightness[thisMask] = maskAverageBrightness[thisMask] / (float) nPixels;


							// Calculate standard deviation
							standardDeviation = 0.0;
							for(int q = 0; q < nPixels; q++)
							{
								standardDeviation += (double) pow(pixelNeighbourBrightness[q] - maskAverageBrightness[thisMask], 2); 
							}
							standardDeviation = (1 / ((double) (nPixels - 1))) * standardDeviation;
							standardDeviation = (double) sqrt(standardDeviation);

							if (standardDeviation < dispersionReference)
							{
								dispersionReference = standardDeviation;
								selectedMask = thisMask;
							}
						}

						// Set new brightness value
						*pixels = ColorGray(maskAverageBrightness[selectedMask]);
						pixels++;
					}
				}

				// Get the averaging time
				elapsedTime = clock();
				averagingTime = (elapsedTime - referenceTime) / (float) CLOCKS_PER_SEC;

				// Write the image to a file
				frame.sync();
				img.write( outputFile );

				// Show results in console
				cout << endl <<"Pixels: " << (img.rows() * img.columns()) << endl << "Averaging time: " << averagingTime << endl;
			}
			catch ( Exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}

			return 0;
		}
*/

/*
	Loop for 3x3 averaging, too agressive
	
		int main (int argc, char const *argv[])
		{
			Image img;
			string outputFile;
			string inputFile;

			// Check for filename
			if( argv[1] == NULL )
			{
				cout<< "There's no input file" << endl;
				return 1;
			}


			// Create output file name
			try
			{
				int dotPosition;

				// Assign the file name
				outputFile = argv[1];

				// Search the dot position
				dotPosition = outputFile.find('.');

				// Append a suffix
				outputFile.insert(dotPosition, "_Averaged");

				// Search the new dot position
				dotPosition = outputFile.find('.');

				// Change the file extension
				outputFile.replace(dotPosition+1, outputFile.size(), "png");

				cout<< "Input file: " << argv[1] << endl;
				cout<< "Output file: " << outputFile << endl;
			}
			catch ( std::exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}


			// Open the image, average it and write the results to another file
			try
			{
				clock_t referenceTime, elapsedTime;
				double averagingTime;

				PixelPacket *pixels, *rotatingPixel, *originPixel;

				// Read image from file
				img.read( argv[1] );

				// Change image colormap to gray scale
				img.type( GrayscaleType );

				// Ensure that there is only one reference to underlying image.
				// If this is not done, then image pixels will not be modified.
				img.modifyImage();

				// Set averaging time reference
				referenceTime = clock();

				// Allocate pixel frame
				Pixels frame(img);
				pixels = frame.get(0, 0, img.columns(), img.rows());
				originPixel = pixels;

				// Apply averaging
				for (unsigned int row = 0; row < frame.rows() ; row++ )
				{
					for (unsigned int column = 0; column < frame.columns() ; column++ )
					{
						int selectedMask = 6;	// The pixel itself by default
						int i, j;				// Origin of mask	
						int nPixels;			// Number of pixels averaged

						double dispersionReference = 500.0;
						double maskAverageBrightness[9], pixelNeighbourBrightness[9];
						double standardDeviation;

						// Calculate standard deviation for every rotated mask
						for(unsigned int thisMask = 0; thisMask < 9; thisMask++)
						{
							ColorGray brightness;

							switch(thisMask)
							{
								case 0:
								{
									i = row - 2;
									j = column;
									break;
								}
								case 1:
								{
									i = row - 2;
									j = column - 1;
									break;
								}
								case 2:
								{
									i = row - 2;
									j = column - 2;
									break;
								}
								case 3:
								{
									i = row - 1;
									j = column - 2;
									break;
								}
								case 4:
								{
									i = row;
									j = column - 2;
									break;
								}
								case 5:
								{
									i = row;
									j = column - 1;
									break;
								}
								case 6:
								{
									i = row;
									j = column;
									break;
								}
								case 7:
								{
									i = row - 1;
									j = column;
									break;
								}
								default:
								{
									i = row - 1;
									j = column - 1;
									break;
								}
							}

							maskAverageBrightness[thisMask] = 0.0;
							nPixels = 0;
							for(int x = i; x < i+3; x++)
							{
								// Check image borders
								if ( x < 0 || x >= frame.rows() )
									continue;

								for(int y = j; y < j+3; y++)
								{
									if ( y < 0 || y >= frame.columns() )
										continue;

									// Store brightness values
									rotatingPixel = originPixel + (x * frame.columns()) + y;
									brightness = ColorGray(*rotatingPixel);

									maskAverageBrightness[thisMask] += brightness.shade();
									pixelNeighbourBrightness[nPixels] =  brightness.shade();
									nPixels++;
								}
							}
							maskAverageBrightness[thisMask] = maskAverageBrightness[thisMask] / (float) nPixels;


							// Calculate standard deviation
							standardDeviation = 0.0;
							for(int q = 0; q < nPixels; q++)
							{
								standardDeviation += (double) pow(pixelNeighbourBrightness[q] - maskAverageBrightness[thisMask], 2); 
							}
							standardDeviation = (1 / ((double) (nPixels - 1))) * standardDeviation;
							standardDeviation = (double) sqrt(standardDeviation);

							if (standardDeviation < dispersionReference)
							{
								dispersionReference = standardDeviation;
								selectedMask = thisMask;
							}
						}

						// Set new brightness value
						*pixels = ColorGray(maskAverageBrightness[selectedMask]);
						pixels++;
					}
				}

				// Get the averaging time
				elapsedTime = clock();
				averagingTime = (elapsedTime - referenceTime) / (float) CLOCKS_PER_SEC;

				// Write the image to a file
				frame.sync();
				img.write( outputFile );

				// Show results in console
				cout << endl <<"Pixels: " << (img.rows() * img.columns()) << endl << "Averaging time: " << averagingTime << endl;
			}
			catch ( Exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}

			return 0;
		}
*/

/*
	Loop for 2x1 averaging, useless
	
		int main (int argc, char const *argv[])
		{
			Image img;
			string outputFile;
			string inputFile;

			// Check for filename
			if( argv[1] == NULL )
			{
				cout<< "There's no input file" << endl;
				return 1;
			}


			// Create output file name
			try
			{
				int dotPosition;

				// Assign the file name
				outputFile = argv[1];

				// Search the dot position
				dotPosition = outputFile.find('.');

				// Append a suffix
				outputFile.insert(dotPosition, "_Averaged");

				// Search the new dot position
				dotPosition = outputFile.find('.');

				// Change the file extension
				outputFile.replace(dotPosition+1, outputFile.size(), "png");

				cout<< "Input file: " << argv[1] << endl;
				cout<< "Output file: " << outputFile << endl;
			}
			catch ( std::exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}


			// Open the image, average it and write the results to another file
			try
			{
				clock_t referenceTime, elapsedTime;
				double averagingTime;

				PixelPacket *pixels, *rotatingPixel, *originPixel;

				// Read image from file
				img.read( argv[1] );

				// Change image colormap to gray scale
				img.type( GrayscaleType );

				// Ensure that there is only one reference to underlying image.
				// If this is not done, then image pixels will not be modified.
				img.modifyImage();

				// Set averaging time reference
				referenceTime = clock();

				// Allocate pixel frame
				Pixels frame(img);
				pixels = frame.get(0, 0, 3, 3);
				//pixels = frame.get(0, 0, img.columns(), img.rows());
				originPixel = pixels;

				// Apply averaging
				for (unsigned int row = 0; row < frame.rows() ; row++ )
				{
					for (unsigned int column = 0; column < frame.columns() ; column++ )
					{
						int selectedMask = 6;	// The pixel itself by default
						int i, j;				// Origin of mask

						double dispersionReference = 500.0;
						double maskAverageBrightness[9];
						double standardDeviation;

						// Calculate standard deviation for every rotated mask
						for(unsigned int thisMask = 0; thisMask < 9; thisMask++)
						{
							ColorGray pixel1, pixel2;

							// Initialize to white
							maskAverageBrightness[thisMask] = 1.0;

							switch(thisMask)
							{
								case 0:
								{
									i = row - 1;
									j = column + 1;
									break;
								}
								case 1:
								{
									i = row - 1;
									j = column;
									break;
								}
								case 2:
								{
									i = row - 1;
									j = column - 1;
									break;
								}
								case 3:
								{
									i = row;
									j = column - 1;
									break;
								}
								case 4:
								{
									i = row + 1;
									j = column - 1;
									break;
								}
								case 5:
								{
									i = row + 1;
									j = column;
									break;
								}
								case 6:
								{
									i = row + 1;
									j = column + 1;
									break;
								}
								case 7:
								{
									i = row;
									j = column + 1;
									break;
								}
								default:
								{
									i = row;
									j = column;
									break;
								}
							}

							// Check image borders
							if ( i < 0 || i >= frame.rows() )
								continue;
							if ( j < 0 || j >= frame.columns() )
								continue;

							// Get reference pixel color
							pixel1 = ColorGray(*pixels);

							// Get neighbour pixel color
							rotatingPixel = originPixel + (i * frame.columns()) + j;
							pixel2 = ColorGray(*rotatingPixel);

							// Calculate average brightness value in mask
							maskAverageBrightness[thisMask] = (pixel1.shade() + pixel2.shade()) / 2.0;

							// Calculate standard deviation in mask
							standardDeviation = 0.0;
							standardDeviation += pow(pixel1.shade() - maskAverageBrightness[thisMask], 2);
							standardDeviation += pow(pixel2.shade() - maskAverageBrightness[thisMask], 2);
							standardDeviation = sqrt(standardDeviation);

							// Update selected mask
							if (standardDeviation < dispersionReference)
							{
								dispersionReference = standardDeviation;
								selectedMask = thisMask;
							}
						}
						// Set new brightness value
						*pixels = ColorGray(maskAverageBrightness[selectedMask]);
						pixels++;
					}
				}

				// Get the averaging time
				elapsedTime = clock();
				averagingTime = (elapsedTime - referenceTime) / (float) CLOCKS_PER_SEC;

				// Write the image to a file
				frame.sync();
				img.write( argv[1] );
				//img.write( outputFile );

				// Show results in console
				cout << endl <<"Pixels: " << (img.rows() * img.columns()) << endl << "Averaging time: " << averagingTime << endl;
			}
			catch ( Exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}

			return 0;
		}
*/


/*
	The code below is for equalizing images
	
		int main (int argc, char const *argv[])
		{
			Image img;
			string outputFile;
			string inputFile;
		
		
			if( argv[1] == NULL )
			{
				cout<< "There's no input file" << endl;
				return 1;
			}
		
		
			// Create output file name
			try
			{
				int dotPosition;
		
				// Assign the file name
				outputFile = argv[1];
		
				// Search the dot position
				dotPosition = outputFile.find('.');
		
				// Append a suffix
				outputFile.insert(dotPosition, "_Equalized");
		
				// Search the new dot position
				dotPosition = outputFile.find('.');
		
				// Change the file extension
				outputFile.replace(dotPosition+1, outputFile.size(), "png");
		
				cout<< "Input file: " << argv[1] << endl;
				cout<< "Output file: " << outputFile << endl;
			}
			catch ( std::exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}
		
		
			// Open the image, equalize it and write the results to another file
			try
			{
				clock_t referenceTime, elapsedTime;
				double equalizationTime;
		
				// Read image from file
				img.read( argv[1] );
		
				// Ensure that there is only one reference to underlying image.
				// If this is not done, then image pixels will not be modified.
				img.modifyImage();
		
				// Change image colormap to gray scale
				img.type( GrayscaleType );
		
				// Equalize image
				referenceTime = clock();
				img.equalize();
				elapsedTime = clock();
		
				equalizationTime = (elapsedTime - referenceTime) / (float) CLOCKS_PER_SEC;
		
				// Write the image to a file
				img.write( outputFile );
		
				// Show results in console
				cout<< endl <<"Pixels: " << (img.rows() * img.columns()) << endl << "Equalization time: " << equalizationTime << endl;
			}
			catch ( Exception &error_ )
			{
				cout << "Caught exception: " << error_.what() << endl;
				return 1;
			}
		
			return 0;
		}
*/

	

/*
	The code below is for reading PDF
	
	int main(int argc, char **argv)
	{
		Image img;
		list<Image> pdf;
		list<Image>::iterator pdfIterator;
		PixelPacket *pixels;
		int rows = 0, columns = 0;
	
		try
		{
			cout << "File: " << argv[1] << endl;
	
			// Read the PDF into image object
			readImages( &pdf, argv[1] );
	
			// Print the PDF number of pages
			cout << "Total pages: " << pdf.size() << endl;
	
			for( pdfIterator = pdf.begin(); pdfIterator != pdf.end(); ++pdfIterator )
			{
				// Get the page
				img = *pdfIterator;
				
				// Print the page dimensions 
				cout << "Rows: " << img.rows() << endl;
				cout << "Columns: " << img.columns() << endl;
			}
			return 0;
			
			// Set the image type to TrueColor DirectClass representation.
			img.type(TrueColorType);
			
			// Ensure that there is only one reference to underlying image 
			// If this is not done, then image pixels will not be modified.
			img.modifyImage();
			
			// Allocate pixel frame
			Pixels frame(img);
			
			pixels = frame.get(0, 0, img.rows(), img.columns()); 
			
			for(size_t i = 0; i < img.rows(); ++i)
			{
				rows++;
				for(size_t j = 0; j < img.columns(); ++j)
				{
					columns++;
				}
			}
		} 
		catch( Exception &error_ ) 
		{ 
			cout << "Caught exception: " << error_.what() << endl; 
			return 1; 
		}
		return 0;
	}
	
*/

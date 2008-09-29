#include <Magick++.h>
using namespace Magick;

#include <list>
#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char **argv)
{
	time_t referenceTime, elapsedTime;
	double averagingTime;
	Image img;
	list<Image> pdf, pdf2;
	// list<Image>::iterator pdfIterator;
	// PixelPacket *pixels;
	// int rows = 0, columns = 0;

	try
	{
		cout << "File: " << argv[1] << endl;

		// Set reference time
		time( &referenceTime );
		
		// Read the PDF into image object
		readImages( &pdf, argv[1] );
		
		// Get elapsed time
		time( &elapsedTime);
		averagingTime = difftime( elapsedTime, referenceTime );

		// Print the PDF number of pages
		cout << pdf.size() << " pages loaded in " << averagingTime << " seconds" << endl;
		
		
		// Set reference time
		time( &referenceTime );
		
		// Read the PDF into image object
		pdf2 = pdf;
		
		// Get elapsed time
		time( &elapsedTime);
		averagingTime = difftime( elapsedTime, referenceTime );

		// Print the PDF number of pages
		cout << pdf2.size() << " pages transferred in " << averagingTime << " seconds" << endl;

		// for( pdfIterator = pdf.begin(); pdfIterator != pdf.end(); ++pdfIterator )
		// 		{
		// 			// Get the page
		// 			img = *pdfIterator;
		// 			
		// 			// Print the page dimensions 
		// 			cout << "Rows: " << img.rows() << endl;
		// 			cout << "Columns: " << img.columns() << endl;
		// 		}
	} 
	catch( Exception &error_ ) 
	{ 
		cout << "Caught exception: " << error_.what() << endl; 
		return 1; 
	}
	return 0;
}
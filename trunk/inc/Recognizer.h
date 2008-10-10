///
/// @file
/// @brief Declaration of the class Recognizer
///

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H

#include <vector>
class string; 	// Forward declaration

#include <Magick++.h>

#include "Text.h"
#include "Statistics.h"
class Clip;		// Forward declaration



///
/// Manager of the whole OCR process.
/// 
/// This class encapsulates all the stages related to the optical character recognition process of
/// every clip within a newspaper's page. For each image provided (via constructors) representing the page,
/// you can obtain its text and a number of statistics regarding the recognition process performance.
/// 
/// At the moment, this class manages the press clips within an image loaded with the Magick++ utilities. The newspaper pages should
/// be an image that comes in several formats, such JPEG, PDF, PNG, etc. The Magick++ library (an API for the ImageMagick suite)
/// provides an abstraction layer to keep the code independent from the image format. The idea behind this class is to encapsulate
/// all the interactions with Magick++, so that the rest of the classes have an unified way to work.
/// 
/// In future modifications any library may be added to load the images. A developer should overload a loadImage() method,
/// modify the constructor Recognizer(const std::string &path) or add a new constructor with specific parameters,
/// and overload a writeExternalImage() method.
/// 
/// @see Text, Statistics, <a href="http://www.imagemagick.org">ImageMagick</a>, <a href="http://www.imagemagick.org/Magick++/">Magick++ API</a>
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-10
///
class Recognizer
{
	public:
		///
		/// Constructor
		///
		Recognizer (const std::string &path);
		
		
		///
		/// Constructor
		///
		Recognizer (Magick::Image &image);
		
		
		///
		/// Recognizes the text within the whole page at once
		///
		void obtainText ();
		
		
		///
		/// Recognizes the text within multiple press clips whose coordinates are passed
		///
		void obtainText (const std::vector<int> &coordinates);
		
		
		///
		/// Recognizes the text within a single press clip located at coordinates (x,y)
		///
		void obtainText (const unsigned int &x, const unsigned int &y, unsigned int &height, unsigned int &width);


		///
		/// Returns the text of a single clip
		/// 
		/// @param label A number that tells the clip where the requested text belongs to
		/// 
		/// @see Text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline Text text (const unsigned int& label=1) const
		{
			if ( label <= texts_.size() )
				return texts_[label];
			else
				return texts_.back();
		};
		
		
		///
		/// Returns the text of every loaded clip
		/// 
		/// @see Text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline std::vector<Text> texts () const
		{
			return texts_;
		};


		///
		/// Returns the statistical data regarding the recognition process of a single clip 
		/// 
		/// @param label A number that tells the clip where the requested statistical data belongs to
		/// 
		/// @see Statistics
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline Statistics statistic (const unsigned int& label=1) const
		{
			if ( label <= statistics_.size() )
				return statistics_[label];
			else
				return statistics_.back();
		};
		
		
		///
		/// Returns the statistical data regarding the recognition process of every loaded clip
		/// 
		/// @see Statistics
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		inline std::vector<Statistics> statistics () const
		{
			return statistics_;
		};
		
		
		///
		/// Writes the information of the internal data into an external image
		///
		void writeExternalImage (Magick::Image &externalImage) const;
		
	private:
		///
		/// Underlying image where where clip belongs to
		///
		std::vector<unsigned char> image_;
		
		///
		/// Height of the underlying image
		///
		unsigned int height_;
		
		///
		/// Width of the underlying image
		///
		unsigned int width_;
		
		///
		/// Text obtained after the recognition process 
		///
		std::vector<Text> texts_;
		
		///
		/// Statistics gathered during the recognition process
		///
		std::vector<Statistics> statistics_;
		
		
		///
		/// Loads an Image object created with the Magick++ API into the internal data structure
		///
		void loadImage (Magick::Image &image);
		
		
		///
		/// Writes the information of a clip into the underlying image
		///
		void updateImage (const Clip &clip);
};

#endif  //_RECOGNIZER_H

///
/// @file
/// @brief Declaration of the class Recognizer
///

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H

#include <vector>
class string; 	// Forward declaration

#include <Magick++.h>

#include "Text.hpp"
#include "Statistics.hpp"
#include "ClipLocation.hpp"
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
/// @see Text, Statistics, <a href="http://www.imagemagick.org/Magick++/">Magick++ API</a>, Clip
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-10
///
class Recognizer
{
	public:
		///
		/// Constructor.
		/// 
		/// @param path Relative path to the image within the filesystem
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10		
		///
		Recognizer (const std::string &path);
		
		
		///
		/// Constructor.
		///
		/// @param image An Image object from the Magick++ API previously loaded
		/// 
		/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Image</a>
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		///
		Recognizer (Magick::Image &image);
		
		
		///
		/// Recognizes the text within the whole page at once.
		///
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-09
		///
		void obtainText ();
		
		
		///
		/// Recognizes the text within multiple press clips whose coordinates are passed.
		///
		/// @param coordinates A list of coordinates to locate a number of clips within the page
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-09
		///
		void obtainText (const std::vector<ClipLocation> &coordinates);
		
		
		///
		/// Recognizes the text within a single press clip located at coordinates (x,y)
		///
		/// @param x		Top left-most pixel X coordinate
		/// @param y		Top left-most pixel Y coordinate
		/// @param height	Clip's height
		/// @param width	Clip's width
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
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
		/// @date 2008-10-11
		///
		Text text (const unsigned int& label=0) const;
		
		
		///
		/// Returns the text of every loaded clip
		/// 
		/// @return A list of texts recognized in the clips previously loaded
		/// 
		/// @see Text
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		std::vector<Text> texts () const;


		///
		/// Returns the statistical data regarding the recognition process of a single clip 
		/// 
		/// @param label A number that tells the clip where the requested statistical data belongs to
		/// 
		/// @return Statistical data about the recognition process of a single clip
		/// 
		/// @see Statistics
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-11
		///
		Statistics statistic (const unsigned int& label=0) const;
		
		
		///
		/// Returns the statistical data regarding the recognition process of every loaded clip
		/// 
		/// @return Statistical data about the recognition process of every clip within the image
		/// 
		/// @see Statistics
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-08
		///
		std::vector<Statistics> statistics () const;
		
		
		///
		/// Writes the information of the internal data into an external image.
		///
		/// @param externalImage The destination Image object from the Magick++ API previously created
		/// 
		/// @remarks The image will be converted to a grayscale colorspace
		/// 
		/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Image</a>
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
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
		/// Loads an Image object created with the Magick++ API into the internal data structure.
		///
		/// @param image An Image object from the Magick++ API previously created
		/// 
		/// @remarks The image is converted to a grayscale colorspace internally
		/// 
		/// @see <a href="http://www.imagemagick.org/Magick++/Image.html">Image</a>
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		///
		void loadImage (Magick::Image &image);
		
		
		///
		/// Writes the information of a clip into the underlying image
		///
		/// @param clip The clip where the new data is taken
		/// 
		/// @see Clip
		/// 
		/// @author Eliezer Talón (elitalon@gmail.com)
		/// @date 2008-10-10
		///
		void updateImage (const Clip &clip);
};



//
// Implementation of inline functions
//


///
/// @details
/// 
inline Text Recognizer::text (const unsigned int& label) const
{
	if ( label <= texts_.size() )
		return texts_[label];
	else
		return texts_.back();
};


///
/// @details
/// 
inline std::vector<Text> Recognizer::texts () const
{
	return texts_;
};


///
/// @details
/// 
inline Statistics Recognizer::statistic (const unsigned int& label) const
{
	if ( label <= statistics_.size() )
		return statistics_[label];
	else
		return statistics_.back();
};


///
/// @details
/// 
inline std::vector<Statistics> Recognizer::statistics () const
{
	return statistics_;
};


#endif  //_RECOGNIZER_H

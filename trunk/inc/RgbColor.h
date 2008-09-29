#if !defined(_RGBCOLOR_H)
#define _RGBCOLOR_H

///
/// @file
/// @brief Declaration of struct RgbColor
///

///
/// Color definition in a RGB colorspace
/// 
/// This struct represents the channel decomposition of a color in a RGB colorspace. The
/// color is stored using a normalized value between 0 and 1 for each RGB channel.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-29
///
struct RgbColor
{
	public:
		
		///
		/// Red component
		///
		double red;
		
		///
		/// Green component
		///
		double green;
		
		///
		/// Blue component
		///
		double blue;
		
		
		///
		/// Constructor
		///
		RgbColor ();
		
		///
		/// Constructor
		///
		RgbColor (double red, double green, double blue);
		
		///
		/// Destructor
		///
		~RgbColor ();
};

#endif  //_RGBCOLOR_H

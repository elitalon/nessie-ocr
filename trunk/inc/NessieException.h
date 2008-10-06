///
/// @file
/// @brief Declaration of class NessieException
///

#if !defined(_NESSIE_EXCEPTION_H)
#define _NESSIE_EXCEPTION_H


#include <string>
#include <exception>


///
/// Exception raised by a Nessie OCR object
/// 
/// This class derives from std::exception class, so that all the exceptions either from Magick++, this library or the STL itself
/// can be caught using a reference to an 'exception' object.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
///
class NessieException : public std::exception
{
	public:
		///
		/// Constructor
		///
		NessieException (const std::string &what);
				
		///
		/// Destructor
		///
		virtual ~NessieException () throw ();
		
		///
		/// Returns a message that explains the exception raised
		///
		virtual const char* what () const throw();
		
	private:
		///
		/// Message that explains the exception raised
		///
		std::string what_;
};

#endif  //_NESSIE_EXCEPTION_H

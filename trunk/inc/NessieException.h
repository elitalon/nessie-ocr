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
		/// Returns the message that explains the exception
		///
		virtual const char* what () const throw();
		
	private:
		///
		/// Message explaining the error that raised the exception
		///
		std::string what_;
};

#endif  //_NESSIE_EXCEPTION_H

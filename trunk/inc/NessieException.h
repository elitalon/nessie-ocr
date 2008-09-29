#if !defined(_NESSIE_EXCEPTION_H)
#define _NESSIE_EXCEPTION_H

///
/// @file
/// @brief Declaration of class NessieException
///

#include <string>
using namespace std;


///
/// Exception raised by a Nessie OCR object
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-09-26
///
class NessieException
{
	public:
		///
		/// Constructor
		///
		NessieException (string message = "Unknown error");
				
		///
		/// Destructor
		///
		virtual ~NessieException ();
		
		///
		/// Returns the message that explains the exception
		///
		virtual string what () const;

	protected:
		///
		/// Message explaining the error that raised the exception
		///
		string message_;
};

#endif  //_NESSIE_EXCEPTION_H

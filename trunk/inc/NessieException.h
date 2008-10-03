#if !defined(_NESSIE_EXCEPTION_H)
#define _NESSIE_EXCEPTION_H

///
/// @file
/// @brief Declaration of class NessieException
///

#include <string>
#include <exception>
using namespace std;


///
/// Exception raised by a Nessie OCR object
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
///
class NessieException
{
	public:
		///
		/// Constructor
		///
		NessieException (const string &message);
				
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
		const string message_;
};

#endif  //_NESSIE_EXCEPTION_H

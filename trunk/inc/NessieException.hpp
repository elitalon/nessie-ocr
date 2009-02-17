/// @file
/// @brief Declaration of NessieException class

#if !defined(_NESSIE_EXCEPTION_H)
#define _NESSIE_EXCEPTION_H


#include <string>
#include <exception>


/// @brief		Exception raised by a NessieOcr object.
/// 
/// @details	This class derives from std::exception class, so that all the exceptions either from this library or the STL itself
/// can be caught using a reference to an <em>std::exception</em> object.
/// 
/// @author	Eliezer Talón (elitalon@gmail.com)
/// @date 2008-10-03
///
class NessieException : public std::exception
{
	public:

		/// @brief	Constructor.
		///
		/// @param	what	A message that explains the exception raised.
		explicit NessieException (const std::string& what);

		/// @brief	Destructor.
		virtual ~NessieException () throw ();

		///	@brief	Returns a message that explains the exception raised.
		/// 
		/// @return	Message that explains the situation that caused the exception.
		virtual const char* what () const throw();

	private:

		std::string	what_;	///< Message that explains the exception raised

		// Explicitly disallowed compiler-generated method. DO NOT IMPLEMENT!!
		NessieException ();
};

#endif


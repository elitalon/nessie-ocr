AC_PREREQ(2.61)
AC_INIT([NessieOCR], 0.1, elitalon@gmail.com, nessieocr)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/Clip.cpp])

# Check for programs.
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL

# Configure library generation
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

CPPFLAGS="$CPPFLAGS `Magick++-config --cppflags`";
CXXFLAGS="$CXXFLAGS -g -O2 -Wall -W -Wextra -ansi -pipe -pthread";
LDFLAGS="$LDFLAGS `Magick++-config --ldflags`";
LIBS="$LIBS `Magick++-config --libs`";

# Check for Magick++
AC_CHECK_PROG(magickconfig, [Magick++-config --version], yes, no)
if test $magickconfig = "no"; then
	AC_MSG_ERROR(Missing Magick++-config script.)
else
		
	AC_LANG_PUSH([C++])
	AC_CHECK_HEADER([Magick++.h], [], AC_MSG_ERROR(Missing Magick++ library))
	AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <Magick++.h>], [Magick::Image img;])], [], AC_MSG_ERROR(Missing 'Image' class inside Magick++ library.))
	AC_LANG_POP([C++])
fi

# Check for Boost libraries
LIBS="$LIBS -lboost_program_options -lboost_regex"
AC_LANG_PUSH([C++])
AC_CHECK_HEADER([boost/timer.hpp], [], AC_MSG_ERROR(Missing 'Timer' package from Boost library.))
AC_CHECK_HEADER([boost/tokenizer.hpp], [], AC_MSG_ERROR(Missing 'Tokenizer' package from Boost library.))
AC_CHECK_HEADER([boost/program_options.hpp], [], AC_MSG_ERROR(Missing 'Program options' package from Boost library.))
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <boost/program_options.hpp>], [boost::program_options::options_description p("");])], [], AC_MSG_ERROR(Missing 'Program options' package from Boost library.))
AC_CHECK_HEADER([boost/regex.hpp], [], AC_MSG_ERROR(Missing 'Regex' package from Boost library.))
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <boost/regex.hpp>], [boost::regex pattern("");])], [], AC_MSG_ERROR(Missing 'Regex' package from Boost library.))
AC_LANG_POP([C++])

# Check for MySQL database drivers
LIBS="$LIBS -lmysqlpp -lmysqlclient"
CPPFLAGS="$CPPFLAGS -I/usr/include/mysql";
AC_LANG_PUSH([C++])
AC_CHECK_HEADER([mysql/mysql.h], [], AC_MSG_ERROR(Missing 'mysql' package.))
AC_CHECK_HEADER([mysql++/mysql++.h], [], AC_MSG_ERROR(Missing 'mysql++' package.))
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <mysql++/mysql++.h>], [mysqlpp::Connection connection ("", 0, "", ""); ])], [], AC_MSG_ERROR(Missing 'mysql++' package.))
AC_LANG_POP([C++])

# Check for PostgreSQL database drivers
LIBS="$LIBS -lpqxx"
AC_LANG_PUSH([C++])
AC_CHECK_HEADER([pqxx/pqxx], [], AC_MSG_ERROR(Missing 'libpqxx' package.))
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <pqxx/pqxx>], [pqxx::connection connection("");])], [], AC_MSG_ERROR(Missing 'libpqxx' package.))
AC_LANG_POP([C++])


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T


# Checks for library functions.
AC_FUNC_STAT
AC_CHECK_FUNCS([pow sqrt])


AC_CONFIG_FILES([Makefile src/Makefile include/Makefile])
AC_OUTPUT


AC_PREREQ(2.61)
AC_INIT([NessieOCR], 0.1, elitalon@gmail.com, nessieocr)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/NessieOcr.cpp])


# Check for basic programs.
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL


# Configure library generation
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


# Configure global flags
CPPFLAGS="$CPPFLAGS `Magick++-config --cppflags` -I/usr/local/include";
CXXFLAGS="$CXXFLAGS -g -Wall -W -pthread -fPIC -O3";
LDFLAGS="$LDFLAGS `Magick++-config --ldflags` -L/usr/local/lib";
LIBS="$LIBS `Magick++-config --libs`";


# Enable/disable use of MySQL
AC_ARG_WITH([mysql],
			[AC_HELP_STRING([--with-mysql],
							[Use MySQL framework to load the dataset])],
			[with_mysql=$withval],
			[with_mysql='no'])


# Enable/disable use of PostgreSQL
AC_ARG_WITH([postgres],
			[AC_HELP_STRING([--with-postgres],
							[Use PostgreSQL framework to load the dataset])],
			[with_postgres=$withval],
			[with_postgres='yes'])


# Check for MySQL database drivers
have_mysql='no'
if test "$with_mysql" != 'no'; then
	CPPFLAGS="$CPPFLAGS -I/usr/include/mysql";
	LIBS="$LIBS -lmysqlpp -lmysqlclient"

	AC_LANG_PUSH([C++])
	AC_CHECK_HEADER([mysql/mysql.h], [], AC_MSG_ERROR(Missing 'mysql' package.))
	AC_CHECK_HEADER([mysql++/mysql++.h], [], AC_MSG_ERROR(Missing 'mysql++' package.))
	AC_LANG_POP([C++])

	have_mysql='yes'
fi
AM_CONDITIONAL(WITH_MYSQL, test "$have_mysql" = 'yes')


# Check for PostgreSQL database drivers
have_postgres='no'
if test "$with_postgres" != 'no'; then
	LIBS="$LIBS -lpqxx"
	AC_LANG_PUSH([C++])
	AC_CHECK_HEADER([pqxx/pqxx], [], AC_MSG_ERROR(Missing 'libpqxx' package.))
	AC_LANG_POP([C++])

	have_postgres='yes'
fi
AM_CONDITIONAL(WITH_POSTGRESQL, test "$have_postgres" = 'yes')


# Check for Magick++
AC_CHECK_PROG(magickconfig, [Magick++-config --version], yes, no)
if test $magickconfig = "no"; then
	AC_MSG_ERROR(Missing Magick++-config script.)
else
	AC_LANG_PUSH([C++])
	AC_CHECK_HEADER([Magick++.h], [], AC_MSG_ERROR(Missing Magick++ library))
	AC_LANG_POP([C++])
fi


# Check for Boost libraries
BOOST_PROGRAM_OPTIONS=`ldconfig -p | grep libboost_program_options | tail -n 1 | awk '{print $1;}' | sed 's/lib//; s/\..*//'`
BOOST_REGEX=`ldconfig -p | grep libboost_regex  | tail -n 1 | awk '{print $1;}' | sed 's/lib//; s/\..*//'`
LIBS="$LIBS -l$BOOST_PROGRAM_OPTIONS -l$BOOST_REGEX"
AC_LANG_PUSH([C++])
AC_CHECK_HEADER([boost/timer.hpp], [], AC_MSG_ERROR(Missing 'Timer' package from Boost library.))
AC_CHECK_HEADER([boost/tokenizer.hpp], [], AC_MSG_ERROR(Missing 'Tokenizer' package from Boost library.))
AC_CHECK_HEADER([boost/program_options.hpp], [], AC_MSG_ERROR(Missing 'Program options' package from Boost library.))
AC_CHECK_HEADER([boost/regex.hpp], [], AC_MSG_ERROR(Missing 'Regex' package from Boost library.))
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


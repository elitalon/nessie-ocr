AC_PREREQ(2.61)
AC_INIT([NessieOCR], 0.1, elitalon@gmail.com, nessieocr)
AC_LANG([C++])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/NessieOcr.cpp])


# Check for basic programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_SED
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


# Check for Magick++ configuration. Setup of global variables.
AC_CHECK_PROG(magickconfig, [Magick++-config --version], yes, no)
if test $magickconfig = "no"; then
	AC_MSG_ERROR(Missing Magick++-config script.)
else
	CPPFLAGS="$CPPFLAGS `Magick++-config --cppflags`";
	CXXFLAGS="$CXXFLAGS `Magick++-config --cxxflags`";
	LDFLAGS="$LDFLAGS `Magick++-config --ldflags`";
	LIBS="$LIBS `Magick++-config --libs`";
	AC_CHECK_HEADER([Magick++.h], [], AC_MSG_ERROR(Missing Magick++ library))
fi


# Configure global flags
CPPFLAGS="$CPPFLAGS -I/usr/local/include";
CXXFLAGS="$CXXFLAGS -fPIC -O3";
LDFLAGS="$LDFLAGS -L/usr/local/lib";
LIBS="$LIBS -L/usr/local/lib";


# Check for Boost libraries
BOOST_PROGRAM_OPTIONS=`find /usr/lib -name *boost_program_options* -type l | tail -n 1 | sed 's/.*lib\/lib\(.*\)\..*/\1/'` 
if test -z "$BOOST_PROGRAM_OPTIONS"; then
	BOOST_PROGRAM_OPTIONS=`find /usr/local/lib -name *boost_program_options* -type l | tail -n 1 | sed 's/.*lib\/lib\(.*\)\..*/\1/'` 
	if test -z "$BOOST_PROGRAM_OPTIONS"; then
		AC_MSG_ERROR(Unable to find Boost's program_options dynamic library.)
	fi
fi

BOOST_REGEX=`find /usr/lib -name *boost_regex* -type  l| tail -n 1 | sed 's/.*lib\/lib\(.*\)\..*/\1/'` 
if test -z "$BOOST_REGEX"; then
	BOOST_REGEX=`find /usr/local/lib -name *boost_regex* -type l | tail -n 1 | sed 's/.*lib\/lib\(.*\)\..*/\1/'` 
	if test -z "$BOOST_REGEX"; then
		AC_MSG_ERROR(Unable to find Boost's regex dynamic library.)
	fi
fi
LIBS="$LIBS -l$BOOST_PROGRAM_OPTIONS -l$BOOST_REGEX"


# Check for Boost headers
AC_CHECK_HEADER([boost/timer.hpp], [], AC_MSG_ERROR(Missing 'Timer' package from Boost library.))
AC_CHECK_HEADER([boost/tokenizer.hpp], [], AC_MSG_ERROR(Missing 'Tokenizer' package from Boost library.))
AC_CHECK_HEADER([boost/program_options.hpp], [], AC_MSG_ERROR(Missing 'Program options' package from Boost library.))
AC_CHECK_HEADER([boost/regex.hpp], [], AC_MSG_ERROR(Missing 'Regex' package from Boost library.))


# Enable/disable use of MySQL
AC_ARG_WITH([mysql],
			[AC_HELP_STRING([--with-mysql],
							[Use MySQL framework to load the dataset])],
			[with_mysql=$withval],
			[with_mysql='no'])


# Check for MySQL database drivers
have_mysql='no'
if test "$with_mysql" != 'no'; then
	CPPFLAGS="$CPPFLAGS -I/usr/include/mysql -I/usr/local/mysql/include";
	LIBS="$LIBS -L/usr/local/mysql/lib/ -lmysqlpp -lmysqlclient"

	AC_CHECK_HEADER([mysql.h], [], AC_MSG_ERROR(Missing 'mysql' package.))
	AC_CHECK_HEADER([mysql++/mysql++.h], [], AC_MSG_ERROR(Missing 'mysql++' package.))

	have_mysql='yes'
	AC_DEFINE(_WITH_MYSQL_DATASET_)
fi
AM_CONDITIONAL(WITH_MYSQL, test "$have_mysql" = 'yes')


# Enable/disable use of PostgreSQL
AC_ARG_WITH([postgres],
			[AC_HELP_STRING([--with-postgres],
							[Use PostgreSQL framework to load the dataset])],
			[with_postgres=$withval],
			[with_postgres='yes'])


# Check for PostgreSQL database drivers
have_postgres='no'
if test "$with_postgres" != 'no'; then
	# Check if any PostgreSQL database is installed.
	AC_PATH_PROGS(PG_CONFIG, pg_config)
	if test -z "$PG_CONFIG" || test ! -r "$PG_CONFIG"; then
		AC_MSG_ERROR([PostgreSQL configuration script pg_config not found.  Make sure this is in your
command path before configuring.  Without it, the configure script has no way to
find the right location for the libpq library and its headers.])
	fi
	
	LIBS="$LIBS -lpqxx"
	AC_CHECK_HEADER([pqxx/pqxx], [], AC_MSG_ERROR(Missing 'libpqxx' package.))

	have_postgres='yes'
	AC_DEFINE(_WITH_POSTGRESQL_DATASET_)
fi
AM_CONDITIONAL(WITH_POSTGRESQL, test "$have_postgres" = 'yes')

AC_CONFIG_FILES([Makefile src/Makefile include/Makefile])
AC_OUTPUT


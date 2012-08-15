NessieOCR
====================
NessieOCR provide a simple library to perform an optical character
recognition process over press clips, extracted from newspapers and
provided as images in multiple formats.

NessieOCR is a work derived from Eliezer Talon's master thesis
project, after investigating about OCR techniques for the Nessie
project.

Please glance through all sections of this `README` file before
starting configuration:

* `COPYING.txt` for copying conditions.
* `INSTALL.md` for compilation and installation instructions.
* `NEWS.md` for a list of major changes in the current release.
* `THANKS.md` for a list of contributors.

NessieOCR library comes with documentation in HTML format. You can
find it under the directory 'doc/html'.

Installation hints
==================
Here are a few hints which might help installing `NessieOCR` on your
system.

ImageMagick
------------
NessieOCR uses Magick++, a ImageMagick's C++ API to read and write image
files. If you don't have the ImageMagick suite already, you
need to install them. The binaries and sources can be found at http://www.imagemagick.org/.

ImageMagick has its own dependencies as well. Read carefully the
installation manual to make your installation of Magick++ can handle
your preferred image format.

Boost library
-------------
NessieOCR also uses some utilities provided by the Boost Library
distribution. If you don't have the Boost library already, you need to
install it. The binaries and sources can be found at http://www.boost.org/.

Databases
---------
During training stage the samples taken can be stored in different
ways. If you are planning to use a database you can use MySQL or
PostgreSQL. In such case you need to install the following libraries,
as they are used to provide internal access to the databases:

* MySQL: [MySQL++](http://tangentsoft.net/mysql++/)		
* PostgreSQL: [libpqxx](http://pqxx.org/development/libpqxx/)

You should also read the package documentation to know the database
design requirements for NessieOCR.


Support
=======
NessieOCR is not being actively mantained and bug reports will be
probably ignored. However, if you are interested on the project in some
way you can email the author/s.


Copying
=======
Copyright (C) 2008-2009 Eliezer Talon

This file is part of NessieOCR.

NessieOCR is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

NessieOCR is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with NessieOCR; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
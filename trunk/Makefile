###
# Makefile: builds the Nessie OCR
#
# Mantainer: Eliezer Talon <elitalon@gmail.com>
#
# Usage: make [ main | all | clean ]
#	- main:		Compiles the source code, default option
#	- clean:	Removes every file generated during compilation
#	- all:		Executes clean and then main
#
###


SHELL = /bin/sh
CHMOD = chmod
.SUFFIXES:
.SUFFIXES: .cpp .o .hpp

srcdir = src/
incdir = inc/
libdir = lib/
vpath %.hpp		$(incdir)
vpath %.cpp		$(srcdir)
vpath %.o		./
vpath %.so		$(libdir)
vpath %.dylib	$(libdir)



#
# Dependencies
#
TEXT = Text.cpp Text.hpp NessieException.o
STATISTICS = Statistics.cpp Statistics.hpp
REGION = Region.cpp Region.hpp
RECOGNIZER = Recognizer.cpp Recognizer.hpp Text.o Statistics.o Clip.o Preprocessor.o
PREPROCESSOR = Preprocessor.cpp Preprocessor.hpp Clip.o Statistics.o Region.o Pattern.o
PATTERN = Pattern.cpp Pattern.hpp
NESSIE_EXCEPTION = NessieException.cpp NessieException.hpp
MAIN = main.cpp Recognizer.o Clip.o
FEATURE_VECTOR = FeatureVector.cpp FeatureVector.hpp NessieException.o
DATASET = DataSet.cpp DataSet.hpp NessieException.o FeatureVector.o
CLIP = Clip.cpp Clip.hpp NessieException.o
CLASSIFIER = Classifier.cpp Classifier.hpp DataSet.o Pattern.o FeatureVector.o



LIBRARY = `sh platformLinkerOptions.sh -t`
LIBRARY_BUILDING_OPTIONS = `sh platformLinkerOptions.sh -o`
LIBRARY_VERSION = 1.0.0

OBJECTS = *.o
PROGRAM = bin/ocr
MAGICK_LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_CXXFLAGS = `Magick++-config --cppflags --cxxflags`
BOOST_CXXFLAGS = -I/usr/local/include/boost
CXXFLAGS = -ansi -pipe -Wall -Wextra -O3 -I$(incdir) -g -Weffc++ -Wold-style-cast -fPIC
LDFLAGS = $(MAGICK_LDFLAGS) 



main: main.o
	$(CXX) $(LDFLAGS) $(LIBRARY_BUILDING_OPTIONS) $(OBJECTS) -o $(libdir)$(LIBRARY).$(LIBRARY_VERSION)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) -o $(PROGRAM)
	@echo

main.o: $(MAIN)
	$(CXX) $(BOOST_CXXFLAGS) $(MAGICK_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo

NessieException.o: $(NESSIE_EXCEPTION)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Clip.o: $(CLIP)
	$(CXX) $(MAGICK_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo

Recognizer.o: $(RECOGNIZER)
	$(CXX) $(MAGICK_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo

Text.o: $(TEXT)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Statistics.o: $(STATISTICS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Preprocessor.o: $(PREPROCESSOR)
	$(CXX) $(BOOST_CXXFLAGS) $(MAGICK_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo

Region.o: $(REGION)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Pattern.o: $(PATTERN)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Classifier.o: $(CLASSIFIER)
	$(CXX) $(BOOST_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo

DataSet.o: $(DATASET)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

FeatureVector.o: $(FEATURE_VECTOR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

install:
	cp $(libdir)$(LIBRARY).$(LIBRARY_VERSION) /usr/local/lib
	ldconfig -n /usr/local/lib

uninstall:
	rm -f /usr/local/lib/$(LIBRARY).$(LIBRARY_VERSION)
	rm -f /usr/local/lib/$(LIBRARY)
	ldconfig -n /usr/local/lib

doc: $(incdir)*.hpp $(srcdir)*.cpp 
	@rm -rf doc/html/*
	doxygen

clean:
	rm -f $(OBJECTS) $(PROGRAM) $(libdir)$(LIBRARY).$(LIBRARY_VERSION)
	$(CHMOD) 0644 $(srcdir)*.cpp $(incdir)*.hpp
	@echo

all: clean main doc


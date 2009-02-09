###
# Makefile: builds the Nessie OCR
#
# Mantainer: Eliezer Talon <elitalon@gmail.com>
#
# Usage: make [ main | all | clean ]
#	- main:		Compiles the source code, default option
#	- clean:	Removes every file generated during compilation
#	- doc:		Generates documentation.
#	- all:		Executes clean and then main and doc
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
NESSIE_EXCEPTION = NessieException.cpp NessieException.hpp
MAIN = main.cpp Clip.o Recognizer.o
CLIP = Clip.cpp Clip.hpp NessieException.o
RECOGNIZER = Recognizer.cpp Recognizer.hpp Text.o Statistics.o Clip.o Preprocessor.o FeatureExtractor.o Classifier.o
TEXT = Text.cpp Text.hpp NessieException.o
STATISTICS = Statistics.cpp Statistics.hpp
PREPROCESSOR = Preprocessor.cpp Preprocessor.hpp Clip.o Statistics.o Region.o
REGION = Region.cpp Region.hpp
FEATURE_EXTRACTOR = FeatureExtractor.cpp FeatureExtractor.hpp Region.o Statistics.o Pattern.o FeatureVector.o
PATTERN = Pattern.cpp Pattern.hpp Region.o Preprocessor.o Clip.o
FEATURE_VECTOR = FeatureVector.cpp FeatureVector.hpp NessieException.o

DATASET = DataSet.cpp DataSet.hpp NessieException.o FeatureVector.o
CLASSIFIER = Classifier.cpp Classifier.hpp

LIBRARY_NAME = NessieOcr
LIBRARY_VERSION = 1.0.0
LIBRARY_SHARED_FILE = lib$(LIBRARY_NAME)`sh platformOptions.sh -e`
LIBRARY_BUILDING_OPTIONS = -shared -Wl,`sh platformOptions.sh -o`,$(LIBRARY_SHARED_FILE)

OBJECTS = *.o
PROGRAM = bin/ocr
MAGICK_LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_CXXFLAGS = `Magick++-config --cppflags --cxxflags`
BOOST_CXXFLAGS = -I/usr/local/include/boost
CXXFLAGS = -ansi -pipe -Wall -Wextra -O3 -I$(incdir) -g -Weffc++ -fPIC
LDFLAGS = $(MAGICK_LDFLAGS) 



main: main.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJECTS) -o $(PROGRAM)
	@echo
	$(CXX) $(LDFLAGS) $(LIBRARY_BUILDING_OPTIONS) $(OBJECTS) -o $(libdir)$(LIBRARY_SHARED_FILE).$(LIBRARY_VERSION)
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

FeatureExtractor.o: $(FEATURE_EXTRACTOR)
	$(CXX) $(BOOST_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo

Pattern.o: $(PATTERN)
	$(CXX) $(MAGICK_CXXFLAGS) $(CXXFLAGS) -c $< -o $@
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
	mkdir /usr/local/include/$(LIBRARY_NAME)
	cp $(incdir)*.hpp /usr/local/include/$(LIBRARY_NAME)
	cp $(libdir)$(LIBRARY_SHARED_FILE).$(LIBRARY_VERSION) /usr/local/lib
	ldconfig -n /usr/local/lib

uninstall:
	rm -f /usr/local/include/$(LIBRARY_NAME)/*.hpp
	rm -f /usr/local/lib/$(LIBRARY_SHARED_FILE).$(LIBRARY_VERSION)
	rm -f /usr/local/lib/$(LIBRARY_SHARED_FILE)
	ldconfig -n /usr/local/lib

doc: $(incdir)*.hpp $(srcdir)*.cpp Doxyfile
	@rm -rf doc/html/*
	@doxygen

clean:
	@rm -f $(OBJECTS) $(PROGRAM) $(libdir)$(LIBRARY_SHARED_FILE).$(LIBRARY_VERSION)
	@$(CHMOD) 0644 $(srcdir)*.cpp $(incdir)*.hpp

all: clean main doc


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



#
# General conventions for Makefiles (extracted from GNU Make manual)
#
SHELL = /bin/sh
CHMOD = chmod
.SUFFIXES:
.SUFFIXES: .cpp .o .hpp


#
# Directories
#
srcdir = src/
incdir = inc/
vpath %.hpp	$(incdir)
vpath %.cpp	$(srcdir)
vpath %.o	./



#
# Magick++ API path
#
MAGICK_LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_CXXFLAGS = `Magick++-config --cppflags --cxxflags`

#
# Boost API path
#
BOOST_CXXFLAGS=-I/usr/local/include/boost
BOOST_LDFLAGS=-L/usr/local/lib



#
# Dependencies
#
MAIN=main.cpp Recognizer.o
NESSIE_EXCEPTION=NessieException.cpp NessieException.hpp
STATISTICS=Statistics.cpp Statistics.hpp
TEXT=Text.cpp Text.hpp
CLIP=Clip.cpp Clip.hpp NessieException.o
SHAPE=Shape.cpp Shape.hpp
PREPROCESSOR=Preprocessor.cpp Preprocessor.hpp Clip.o
SEGMENTER=Segmenter.cpp Segmenter.hpp Clip.o Shape.o
CLASSIFIER=Classifier.cpp Classifier.hpp DataSet.o Shape.o
RECOGNIZER=Recognizer.cpp Recognizer.hpp Text.o Statistics.o Preprocessor.o Segmenter.o Classifier.o
FEATURE_VECTOR=FeatureVector.cpp FeatureVector.hpp NessieException.o
DATASET=DataSet.cpp DataSet.hpp NessieException.o FeatureVector.o



#
# Compiler and linker options
#
OBJECTS = main.o\
		  Recognizer.o\
		  Text.o\
		  Statistics.o\
		  Preprocessor.o\
		  Clip.o\
		  NessieException.o\
		  Segmenter.o\
		  Shape.o\
		  Classifier.o\
		  DataSet.o\
		  FeatureVector.o
PROGRAM = bin/ocr
CXXFLAGS = -Wall -Wextra -O2 -I$(incdir) -g #-Weffc++ #-Wold-style-cast #-Winline



main: main.o
	$(CXX) $(CXXFLAGS) $(BOOST_LDFLAGS) $(MAGICK_LDFLAGS) $(OBJECTS) -o $(PROGRAM)
	@echo

main.o: $(MAIN)
	$(CXX) $(CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo

Recognizer.o: $(RECOGNIZER)
	$(CXX) $(CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo

Text.o: $(TEXT)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Statistics.o: $(STATISTICS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Preprocessor.o: $(PREPROCESSOR)
	$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) -c $< -o $@
	@echo

Clip.o: $(CLIP)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

NessieException.o: $(NESSIE_EXCEPTION)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Segmenter.o: $(SEGMENTER)
	$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) -c $< -o $@
	@echo

Shape.o: $(SHAPE)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Classifier.o: $(CLASSIFIER)
	$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) -c $< -o $@
	@echo

DataSet.o: $(DATASET)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

FeatureVector.o: $(FEATURE_VECTOR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo



# Make everything
all: clean main


# Delete everything
clean:
	rm -f $(OBJECTS) $(PROGRAM)
	$(CHMOD) 0644 $(srcdir)*.cpp $(incdir)*.hpp
	@echo

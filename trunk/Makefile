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
# Dependencies
#
MAIN = main.cpp Recognizer.o Clip.o
RECOGNIZER = Recognizer.cpp Recognizer.hpp Text.o Statistics.o Clip.o
TEXT = Text.cpp Text.hpp
STATISTICS = Statistics.cpp Statistics.hpp

NESSIE_EXCEPTION = NessieException.cpp NessieException.hpp
CLIP = Clip.cpp NessieException.o
SHAPE = Shape.cpp Shape.hpp
PREPROCESSOR = Preprocessor.cpp Preprocessor.hpp Shape.o Clip.o
CLASSIFIER = Classifier.cpp Classifier.hpp DataSet.o Shape.o
FEATURE_VECTOR = FeatureVector.cpp FeatureVector.hpp NessieException.o
DATASET = DataSet.cpp DataSet.hpp NessieException.o FeatureVector.o



#
# Compiler and linker options
#
OBJECTS = *.o
PROGRAM = bin/ocr
CXXFLAGS = -Wall -Wextra -O2 -I$(incdir) -g #-Weffc++ #-Wold-style-cast #-Winline
MAGICK_LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_CXXFLAGS = `Magick++-config --cppflags --cxxflags`
BOOST_CXXFLAGS = -I`find /usr/*/include -maxdepth 1 -name boost`



main: main.o
	$(CXX) $(CXXFLAGS) $(MAGICK_LDFLAGS) $(OBJECTS) -o $(PROGRAM)
	@echo

main.o: $(MAIN)
	$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo

Recognizer.o: $(RECOGNIZER)
	$(CXX) $(CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo

Clip.o: $(CLIP)
	$(CXX) $(CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo

Text.o: $(TEXT)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Statistics.o: $(STATISTICS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Preprocessor.o: $(PREPROCESSOR)
	$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo


NessieException.o: $(NESSIE_EXCEPTION)
	$(CXX) $(CXXFLAGS) -c $< -o $@
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

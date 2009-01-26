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
NESSIE_EXCEPTION = NessieException.cpp NessieException.hpp
CLIP = Clip.cpp NessieException.o
RECOGNIZER = Recognizer.cpp Recognizer.hpp Clip.o Text.o Statistics.o Preprocessor.o
TEXT = Text.cpp Text.hpp NessieException.o
STATISTICS = Statistics.cpp Statistics.hpp
PREPROCESSOR = Preprocessor.cpp Preprocessor.hpp Clip.o Statistics.o Region.o Pattern.o

REGION = Region.cpp Region.hpp
PATTERN = Pattern.cpp Pattern.hpp
CLASSIFIER = Classifier.cpp Classifier.hpp DataSet.o Pattern.o
FEATURE_VECTOR = FeatureVector.cpp FeatureVector.hpp NessieException.o
DATASET = DataSet.cpp DataSet.hpp NessieException.o FeatureVector.o



#
# Compiler and linker options
#
OBJECTS = *.o
PROGRAM = bin/ocr
CXXFLAGS = -ansi -pipe -Wall -Wextra -O3 -I$(incdir) -g -Weffc++ -Wold-style-cast
MAGICK_LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_CXXFLAGS = `Magick++-config --cppflags --cxxflags`
BOOST_CXXFLAGS = -I/usr/local/include/boost



main: main.o
	$(CXX) $(CXXFLAGS) $(MAGICK_LDFLAGS) $(OBJECTS) -o $(PROGRAM)
	@echo

main.o: $(MAIN)
	$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo

NessieException.o: $(NESSIE_EXCEPTION)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Clip.o: $(CLIP)
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
	$(CXX) $(CXXFLAGS) $(BOOST_CXXFLAGS) $(MAGICK_CXXFLAGS) -c $< -o $@
	@echo

Region.o: $(REGION)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo

Pattern.o: $(PATTERN)
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

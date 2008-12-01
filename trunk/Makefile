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
.SUFFIXES:
.SUFFIXES: .cpp .o .hpp



#
# Directories
#
SRC=src/
INC=inc/
vpath %.hpp	$(INC)
vpath %.cpp	$(SRC)
vpath %.o	$(SRC)



#
# Magick++ API path
#
MAGICK_LINKER = `Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_COMPILER = `Magick++-config --cppflags --cxxflags`

#
# Boost API path
#
BOOST_COMPILER = -I/usr/local/include/boost
BOOST_LINKER = -L/usr/local/lib



#
# Targets
#
MAIN_OBJ = main.o
NESSIE_EXCEPTION_OBJ = NessieException.o
STATISTICS_OBJ = Statistics.o
TEXT_OBJ = Text.o
CLIP_OBJ = Clip.o
CLIP_LOCATION_OBJ = ClipLocation.o
SHAPE_OBJ = Shape.o
PREPROCESSOR_OBJ = Preprocessor.o
SEGMENTER_OBJ = Segmenter.o
CLASSIFIER_OBJ = Classifier.o
RECOGNIZER_OBJ = Recognizer.o
FEATURE_VECTOR_OBJ = FeatureVector.o
DATASET_OBJ = DataSet.o



#
# Dependencies
#
MAIN = main.cpp $(RECOGNIZER_OBJ)
NESSIE_EXCEPTION = NessieException.cpp NessieException.hpp
STATISTICS = Statistics.cpp Statistics.hpp
TEXT = Text.cpp Text.hpp
CLIP = Clip.cpp Clip.hpp $(NESSIE_EXCEPTION_OBJ)
CLIP_LOCATION = ClipLocation.cpp ClipLocation.hpp
SHAPE = Shape.cpp Shape.hpp
PREPROCESSOR = Preprocessor.cpp Preprocessor.hpp $(CLIP_OBJ)
SEGMENTER = Segmenter.cpp Segmenter.hpp $(CLIP_OBJ) $(SHAPE_OBJ)
CLASSIFIER = Classifier.cpp Classifier.hpp $(DATASET_OBJ) $(SHAPE_OBJ)
RECOGNIZER = Recognizer.cpp Recognizer.hpp $(TEXT_OBJ) $(STATISTICS_OBJ) $(PREPROCESSOR_OBJ) $(SEGMENTER_OBJ) $(CLASSIFIER_OBJ) $(CLIP_LOCATION_OBJ)
FEATURE_VECTOR = FeatureVector.cpp FeatureVector.hpp $(NESSIE_EXCEPTION_OBJ)
DATASET = DataSet.cpp DataSet.hpp $(NESSIE_EXCEPTION_OBJ) $(FEATURE_VECTOR_OBJ)



#
# Compiler and linker options
# 
EXECUTABLE = bin/ocr
FLAGS = -Wall -Wextra -O2 -Iinc/ -g #-Weffc++ -Wold-style-cast -Winline



main: $(MAIN_OBJ)
	$(CXX) $(FLAGS) $(BOOST_LINKER) $(MAGICK_LINKER) $(SRC)*.o -o $(EXECUTABLE)
	@printf "\n"

$(MAIN_OBJ): $(MAIN)
	$(CXX) $(FLAGS) $(MAGICK_COMPILER) -c $<
	@mv main.o $(SRC)
	@printf "\n"

$(RECOGNIZER_OBJ): $(RECOGNIZER)
	$(CXX) $(FLAGS) $(MAGICK_COMPILER) -c $<
	@mv $(RECOGNIZER_OBJ) $(SRC)
	@printf "\n"

$(TEXT_OBJ): $(TEXT)
	$(CXX) $(FLAGS) $(BOOST_COMPILER) -c $<
	@mv $(TEXT_OBJ) $(SRC)
	@printf "\n"

$(STATISTICS_OBJ): $(STATISTICS) 
	$(CXX) $(FLAGS) -c $<
	@mv $(STATISTICS_OBJ) $(SRC)
	@printf "\n"

$(PREPROCESSOR_OBJ): $(PREPROCESSOR)
	$(CXX) $(FLAGS) $(BOOST_COMPILER) -c $<
	@mv $(PREPROCESSOR_OBJ) $(SRC)
	@printf "\n"

$(CLIP_OBJ): $(CLIP)
	$(CXX) $(FLAGS) -c $<
	@mv $(CLIP_OBJ) $(SRC)
	@printf "\n"

$(NESSIE_EXCEPTION_OBJ): $(NESSIE_EXCEPTION)
	$(CXX) $(FLAGS) -c $<
	@mv $(NESSIE_EXCEPTION_OBJ) $(SRC)
	@printf "\n"

$(CLIP_LOCATION_OBJ): $(CLIP_LOCATION)
	$(CXX) $(FLAGS) -c $<
	@mv $(CLIP_LOCATION_OBJ) $(SRC)
	@printf "\n"

$(SEGMENTER_OBJ): $(SEGMENTER)
	$(CXX) $(FLAGS) $(BOOST_COMPILER) -c $<
	@mv $(SEGMENTER_OBJ) $(SRC)
	@printf "\n"

$(SHAPE_OBJ): $(SHAPE)
	$(CXX) $(FLAGS) -c $<
	@mv $(SHAPE_OBJ) $(SRC)
	@printf "\n"

$(CLASSIFIER_OBJ): $(CLASSIFIER)
	$(CXX) $(FLAGS) -c $<
	@mv $(CLASSIFIER_OBJ) $(SRC)
	@printf "\n"
	
$(DATASET_OBJ): $(DATASET)
	$(CXX) $(FLAGS) -c $<
	@mv $(DATASET_OBJ) $(SRC)
	@printf "\n"

$(FEATURE_VECTOR_OBJ): $(FEATURE_VECTOR)
	$(CXX) $(FLAGS) -c $<
	@mv $(FEATURE_VECTOR_OBJ) $(SRC)
	@printf "\n"



# Make everything
all: clean main


# Delete everything
clean:
	rm -f $(SRC)*.o $(EXECUTABLE)
	chmod 0644 $(SRC)*.cpp $(INC)*.hpp
	@printf "\n"

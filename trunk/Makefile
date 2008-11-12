###
# Makefile: builds the Nessie OCR
#
# Copyright (C) 2008 Eliezer Talon <elitalon@gmail.com>
#
# Usage: make [ main | all | clean ]
#	- main:		Compiles the source code, default option
#	- clean:	Removes every file generated during compilation
#	- all:		Executes clean and then main
#
###


# Directories
SRC=src/
BIN=bin/
INC=inc/
LIB=lib/

# Magick++ API directives
MAGICK_LINKER=`Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_COMPILER=`Magick++-config --cppflags --cxxflags`

# Source file of main program
MAIN_SRC=$(SRC)main.cpp

# Source files of 'NessieException' struct
NESSIE_EXCEPTION_SRC=$(SRC)NessieException.cpp
NESSIE_EXCEPTION_INC=$(INC)NessieException.hpp

# Source files of 'Statistics' struct
STATISTICS_SRC=$(SRC)Statistics.cpp
STATISTICS_INC=$(INC)Statistics.hpp

# Source files of 'Text' class
TEXT_SRC=$(SRC)Text.cpp
TEXT_INC=$(INC)Text.hpp

# Source files of 'Clip' class
CLIP_SRC=$(SRC)Clip.cpp
CLIP_INC=$(INC)Clip.hpp

# Source files of 'Preprocessor' class
PREPROCESSOR_SRC=$(SRC)Preprocessor.cpp
PREPROCESSOR_INC=$(INC)Preprocessor.hpp

# Source files of 'Segmenter' class
SEGMENTER_SRC=$(SRC)Segmenter.cpp
SEGMENTER_INC=$(INC)Segmenter.hpp

# Source files of 'Classifier' class
CLASSIFIER_SRC=$(SRC)Classifier.cpp
CLASSIFIER_INC=$(INC)Classifier.hpp

# Source files of 'Recognizer' class
RECOGNIZER_SRC=$(SRC)Recognizer.cpp
RECOGNIZER_INC=$(INC)Recognizer.hpp

# Source files of 'ClipLocation' class
CLIP_LOCATION_SRC=$(SRC)ClipLocation.cpp
CLIP_LOCATION_INC=$(INC)ClipLocation.hpp

# Source files of 'Shape' class
SHAPE_SRC=$(SRC)Shape.cpp
SHAPE_INC=$(INC)Shape.hpp

# Source files of 'FeatureVector' class
FEATURE_VECTOR_SRC=$(SRC)FeatureVector.cpp
FEATURE_VECTOR_INC=$(INC)FeatureVector.hpp

# Source files of 'DataSet' class
DATASET_SRC=$(SRC)DataSet.cpp
DATASET_INC=$(INC)DataSet.hpp

# Object files
MAIN_OBJ=$(SRC)main.o
NESSIE_EXCEPTION_OBJ=$(SRC)NessieException.o
STATISTICS_OBJ=$(SRC)Statistics.o
TEXT_OBJ=$(SRC)Text.o
CLIP_OBJ=$(SRC)Clip.o
CLIP_LOCATION_OBJ=$(SRC)ClipLocation.o
SHAPE_OBJ=$(SRC)Shape.o
PREPROCESSOR_OBJ=$(SRC)Preprocessor.o
SEGMENTER_OBJ=$(SRC)Segmenter.o
CLASSIFIER_OBJ=$(SRC)Classifier.o
RECOGNIZER_OBJ=$(SRC)Recognizer.o
FEATURE_VECTOR_OBJ=$(SRC)FeatureVector.o
DATASET_OBJ=$(SRC)DataSet.o

# Dependencies
MAIN=$(MAIN_SRC)
NESSIE_EXCEPTION=$(NESSIE_EXCEPTION_INC) $(NESSIE_EXCEPTION_SRC)
STATISTICS=$(STATISTICS_INC) $(STATISTICS_SRC)
TEXT=$(TEXT_INC) $(TEXT_SRC)
CLIP=$(CLIP_INC) $(CLIP_SRC)
CLIP_LOCATION=$(CLIP_LOCATION_INC) $(CLIP_LOCATION_SRC)
SHAPE=$(SHAPE_INC) $(SHAPE_SRC)
PREPROCESSOR=$(PREPROCESSOR_INC) $(PREPROCESSOR_SRC)
SEGMENTER=$(SEGMENTER_INC) $(SEGMENTER_SRC)
CLASSIFIER=$(CLASSIFIER_INC) $(CLASSIFIER_SRC)
RECOGNIZER=$(RECOGNIZER_INC) $(RECOGNIZER_SRC)
FEATURE_VECTOR=$(FEATURE_VECTOR_INC) $(FEATURE_VECTOR_SRC)
DATASET=$(DATASET_INC) $(DATASET_SRC)


# Object files
OBJECTS=$(RECOGNIZER_OBJ) $(NESSIE_EXCEPTION_OBJ) $(CLIP_LOCATION_OBJ) $(STATISTICS_OBJ) $(TEXT_OBJ)\
		$(PREPROCESSOR_OBJ) $(CLIP_OBJ)\
		$(SEGMENTER_OBJ) $(SHAPE_OBJ)\
		$(CLASSIFIER_OBJ) $(DATASET_OBJ) $(FEATURE_VECTOR_OBJ)
		
		

# Compiler options
EXECUTABLE=$(BIN)ocr
DEBUG=NO
COMPILER_DEBUGGING_OPTIONS=-Wextra -Weffc++ -Wold-style-cast -Winline -g
LINKER_DEBUGGING_OPTIONS=
FLAGS=-Wall -O2 -I$(INC) -I$(LIB)

# Formatted output commands
NL=\n
TAB=\t


# Main rule
main: $(MAIN_OBJ)
	@printf "** Linking and building:$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) $(MAGICK_LINKER) $(OBJECTS) $(MAIN_OBJ) -o $(EXECUTABLE)
else
	g++ $(FLAGS) $(LINKER_DEBUGGING_OPTIONS) $(MAGICK_LINKER) $(OBJECTS) $(MAIN_OBJ) -o $(EXECUTABLE)
endif
	@printf "$(NL)** Compilation completed!$(NL)$(NL)"


$(MAIN_OBJ): $(RECOGNIZER_OBJ) $(MAIN)
	@printf "** Making rule $(MAIN_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) $(MAGICK_COMPILER) -c $(MAIN_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) $(MAGICK_COMPILER) -c $(MAIN_SRC)
endif
	@printf "$(TAB)"
	mv main.o $(SRC)
	@printf "$(NL)"


$(RECOGNIZER_OBJ): $(TEXT_OBJ) $(STATISTICS_OBJ) $(PREPROCESSOR_OBJ) $(CLIP_OBJ) $(CLIP_LOCATION_OBJ) $(SEGMENTER_OBJ) $(CLASSIFIER_OBJ) $(RECOGNIZER)
	@printf "** Making rule $(RECOGNIZER_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) $(MAGICK_COMPILER) -c $(RECOGNIZER_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) $(MAGICK_COMPILER) -c $(RECOGNIZER_SRC)
endif
	@printf "$(TAB)"
	mv Recognizer.o $(SRC)
	@printf "$(NL)"


$(TEXT_OBJ): $(TEXT)
	@printf "** Making rule $(TEXT_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(TEXT_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(TEXT_SRC)
endif	
	@printf "$(TAB)"
	mv Text.o $(SRC)
	@printf "$(NL)"


$(STATISTICS_OBJ): $(STATISTICS) 
	@printf "** Making rule $(STATISTICS_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(STATISTICS_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(STATISTICS_SRC)
endif
	@printf "$(TAB)"
	mv Statistics.o $(SRC)
	@printf "$(NL)"


$(PREPROCESSOR_OBJ): $(CLIP_OBJ) $(PREPROCESSOR)
	@printf "** Making rule $(PREPROCESSOR_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(PREPROCESSOR_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(PREPROCESSOR_SRC)
endif
	@printf "$(TAB)"
	mv Preprocessor.o $(SRC)
	@printf "$(NL)"


$(CLIP_OBJ): $(NESSIE_EXCEPTION_OBJ) $(CLIP)
	@printf "** Making rule $(CLIP_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(CLIP_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(CLIP_SRC)
endif
	@printf "$(TAB)"
	mv Clip.o $(SRC)
	@printf "$(NL)"


$(NESSIE_EXCEPTION_OBJ): $(NESSIE_EXCEPTION)
	@printf "** Making rule $(NESSIE_EXCEPTION_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(NESSIE_EXCEPTION_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(NESSIE_EXCEPTION_SRC)
endif
	@printf "$(TAB)"
	mv NessieException.o $(SRC)
	@printf "$(NL)"


$(CLIP_LOCATION_OBJ): $(CLIP_LOCATION)
	@printf "** Making rule $(CLIP_LOCATION_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(CLIP_LOCATION_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(CLIP_LOCATION_SRC)
endif
	@printf "$(TAB)"
	mv ClipLocation.o $(SRC)
	@printf "$(NL)"


$(SEGMENTER_OBJ): $(CLIP_OBJ) $(SHAPE_OBJ) $(SEGMENTER)
	@printf "** Making rule $(SEGMENTER_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(SEGMENTER_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(SEGMENTER_SRC)
endif
	@printf "$(TAB)"
	mv Segmenter.o $(SRC)
	@printf "$(NL)"


$(SHAPE_OBJ): $(SHAPE)
	@printf "** Making rule $(SHAPE_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(SHAPE_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(SHAPE_SRC)
endif
	@printf "$(TAB)"
	mv Shape.o $(SRC)
	@printf "$(NL)"


$(CLASSIFIER_OBJ): $(DATASET_OBJ) $(SHAPE_OBJ) $(CLASSIFIER)
	@printf "** Making rule $(CLASSIFIER_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(CLASSIFIER_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(CLASSIFIER_SRC)
endif
	@printf "$(TAB)"
	mv Classifier.o $(SRC)
	@printf "$(NL)"
	
	
$(DATASET_OBJ): $(NESSIE_EXCEPTION_OBJ) $(FEATURE_VECTOR_OBJ) $(DATASET)
	@printf "** Making rule $(DATASET_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(DATASET_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(DATASET_SRC)
endif
	@printf "$(TAB)"
	mv DataSet.o $(SRC)
	@printf "$(NL)"


$(FEATURE_VECTOR_OBJ): $(NESSIE_EXCEPTION_OBJ) $(FEATURE_VECTOR)
	@printf "** Making rule $(FEATURE_VECTOR_OBJ):$(NL)"
	@printf "$(TAB)"
ifeq ($(DEBUG),NO)
	g++ $(FLAGS) -c $(FEATURE_VECTOR_SRC)
else
	g++ $(FLAGS) $(COMPILER_DEBUGGING_OPTIONS) -c $(FEATURE_VECTOR_SRC)
endif
	@printf "$(TAB)"
	mv FeatureVector.o $(SRC)
	@printf "$(NL)"



# Make everything
all: clean main


# Delete everything
clean:
	@printf "** Removing object files$(NL)"
	@rm -f $(SRC)*.o
	@printf "** Restoring permissions$(NL)"
	@chmod 0644 $(SRC)*.cpp $(INC)*.hpp
	@printf "$(NL)"

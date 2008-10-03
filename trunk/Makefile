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
DOC=doc/

# Magick++ API directives
MAGICK_LINK=`Magick++-config --cppflags --cxxflags --ldflags --libs`
MAGICK_COMPILE=`Magick++-config --cppflags --cxxflags`

# Source file of main program
MAIN_SRC=$(SRC)main.cpp

# Source files of 'NessieException' struct
NESSIE_EXCEPTION_SRC=$(SRC)NessieException.cpp
NESSIE_EXCEPTION_INC=$(INC)NessieException.h

# Source files of 'WordRate' pair
WORD_RATE_INC=$(INC)WordRate.h

# Source files of 'Statistics' struct
STATISTICS_SRC=$(SRC)Statistics.cpp
STATISTICS_INC=$(INC)Statistics.h

# Source files of 'Colorspace' enumeration
COLORSPACE_INC=$(INC)Colorspace.h

# Source files of 'RgbColor' struct
RGB_COLOR_SRC=$(SRC)RgbColor.cpp
RGB_COLOR_INC=$(INC)RgbColor.h

# Source files of 'Text' class
TEXT_SRC=$(SRC)Text.cpp
TEXT_INC=$(INC)Text.h

# Source files of 'Pixel' class
PIXEL_SRC=$(SRC)Pixel.cpp
PIXEL_INC=$(INC)Pixel.h

# Source files of 'Clip' class
CLIP_SRC=$(SRC)Clip.cpp
CLIP_INC=$(INC)Clip.h

# Source files of 'Preprocessor' class
PREPROCESSOR_SRC=$(SRC)Preprocessor.cpp
PREPROCESSOR_INC=$(INC)Preprocessor.h

# Object files
MAIN_OBJ=$(SRC)main.o
NESSIE_EXCEPTION_OBJ=$(SRC)NessieException.o
STATISTICS_OBJ=$(SRC)Statistics.o
RGB_COLOR_OBJ=$(SRC)RgbColor.o
TEXT_OBJ=$(SRC)Text.o
PIXEL_OBJ=$(SRC)Pixel.o
CLIP_OBJ=$(SRC)Clip.o
PREPROCESSOR_OBJ=$(SRC)Preprocessor.o

# Dependencies
MAIN=$(MAIN_SRC)
NESSIE_EXCEPTION=$(NESSIE_EXCEPTION_INC) $(NESSIE_EXCEPTION_SRC)
COLORSPACE=$(COLORSPACE_INC)
WORD_RATE=$(WORD_RATE_INC)
STATISTICS=$(STATISTICS_INC) $(STATISTICS_SRC)
RGB_COLOR=$(RGB_COLOR_INC) $(RGB_COLOR_SRC)
TEXT=$(TEXT_INC) $(TEXT_SRC)
CLIP=$(CLIP_INC) $(CLIP_SRC)
PIXEL=$(PIXEL_INC) $(PIXEL_SRC)
PREPROCESSOR=$(PREPROCESSOR_INC) $(PREPROCESSOR_SRC)

# Final object files
OBJECTS=$(NESSIE_EXCEPTION_OBJ) $(STATISTICS_OBJ) $(RGB_COLOR_OBJ) $(TEXT_OBJ) $(PIXEL_OBJ) $(CLIP_OBJ) $(PREPROCESSOR_OBJ) $(MAIN_OBJ)

# Compiler options
EXECUTABLE=$(BIN)ocr
FLAGS=-Wall -g -O3 -I$(INC)

# Formatted output commands
NL=\n
TAB=\t


# Main rule
main: $(OBJECTS)
	@printf "** Linking and building the main rule:$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) $(MAGICK_LINK) $(OBJECTS) -o $(EXECUTABLE)
	@printf "$(NL)** Compilation completed!$(NL)$(NL)"

$(MAIN_OBJ): $(MAIN)
	@printf "** Making rule $(MAIN_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) $(MAGICK_COMPILE) -c $(MAIN_SRC) 
	@printf "$(TAB)"
	mv main.o $(SRC)
	@printf "$(NL)"

$(NESSIE_EXCEPTION_OBJ): $(NESSIE_EXCEPTION)
	@printf "** Making rule $(NESSIE_EXCEPTION_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(NESSIE_EXCEPTION_SRC) 
	@printf "$(TAB)"
	mv NessieException.o $(SRC)
	@printf "$(NL)"

$(STATISTICS_OBJ): $(WORD_RATE) $(STATISTICS) 
	@printf "** Making rule $(STATISTICS_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(STATISTICS_SRC) 
	@printf "$(TAB)"
	mv Statistics.o $(SRC)
	@printf "$(NL)"

$(RGB_COLOR_OBJ): $(RGB_COLOR)
	@printf "** Making rule $(RGB_COLOR_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(RGB_COLOR_SRC)
	@printf "$(TAB)"
	mv RgbColor.o $(SRC)
	@printf "$(NL)"

$(TEXT_OBJ): $(WORD_RATE) $(TEXT)
	@printf "** Making rule $(TEXT_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(TEXT_SRC)
	@printf "$(TAB)"
	mv Text.o $(SRC)
	@printf "$(NL)"
	
$(PIXEL_OBJ): $(RGB_COLOR_OBJ) $(COLORSPACE) $(PIXEL)
	@printf "** Making rule $(PIXEL_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) $(MAGICK_COMPILE) -c $(PIXEL_SRC)
	@printf "$(TAB)"
	mv Pixel.o $(SRC)
	@printf "$(NL)"

$(CLIP_OBJ): $(PIXEL_OBJ) $(COLORSPACE) $(CLIP)
	@printf "** Making rule $(CLIP_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) $(MAGICK_COMPILE) -c $(CLIP_SRC)
	@printf "$(TAB)"
	mv Clip.o $(SRC)
	@printf "$(NL)"

$(PREPROCESSOR_OBJ): $(CLIP_OBJ) $(PREPROCESSOR)
	@printf "** Making rule $(PREPROCESSOR_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) $(MAGICK_COMPILE) -c $(PREPROCESSOR_SRC)
	@printf "$(TAB)"
	mv Preprocessor.o $(SRC)
	@printf "$(NL)"


# Make everything
all: clean main doc

# Generate documentation
doc: $(INC)*.h $(SRC)*.cpp
	@printf "** Updating documentation:$(NL)"
	@printf "$(TAB)"
	doxygen
	@printf "$(NL)"

# Delete everything
clean:
	@printf "** Removing object and executable files$(NL)"
	@rm -f $(SRC)*.o
	@printf "** Restoring permissions$(NL)"
	@chmod 0644 $(SRC)*.cpp $(INC)*.h
	@printf "$(NL)"

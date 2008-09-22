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

# Magick++ API flags
MAGICK=`Magick++-config --cppflags --cxxflags --ldflags --libs`

# Source file of main program
MAIN_SRC=$(SRC)main.cpp

# Source files of 'WordRate' structure
WORD_RATE_INC=$(INC)WordRate.h

# Source files of 'Statistics' struct
STATISTICS_SRC=$(SRC)Statistics.cpp
STATISTICS_INC=$(INC)Statistics.h

# Source files of 'FontWeight' enumeration
FONT_WEIGHT_INC=$(INC)FontWeight.h

# Source files of 'FontProportionality' enumeration
FONT_PROPORTIONALITY_INC=$(INC)FontProportionality.h

# Source files of 'FontColor' struct
FONT_COLOR_SRC=$(SRC)FontColor.cpp
FONT_COLOR_INC=$(INC)FontColor.h

# Source files of 'Style' class
STYLE_SRC=$(SRC)Style.cpp
STYLE_INC=$(INC)Style.h

# Source files of 'Text' class
TEXT_SRC=$(SRC)Text.cpp
TEXT_INC=$(INC)Text.h

# Object files
MAIN_OBJ=$(SRC)main.o
STATISTICS_OBJ=$(SRC)Statistics.o
FONT_COLOR_OBJ=$(SRC)FontColor.o
STYLE_OBJ=$(SRC)Style.o
TEXT_OBJ=$(SRC)Text.o

# Dependencies
MAIN=$(MAIN_SRC)
WORD_RATE=$(WORD_RATE_INC)
STATISTICS=$(STATISTICS_INC) $(STATISTICS_SRC)
FONT_WEIGHT=$(FONT_WEIGHT_INC)
FONT_PROPORTIONALITY=$(FONT_PROPORTIONALITY_INC)
FONT_COLOR=$(FONT_COLOR_INC) $(FONT_COLOR_SRC)
STYLE=$(STYLE_INC) $(STYLE_SRC)
TEXT=$(TEXT_INC) $(TEXT_SRC)

# Final object files
OBJECTS=$(STATISTICS_OBJ) $(FONT_COLOR_OBJ) $(STYLE_OBJ) $(TEXT_OBJ) $(MAIN_OBJ)

# Compiler options
EXECUTABLE=test
FLAGS=-Wall -O3 -I$(INC)

# Formatted output commands
NL=\n
TAB=\t


# Main rule
main: $(OBJECTS)
	@printf "** Linking and building the main rule:$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) $(MAGICK) $(OBJECTS) -o $(EXECUTABLE)
	@printf "$(NL)** Compilation completed!$(NL)$(NL)"

$(MAIN_OBJ): $(MAIN)
	@printf "** Making rule $(MAIN_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(MAIN_SRC) 
	@printf "$(TAB)"
	mv main.o $(SRC)
	@printf "$(NL)"

$(STATISTICS_OBJ): $(WORD_RATE) $(STATISTICS) 
	@printf "** Making rule $(STATISTICS_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(STATISTICS_SRC) 
	@printf "$(TAB)"
	mv Statistics.o $(SRC)
	@printf "$(NL)"

$(STYLE_OBJ): $(FONT_COLOR_OBJ) $(FONT_WEIGHT) $(STYLE) 
	@printf "** Making rule $(STYLE_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(STYLE_SRC)
	@printf "$(TAB)"
	mv Style.o $(SRC)
	@printf "$(NL)"
	
$(FONT_COLOR_OBJ): $(FONT_COLOR)
	@printf "** Making rule $(FONT_COLOR_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(FONT_COLOR_SRC)
	@printf "$(TAB)"
	mv FontColor.o $(SRC)
	@printf "$(NL)"

$(TEXT_OBJ): $(FONT_PROPORTIONALITY) $(STYLE_OBJ) $(WORD_RATE) $(TEXT)
	@printf "** Making rule $(TEXT_OBJ):$(NL)"
	@printf "$(TAB)"
	g++ $(FLAGS) -c $(TEXT_SRC)
	@printf "$(TAB)"
	mv Text.o $(SRC)
	@printf "$(NL)"

# Makes everything
all: clean main


# Deletes everything
clean:
	@printf "** Removing object and executable files$(NL)"
	@rm $(SRC)*.o
	@printf "** Restoring permissions$(NL)"
	@chmod 0644 $(SRC)*.cpp $(INC)*.h
	@printf "$(NL)"

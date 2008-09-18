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
WORD_RATE_SRC=$(SRC)WordRate.cpp
WORD_RATE_INC=$(INC)WordRate.h

# Source files of 'Statistics' class
STATISTICS_SRC=$(SRC)Statistics.cpp
STATISTICS_INC=$(INC)Statistics.h

# Object files
MAIN_OBJ=$(SRC)main.o
WORD_RATE_OBJ=$(SRC)WordRate.o
STATISTICS_OBJ=$(SRC)Statistics.o

# Dependencies
MAIN=$(MAIN_SRC)
WORD_RATE=$(WORD_RATE_INC) $(WORD_RATE_SRC)
STATISTICS=$(STATISTICS_INC) $(STATISTICS_SRC)

# Final object files
OBJECTS=$(WORD_RATE_OBJ) $(STATISTICS_OBJ) $(MAIN_OBJ)
#OBJECTS=$(FLEX_OBJ) $(SYMBOL_TABLE_OBJ) $(GESTION_MEMORIA_OBJ) $(SINTACTICO_OBJ) 

# Compiler options
EXECUTABLE=test
FLAGS=-Wall -O3 -I$(INC)

# New line command
NL=\n


# Main rule
main: $(OBJECTS)
	@printf "** Linking and building the main rule:$(NL)"
	@printf "\t- Linking...$(NL)"
	@g++ $(FLAGS) $(MAGICK) $(OBJECTS) -o $(EXECUTABLE)
	@printf "\t- Cleaning up...$(NL)"
	@printf "$(NL)** Compilation completed!$(NL)$(NL)"

$(MAIN_OBJ): $(MAIN)
	@printf "** Making rule $(MAIN_OBJ):$(NL)"
	@printf "\t- Compiling...$(NL)"
	@g++ $(FLAGS) -c $(MAIN_SRC) 
	@printf "\t- Moving to $(SRC) directory...$(NL)"
	@mv main.o $(SRC)
	@printf "\t- Finishing...$(NL)$(NL)"

$(WORD_RATE_OBJ): $(WORD_RATE)
	@printf "** Making rule $(WORD_RATE_OBJ):$(NL)"
	@printf "\t- Compiling...$(NL)"
	@g++ $(FLAGS) -c -I$(INC) $(WORD_RATE_SRC) 
	@printf "\t- Moving to $(SRC) directory...$(NL)"
	@mv WordRate.o $(SRC)
	@printf "\t- Finishing...$(NL)$(NL)"

$(STATISTICS_OBJ): $(WORD_RATE_OBJ) $(STATISTICS) 
	@printf "** Making rule $(STATISTICS_OBJ):$(NL)"
	@printf "\t- Compiling...$(NL)"
	@g++ $(FLAGS) -c -I$(INC) $(STATISTICS_SRC) 
	@printf "\t- Moving to $(SRC) directory...$(NL)"
	@mv Statistics.o $(SRC)
	@printf "\t- Finishing...$(NL)$(NL)"


# Makes everything
all: clean main


# Deletes everything
clean:
	@printf "** Removing object and executable files$(NL)"
	@rm $(SRC)*.o
	@printf "** Restoring permissions$(NL)"
	@chmod 0644 $(SRC)*.cpp $(INC)*.h
	@printf "$(NL)"

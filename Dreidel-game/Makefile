#
# Makefile for Assignment 3, CSE 13S, Fall 2022.
#
# You are welcome to modify this Makefile to meet your needs.
# You should learn from the Makefile, and try building your own!
#

# These are "phony" targets: they're not real files
.PHONY: all pdfs clean

##################################################################
#
# C stuff
#
##################################################################

# Name of the program this Makefile is going to build
EXECBIN  = play-dreidel

# Default values for compiling C files
CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra $(OPTFLAG)
# Optimization level
OPTFLAG  = -O2

# All available .c files are included as SOURCES
#SOURCES  = $(wildcard *.c)
# Specify the C source files manually. May be useful if you
# don't want to compile *all* the C files together.
SOURCES   = dreidel.c play-dreidel.c mtrand.c

# Each .c file has a corresponding .o file
OBJECTS  = $(SOURCES:%.c=%.o)

# This is the first actual target in the file.
# That means it's built when 'make' is run without arguments.
all: $(EXECBIN)
# If you want to build the pdf files as well as the executable (if needed),
# use the following line:
all: $(EXECBIN) pdfs

# The program depends on *all* of the OBJECTS.
$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFLAGS)


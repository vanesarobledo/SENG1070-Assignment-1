# Makefile template blatantly taken from: 
# Poworoznyk, D. (2024, Jan 17). Command-line Development Tools [PowerPoint Slides]. eConestoga.

# Define variables for compiler, compiler flags, and executable name  
CC = gcc # Compiler to use (gcc for C programs)  
CFLAGS = -Wall -g # Compiler flags: show warnings (-Wall) and debugging info (-g)  
TARGET = FileProcessing # The name of the final executable  

# List of object files (compiled versions of source files)  
OBJ = main.o operations.o fileProcessing.o

# Default target that will be built when running "make" with no arguments  
all: $(TARGET)  

# Link all object files to create the final executable  
# The $(CC) $(CFLAGS) -o $(TARGET) $(OBJ) command compiles the object files into an executable  
$(TARGET): $(OBJ)  
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)  

# Rule to compile main.c into main.o, specifying its dependency on operations.h  
main.o: main.c operations.h 
	$(CC) $(CFLAGS) -c main.c

# Rule to compile operations.c into operations.o, specifying its dependency on operations.h  
operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c operations.c

# Rule to compile fileProcessing.c into fileProcessing.o, specifying its dependency on fileProcessing.h  
fileProcessing.o: fileProcessing.c fileProcessing.h
	$(CC) $(CFLAGS) -c fileProcessing.c

# Optional target to remove all object files and the executable  
# Run "make clean" to remove generated files and clean up the directory  
clean:  
	rm -f *.o $(TARGET)
# Makefile for PA4 - Movie and TV Show Search and Sort
# CPTS 223 Advanced Data Structures

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable name
TARGET = pa4

# Source files
SOURCES = main.cpp MediaItem.cpp MovieDatabase.cpp Testing.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(TARGET) $(OBJECTS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = linux_game
SOURCES = main.cpp Game.cpp
HEADERS = Node.h List.h Command.h Player.h Game.h
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -DDEBUG
debug: $(TARGET)

help:
	@echo "Available targets:"
	@echo "  all     - Build the program (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  rebuild - Clean and build"
	@echo "  run     - Build and run the program"
	@echo "  debug   - Build with debug flags"
	@echo "  help    - Show this help message"

.PHONY: all clean rebuild run debug help

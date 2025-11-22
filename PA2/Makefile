CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
DEBUGFLAGS = -g -O0

TARGET = avl_test
TEST_TARGET = test_avl
DEBUG_TARGET = test_avl_debug

MAIN_SOURCES = main.cpp
TEST_SOURCES = test_avl.cpp

HEADERS = avl_map.h USCity.h CSVParser.h

MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJECTS)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS)

debug: $(TEST_SOURCES) $(HEADERS)
	$(CXX) $(DEBUGFLAGS) -std=c++11 -o $(DEBUG_TARGET) $(TEST_SOURCES)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

gdb-test: debug
	gdb ./$(DEBUG_TARGET)

clean:
	rm -f $(MAIN_OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET) $(DEBUG_TARGET)

rebuild: clean all

help:
	@echo "Available targets:"
	@echo "  make          - Build main and test programs"
	@echo "  make run      - Build and run main program"
	@echo "  make test     - Build and run test program"
	@echo "  make debug    - Build debug version for GDB"
	@echo "  make gdb-test - Build and run with GDB debugger"
	@echo "  make clean    - Remove all build artifacts"
	@echo "  make rebuild  - Clean and rebuild everything"

.PHONY: all clean rebuild run test debug gdb-test help

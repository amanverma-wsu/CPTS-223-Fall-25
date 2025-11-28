CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = emergency_system
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Graph.h Hospital.h PriorityQueue.h Patient.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = priority_queue

SRCS = main.cpp ListPriorityQueue.cpp PrinterJob.cpp HeapPriorityQueue.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

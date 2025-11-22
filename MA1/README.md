# Heap Priority Queue Implementation

## Overview
This project implements a **heap-based priority queue** using a fixed-size array to manage PrinterJob objects. The priority queue maintains a **min-heap property** where lower priority numbers represent higher priority tasks that should be processed first.

## Project Structure
```
HeapPriorityQueue/
├── HeapPriorityQueue.h
├── HeapPriorityQueue.cpp
├── PrinterJob.h
├── PrinterJob.cpp
├── ListPriorityQueue.h
├── ListPriorityQueue.cpp
├── main.cpp
├── Makefile
└── README.md
```

## Implementation Overview

### HeapPriorityQueue Class
The `HeapPriorityQueue` class uses a fixed-size array of 100 elements to store `PrinterJob` objects in a min-heap structure.

**Key Features:**
- Fixed array capacity of 100 elements
- Min-heap property: parent priority ≤ child priority
- Array-based heap indexing:
  - Root at index 0
  - Parent of index i: `(i-1)/2`
  - Left child of index i: `2*i+1`
  - Right child of index i: `2*i+2`

### Methods Implemented

**1. Constructor**
- Initializes the heap with size 0

**2. Destructor**
- No dynamic memory allocation, so minimal cleanup

**3. Copy Constructor**
- Performs deep copy of heap array and size

**4. Copy Assignment Operator**
- Handles self-assignment and performs deep copy

**5. enqueue(string str, int priority)**
- Adds a new PrinterJob to the heap
- Places element at end of array
- Calls `percolateUp()` to restore heap property
- Checks for overflow (max 100 elements)

**6. printJobs()**
- Removes and prints all jobs in priority order
- Extracts root (minimum priority) repeatedly
- Replaces root with last element
- Calls `percolateDown()` to restore heap property

**7. percolateUp(int index)** - Private Helper
- Moves newly inserted element up the tree
- Compares with parent and swaps if necessary
- Continues until heap property is satisfied

**8. percolateDown(int index)** - Private Helper
- Moves element down the tree after removal
- Compares with both children
- Swaps with smaller child if necessary
- Continues until heap property is satisfied

## How to Compile

### Option 1: Using Makefile
```bash
make
```

### Option 2: Manual Compilation
```bash
g++ -std=c++11 -Wall -Wextra -c main.cpp
g++ -std=c++11 -Wall -Wextra -c ListPriorityQueue.cpp
g++ -std=c++11 -Wall -Wextra -c PrinterJob.cpp
g++ -std=c++11 -Wall -Wextra -c HeapPriorityQueue.cpp
g++ -std=c++11 -Wall -Wextra -o priority_queue main.o ListPriorityQueue.o PrinterJob.o HeapPriorityQueue.o
```

### Clean Build Files
```bash
make clean
```

## How to Run

Execute the program:
```bash
./priority_queue
```

## Usage

The program provides an interactive command-line interface (REPL):

### Commands

**1. Add a print job:**
```
> <document_name> <priority_number>
```
Example:
```
> Document1 5
> Document2 2
> Report 10
```

**2. Print all jobs in priority order:**
```
> print
```

**3. Exit the program:**
```
> exit
```

## Example Session

```
Enter print jobs in format: <string> <priority>. Type 'print' to process jobs. Type 'exit' to exit.
> Document1 5
> Document2 2
> Document3 8
> Document4 1
> print
Printing jobs in priority order:
Document4 (Priority: 1)
Document2 (Priority: 2)
Document1 (Priority: 5)
Document3 (Priority: 8)
> Report 3
> Email 7
> print
Printing jobs in priority order:
Report (Priority: 3)
Email (Priority: 7)
> exit
```

## How the Heap Works

### Min-Heap Property
- Each parent node has a priority value less than or equal to its children
- The root (index 0) always contains the job with the lowest priority number (highest priority)
- Lower priority number = Higher importance = Processed first

### Insertion (enqueue)
1. Add new element at the end of the array
2. Compare with parent
3. If new element has lower priority than parent, swap
4. Repeat until heap property is restored

### Removal (printJobs)
1. Print and remove the root element (lowest priority number)
2. Move the last element to the root
3. Compare with children
4. Swap with smaller child if necessary
5. Repeat until heap property is restored

## Time Complexity

| Operation | Complexity | Explanation |
|-----------|------------|-------------|
| enqueue | O(log n) | Percolate up at most log n levels |
| dequeue (single) | O(log n) | Percolate down at most log n levels |
| printJobs (all) | O(n log n) | Dequeue n elements, each O(log n) |

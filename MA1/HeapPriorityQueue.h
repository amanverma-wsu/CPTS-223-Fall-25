#ifndef HEAPPRIORITYQUEUE_H
#define HEAPPRIORITYQUEUE_H

#include "PrinterJob.h"

using namespace std;

// The HeapPriorityQueue class implements a priority queue using a min-heap.
// Each element in the heap is a PrinterJob object.
// Lower priority number = higher priority in the queue.
class HeapPriorityQueue {
private:
    static const int MAX_SIZE = 100;  // Maximum number of jobs that can be stored in the heap
    PrinterJob heap[MAX_SIZE];        // Array-based representation of the heap
    int size;                         // Keeps track of how many jobs are currently in the heap

    // Helper functions to maintain heap order
    void percolateUp(int index);      // Moves an element up to restore heap property (used during insertion)
    void percolateDown(int index);    // Moves an element down to restore heap property (used during deletion)

public:
    // Constructor and destructor
    HeapPriorityQueue();              // Initializes an empty heap
    ~HeapPriorityQueue();             // Cleans up (nothing dynamic here, but defined for completeness)

    // Copy control functions
    HeapPriorityQueue(const HeapPriorityQueue& other);        // Copy constructor for deep copy
    HeapPriorityQueue& operator=(const HeapPriorityQueue& other); // Copy assignment operator

    // Core heap operations
    void enqueue(const string& str, int priority);  // Inserts a new print job with given name and priority
    void printJobs();                               // Prints all jobs in order of their priority
};

#endif

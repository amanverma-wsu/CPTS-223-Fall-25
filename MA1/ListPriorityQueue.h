#ifndef LISTPRIORITYQUEUE_H
#define LISTPRIORITYQUEUE_H

#include <list>
#include "PrinterJob.h"

using namespace std;

// The ListPriorityQueue class implements a simple priority queue using a linked list (std::list).
// Unlike the heap version, this one keeps elements in order using insertion logic when enqueuing.
class ListPriorityQueue {
private:
    list<PrinterJob> jobs;   // STL list to store PrinterJob objects (acts as the queue)

public:
    // Constructor and Destructor
    ListPriorityQueue();     // Initializes an empty list-based priority queue
    ~ListPriorityQueue();    // Destructor (automatic cleanup handled by std::list)

    // Copy control methods
    ListPriorityQueue(const ListPriorityQueue& other);           // Copy constructor for deep copy
    ListPriorityQueue& operator=(const ListPriorityQueue& other); // Copy assignment operator

    // Core queue operations
    void enqueue(const string& str, int priority);  // Adds a new PrinterJob at the correct position by priority
    void printJobs();                               // Prints and removes all jobs in order of priority
};

#endif

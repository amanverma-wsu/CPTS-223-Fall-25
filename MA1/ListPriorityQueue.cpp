#include "ListPriorityQueue.h"
#include <iostream>

// Default constructor:
// Initializes an empty list-based priority queue.
// Using '= default' tells the compiler to automatically generate the default constructor.
ListPriorityQueue::ListPriorityQueue() = default;

// Destructor:
// Automatically called when the object goes out of scope.
// Since std::list handles its own memory, no manual cleanup is required.
ListPriorityQueue::~ListPriorityQueue() = default;

// Copy constructor:
// Creates a deep copy of another ListPriorityQueue by copying its 'jobs' list.
ListPriorityQueue::ListPriorityQueue(const ListPriorityQueue& other) : jobs(other.jobs) {}

// Copy assignment operator:
// Assigns one ListPriorityQueue to another (deep copy of all PrinterJob elements).
ListPriorityQueue& ListPriorityQueue::operator=(const ListPriorityQueue& other) {
    if (this != &other) {   // Prevent self-assignment
        jobs = other.jobs;  // Copy the entire list
    }
    return *this;
}

// enqueue():
// Adds a new PrinterJob (with given string and priority) into the list
// so that the list remains sorted by priority.
// Lower 'priority' value = higher print priority.
void ListPriorityQueue::enqueue(const string& str, int priority) {
    PrinterJob newJob(str, priority);  // Create a new print job
    auto it = jobs.begin();
    
    // Move iterator forward until we find a job with a higher priority value
    // (i.e., insert before any job with a larger priority number)
    while (it != jobs.end() && it->priority <= priority) {
        ++it;
    }

    // Insert the new job at the correct position in the list
    jobs.insert(it, newJob);
}

// printJobs():
// Prints all jobs in order of priority and removes them from the list one by one.
void ListPriorityQueue::printJobs() {
    if (jobs.empty()) {
        cout << "No jobs in the queue.\n";
        return;
    }
}

#include "HeapPriorityQueue.h"
#include <iostream>

// Constructor: called when an object of HeapPriorityQueue is created
// Initializes the size of the heap to 0
HeapPriorityQueue::HeapPriorityQueue() {
    size = 0;
}

// Destructor: runs automatically when the object is destroyed
// Since we are not using any dynamically allocated memory, nothing special is needed here
HeapPriorityQueue::~HeapPriorityQueue() {
    // No cleanup needed for fixed array
}

// Copy constructor: creates a new HeapPriorityQueue as a copy of another
// Copies all elements of the other heap and its size
HeapPriorityQueue::HeapPriorityQueue(const HeapPriorityQueue& other) {
    size = other.size;
    for (int i = 0; i < size; i++) {
        heap[i] = other.heap[i];
    }
}

// Copy assignment operator: called when assigning one HeapPriorityQueue to another
// Checks for self-assignment and then copies over the data
HeapPriorityQueue& HeapPriorityQueue::operator=(const HeapPriorityQueue& other) {
    if (this != &other) { // prevent self-assignment
        size = other.size;
        for (int i = 0; i < size; i++) {
            heap[i] = other.heap[i];
        }
    }
    return *this;
}

// enqueue(): Adds a new print job to the heap with a given string and priority
// Maintains the heap order property by using percolateUp
void HeapPriorityQueue::enqueue(const string& str, int priority) {
    if (size >= MAX_SIZE) {
        cout << "Queue is full. Cannot enqueue.\n";
        return;
    }
    
    // Insert the new job at the end of the heap array
    heap[size] = PrinterJob(str, priority);
    
    // Move it up to maintain the heap order (min-heap based on priority value)
    percolateUp(size);
    
    // Increase the heap size since a new element was added
    size++;
}

// printJobs(): Prints and removes all jobs in the heap based on their priority order
// Keeps removing the smallest (highest priority) element until the heap is empty
void HeapPriorityQueue::printJobs() {
    if (size == 0) {
        cout << "No jobs in the queue.\n";
        return;
    }
    
    cout << "Printing jobs in priority order:\n";
    while (size > 0) {
        // Print the root job, which always has the smallest priority number
        cout << heap[0].printString << " (Priority: " << heap[0].priority << ")\n";
        
        // Replace root with the last element in the heap
        heap[0] = heap[size - 1];
        size--;
        
        // Restore heap order after removal
        if (size > 0) {
            percolateDown(0);
        }
    }
}

// percolateUp(): Moves an element up the heap until the min-heap property is restored
// Used during insertion (enqueue)
void HeapPriorityQueue::percolateUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        
        // Stop if the parent has equal or smaller priority (min-heap condition satisfied)
        if (heap[index].priority >= heap[parentIndex].priority) {
            break;
        }
        
        // Otherwise, swap the current node with its parent
        PrinterJob temp = heap[index];
        heap[index] = heap[parentIndex];
        heap[parentIndex] = temp;
        
        // Move up to the parent position
        index = parentIndex;
    }
}

// percolateDown(): Moves an element down to maintain min-heap property after removal
// Used during deletion (printJobs)
void HeapPriorityQueue::percolateDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;
        
        // Check if left child exists and has smaller priority value
        if (leftChild < size && heap[leftChild].priority < heap[smallest].priority) {
            smallest = leftChild;
        }
        
        // Check if right child exists and has smaller priority value than current smallest
        if (rightChild < size && heap[rightChild].priority < heap[smallest].priority) {
            smallest = rightChild;
        }
        
        // If the current node is already in correct position, stop
        if (smallest == index) {
            break;
        }
        
        // Swap the current node with the smaller child
        PrinterJob temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        
        // Move down to the swapped child's position
        index = smallest;
    }
}

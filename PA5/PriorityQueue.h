#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Patient.h"
#include <vector>
#include <stdexcept>

class PriorityQueue {
private:
    std::vector<Patient> heap;
    
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }
    
    void heapifyUp(int index) {
        while (index > 0 && heap[index] > heap[parent(index)]) {
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);
            
            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }
            
            if (largest == index) break;
            
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    PriorityQueue() {}
    
    void insert(const Patient& patient) {
        heap.push_back(patient);
        heapifyUp(heap.size() - 1);
    }
    
    Patient extractMax() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        Patient maxPatient = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!isEmpty()) {
            heapifyDown(0);
        }
        
        return maxPatient;
    }
    
    const Patient& peekMax() const {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return heap[0];
    }
    
    bool isEmpty() const {
        return heap.empty();
    }
    
    int size() const {
        return heap.size();
    }
    
    // Merge another priority queue into this one
    // This implementation uses heapify-based merging for O(n) complexity
    void merge(PriorityQueue& other) {
        if (other.isEmpty()) return;
        
        // Add all elements from other queue
        for (const auto& patient : other.heap) {
            heap.push_back(patient);
        }
        
        // Build heap from combined elements using bottom-up heapify
        // Start from last non-leaf node and heapify down
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
        
        // Clear the other queue
        other.heap.clear();
    }
    
    // For debugging
    const std::vector<Patient>& getHeap() const {
        return heap;
    }
};

#endif // PRIORITY_QUEUE_H
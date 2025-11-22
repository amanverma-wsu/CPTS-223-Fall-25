// Sort.cpp
#ifndef SORT_CPP
#define SORT_CPP

#include "Sort.h"

// ==================== MERGE SORT IMPLEMENTATION ====================

template<typename T, typename Compare>
void merge(std::vector<T>& data, int left, int mid, int right, Compare comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    std::vector<T> leftArray(n1);
    std::vector<T> rightArray(n2);
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArray[i] = data[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = data[mid + 1 + j];
    }
    
    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (comp(leftArray[i], rightArray[j])) {
            data[k] = leftArray[i];
            i++;
        } else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of leftArray
    while (i < n1) {
        data[k] = leftArray[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of rightArray
    while (j < n2) {
        data[k] = rightArray[j];
        j++;
        k++;
    }
}

template<typename T, typename Compare>
void mergeSortHelper(std::vector<T>& data, int left, int right, Compare comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSortHelper(data, left, mid, comp);
        mergeSortHelper(data, mid + 1, right, comp);
        
        // Merge the sorted halves
        merge(data, left, mid, right, comp);
    }
}

template<typename T, typename Compare>
void mergeSort(std::vector<T>& data, Compare comp) {
    if (data.size() > 1) {
        mergeSortHelper(data, 0, data.size() - 1, comp);
    }
}

// ==================== QUICK SORT IMPLEMENTATION ====================

template<typename T, typename Compare>
int partition(std::vector<T>& data, int left, int right, Compare comp) {
    T pivot = data[right];
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        if (comp(data[j], pivot)) {
            i++;
            std::swap(data[i], data[j]);
        }
    }
    
    std::swap(data[i + 1], data[right]);
    return i + 1;
}

template<typename T, typename Compare>
void quickSortHelper(std::vector<T>& data, int left, int right, Compare comp) {
    if (left < right) {
        int pivotIndex = partition(data, left, right, comp);
        
        quickSortHelper(data, left, pivotIndex - 1, comp);
        quickSortHelper(data, pivotIndex + 1, right, comp);
    }
}

template<typename T, typename Compare>
void quickSort(std::vector<T>& data, Compare comp) {
    if (data.size() > 1) {
        quickSortHelper(data, 0, data.size() - 1, comp);
    }
}

#endif

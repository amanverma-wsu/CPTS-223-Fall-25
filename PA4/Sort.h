// Sort.h
#ifndef SORT_H
#define SORT_H

#include <vector>
#include <functional>

// Merge Sort declarations
template<typename T, typename Compare>
void merge(std::vector<T>& data, int left, int mid, int right, Compare comp);

template<typename T, typename Compare>
void mergeSortHelper(std::vector<T>& data, int left, int right, Compare comp);

template<typename T, typename Compare>
void mergeSort(std::vector<T>& data, Compare comp);

// Quick Sort declarations
template<typename T, typename Compare>
int partition(std::vector<T>& data, int left, int right, Compare comp);

template<typename T, typename Compare>
void quickSortHelper(std::vector<T>& data, int left, int right, Compare comp);

template<typename T, typename Compare>
void quickSort(std::vector<T>& data, Compare comp);

// Include implementation since these are templates
#include "Sort.cpp"

#endif

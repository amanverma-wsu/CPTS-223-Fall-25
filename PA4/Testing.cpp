// Testing.cpp
#include "Testing.h"
#include "Sort.h"
#include "MediaItem.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

void runAllTests() {
    std::cout << "\n=== Running Tests ===" << std::endl;
    
    testMergeSortIntegers();
    testQuickSortIntegers();
    testMergeSortStrings();
    testQuickSortStrings();
    testMergeSortDescending();
    testQuickSortDescending();
    testSortingMediaItems();
    testEdgeCases();
    
    std::cout << "=== All Tests Passed ===" << std::endl << std::endl;
}

void testMergeSortIntegers() {
    std::cout << "Testing Merge Sort with Integers..." << std::endl;
    
    // Test case 1: Normal case - unsorted array
    std::vector<int> data1 = {5, 2, 8, 1, 9, 3};
    std::function<bool(const int&, const int&)> comp1 = [](const int& a, const int& b) { return a < b; };
    mergeSort(data1, comp1);
    assert(data1[0] == 1 && data1[1] == 2 && data1[2] == 3);
    assert(data1[3] == 5 && data1[4] == 8 && data1[5] == 9);
    
    // Test case 2: Edge case - already sorted
    std::vector<int> data2 = {1, 2, 3, 4, 5};
    std::function<bool(const int&, const int&)> comp2 = [](const int& a, const int& b) { return a < b; };
    mergeSort(data2, comp2);
    assert(data2[0] == 1 && data2[4] == 5);
    
    std::cout << "  ✓ Merge Sort Integers passed" << std::endl;
}

void testQuickSortIntegers() {
    std::cout << "Testing Quick Sort with Integers..." << std::endl;
    
    // Test case 1: Normal case - unsorted array
    std::vector<int> data1 = {5, 2, 8, 1, 9, 3};
    std::function<bool(const int&, const int&)> comp1 = [](const int& a, const int& b) { return a < b; };
    quickSort(data1, comp1);
    assert(data1[0] == 1 && data1[1] == 2 && data1[2] == 3);
    assert(data1[3] == 5 && data1[4] == 8 && data1[5] == 9);
    
    // Test case 2: Edge case - reverse sorted
    std::vector<int> data2 = {5, 4, 3, 2, 1};
    std::function<bool(const int&, const int&)> comp2 = [](const int& a, const int& b) { return a < b; };
    quickSort(data2, comp2);
    assert(data2[0] == 1 && data2[4] == 5);
    
    std::cout << "  ✓ Quick Sort Integers passed" << std::endl;
}

void testMergeSortStrings() {
    std::cout << "Testing Merge Sort with Strings..." << std::endl;
    
    // Test case 1: Normal case
    std::vector<std::string> data1 = {"zebra", "apple", "mango", "banana"};
    std::function<bool(const std::string&, const std::string&)> comp1 = 
        [](const std::string& a, const std::string& b) { return a < b; };
    mergeSort(data1, comp1);
    assert(data1[0] == "apple" && data1[1] == "banana");
    assert(data1[2] == "mango" && data1[3] == "zebra");
    
    // Test case 2: Edge case - single element
    std::vector<std::string> data2 = {"single"};
    std::function<bool(const std::string&, const std::string&)> comp2 = 
        [](const std::string& a, const std::string& b) { return a < b; };
    mergeSort(data2, comp2);
    assert(data2[0] == "single");
    
    std::cout << "  ✓ Merge Sort Strings passed" << std::endl;
}

void testQuickSortStrings() {
    std::cout << "Testing Quick Sort with Strings..." << std::endl;
    
    // Test case 1: Normal case
    std::vector<std::string> data1 = {"zebra", "apple", "mango", "banana"};
    std::function<bool(const std::string&, const std::string&)> comp1 = 
        [](const std::string& a, const std::string& b) { return a < b; };
    quickSort(data1, comp1);
    assert(data1[0] == "apple" && data1[1] == "banana");
    assert(data1[2] == "mango" && data1[3] == "zebra");
    
    // Test case 2: Edge case - two elements
    std::vector<std::string> data2 = {"zoo", "ant"};
    std::function<bool(const std::string&, const std::string&)> comp2 = 
        [](const std::string& a, const std::string& b) { return a < b; };
    quickSort(data2, comp2);
    assert(data2[0] == "ant" && data2[1] == "zoo");
    
    std::cout << "  ✓ Quick Sort Strings passed" << std::endl;
}

void testMergeSortDescending() {
    std::cout << "Testing Merge Sort Descending Order..." << std::endl;
    
    // Test case 1: Normal case - descending integers
    std::vector<int> data1 = {5, 2, 8, 1, 9, 3};
    std::function<bool(const int&, const int&)> comp1 = [](const int& a, const int& b) { return a > b; };
    mergeSort(data1, comp1);
    assert(data1[0] == 9 && data1[1] == 8 && data1[2] == 5);
    assert(data1[5] == 1);
    
    // Test case 2: Edge case - already reverse sorted
    std::vector<int> data2 = {9, 8, 7, 6, 5};
    std::function<bool(const int&, const int&)> comp2 = [](const int& a, const int& b) { return a > b; };
    mergeSort(data2, comp2);
    assert(data2[0] == 9 && data2[4] == 5);
    
    std::cout << "  ✓ Merge Sort Descending passed" << std::endl;
}

void testQuickSortDescending() {
    std::cout << "Testing Quick Sort Descending Order..." << std::endl;
    
    // Test case 1: Normal case - descending integers
    std::vector<int> data1 = {5, 2, 8, 1, 9, 3};
    std::function<bool(const int&, const int&)> comp1 = [](const int& a, const int& b) { return a > b; };
    quickSort(data1, comp1);
    assert(data1[0] == 9 && data1[1] == 8 && data1[2] == 5);
    assert(data1[5] == 1);
    
    // Test case 2: Edge case - duplicates
    std::vector<int> data2 = {5, 2, 5, 1, 5};
    std::function<bool(const int&, const int&)> comp2 = [](const int& a, const int& b) { return a > b; };
    quickSort(data2, comp2);
    assert(data2[0] == 5 && data2[4] == 1);
    
    std::cout << "  ✓ Quick Sort Descending passed" << std::endl;
}

void testSortingMediaItems() {
    std::cout << "Testing Sorting with MediaItem Objects..." << std::endl;
    
    // Create test media items
    std::vector<std::string> genres1 = {"Action", "Drama"};
    std::vector<std::string> genres2 = {"Comedy"};
    std::vector<std::string> genres3 = {"Drama"};
    
    MediaItem item1("Inception", 2010, 8.8, 148, genres1);
    MediaItem item2("The Godfather", 1972, 9.2, 175, genres2);
    MediaItem item3("Fight Club", 1999, 8.8, 139, genres3);
    
    // Test case 1: Sort by rating ascending
    std::vector<MediaItem*> items1 = {&item1, &item2, &item3};
    std::function<bool(MediaItem* const&, MediaItem* const&)> comp1 = 
        [](MediaItem* const& a, MediaItem* const& b) { 
            return a->getRating() < b->getRating(); 
        };
    mergeSort(items1, comp1);
    assert(items1[0]->getRating() == 8.8);
    assert(items1[2]->getRating() == 9.2);
    
    // Test case 2: Sort by year descending using quicksort
    std::vector<MediaItem*> items2 = {&item1, &item2, &item3};
    std::function<bool(MediaItem* const&, MediaItem* const&)> comp2 = 
        [](MediaItem* const& a, MediaItem* const& b) { 
            return a->getYear() > b->getYear(); 
        };
    quickSort(items2, comp2);
    assert(items2[0]->getYear() == 2010);
    assert(items2[2]->getYear() == 1972);
    
    std::cout << "  ✓ MediaItem Sorting passed" << std::endl;
}

void testEdgeCases() {
    std::cout << "Testing Edge Cases..." << std::endl;
    
    // Test case 1: Empty vector
    std::vector<int> empty;
    std::function<bool(const int&, const int&)> comp1 = [](const int& a, const int& b) { return a < b; };
    mergeSort(empty, comp1);
    assert(empty.size() == 0);
    
    // Test case 2: Single element
    std::vector<int> single = {42};
    std::function<bool(const int&, const int&)> comp2 = [](const int& a, const int& b) { return a < b; };
    quickSort(single, comp2);
    assert(single[0] == 42 && single.size() == 1);
    
    // Test case 3: All duplicate elements
    std::vector<int> duplicates = {5, 5, 5, 5, 5};
    std::function<bool(const int&, const int&)> comp3 = [](const int& a, const int& b) { return a < b; };
    mergeSort(duplicates, comp3);
    assert(duplicates[0] == 5 && duplicates[4] == 5);
    
    std::cout << "  ✓ Edge Cases passed" << std::endl;
}

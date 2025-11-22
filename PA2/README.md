# Programming Assignment 2: AVL Map Implementation and Performance Analysis

## Overview
This project implements an AVL Tree-based map structure (`avl_map`) in C++ and compares its performance with the Standard Template Library’s `std::map`, which uses a Red-Black Tree. The comparison is performed using real-world ZIP code data for lookup efficiency analysis.

The goal of this assignment is to understand:
- The structure and operations of AVL Trees
- How self-balancing affects performance
- Differences between AVL and Red-Black Tree implementations

---

## Features
- Fully templated `avl_map` class  
- Self-balancing after insertions and deletions  
- Custom iterator class for traversal  
- Comparison with `std::map` using benchmark tests  
- Works with real CSV data (`uszips.csv`)  
- Includes automated test cases for correctness and rotations  

---

## File Structure

```
PA2/
├── avl_map.h              # AVL map template implementation
├── CSVParser.h            # CSV parsing utility
├── USCity.h               # Class to represent ZIP code information
├── generate_test_data.cpp # Utility for generating test CSV files
├── main.cpp               # Main benchmarking program
├── test_avl.cpp           # AVL tree test suite (rotations, insertions, deletions)
├── uszips.csv             # Dataset (ZIP codes, cities, etc.)
└── Makefile               # Build configuration
```

---

## Implementation Details

### AVL Tree
The AVL Tree is a height-balanced Binary Search Tree.  
Each node maintains a balance factor (difference between heights of left and right subtrees).  
Rotations are performed to ensure the height difference never exceeds one.

### Supported Rotations
1. **Left-Left (LL)** – Right rotation  
2. **Right-Right (RR)** – Left rotation  
3. **Left-Right (LR)** – Left rotation on left child, then right rotation on parent  
4. **Right-Left (RL)** – Right rotation on right child, then left rotation on parent  

---

## Complexity Analysis

| Operation | Average Case | Worst Case |
|------------|--------------|-------------|
| Insertion  | O(log n)     | O(log n)    |
| Deletion   | O(log n)     | O(log n)    |
| Search     | O(log n)     | O(log n)    |

AVL Trees guarantee logarithmic height, ensuring consistent performance even for large datasets.

---

## Benchmarking

The program loads the ZIP code dataset into both structures (`avl_map` and `std::map`), then performs 1000 random lookups to measure and compare lookup times.

**Sample Output:**
```
=== Performance Benchmark ===
Testing with 1000 random ZIP codes

AVL Map Results:
  Time: 317 microseconds
  Found: 1000 / 1000

STL Map Results:
  Time: 220 microseconds
  Found: 1000 / 1000

AVL Map / STL Map ratio: 1.44x
STL Map was faster by 44%
```

---

## Build Instructions

### Compilation
```bash
make
```

### Execution
```bash
./avl_test [csv_filename]
```
(Default filename: `uszips.csv`)

### Run Unit Tests
```bash
make test
```

### Clean Build
```bash
make clean
make rebuild
```

---

## Conclusion
This project demonstrates a correct and efficient AVL Tree implementation that maintains self-balancing through rotations. While `std::map` is typically faster due to compiler and memory optimizations, the AVL implementation provides educational insight into the balance and performance of self-adjusting data structures.

# PA4: Movie and TV Show Search and Sort System

---

## Overview

This project implements a command-line program that allows users to **search and sort movies and TV shows** from the IMDB Top 1000 dataset. It supports searching by genre, sorting by multiple fields, and switching between **Merge Sort** and **Quick Sort** algorithms.  

**Key Features**
- Search movies or shows by genre  
- Sort by title, year, rating, or runtime  
- Choose ascending or descending order  
- Switch between Merge Sort and Quick Sort  
- O(1) genre lookup using a hash map  
- Handles movies with multiple genres  

**Dataset:** 999 entries loaded from `imdb_top_1000.csv`

---

## Installation

### Requirements
- C++11 or newer compiler (e.g., `g++`)
- `make` build system
- Dataset file: `imdb_top_1000.csv`

### Build and Run
```bash
# Navigate to project folder
cd PA4

# Compile
make

# Run the program
./pa4

# Clean build files
make clean
```

---

## Usage

When the program starts:
```
==================================================
  Movie and TV Show Search and Sort System
==================================================
Type :help for available commands or :quit to exit
```

### 1. Find by Genre
```
findByGenre <genre> <sort_field> <order>
```

**Parameters**
- `genre` — e.g., Drama, Action, Comedy  
- `sort_field` — `title`, `year`, `rating`, `runtime`  
- `order` — `asc` or `desc`

**Examples**
```bash
findByGenre Drama rating desc
findByGenre Action year asc
findByGenre Comedy title asc
```

**Sample Output**
```
Using Merge Sort...

Found 357 items in genre 'Drama':
Sorted by 'rating' (descending)

Title: The Shawshank Redemption (1994)
  Rating: 9.3 | Runtime: 142 min | Director: Frank Darabont
...
```

---

### 2. Top Rated
```
topRated <genre> <count> <order>
```

**Parameters**
- `genre` — Genre name  
- `count` — Number of results to show  
- `order` — `asc` (lowest first) or `desc` (highest first)

**Examples**
```bash
topRated Drama 10 desc
topRated Action 5 desc
topRated Horror 10 asc
```

---

### 3. Other Commands
```
:help   # List all available commands
:quit   # Exit the program
```

---

## Switching Sorting Algorithms

You can choose between **Merge Sort** and **Quick Sort** in `main.cpp`.

1. Open `main.cpp`
2. Find the constant:
   ```cpp
   const int SORTING_ALGORITHM = 1; // 1 = Merge Sort, 2 = Quick Sort
   ```
3. Change its value and recompile:
   ```bash
   make clean
   make
   ```

When running, the program will display the active algorithm:
```
Using Merge Sort...
```
or
```
Using Quick Sort...
```

---

## Design Overview

### Data Structures
- `vector<MediaItem>` — stores all movies and TV shows  
- `unordered_map<string, vector<MediaItem*>>` — maps each genre to a list of movies (O(1) lookup)

### Sorting Algorithms
| Algorithm   | Time Complexity | Space | Stable | Best Use |
|--------------|----------------|--------|---------|-----------|
| Merge Sort   | O(n log n)     | O(n)   | Yes     | Predictable performance |
| Quick Sort   | O(n log n)*    | O(log n) | No    | Faster average case |

### CSV Parsing
- Splits multiple genres per movie  
- Extracts numeric runtime values (e.g., “142 min”)  
- Converts genre names to lowercase for case-insensitive search  
- Handles missing or malformed data safely  

---

## Testing

The program runs **automated unit tests** at startup to verify sorting correctness and stability:
```
=== Running Tests ===
✓ Merge Sort passed
✓ Quick Sort passed
✓ MediaItem Sorting passed
✓ Edge Cases passed
=== All Tests Passed ===
```

**Manual Testing Examples**
```bash
findByGenre Drama rating desc
topRated Comedy 5 desc
findByGenre Sci-Fi runtime asc
```

---

## File Structure
```
PA4/
├── main.cpp
├── MediaItem.h / MediaItem.cpp
├── MovieDatabase.h / MovieDatabase.cpp
├── Sort.h / Sort.cpp
├── Comparators.h
├── Testing.h / Testing.cpp
├── Makefile
├── README.md
└── imdb_top_1000.csv
```

---

## Troubleshooting

**Compilation errors**
```bash
make clean && make
```

**CSV file not found**
- Ensure `imdb_top_1000.csv` is in the same directory as the executable

**Incorrect sorting results**
- Recompile after changing `SORTING_ALGORITHM`
- Verify with automated tests

---

## Example Run
```
$ ./pa4
==================================================
  Movie and TV Show Search and Sort System
==================================================

Running automated tests...
=== All Tests Passed ===

Loading data from CSV...
Successfully loaded 999 items from imdb_top_1000.csv

PA4> findByGenre Drama rating desc
Using Merge Sort...

Found 357 items in genre 'Drama':
Sorted by 'rating' in descending order

Title: The Shawshank Redemption (1994)
  Rating: 9.3 | Runtime: 142 min | Director: Frank Darabont
...
```

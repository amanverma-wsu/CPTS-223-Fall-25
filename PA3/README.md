# PA3: Amazon Inventory Management System

---

## Overview

This project implements a command-line inventory management system for Amazon products using custom-built data structures. The system supports fast product lookups and category-based searches on a dataset of 10,000+ products.

---

## Design Decisions

### Data Structure Selection: Hash Tables

I chose **Hash Tables** as the primary data structure for this inventory management system for the following reasons:

1. **O(1) Average-Case Lookup Performance**: Hash tables provide constant-time average complexity for find operations, which is critical for quickly locating products by their unique ID.

2. **Efficient Category Indexing**: By using a second hash table that maps categories to lists of products, category-based searches also achieve O(1) lookup time.

3. **Scalability**: Hash tables handle large datasets efficiently (10,000+ products) with proper load factor management and dynamic resizing.

4. **Space-Time Tradeoff**: While hash tables use more memory than some alternatives (like binary search trees), the O(1) lookup time is worth the memory cost for a real-world inventory system where query speed is paramount.

### Implementation Architecture

**Two Hash Tables:**
- `HashTable<string, Product*> productById`: Maps Uniq ID → Product pointer (for `find` command)
- `HashTable<string, vector<Product*>*> productsByCategory`: Maps Category → List of Products (for `listInventory` command)

**Key Features:**
- Template-based implementation for type flexibility
- Separate chaining for collision resolution
- Dynamic resizing when load factor exceeds 0.7
- Proper memory management with destructors

### Product Class Design

The Product class includes fields for `numberOfReviews`, `numberOfAnsweredQuestions`, and `averageReviewRating` for completeness and future extensibility. However, the **current Amazon dataset CSV does not provide these values**, so they default to 0 for all products.

This design decision was made to:
- Support potential future data sources that include review/rating information
- Create a complete product model representing typical e-commerce data
- Demonstrate forward-thinking software design practices

### CSV Data Processing Decisions

1. **Multiple Categories**: Products can belong to multiple categories separated by `|` (pipe character). Each product is indexed under ALL its categories. For example, a product in "Toys & Games|Learning & Education" appears in both category searches.

2. **Missing Categories**: Products with empty category fields are assigned the category "NA" to indicate unavailable category information.

3. **Price Parsing**: The parser attempts to read Selling Price first, then falls back to List Price if Selling Price is unavailable. Handles prices with/without '$' symbols.

4. **Quoted Field Handling**: Custom CSV parser properly handles quoted fields containing commas and escaped quotes (two consecutive quotes).

5. **Whitespace Trimming**: All fields and categories are trimmed of leading/trailing whitespace to ensure consistent matching.

6. **Dynamic Header Parsing**: The CSV parser reads the header row to dynamically find column indices, making it robust to column reordering.

---

## File Structure
```
├── HashTable.h              # Template hash table implementation
├── Product.h                # Product class definition
├── InventorySystem.h        # Main system header
├── InventorySystem.cpp      # CSV loading and command implementation
├── main.cpp                 # REPL interface
├── test.cpp                 # Unit tests with cassert
├── Makefile                 # Build configuration
└── README.md                # This file
```

---

## Build Instructions

### Prerequisites
- g++ compiler with C++11 support
- make utility
- CSV dataset file

### Compilation
```bash
# Clean previous builds
make clean

# Run unit tests
make test

# Build the main program
make

# Run the inventory system
./inventory
```

### Custom CSV File

By default, the program looks for:
```
marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv
```

To use a different CSV file:
```bash
./inventory path/to/your/file.csv
```

---

## Usage

### Available Commands

The program provides a REPL (Read-Eval-Print Loop) interface with the following commands:
```bash
find <inventoryid>       # Find product by Uniq Id
listInventory <category> # List all products in a category
help                     # Show help message
quit                     # Exit the program
```

### Example Session
```bash
$ ./inventory
=== Amazon Inventory Management System ===
Loading inventory from: marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv
Loaded 10002 products from CSV
Inventory loaded successfully!

Available commands:
  find <inventoryid>       - Find product by Uniq Id
  listInventory <category> - List all products in a category
  help                     - Show this help message
  quit                     - Exit the program

> find 4c69b61db1fc16e7013b43fc926e502d

=== Product Found ===
Uniq Id: 4c69b61db1fc16e7013b43fc926e502d
Product Name: DB Longboards CoreFlex Crossbow 41" Bamboo Fiberglass Longboard Complete
Manufacturer: 
Price: $237.68
Number of Reviews: 0
Number of Answered Questions: 0
Average Review Rating: 0
Categories: Sports & Outdoors | Outdoor Recreation | Skates, Skateboards & Scooters | Skateboarding | Standard Skateboards & Longboards | Longboards

> listInventory Toys & Games

=== Products in category: Toys & Games ===
Found 487 product(s)

Uniq Id: 66d49bbed043f5be260fa9f7fbff5957 | Product Name: Electronic Snap Circuits Mini Kits Classpack
Uniq Id: 2c55cae269aebf53838484b0d7dd931a | Product Name: 3Doodler Create Flexy 3D Printing Filament
Uniq Id: 18018b6bc416dab347b1b7db79994afa | Product Name: Guillow Airplane Design Studio
...

> find invalidid123
Inventory/Product not found

> listInventory FakeCategory
Invalid Category

> quit
Goodbye!
```

---

## Testing Approach

All tests use `cassert` for validation as required. The test suite (`test.cpp`) includes comprehensive tests for:

### Hash Table Tests
- Basic insert and find operations (normal and edge cases)
- Multiple insertions and updates
- Remove operations with existing and non-existent keys
- Dynamic resizing with large datasets
- Collision handling with separate chaining

### Product Class Tests
- Category parsing with pipe-separated values
- Handling of empty categories (defaults to "NA")
- Single and multiple category parsing
- Special characters in category names

Each test includes both a normal case and an edge case to ensure robust functionality.

### Running Tests
```bash
make test
```

Expected output:
```
=== Running HashTable Tests ===
Testing HashTable basic operations...
  Basic operations tests passed!
Testing HashTable multiple inserts...
  Multiple inserts tests passed!
Testing HashTable remove...
  Remove tests passed!
Testing HashTable resize...
  Resize tests passed!
Testing HashTable collision handling...
  Collision handling tests passed!

=== Running Product Tests ===
Testing Product class...
  Product class tests passed!
Testing Product category parsing...
  Category parsing tests passed!

=== All tests passed! ===
```

---

## Sample Test Runs

### Test 1: Find Product by ID
```bash
> find 66d49bbed043f5be260fa9f7fbff5957

Expected: Product details for Electronic Snap Circuits Mini Kits Classpack
Result: Successfully displays all product information including price $99.95
```

### Test 2: List Products by Category
```bash
> listInventory Toys & Games

Expected: List of all products in "Toys & Games" category
Result: Found 487 products in category
```

### Test 3: Invalid Product ID
```bash
> find nonexistentid123

Expected: "Inventory/Product not found"
Result: Correctly displays error message
```

### Test 4: Invalid Category
```bash
> listInventory NonExistentCategory

Expected: "Invalid Category"
Result: Correctly displays error message
```

### Test 5: Products with Multiple Categories
```bash
> listInventory Learning & Education

Expected: Shows products that have this as one of their categories
Result: Successfully lists all products including those with multiple categories
```

---

## Time Complexity Analysis

| Operation | Average Case | Worst Case | Notes |
|-----------|-------------|------------|-------|
| `find <id>` | O(1) | O(n) | Average O(1) via hash table; worst case if all keys collide |
| `listInventory <cat>` | O(1) + O(k) | O(n) + O(k) | O(1) category lookup + O(k) to return k products |
| CSV loading | O(n) | O(n) | n = number of products |
| Space complexity | O(n + c) | O(n + c) | n = products, c = unique categories |

**Load Factor Management**: Hash table resizes when load factor exceeds 0.7, maintaining average O(1) performance.


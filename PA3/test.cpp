#include "HashTable.h"
#include "Product.h"
#include <cassert>
#include <iostream>
#include <string>

// Small test suite for HashTable and Product classes
// Written to verify correctness of operations like insert, find, remove, etc.

void testHashTableBasicOperations() {
    std::cout << "Testing HashTable basic operations..." << std::endl;
    
    HashTable<std::string, int> ht(10); // create a hash table of size 10
    
    ht.insert("key1", 100); // insert key-value pair
    int value;
    assert(ht.find("key1", value) == true); // should find key1
    assert(value == 100); // verify correct value stored
    
    // searching for something that doesn't exist
    assert(ht.find("nonexistent", value) == false);
    
    std::cout << "  Basic operations tests passed!" << std::endl;
}

void testHashTableMultipleInserts() {
    std::cout << "Testing HashTable multiple inserts..." << std::endl;
    
    HashTable<std::string, std::string> ht(5); // small table to test chaining
    
    // inserting multiple products
    ht.insert("id1", "product1");
    ht.insert("id2", "product2");
    ht.insert("id3", "product3");
    
    std::string value;
    // checking that all products are inserted correctly
    assert(ht.find("id1", value) && value == "product1");
    assert(ht.find("id2", value) && value == "product2");
    assert(ht.find("id3", value) && value == "product3");
    
    // testing overwrite behavior (same key, new value)
    ht.insert("id1", "updated_product");
    assert(ht.find("id1", value) && value == "updated_product");
    
    std::cout << "  Multiple inserts tests passed!" << std::endl;
}

void testHashTableRemove() {
    std::cout << "Testing HashTable remove..." << std::endl;
    
    HashTable<int, std::string> ht(10); // integer keys this time
    
    ht.insert(1, "item1");
    ht.insert(2, "item2");
    assert(ht.remove(1) == true); // remove existing key
    
    std::string value;
    assert(ht.find(1, value) == false); // removed one should not be found
    assert(ht.find(2, value) == true);  // the other should still be present
    
    // removing non-existent key should return false
    assert(ht.remove(999) == false);
    
    std::cout << "  Remove tests passed!" << std::endl;
}

void testHashTableResize() {
    std::cout << "Testing HashTable resize..." << std::endl;
    
    HashTable<int, int> ht(5); // deliberately small to trigger resize
    
    // insert 20 items to force resize logic
    for (int i = 0; i < 20; i++) {
        ht.insert(i, i * 10);
    }
    
    int value;
    for (int i = 0; i < 20; i++) {
        assert(ht.find(i, value) == true);
        assert(value == i * 10);
    }
    
    // quick check for isEmpty function
    HashTable<int, int> emptyHt(2);
    assert(emptyHt.isEmpty() == true);
    
    std::cout << "  Resize tests passed!" << std::endl;
}

void testHashTableCollisions() {
    std::cout << "Testing HashTable collision handling..." << std::endl;
    
    HashTable<std::string, int> ht(3); // very small table to force collisions
    
    // inserting multiple keys that will collide based on hash
    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);
    ht.insert("d", 4);
    
    int value;
    // all should still be retrievable despite collisions
    assert(ht.find("a", value) && value == 1);
    assert(ht.find("b", value) && value == 2);
    assert(ht.find("c", value) && value == 3);
    assert(ht.find("d", value) && value == 4);
    
    // verifying internal counters
    assert(ht.getSize() == 4);
    assert(ht.isEmpty() == false);
    
    std::cout << "  Collision handling tests passed!" << std::endl;
}

void testProductClass() {
    std::cout << "Testing Product class..." << std::endl;
    
    // creating a sample product with multiple categories
    Product p1("id123", "Test Product", "Test Mfr", 29.99, 150, 20, 4.5, 
               "Electronics|Computers|Laptops");
    
    // verifying fields
    assert(p1.getUniqId() == "id123");
    assert(p1.getProductName() == "Test Product");
    assert(p1.getPrice() == 29.99);
    assert(p1.getCategories().size() == 3);
    assert(p1.getCategories()[0] == "Electronics");
    
    // creating another product with no categories to test fallback
    Product p2("id456", "No Category Product", "Test Mfr", 19.99, 50, 5, 4.0, "");
    
    assert(p2.getCategories().size() == 1);
    assert(p2.getCategories()[0] == "NA");
    
    std::cout << "  Product class tests passed!" << std::endl;
}

void testProductCategoryParsing() {
    std::cout << "Testing Product category parsing..." << std::endl;
    
    // single category case
    Product p1("id1", "Product1", "Mfr", 10.0, 0, 0, 0.0, "Toys");
    assert(p1.getCategories().size() == 1);
    assert(p1.getCategories()[0] == "Toys");
    
    // multiple categories with special chars
    Product p2("id2", "Product2", "Mfr", 10.0, 0, 0, 0.0, "Books & Media|Kids' Books");
    assert(p2.getCategories().size() == 2);
    
    std::cout << "  Category parsing tests passed!" << std::endl;
}

int main() {
    std::cout << "=== Running HashTable Tests ===" << std::endl;
    testHashTableBasicOperations();
    testHashTableMultipleInserts();
    testHashTableRemove();
    testHashTableResize();
    testHashTableCollisions();
    
    std::cout << "\n=== Running Product Tests ===" << std::endl;
    testProductClass();
    testProductCategoryParsing();
    
    std::cout << "\n=== All tests passed! ===" << std::endl;
    
    return 0; // all tests done
}

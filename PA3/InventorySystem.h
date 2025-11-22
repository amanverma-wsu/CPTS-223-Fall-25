#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include "HashTable.h"
#include "Product.h"
#include <vector>
#include <string>

// InventorySystem class
// ----------------------
// This class manages a collection of products.
// It stores products in two hash tables:
// 1. productById - for quick lookup by product ID.
// 2. productsByCategory - for grouping by category.
class InventorySystem {
private:
    // Maps each unique product ID to its Product* object
    HashTable<std::string, Product*> productById;
    
    // Maps each category name to a list of Product pointers
    HashTable<std::string, std::vector<Product*>*> productsByCategory;
    
public:
    // Default constructor (nothing fancy here)
    InventorySystem() {}
    
    // Destructor - cleans up all dynamic memory
    // Deletes all Product objects and all category vectors
    ~InventorySystem() {
        std::vector<Product*> allProducts;
        productById.getAllValues(allProducts);
        for (Product* p : allProducts) {
            delete p;
        }
        
        std::vector<std::vector<Product*>*> allVectors;
        productsByCategory.getAllValues(allVectors);
        for (std::vector<Product*>* vec : allVectors) {
            delete vec;
        }
    }
    
    // Adds a product to the hash tables
    // -> stores by ID and assigns it to one or more categories
    void addProduct(Product* product);
    
    // Finds a product by its unique ID
    // -> returns pointer if found, nullptr otherwise
    Product* findProductById(const std::string& id);
    
    // Lists all products that belong to a given category
    std::vector<Product*> listInventoryByCategory(const std::string& category);
    
    // Loads product data from a CSV file and fills both hash tables
    bool loadFromCSV(const std::string& filename);
};

#endif

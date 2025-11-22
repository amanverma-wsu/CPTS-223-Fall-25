#include "InventorySystem.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Adds a new product to the inventory system
// - Stores it by unique ID
// - Also groups it under one or more categories
void InventorySystem::addProduct(Product* product) {
    productById.insert(product->getUniqId(), product);
    
    const std::vector<std::string>& categories = product->getCategories();
    for (const std::string& category : categories) {
        std::vector<Product*>* categoryProducts = nullptr;
        
        // if category not found yet, make a new vector for it
        if (!productsByCategory.find(category, categoryProducts)) {
            categoryProducts = new std::vector<Product*>();
            productsByCategory.insert(category, categoryProducts);
        }
        
        // push product into its category
        categoryProducts->push_back(product);
    }
}

// Finds a product in the hash table using its unique ID
Product* InventorySystem::findProductById(const std::string& id) {
    Product* product = nullptr;
    if (productById.find(id, product)) {
        return product; // found!
    }
    return nullptr; // not found
}

// Returns a list of products belonging to a given category
std::vector<Product*> InventorySystem::listInventoryByCategory(const std::string& category) {
    std::vector<Product*>* categoryProducts = nullptr;
    if (productsByCategory.find(category, categoryProducts)) {
        return *categoryProducts;
    }
    // return empty list if category doesn’t exist
    return std::vector<Product*>();
}

// Helper function to remove leading/trailing spaces, quotes, etc.
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n\"");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n\"");
    return str.substr(first, (last - first + 1));
}

// Custom CSV parser that handles quoted fields and commas
std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    
    for (size_t i = 0; i < line.length(); i++) {
        char c = line[i];
        
        if (c == '"') {
            // handle escaped quotes ("")
            if (i + 1 < line.length() && line[i + 1] == '"') {
                field += '"';
                i++;
            } else {
                inQuotes = !inQuotes; // toggle inQuotes state
            }
        } else if (c == ',' && !inQuotes) {
            // when not in quotes, comma means new field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    fields.push_back(field); // last field
    return fields;
}

// Safely convert string to double (returns 0.0 if invalid)
// Handles '$' sign and trims spaces
double parseDoubleSafe(const std::string& str) {
    if (str.empty()) return 0.0;
    try {
        std::string cleaned = trim(str);
        if (!cleaned.empty() && cleaned[0] == '$') {
            cleaned = cleaned.substr(1);
        }
        return std::stod(cleaned);
    } catch (...) {
        return 0.0;
    }
}

// Loads product data from a CSV file and populates the inventory
bool InventorySystem::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    std::string line;
    std::getline(file, line); // read header row
    std::vector<std::string> headers = parseCSVLine(line);
    
    // store header indices so we can find data by name
    int idxUniqId = -1, idxProductName = -1, idxBrandName = -1;
    int idxCategory = -1, idxListPrice = -1, idxSellingPrice = -1;
    
    for (size_t i = 0; i < headers.size(); i++) {
        std::string header = trim(headers[i]);
        if (header == "Uniq Id") idxUniqId = i;
        else if (header == "Product Name") idxProductName = i;
        else if (header == "Brand Name") idxBrandName = i;
        else if (header == "Category") idxCategory = i;
        else if (header == "List Price") idxListPrice = i;
        else if (header == "Selling Price") idxSellingPrice = i;
    }
    
    int lineCount = 0;     // total valid lines read
    int skippedCount = 0;  // invalid rows skipped
    
    // read each row of CSV
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::vector<std::string> fields = parseCSVLine(line);
        
        // safely extract all needed columns
        std::string uniqId = (idxUniqId >= 0 && fields.size() > (size_t)idxUniqId) ? trim(fields[idxUniqId]) : "";
        std::string productName = (idxProductName >= 0 && fields.size() > (size_t)idxProductName) ? trim(fields[idxProductName]) : "";
        std::string manufacturer = (idxBrandName >= 0 && fields.size() > (size_t)idxBrandName) ? trim(fields[idxBrandName]) : "";
        std::string category = (idxCategory >= 0 && fields.size() > (size_t)idxCategory) ? trim(fields[idxCategory]) : "";
        
        // skip invalid row if no uniq id
        if (uniqId.empty()) {
            skippedCount++;
            continue;
        }
        
        // read price from either Selling Price or List Price
        double price = 0.0;
        if (idxSellingPrice >= 0 && fields.size() > (size_t)idxSellingPrice) {
            price = parseDoubleSafe(fields[idxSellingPrice]);
        }
        if (price == 0.0 && idxListPrice >= 0 && fields.size() > (size_t)idxListPrice) {
            price = parseDoubleSafe(fields[idxListPrice]);
        }
        
        // dummy placeholders (CSV doesn’t contain these)
        int reviews = 0;
        int questions = 0;
        double rating = 0.0;
        
        // make a new Product object
        Product* product = new Product(uniqId, productName, manufacturer,
                                       price, reviews, questions, rating, category);
        addProduct(product); // add to hash tables
        lineCount++;
    }
    
    file.close();
    std::cout << "Loaded " << lineCount << " products from CSV";
    if (skippedCount > 0) {
        std::cout << " (skipped " << skippedCount << " invalid rows)";
    }
    std::cout << std::endl;
    return true;
}

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include <iostream>

// Product class
// -------------
// Represents a single product from the CSV file.
// Stores details like name, price, brand, and categories.
// Also provides functions to access, modify, and print product info.
class Product {
private:
    // Basic product details
    std::string uniqId;                       // unique product ID
    std::string productName;                  // name of the product
    std::string manufacturer;                 // brand or manufacturer
    double price;                             // selling or list price
    int numberOfReviews;                      // total reviews count
    int numberOfAnsweredQuestions;            // how many questions answered
    double averageReviewRating;               // average star rating
    std::string amazonCategoryAndSubCategory; // raw category string from CSV
    std::vector<std::string> categories;      // parsed category list
    
    // Helper function to remove spaces/tabs/newlines from category text
    std::string trimCategory(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
    }

public:
    // Default constructor: initializes everything to zero/empty
    Product() : price(0.0), numberOfReviews(0), 
                numberOfAnsweredQuestions(0), averageReviewRating(0.0) {}
    
    // Parameterized constructor: builds a product with all details
    Product(const std::string& id, const std::string& name,
            const std::string& mfr, double p, int reviews,
            int questions, double rating, const std::string& cat)
        : uniqId(id), productName(name), manufacturer(mfr),
          price(p), numberOfReviews(reviews),
          numberOfAnsweredQuestions(questions),
          averageReviewRating(rating),
          amazonCategoryAndSubCategory(cat) {
        parseCategories(); // split categories right away
    }
    
    // Parses category string like "Electronics|Laptops"
    // and stores them into a vector
    void parseCategories() {
        categories.clear();
        if (amazonCategoryAndSubCategory.empty()) {
            categories.push_back("NA"); // no category, mark as "NA"
            return;
        }
        
        std::string category;
        for (char c : amazonCategoryAndSubCategory) {
            if (c == '|') {
                if (!category.empty()) {
                    std::string trimmed = trimCategory(category);
                    if (!trimmed.empty()) {
                        categories.push_back(trimmed);
                    }
                    category.clear();
                }
            } else {
                category += c;
            }
        }
        // add the last category if any
        if (!category.empty()) {
            std::string trimmed = trimCategory(category);
            if (!trimmed.empty()) {
                categories.push_back(trimmed);
            }
        }
        
        // fallback in case all were empty
        if (categories.empty()) {
            categories.push_back("NA");
        }
    }
    
    // ======= Getters =======
    std::string getUniqId() const { return uniqId; }
    std::string getProductName() const { return productName; }
    std::string getManufacturer() const { return manufacturer; }
    double getPrice() const { return price; }
    int getNumberOfReviews() const { return numberOfReviews; }
    int getNumberOfAnsweredQuestions() const { return numberOfAnsweredQuestions; }
    double getAverageReviewRating() const { return averageReviewRating; }
    std::string getAmazonCategoryAndSubCategory() const { return amazonCategoryAndSubCategory; }
    const std::vector<std::string>& getCategories() const { return categories; }
    
    // ======= Setters =======
    void setUniqId(const std::string& id) { uniqId = id; }
    void setProductName(const std::string& name) { productName = name; }
    void setManufacturer(const std::string& mfr) { manufacturer = mfr; }
    void setPrice(double p) { price = p; }
    void setNumberOfReviews(int reviews) { numberOfReviews = reviews; }
    void setNumberOfAnsweredQuestions(int questions) { numberOfAnsweredQuestions = questions; }
    void setAverageReviewRating(double rating) { averageReviewRating = rating; }
    
    // Updates the raw category string and re-parses it into vector
    void setAmazonCategoryAndSubCategory(const std::string& cat) {
        amazonCategoryAndSubCategory = cat;
        parseCategories();
    }
    
    // Displays all product details on console in a readable format
    void display() const {
        std::cout << "Uniq Id: " << uniqId << std::endl;
        std::cout << "Product Name: " << productName << std::endl;
        std::cout << "Manufacturer: " << manufacturer << std::endl;
        std::cout << "Price: $" << price << std::endl;
        std::cout << "Number of Reviews: " << numberOfReviews << std::endl;
        std::cout << "Number of Answered Questions: " << numberOfAnsweredQuestions << std::endl;
        std::cout << "Average Review Rating: " << averageReviewRating << std::endl;
        std::cout << "Categories: " << amazonCategoryAndSubCategory << std::endl;
    }
};

#endif

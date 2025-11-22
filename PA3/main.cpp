#include "InventorySystem.h"
#include <iostream>
#include <sstream>

void printHelp() {
    std::cout << "\nAvailable commands:" << std::endl;
    std::cout << "  find <inventoryid>       - Find product by Uniq Id" << std::endl;
    std::cout << "  listInventory <category> - List all products in a category" << std::endl;
    std::cout << "  help                     - Show this help message" << std::endl;
    std::cout << "  quit                     - Exit the program" << std::endl;
    std::cout << std::endl;
}

void processCommand(InventorySystem& system, const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    
    if (cmd == "find") {
        std::string inventoryId;
        iss >> inventoryId;
        
        if (inventoryId.empty()) {
            std::cout << "Error: Please provide an inventory ID" << std::endl;
            return;
        }
        
        Product* product = system.findProductById(inventoryId);
        if (product != nullptr) {
            std::cout << "\n=== Product Found ===" << std::endl;
            product->display();
            std::cout << std::endl;
        } else {
            std::cout << "Inventory/Product not found" << std::endl;
        }
    }
    else if (cmd == "listInventory") {
        std::string category;
        std::getline(iss >> std::ws, category);
        
        if (category.empty()) {
            std::cout << "Error: Please provide a category" << std::endl;
            return;
        }
        
        std::vector<Product*> products = system.listInventoryByCategory(category);
        
        if (products.empty()) {
            std::cout << "Invalid Category" << std::endl;
        } else {
            std::cout << "\n=== Products in category: " << category << " ===" << std::endl;
            std::cout << "Found " << products.size() << " product(s)\n" << std::endl;
            
            for (Product* p : products) {
                std::cout << "Uniq Id: " << p->getUniqId() 
                         << " | Product Name: " << p->getProductName() << std::endl;
            }
            std::cout << std::endl;
        }
    }
    else if (cmd == "help") {
        printHelp();
    }
    else if (cmd == "quit" || cmd == "exit") {
        std::cout << "Goodbye!" << std::endl;
        exit(0);
    }
    else {
        std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string csvFile = "marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv";
    
    if (argc > 1) {
        csvFile = argv[1];
    }
    
    std::cout << "=== Amazon Inventory Management System ===" << std::endl;
    std::cout << "Loading inventory from: " << csvFile << std::endl;
    
    InventorySystem system;
    
    if (!system.loadFromCSV(csvFile)) {
        std::cerr << "Failed to load inventory. Exiting." << std::endl;
        return 1;
    }
    
    std::cout << "Inventory loaded successfully!" << std::endl;
    printHelp();
    
    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        
        if (command.empty()) {
            continue;
        }
        
        processCommand(system, command);
    }
    
    return 0;
}

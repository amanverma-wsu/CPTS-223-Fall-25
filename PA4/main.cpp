// main.cpp
/**
 * Programming Assignment 4: Movie and TV Show Search and Sort
 * CPTS 223 Advanced Data Structures
 *
 * This file provides the REPL (Read-Eval-Print Loop) interface.
 * Updated implementation with full functionality for searching and sorting
 * movies and TV shows from the IMDB dataset.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "MovieDatabase.h"
#include "Sort.h"
#include "Comparators.h"
#include "Testing.h"

using namespace std;

// Global flag to select sorting algorithm
// 1 = Merge Sort, 2 = Quick Sort
const int SORTING_ALGORITHM = 2;

// Global database instance
MovieDatabase database;

/**
 * Display the help message showing available commands
 */
void displayHelp()
{
    cout << "\n=== Available Commands ===" << endl;
    cout << "findByGenre <genre> <sort_field> <order>" << endl;
    cout << "  - Finds all movies/TV shows in the specified genre" << endl;
    cout << "  - sort_field: title, year, rating, or runtime" << endl;
    cout << "  - order: asc (ascending) or desc (descending)" << endl;
    cout << "  - Example: findByGenre Action rating desc" << endl;
    cout << endl;
    cout << "topRated <genre> <count> <order>" << endl;
    cout << "  - Shows the top N movies/TV shows in a genre sorted by rating" << endl;
    cout << "  - count: number of items to display" << endl;
    cout << "  - order: asc or desc" << endl;
    cout << "  - Example: topRated Drama 10 desc" << endl;
    cout << endl;
    cout << ":help - Display this help message" << endl;
    cout << ":quit - Exit the application" << endl;
    cout << "==========================\n"
         << endl;
}

/**
 * Parse and execute the findByGenre command
 * Format: findByGenre <genre> <sort_field> <order>
 */
void executeFindByGenre(const vector<string> &tokens)
{
    if (tokens.size() != 4)
    {
        cout << "Error: Incorrect command pattern" << endl;
        cout << "Usage: findByGenre <genre> <sort_field> <order>" << endl;
        cout << "Example: findByGenre Action rating desc" << endl;
        return;
    }

    string genre = tokens[1];
    string sortField = tokens[2];
    string order = tokens[3];

    // Validate sort_field
    if (sortField != "title" && sortField != "year" &&
        sortField != "rating" && sortField != "runtime")
    {
        cout << "Error: Invalid sort field. Must be: title, year, rating, or runtime" << endl;
        return;
    }

    // Validate order
    if (order != "asc" && order != "desc")
    {
        cout << "Error: Invalid order. Must be: asc or desc" << endl;
        return;
    }

    // Find items by genre
    vector<MediaItem*> results = database.findByGenre(genre);
    
    if (results.empty())
    {
        cout << "Invalid Genre" << endl;
        return;
    }

    // Get appropriate comparator
    auto comp = Comparators::getComparator(sortField, order);
    
    // Sort using selected algorithm
    if (SORTING_ALGORITHM == 1) {
        mergeSort(results, comp);
        cout << "Using Merge Sort..." << endl;
    } else {
        quickSort(results, comp);
        cout << "Using Quick Sort..." << endl;
    }
    
    // Display results
    cout << "\nFound " << results.size() << " items in genre '" << genre << "':" << endl;
    cout << "Sorted by '" << sortField << "' in " << order << "ending order\n" << endl;
    
    for (const auto* item : results) {
        cout << "Title: " << item->getTitle() << " (" << item->getYear() << ")" << endl;
        cout << "  Rating: " << item->getRating() 
             << " | Runtime: " << item->getRuntime() << " min" << endl;
        cout << "  Director: " << item->getDirector() << endl;
        cout << endl;
    }
}

/**
 * Parse and execute the topRated command
 * Format: topRated <genre> <count> <order>
 */
void executeTopRated(const vector<string> &tokens)
{
    if (tokens.size() != 4)
    {
        cout << "Error: Incorrect command pattern" << endl;
        cout << "Usage: topRated <genre> <count> <order>" << endl;
        cout << "Example: topRated Drama 10 desc" << endl;
        return;
    }

    string genre = tokens[1];
    string countStr = tokens[2];
    string order = tokens[3];

    // Validate count is a number
    int count;
    try
    {
        count = stoi(countStr);
        if (count <= 0)
        {
            cout << "Error: Count must be a positive number" << endl;
            return;
        }
    }
    catch (const exception &e)
    {
        cout << "Error: Count must be a valid number" << endl;
        return;
    }

    // Validate order
    if (order != "asc" && order != "desc")
    {
        cout << "Error: Invalid order. Must be: asc or desc" << endl;
        return;
    }

    // Find items by genre
    vector<MediaItem*> results = database.findByGenre(genre);
    
    if (results.empty())
    {
        cout << "Invalid Genre" << endl;
        return;
    }
    
    // Sort by rating
    auto comp = Comparators::getComparator("rating", order);
    
    if (SORTING_ALGORITHM == 1) {
        mergeSort(results, comp);
        cout << "Using Merge Sort..." << endl;
    } else {
        quickSort(results, comp);
        cout << "Using Quick Sort..." << endl;
    }
    
    // Limit to requested count
    int displayCount = min(count, (int)results.size());
    
    // Display results
    cout << "\nTop " << displayCount << " rated items in genre '" << genre << "':" << endl;
    cout << "Displaying in " << order << "ending order\n" << endl;
    
    for (int i = 0; i < displayCount; ++i) {
        cout << (i + 1) << ". " << results[i]->getTitle() 
             << " (" << results[i]->getYear() << ")" << endl;
        cout << "   Rating: " << results[i]->getRating() 
             << " | Runtime: " << results[i]->getRuntime() << " min" << endl;
        cout << "   Director: " << results[i]->getDirector() << endl;
        cout << endl;
    }
}

/**
 * Tokenize the input string by whitespace
 */
vector<string> tokenize(const string &input)
{
    vector<string> tokens;
    istringstream iss(input);
    string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

/**
 * Process a single command
 */
void processCommand(const string &input)
{
    // Handle empty input
    if (input.empty())
    {
        return;
    }

    // Tokenize the input
    vector<string> tokens = tokenize(input);

    if (tokens.empty())
    {
        return;
    }

    string command = tokens[0];

    // Handle built-in commands
    if (command == "help")
    {
        displayHelp();
    }
    else if (command == "findByGenre")
    {
        executeFindByGenre(tokens);
    }
    else if (command == "topRated")
    {
        executeTopRated(tokens);
    }
    else
    {
        cout << "Error: Unknown command '" << command << "'" << endl;
        cout << "Type :help for a list of available commands" << endl;
    }
}

/**
 * Main REPL loop
 */
int main()
{
    cout << "==================================================" << endl;
    cout << "  Movie and TV Show Search and Sort System" << endl;
    cout << "  CPTS 223 - Programming Assignment 4" << endl;
    cout << "==================================================" << endl;
    cout << "Type :help for available commands or :quit to exit" << endl;
    cout << endl;

    // Run tests first
    cout << "Running automated tests..." << endl;
    runAllTests();

    // Load data from CSV file
    cout << "Loading data from CSV..." << endl;
    if (!database.loadFromCSV("imdb_top_1000.csv")) {
        cout << "Error: Failed to load data. Please ensure imdb_top_1000.csv is in the current directory." << endl;
        cout << "Exiting..." << endl;
        return 1;
    }
    cout << endl;

    string input;

    // Main REPL loop
    while (true)
    {
        cout << "PA4> ";
        getline(cin, input);

        // Check for quit command
        if (input == "quit")
        {
            cout << "Goodbye!" << endl;
            break;
        }

        // Process the command
        processCommand(input);
        cout << endl;
    }

    return 0;
}

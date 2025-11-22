#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include <vector>

// CSVParser: A simple utility class to handle parsing of CSV (comma-separated values) lines
// This class provides static functions for splitting CSV lines, trimming whitespace,
// and converting string values into numbers (int or double).
class CSVParser {
public:
    // Parses a single line from a CSV file into individual fields (columns)
    // Handles commas inside quotes correctly (like "New York, NY")
    static std::vector<std::string> parseLine(const std::string& line) {
        std::vector<std::string> result;   // Vector to store all fields
        std::string field;                 // Current field being read
        bool inQuotes = false;             // Flag to track if we are inside quotes

        // Loop through every character in the line
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
            if (c == '"') {
                // Toggle inQuotes flag when encountering a quote
                inQuotes = !inQuotes;
            } 
            else if (c == ',' && !inQuotes) {
                // When we hit a comma (not inside quotes), push the current field
                result.push_back(trim(field));
                field.clear();
            } 
            else {
                // Add normal character to current field
                field += c;
            }
        }

        // Add the last field after finishing the loop
        result.push_back(trim(field));
        return result;
    }

    // Removes leading and trailing whitespace, tabs, or newlines from a string
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";  // If string is empty or all spaces
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));  // Return cleaned substring
    }

    // Converts a string to an integer safely
    // Returns 0 if the string is empty or invalid
    static int toInt(const std::string& str) {
        if (str.empty()) return 0;
        try {
            return std::stoi(str);  // Convert using built-in stoi
        } catch (...) {
            // If stoi fails (e.g., invalid format), return 0
            return 0;
        }
    }

    // Converts a string to a double safely
    // Returns 0.0 if the string is empty or invalid
    static double toDouble(const std::string& str) {
        if (str.empty()) return 0.0;
        try {
            return std::stod(str);  // Convert using built-in stod
        } catch (...) {
            // Return 0.0 if conversion fails
            return 0.0;
        }
    }
};

#endif

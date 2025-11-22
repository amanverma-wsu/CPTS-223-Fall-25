// MovieDatabase.cpp
#include "MovieDatabase.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::string MovieDatabase::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\"");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r\"");
    return str.substr(first, last - first + 1);
}

std::vector<std::string> MovieDatabase::parseGenres(const std::string& genreStr) {
    std::vector<std::string> genres;
    std::stringstream ss(genreStr);
    std::string genre;
    
    while (std::getline(ss, genre, ',')) {
        genre = trim(genre);
        if (!genre.empty()) {
            genres.push_back(genre);
        }
    }
    
    if (genres.empty()) {
        genres.push_back("Unknown");
    }
    
    return genres;
}

int MovieDatabase::parseRuntime(const std::string& runtimeStr) {
    std::string cleaned = trim(runtimeStr);
    
    // Remove " min" suffix
    size_t pos = cleaned.find(" min");
    if (pos != std::string::npos) {
        cleaned = cleaned.substr(0, pos);
        cleaned = trim(cleaned);
    }
    
    // Try to parse the number
    try {
        return std::stoi(cleaned);
    } catch (...) {
        return 0;
    }
}

std::vector<std::string> MovieDatabase::parseCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::string current;
    bool inQuotes = false;
    
    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];
        
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            // Comma is the delimiter
            result.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }
    
    // Add last field
    result.push_back(current);
    
    return result;
}

bool MovieDatabase::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int lineNum = 0;
    int loadedCount = 0;
    bool isFirstLine = true;
    
    while (std::getline(file, line)) {
        lineNum++;
        
        // Skip header
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        // Skip empty lines
        if (line.empty() || trim(line).empty()) {
            continue;
        }
        
        try {
            // Parse the comma-separated line
            std::vector<std::string> fields = parseCSVLine(line);
            
            // CSV Format:
            // 0: Poster_Link
            // 1: Series_Title
            // 2: Released_Year
            // 3: Certificate
            // 4: Runtime
            // 5: Genre
            // 6: IMDB_Rating
            // 7: Overview
            // 8: Meta_score
            // 9: Director
            // 10: Star1
            // 11: Star2
            // 12: Star3
            // 13: Star4
            // 14: No_of_Votes
            // 15: Gross
            
            if (fields.size() < 7) {
                continue;
            }
            
            // Extract and clean data
            std::string title = trim(fields[1]);
            if (title.empty()) continue;
            
            // Parse year
            std::string yearStr = trim(fields[2]);
            int year = 0;
            try {
                year = std::stoi(yearStr);
            } catch (...) {
                continue; // Skip if year is invalid
            }
            
            std::string certificate = trim(fields[3]);
            
            // Parse runtime
            int runtime = parseRuntime(fields[4]);
            
            // Parse genres (may contain multiple comma-separated values)
            std::vector<std::string> genres = parseGenres(fields[5]);
            
            // Parse rating
            std::string ratingStr = trim(fields[6]);
            double rating = 0.0;
            try {
                rating = std::stod(ratingStr);
            } catch (...) {
                continue; // Skip if rating is invalid
            }
            
            // Optional fields
            std::string overview = fields.size() > 7 ? trim(fields[7]) : "";
            std::string director = fields.size() > 9 ? trim(fields[9]) : "";
            
            // Create and add the item
            MediaItem item(title, year, rating, runtime, genres, certificate, overview, director);
            allItems.push_back(item);
            loadedCount++;
            
        } catch (const std::exception& e) {
            // Skip problematic lines silently
            continue;
        }
    }
    
    file.close();
    
    if (loadedCount == 0) {
        std::cerr << "Error: No data loaded from CSV file." << std::endl;
        return false;
    }
    
    // Build genre index for fast lookup
    buildGenreIndex();
    
    std::cout << "Successfully loaded " << loadedCount << " items from " << filename << std::endl;
    return true;
}

void MovieDatabase::buildGenreIndex() {
    genreIndex.clear();
    
    for (auto& item : allItems) {
        for (const auto& genre : item.getGenres()) {
            std::string genreLower = genre;
            std::transform(genreLower.begin(), genreLower.end(), genreLower.begin(), ::tolower);
            genreIndex[genreLower].push_back(&item);
        }
    }
}

std::vector<MediaItem*> MovieDatabase::findByGenre(const std::string& genre) {
    std::string genreLower = genre;
    std::transform(genreLower.begin(), genreLower.end(), genreLower.begin(), ::tolower);
    
    auto it = genreIndex.find(genreLower);
    if (it != genreIndex.end()) {
        return it->second;
    }
    
    return std::vector<MediaItem*>();
}

std::vector<std::string> MovieDatabase::getAllGenres() const {
    std::vector<std::string> genres;
    for (const auto& pair : genreIndex) {
        genres.push_back(pair.first);
    }
    return genres;
}

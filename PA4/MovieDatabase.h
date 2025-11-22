// MovieDatabase.h
#ifndef MOVIE_DATABASE_H
#define MOVIE_DATABASE_H

#include "MediaItem.h"
#include <vector>
#include <unordered_map>
#include <string>

class MovieDatabase {
private:
    std::vector<MediaItem> allItems;
    std::unordered_map<std::string, std::vector<MediaItem*>> genreIndex;
    
    // Helper methods for CSV parsing
    std::vector<std::string> parseCSVLine(const std::string& line);
    std::vector<std::string> parseGenres(const std::string& genreStr);
    int parseRuntime(const std::string& runtimeStr);
    std::string trim(const std::string& str);
    void buildGenreIndex();

public:
    // Load data from CSV file
    bool loadFromCSV(const std::string& filename);
    
    // Find items by genre
    std::vector<MediaItem*> findByGenre(const std::string& genre);
    
    // Get all available genres
    std::vector<std::string> getAllGenres() const;
    
    // Get total number of items
    size_t getItemCount() const { return allItems.size(); }
};

#endif

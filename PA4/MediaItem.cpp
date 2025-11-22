// MediaItem.cpp
#include "MediaItem.h"
#include <iostream>
#include <algorithm>

MediaItem::MediaItem(const std::string& title, int year, double rating, 
                     int runtime, const std::vector<std::string>& genres,
                     const std::string& certificate,
                     const std::string& overview,
                     const std::string& director)
    : title(title), year(year), rating(rating), runtime(runtime), 
      genres(genres), certificate(certificate), overview(overview),
      director(director) {}

bool MediaItem::hasGenre(const std::string& genre) const {
    for (const auto& g : genres) {
        // Case-insensitive comparison
        std::string genreLower = g;
        std::string searchLower = genre;
        
        std::transform(genreLower.begin(), genreLower.end(), genreLower.begin(), ::tolower);
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
        
        if (genreLower == searchLower) {
            return true;
        }
    }
    return false;
}

void MediaItem::display() const {
    std::cout << "Title: " << title << " (" << year << ")" << std::endl;
    std::cout << "Rating: " << rating << " | Runtime: " << runtime << " min" << std::endl;
    std::cout << "Genres: ";
    for (size_t i = 0; i < genres.size(); ++i) {
        std::cout << genres[i];
        if (i < genres.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Director: " << director << std::endl;
    std::cout << "---" << std::endl;
}

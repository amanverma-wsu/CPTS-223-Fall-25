// MediaItem.h
#ifndef MEDIA_ITEM_H
#define MEDIA_ITEM_H

#include <string>
#include <vector>

class MediaItem {
private:
    std::string title;
    int year;
    double rating;
    int runtime; // in minutes
    std::vector<std::string> genres;
    std::string certificate;
    std::string overview;
    std::string director;

public:
    // Constructor
    MediaItem(const std::string& title, int year, double rating, 
              int runtime, const std::vector<std::string>& genres,
              const std::string& certificate = "NA",
              const std::string& overview = "",
              const std::string& director = "");
    
    // Getters
    std::string getTitle() const { return title; }
    int getYear() const { return year; }
    double getRating() const { return rating; }
    int getRuntime() const { return runtime; }
    const std::vector<std::string>& getGenres() const { return genres; }
    std::string getCertificate() const { return certificate; }
    std::string getOverview() const { return overview; }
    std::string getDirector() const { return director; }
    
    // Check if this item belongs to a specific genre
    bool hasGenre(const std::string& genre) const;
    
    // Display information
    void display() const;
};

#endif

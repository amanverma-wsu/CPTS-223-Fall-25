// Comparators.h
#ifndef COMPARATORS_H
#define COMPARATORS_H

#include "MediaItem.h"
#include <functional>
#include <string>

class Comparators {
public:
    // Get comparator based on field and order
    // Returns a lambda function that compares MediaItem pointers
    static auto getComparator(const std::string& field, const std::string& order) 
        -> std::function<bool(MediaItem* const&, MediaItem* const&)> {
        
        if (field == "title") {
            if (order == "asc") {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getTitle() < b->getTitle(); 
                };
            } else {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getTitle() > b->getTitle(); 
                };
            }
        }
        else if (field == "year") {
            if (order == "asc") {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getYear() < b->getYear(); 
                };
            } else {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getYear() > b->getYear(); 
                };
            }
        }
        else if (field == "rating") {
            if (order == "asc") {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getRating() < b->getRating(); 
                };
            } else {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getRating() > b->getRating(); 
                };
            }
        }
        else if (field == "runtime") {
            if (order == "asc") {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getRuntime() < b->getRuntime(); 
                };
            } else {
                return [](MediaItem* const& a, MediaItem* const& b) { 
                    return a->getRuntime() > b->getRuntime(); 
                };
            }
        }
        
        // Default comparator (should never be reached)
        return [](MediaItem* const&, MediaItem* const&) { return false; };
    }
};

#endif

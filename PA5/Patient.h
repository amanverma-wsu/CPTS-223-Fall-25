#ifndef PATIENT_H
#define PATIENT_H

#include <string>

struct Patient {
    std::string name;
    int severity;
    std::string originalCity;
    
    Patient() : name(""), severity(0), originalCity("") {}
    
    Patient(const std::string& n, int s, const std::string& city)
        : name(n), severity(s), originalCity(city) {}
    
    // For max heap: higher severity = higher priority
    bool operator<(const Patient& other) const {
        return severity < other.severity;
    }
    
    bool operator>(const Patient& other) const {
        return severity > other.severity;
    }
};

#endif // PATIENT_H
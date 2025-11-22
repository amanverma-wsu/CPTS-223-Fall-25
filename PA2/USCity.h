#ifndef USCITY_H
#define USCITY_H

#include <string>
#include <iostream>

// The USCity class stores information about a single U.S. city.
// Each object represents one record from the ZIP code CSV file.
class USCity {
private:
    // Basic identifying information
    std::string city;         // City name (e.g., "Seattle")
    std::string state_id;     // Two-letter state abbreviation (e.g., "WA")
    std::string state_name;   // Full state name (e.g., "Washington")
    std::string county_name;  // County name (e.g., "Whitman County")
    std::string timezone;     // Timezone string (e.g., "America/Los_Angeles")

    // Geographic and demographic data
    double lat;               // Latitude coordinate
    double lng;               // Longitude coordinate
    int population;           // Population count

public:
    // Default constructor: initializes numeric fields to 0
    USCity() : lat(0.0), lng(0.0), population(0) {}

    // Parameterized constructor: initializes all member variables
    USCity(const std::string& city, const std::string& state_id,
           const std::string& state_name, const std::string& county,
           const std::string& tz, double latitude, double longitude, int pop)
        : city(city), state_id(state_id), state_name(state_name),
          county_name(county), timezone(tz), lat(latitude),
          lng(longitude), population(pop) {}

    // Getter functions – used to access private member values
    std::string getCity() const { return city; }
    std::string getStateId() const { return state_id; }
    std::string getStateName() const { return state_name; }
    std::string getCountyName() const { return county_name; }
    std::string getTimezone() const { return timezone; }
    double getLatitude() const { return lat; }
    double getLongitude() const { return lng; }
    int getPopulation() const { return population; }

    // Setter functions – used to modify city data
    void setCity(const std::string& c) { city = c; }
    void setStateId(const std::string& s) { state_id = s; }
    void setStateName(const std::string& s) { state_name = s; }
    void setCountyName(const std::string& c) { county_name = c; }
    void setTimezone(const std::string& tz) { timezone = tz; }
    void setLatitude(double l) { lat = l; }
    void setLongitude(double l) { lng = l; }
    void setPopulation(int p) { population = p; }

    // Display function – prints all city data in one formatted line
    void display() const {
        std::cout << "City: " << city << ", " << state_id << " " << state_name
                  << " | County: " << county_name
                  << " | Timezone: " << timezone
                  << " | Lat: " << lat << ", Lng: " << lng
                  << " | Population: " << population << std::endl;
    }
};

#endif

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

// This program generates a small CSV file (test_zips.csv)
// with random city, state, latitude, longitude, timezone, and population data.
// It helps test the AVL Map project without needing the full uszips.csv dataset.
int main() {
    // Create an output file stream to write CSV data
    ofstream file("test_zips.csv");

    // Check if file was successfully opened/created
    if (!file.is_open()) {
        cerr << "Error: Could not create test_zips.csv" << endl;
        return 1;
    }

    // Write CSV header (column names)
    file << "zip,city,state_id,state_name,county_name,lat,lng,timezone,population\n";

    // Random number generator setup
    random_device rd;          // Provides a seed for randomness
    mt19937 gen(rd());         // Mersenne Twister engine for random number generation
    uniform_int_distribution<> pop_dist(1000, 100000);     // Random population range
    uniform_real_distribution<> lat_dist(25.0, 49.0);      // Latitude between 25°–49°
    uniform_real_distribution<> lng_dist(-125.0, -65.0);   // Longitude between -125°–-65°

    // Sample data arrays for generating fake but realistic city/state info
    string cities[] = {"Springfield", "Franklin", "Clinton", "Madison", "Washington",
                       "Georgetown", "Arlington", "Salem", "Fairview", "Riverside"};
    string states[] = {"WA", "OR", "CA", "TX", "NY", "FL", "IL", "PA", "OH", "GA"};
    string state_names[] = {"Washington", "Oregon", "California", "Texas", "New York",
                           "Florida", "Illinois", "Pennsylvania", "Ohio", "Georgia"};
    string counties[] = {"King County", "Pierce County", "Spokane County", "Clark County",
                        "Snohomish County", "Thurston County", "Kitsap County"};
    string timezones[] = {"America/Los_Angeles", "America/New_York", "America/Chicago",
                         "America/Denver"};

    // Calculate the size of each array for indexing
    int num_cities = sizeof(cities) / sizeof(cities[0]);
    int num_states = sizeof(states) / sizeof(states[0]);
    int num_counties = sizeof(counties) / sizeof(counties[0]);
    int num_timezones = sizeof(timezones) / sizeof(timezones[0]);

    cout << "Generating test_zips.csv with 100 entries..." << endl;

    // Generate 100 fake ZIP code entries
    for (int i = 0; i < 100; i++) {
        int zip = 10000 + i * 100;              // Incremental ZIP codes (10000, 10100, ...)
        string city = cities[i % num_cities];   // Cycle through city names
        int state_idx = i % num_states;         // Select state index
        string state = states[state_idx];
        string state_name = state_names[state_idx];
        string county = counties[i % num_counties];
        double lat = lat_dist(gen);             // Random latitude
        double lng = lng_dist(gen);             // Random longitude
        string timezone = timezones[i % num_timezones];
        int population = pop_dist(gen);         // Random population

        // Write one line of CSV data
        file << zip << ","
             << city << ","
             << state << ","
             << state_name << ","
             << county << ","
             << fixed << setprecision(4) << lat << ","    // 4 decimal places
             << fixed << setprecision(4) << lng << ","
             << timezone << ","
             << population << "\n";
    }

    // Close file after writing all records
    file.close();
    cout << "Successfully created test_zips.csv" << endl;
    cout << "You can now test with: ./avl_test test_zips.csv" << endl;

    return 0;
}

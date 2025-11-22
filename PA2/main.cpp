#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "avl_map.h"
#include "USCity.h"
#include "CSVParser.h"

using namespace std;

/*
 * Function: loadZipCodeData
 * --------------------------
 * Loads ZIP code data from a CSV file into both:
 * - a custom avl_map<int, USCity>
 * - a standard STL map<int, USCity>
 * It also stores all ZIP codes into a std::list for later random selection.
 */
bool loadZipCodeData(const string& filename, avl_map<int, USCity>& avl_cities,
                     map<int, USCity>& std_cities, list<int>& zipCodes) {

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header line
    int count = 0;

    // Read file line by line
    while (getline(file, line)) {
        if (line.empty()) continue;  // Skip blank lines

        vector<string> fields = CSVParser::parseLine(line);
        if (fields.size() < 1) continue;

        // Extract and convert CSV fields safely
        int zipCode = CSVParser::toInt(fields[0]);
        if (zipCode == 0) continue;

        string city = fields.size() > 1 ? fields[1] : "";
        string state_id = fields.size() > 2 ? fields[2] : "";
        string state_name = fields.size() > 3 ? fields[3] : "";
        string county = fields.size() > 4 ? fields[4] : "";
        double lat = fields.size() > 5 ? CSVParser::toDouble(fields[5]) : 0.0;
        double lng = fields.size() > 6 ? CSVParser::toDouble(fields[6]) : 0.0;
        string timezone = fields.size() > 7 ? fields[7] : "";
        int population = fields.size() > 8 ? CSVParser::toInt(fields[8]) : 0;

        // Create a USCity object and insert into both maps
        USCity cityData(city, state_id, state_name, county, timezone, lat, lng, population);
        avl_cities.insert(zipCode, cityData);
        std_cities[zipCode] = cityData;
        zipCodes.push_back(zipCode);
        count++;
    }

    file.close();
    cout << "Loaded " << count << " ZIP codes successfully." << endl;
    return true;
}

/*
 * Function: selectRandomZipCodes
 * ------------------------------
 * Takes a list of all ZIP codes and returns a vector
 * containing a random subset of ZIPs (used for benchmarking).
 */
vector<int> selectRandomZipCodes(const list<int>& zipCodes, int count) {
    vector<int> allZips(zipCodes.begin(), zipCodes.end());
    vector<int> selected;

    random_device rd;
    mt19937 gen(rd());

    // Select up to 'count' random ZIP codes (or fewer if not enough)
    int selectCount = min(count, static_cast<int>(allZips.size()));
    shuffle(allZips.begin(), allZips.end(), gen);

    selected.assign(allZips.begin(), allZips.begin() + selectCount);
    return selected;
}

/*
 * Function: benchmarkLookups
 * --------------------------
 * Measures lookup performance between:
 * - avl_map (your custom AVL implementation)
 * - std::map (C++ STL Red-Black Tree)
 * Uses chrono for timing.
 */
void benchmarkLookups(avl_map<int, USCity>& avl_cities, map<int, USCity>& std_cities,
                      const vector<int>& testZips) {

    cout << "\n=== Performance Benchmark ===" << endl;
    cout << "Testing with " << testZips.size() << " random ZIP codes\n" << endl;

    // Measure AVL lookup performance
    auto start = chrono::high_resolution_clock::now();
    int avl_found = 0;
    for (int zip : testZips) {
        auto it = avl_cities.find(zip);
        if (it != avl_cities.end()) avl_found++;
    }
    auto end = chrono::high_resolution_clock::now();
    auto avl_duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "AVL Map Results:" << endl;
    cout << "  Time: " << avl_duration.count() << " microseconds" << endl;
    cout << "  Found: " << avl_found << " / " << testZips.size() << endl;

    // Measure STL map lookup performance
    start = chrono::high_resolution_clock::now();
    int std_found = 0;
    for (int zip : testZips) {
        auto it = std_cities.find(zip);
        if (it != std_cities.end()) std_found++;
    }
    end = chrono::high_resolution_clock::now();
    auto std_duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "\nSTL Map Results:" << endl;
    cout << "  Time: " << std_duration.count() << " microseconds" << endl;
    cout << "  Found: " << std_found << " / " << testZips.size() << endl;

    // Compare performance ratios
    cout << "\n=== Performance Comparison ===" << endl;
    double ratio = static_cast<double>(avl_duration.count()) / std_duration.count();
    cout << "AVL Map / STL Map ratio: " << ratio << "x" << endl;

    if (ratio < 1.0) {
        cout << "AVL Map was faster!" << endl;
    } else if (ratio > 1.0) {
        cout << "STL Map was faster by " << (ratio - 1.0) * 100 << "%" << endl;
    } else {
        cout << "Both performed similarly." << endl;
    }
}

/*
 * Function: testAVLOperations
 * ---------------------------
 * Performs a simple functional test of insert, find, and erase
 * operations on the AVL map using integer keys and string values.
 */
void testAVLOperations() {
    cout << "\n=== Testing Basic AVL Operations ===" << endl;
    avl_map<int, string> test_map;

    cout << "Inserting values: 10, 20, 30, 40, 50, 25" << endl;
    test_map.insert(10, "Ten");
    test_map.insert(20, "Twenty");
    test_map.insert(30, "Thirty");
    test_map.insert(40, "Forty");
    test_map.insert(50, "Fifty");
    test_map.insert(25, "Twenty-Five");

    cout << "Map size: " << test_map.size() << endl;

    // Test find() function
    auto it = test_map.find(30);
    if (it != test_map.end()) cout << "Found 30: " << *it << endl;

    // Test erase() function
    cout << "Erasing key 20..." << endl;
    test_map.erase(20);
    cout << "Map size after erase: " << test_map.size() << endl;

    // Verify deletion
    it = test_map.find(20);
    if (it == test_map.end()) cout << "Key 20 successfully deleted." << endl;
}

/*
 * main()
 * ------
 * The main function ties everything together:
 * 1. Tests basic AVL functionality.
 * 2. Loads real ZIP code data from a CSV file.
 * 3. Benchmarks lookup performance against std::map.
 * 4. Displays one example lookup result.
 */
int main(int argc, char* argv[]) {
    cout << "AVL Map vs STL Map Performance Comparison" << endl;
    cout << "========================================\n" << endl;

    // Step 1: Sanity test for AVL functions
    testAVLOperations();

    // Step 2: Prepare data structures
    avl_map<int, USCity> avl_cities;
    map<int, USCity> std_cities;
    list<int> zipCodes;

    // Step 3: Load data from file
    string filename = "uszips.csv";
    if (argc > 1) filename = argv[1];  // Allow user to specify custom file
    cout << "\nLoading ZIP code data from: " << filename << endl;

    if (!loadZipCodeData(filename, avl_cities, std_cities, zipCodes))
        return 1;

    // Step 4: Display data sizes for confirmation
    cout << "\nAVL Map size: " << avl_cities.size() << endl;
    cout << "STL Map size: " << std_cities.size() << endl;
    cout << "ZIP codes list size: " << zipCodes.size() << endl;

    // Step 5: Randomly pick ZIPs for benchmarking
    int testCount = 1000;
    if (zipCodes.size() < 1000) testCount = zipCodes.size();
    vector<int> testZips = selectRandomZipCodes(zipCodes, testCount);

    // Step 6: Run benchmark
    benchmarkLookups(avl_cities, std_cities, testZips);

    // Step 7: Display one sample lookup
    if (!testZips.empty()) {
        cout << "\n=== Sample Lookup ===" << endl;
        int sampleZip = testZips[0];
        cout << "Looking up ZIP: " << sampleZip << endl;

        auto it = avl_cities.find(sampleZip);
        if (it != avl_cities.end()) {
            cout << "Found in AVL Map: ";
            (*it).display();  // Call USCity::display() to show info
        }
    }

    cout << "\nProgram completed successfully!" << endl;
    return 0;
}

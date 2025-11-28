/*
 * PA5: Micro Project - Emergency Management System
 * CPTS 223 Advanced Data Structures
 * 
 * Skeleton Code - main.cpp
 * 
 * This file provides the basic REPL structure and command parsing.
 * You need to implement the actual functionality for each command.
 * 
 * AI USAGE POLICY:
 * - You MAY use AI assistance for: priority queue, graph structure, REPL logic
 * - You MUST NOT use AI for: Dijkstra's algorithm (use your MA3 implementation)
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Graph.h"
#include "Hospital.h"
#include <unordered_map>
#include <limits>

using namespace std;

// Global data structures
Graph hospitalNetwork;
unordered_map<string, Hospital> hospitals;
unordered_map<string, unordered_map<string, int>> allPairsDistances;

/*
 * Initialize the hospital network graph with the 5 cities and their connections.
 * 
 * Cities: Pullman, Moscow, Colfax, Lewiston, Spokane
 * 
 * Connections:
 * - Pullman <-> Moscow: 8 miles
 * - Pullman <-> Colfax: 17 miles
 * - Pullman <-> Lewiston: 30 miles
 * - Moscow <-> Lewiston: 32 miles
 * - Moscow <-> Spokane: 85 miles
 * - Colfax <-> Spokane: 50 miles
 */
void initializeNetwork() {
    // Initialize all cities and hospitals
    vector<string> cityNames = {
        "Pullman", "Moscow", "Colfax", "Lewiston", "Spokane"
    };
    
    for (const auto& city : cityNames) {
        hospitals.emplace(city, Hospital(city));
    }
    
    // Add edges according to the network topology
    hospitalNetwork.addEdge("Pullman", "Moscow", 8);
    hospitalNetwork.addEdge("Pullman", "Colfax", 17);
    hospitalNetwork.addEdge("Pullman", "Lewiston", 30);
    hospitalNetwork.addEdge("Moscow", "Lewiston", 32);
    hospitalNetwork.addEdge("Moscow", "Spokane", 85);
    hospitalNetwork.addEdge("Colfax", "Spokane", 50);
    
    // Pre-compute shortest paths from each city to all other cities
    // This optimization allows O(1) lookup later
    for (const auto& city : hospitalNetwork.getCities()) {
        allPairsDistances[city] = hospitalNetwork.dijkstra(city);
    }
    
    cout << "Hospital network initialized." << endl;
}

/*
 * Helper function to find nearest open hospital
 */
string findNearestOpenHospital(const string& city) {
    int minDistance = numeric_limits<int>::max();
    string nearestHospital;
    
    // Look up pre-computed distances
    const auto& distances = allPairsDistances[city];
    
    for (const auto& entry : distances) {
        const string& targetCity = entry.first;
        int distance = entry.second;
        
        // Check if hospital is open
        auto it = hospitals.find(targetCity);
        if (it != hospitals.end() && it->second.getIsOpen()) {
            if (distance < minDistance) {
                minDistance = distance;
                nearestHospital = targetCity;
            }
        }
    }
    
    return nearestHospital;
}

/*
 * Handle the emergency command.
 * Format: emergency "<name>" <severity> <city>
 * 
 * @param name - Patient name
 * @param severity - Severity level (1-10)
 * @param city - City where emergency occurred
 */
void handleEmergency(const string& name, int severity, const string& city) {
    // Validate city
    if (!hospitalNetwork.hasCity(city)) {
        cout << "Error: Unknown city " << city << endl;
        return;
    }
    
    // Find nearest open hospital
    string targetHospital = findNearestOpenHospital(city);
    
    if (targetHospital.empty()) {
        cout << "Error: No open hospitals available" << endl;
        return;
    }
    
    // Create patient and admit to hospital
    Patient patient(name, severity, city);
    hospitals.at(targetHospital).admitPatient(patient);
    
    cout << "Patient " << name << " (severity " << severity 
         << ") from " << city << " admitted to " << targetHospital << " hospital." << endl;
}


/*
 * Handle the hospital close command.
 * Format: hospital close <city>
 * 
 * @param city - City whose hospital to close
 */
void handleHospitalClose(const string& city) {
    auto it = hospitals.find(city);
    if (it == hospitals.end()) {
        cout << "Error: Unknown hospital " << city << endl;
        return;
    }
    
    Hospital& hospital = it->second;
    
    if (!hospital.getIsOpen()) {
        cout << city << " hospital is already closed." << endl;
        return;
    }
    
    hospital.close();
    cout << city << " hospital closed.";
    
    // Transfer patients if any exist
    if (hospital.hasPatients()) {
        string nearestHospital = findNearestOpenHospital(city);
        
        if (nearestHospital.empty()) {
            cout << " Warning: No open hospitals available for patient transfer." << endl;
            return;
        }
        
        int patientCount = hospital.getPatientCount();
        
        // Merge the priority queues
        hospitals.at(nearestHospital).getPatientQueue().merge(hospital.getPatientQueue());
        
        cout << " " << patientCount << " patients transferred to " 
             << nearestHospital << " hospital." << endl;
    } else {
        cout << endl;
    }
}


/*
 * Handle the hospital open command.
 * Format: hospital open <city>
 * 
 * @param city - City whose hospital to reopen
 */
void handleHospitalOpen(const string& city) {
    auto it = hospitals.find(city);
    if (it == hospitals.end()) {
        cout << "Error: Unknown hospital " << city << endl;
        return;
    }
    
    Hospital& hospital = it->second;
    
    if (hospital.getIsOpen()) {
        cout << city << " hospital is already open." << endl;
        return;
    }
    
    hospital.open();
    cout << city << " hospital is now open." << endl;
}


/*
 * Handle the treat command.
 * Format: treat <city>
 * 
 * @param city - City whose hospital should treat next patient
 */
void handleTreat(const string& city) {
    auto it = hospitals.find(city);
    if (it == hospitals.end()) {
        cout << "Error: Unknown hospital " << city << endl;
        return;
    }
    
    Hospital& hospital = it->second;
    
    if (!hospital.getIsOpen()) {
        cout << "Error: " << city << " hospital is closed." << endl;
        return;
    }
    
    if (!hospital.hasPatients()) {
        cout << "No patients waiting at " << city << " hospital." << endl;
        return;
    }
    
    Patient patient = hospital.treatPatient();
    cout << "Treating " << patient.name << " (severity " 
         << patient.severity << ") originally from " << patient.originalCity 
         << " at " << city << " hospital." << endl;
}


/*
 * Handle the status command.
 * Format: status
 * 
 * Displays for each hospital:
 * - Hospital name/city
 * - Status (Open or Closed)
 * - Number of patients waiting
 * - Next patient info (if any): name, severity, original city
 */
void handleStatus() {
    cout << "\n=== Hospital Network Status ===" << endl;
    
    // Display in consistent order
    vector<string> cityOrder = {
        "Pullman", "Moscow", "Colfax", "Lewiston", "Spokane"
    };
    
    for (const auto& city : cityOrder) {
        auto it = hospitals.find(city);
        if (it == hospitals.end()) continue;
        
        const Hospital& hospital = it->second;
        
        cout << "\nHospital: " << city << ", WA" << endl;
        cout << "Status: " << (hospital.getIsOpen() ? "OPEN" : "CLOSED") << endl;
        cout << "Patients Waiting: " << hospital.getPatientCount() << endl;
        
        if (hospital.hasPatients()) {
            const Patient& nextPatient = hospital.getNextPatient();
            cout << "Next Patient: " << nextPatient.name 
                 << ", Severity: " << nextPatient.severity 
                 << ", From: " << nextPatient.originalCity << endl;
        }
    }
    
    cout << "\n==============================\n" << endl;
}


/*
 * Parse and execute a command from user input.
 * 
 * @param input - The full command line entered by user
 * @return true if should continue, false if should quit
 */
bool processCommand(const string& input) {
    istringstream iss(input);
    string command;
    iss >> command;
    
    if (command == "quit" || command == "exit") {
        return false;
    }
    else if (command == "emergency") {
        // Parse: emergency "<name>" <severity> <city>
        string name;
        int severity;
        string city;
        
        // Handle quoted name
        char ch;
        iss >> ch; // Get opening quote
        if (ch == '"') {
            getline(iss, name, '"'); // Read until closing quote
        } else {
            // Name might not be quoted, read as single word
            iss.putback(ch);
            iss >> name;
        }
        
        iss >> severity >> city;
        
        if (severity < 1 || severity > 10) {
            cout << "Error: Severity must be between 1 and 10." << endl;
        } else {
            handleEmergency(name, severity, city);
        }
    }
    else if (command == "hospital") {
        string action, city;
        iss >> action >> city;
        
        if (action == "close") {
            handleHospitalClose(city);
        }
        else if (action == "open") {
            handleHospitalOpen(city);
        }
        else {
            cout << "Unknown hospital action: " << action << endl;
        }
    }
    else if (command == "treat") {
        string city;
        iss >> city;
        handleTreat(city);
    }
    else if (command == "status") {
        handleStatus();
    }
    else if (command == "help") {
        cout << "\nAvailable commands:" << endl;
        cout << "  emergency \"<name>\" <severity> <city> - Register new emergency" << endl;
        cout << "  hospital close <city>                 - Close a hospital" << endl;
        cout << "  hospital open <city>                  - Reopen a hospital" << endl;
        cout << "  treat <city>                          - Treat next patient" << endl;
        cout << "  status                                - Show all hospital status" << endl;
        cout << "  help                                  - Show this help message" << endl;
        cout << "  quit/exit                             - Exit the program" << endl;
        cout << endl;
    }
    else {
        cout << "Unknown command: " << command << endl;
        cout << "Type 'help' for available commands." << endl;
    }
    
    return true;
}


int main() {
    cout << "========================================" << endl;
    cout << "  Emergency Management System" << endl;
    cout << "  PA5 - CPTS 223" << endl;
    cout << "========================================" << endl;
    
    // Initialize the hospital network
    initializeNetwork();
    
    cout << "\nType 'help' for available commands." << endl;
    cout << "Type 'quit' or 'exit' to end the program.\n" << endl;
    
    // Main REPL loop
    string input;
    bool running = true;
    
    while (running) {
        cout << "> ";
        getline(cin, input);
        
        // Skip empty input
        if (input.empty()) {
            continue;
        }
        
        running = processCommand(input);
    }
    
    cout << "Exiting Emergency Management System. Goodbye!" << endl;
    
    return 0;
}
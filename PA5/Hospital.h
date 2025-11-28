#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "PriorityQueue.h"
#include <string>

class Hospital {
private:
    std::string city;
    bool isOpen;
    PriorityQueue patientQueue;

public:
    Hospital(const std::string& c) : city(c), isOpen(true) {}
    
    const std::string& getCity() const { return city; }
    
    bool getIsOpen() const { return isOpen; }
    
    void open() { isOpen = true; }
    
    void close() { isOpen = false; }
    
    void admitPatient(const Patient& patient) {
        patientQueue.insert(patient);
    }
    
    Patient treatPatient() {
        return patientQueue.extractMax();
    }
    
    bool hasPatients() const {
        return !patientQueue.isEmpty();
    }
    
    int getPatientCount() const {
        return patientQueue.size();
    }
    
    const Patient& getNextPatient() const {
        return patientQueue.peekMax();
    }
    
    PriorityQueue& getPatientQueue() {
        return patientQueue;
    }
};

#endif // HOSPITAL_H
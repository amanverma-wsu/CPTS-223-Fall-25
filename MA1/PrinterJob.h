#ifndef PRINTERJOB_H
#define PRINTERJOB_H

#include <string>

using namespace std;

// The PrinterJob class represents a single print job in the queue.
// Each job has a 'printString' (the job name or description) and a 'priority' value.
// Lower 'priority' numbers mean higher priority in processing.
class PrinterJob {
public:
    string printString;  // The name or description of the print job
    int priority;        // Priority level (lower value = higher priority)

    // Default constructor: initializes job with default/empty values
    PrinterJob();

    // Parameterized constructor: initializes with given string and priority
    PrinterJob(string str, int pri);
    
    // Comparison operator: compares two PrinterJob objects by priority
    // Returns true if this job has lower priority (i.e., higher precedence)
    bool operator<(const PrinterJob& other) const;
};

#endif

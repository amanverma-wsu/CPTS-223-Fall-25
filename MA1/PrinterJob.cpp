#include "PrinterJob.h"

// Default constructor:
// Initializes printString to an empty string and priority to 0.
// This ensures that even if no data is passed, the job object starts in a valid state.
PrinterJob::PrinterJob() : printString(""), priority(0) {}

// Parameterized constructor:
// Used when creating a new PrinterJob with a specific job name and priority value.
PrinterJob::PrinterJob(string str, int pri) : printString(str), priority(pri) {}

// Overloaded < operator:
// Allows comparison between two PrinterJob objects based on their priority values.
// Returns true if this job’s priority value is smaller (meaning higher priority in the queue).
bool PrinterJob::operator<(const PrinterJob& other) const {
    return priority < other.priority;
}

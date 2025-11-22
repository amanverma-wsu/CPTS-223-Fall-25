#include "ListPriorityQueue.h"
#include "HeapPriorityQueue.h"

#include <iostream>
#include <sstream>

using namespace std;

int main() {
    // You can switch between ListPriorityQueue and HeapPriorityQueue
    // to test both implementations. Only one should be active at a time.
    // ListPriorityQueue queue;
    HeapPriorityQueue queue;

    string input;  // to store user input line

    cout << "Enter print jobs in format: <string> <priority>. Type 'print' to process jobs. Type 'exit' to exit.\n";

    // Infinite loop for user interaction until 'exit' is typed
    while (true) {
        cout << "> ";
        getline(cin, input);  // Read full line from user

        // Exit the program if user types 'exit'
        if (input == "exit") break;

        // If user types 'print', process all queued jobs
        if (input == "print") {
            queue.printJobs();
            continue;
        }

        // Parse the input using string stream to separate job name and priority
        istringstream iss(input);
        string printString;
        int priority;

        // Example valid input: "Doc1 2"
        if (iss >> printString >> priority) {
            // Add the job to the queue (min-heap or list)
            queue.enqueue(printString, priority);
        } else {
            // Handle invalid input format
            cout << "Invalid input. Format: <string> <priority>\n";
        }
    }

    // Program ends when user types 'exit'
    return 0;
}

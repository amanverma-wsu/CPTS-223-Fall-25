# PA5 - Emergency Response System

## How to Compile and Run
```bash
make
./emergency_system
```

To clean up:
```bash
make clean
```

---

## Files Included

- `Patient.h` - Patient data structure with severity comparison operators
- `PriorityQueue.h` - Max heap implementation with merge support
- `Graph.h` - Graph data structure with Dijkstra's algorithm
- `Hospital.h` - Hospital class managing patient queues
- `main.cpp` - REPL implementation with all command handlers
- `Makefile` - Build configuration
- `README.md` - This file
- `walkthrough.mp4` - Video demonstration (uploaded to Canvas)
- `repo.txt` - GitHub repository URL

---

## Design Decisions

### 1. Graph Implementation
- **Data Structure:** Adjacency list using `unordered_map<string, vector<Edge>>`
- **Rationale:** Efficient for sparse graphs with O(1) average-case neighbor lookup
- **Graph Type:** Undirected (bidirectional edges) representing road connections
- All 5 cities and their distances implemented as specified in assignment

### 2. Dijkstra's Algorithm Implementation (NO AI - From MA3)
- **Source:** Reused and modified from Micro Assignment 3
- **Implementation:** Classic Dijkstra with linear scan for minimum distance vertex
- **Key Modification:** Added `excludedCities` parameter to handle closed hospitals
- **Algorithm Flow:**
  1. Initialize all distances to infinity, source to 0
  2. Mark excluded (closed) hospitals as visited
  3. For each vertex, find minimum unvisited vertex
  4. Update distances to all neighbors (edge relaxation)
- **Complexity:** O(V²) time, O(V) space - acceptable for 5 nodes
- **Understanding:** I can explain every step - maintains distance array, picks min unvisited node, relaxes edges to neighbors

### 3. Pre-computed Shortest Paths Optimization
- **Strategy:** At initialization, run Dijkstra from each city to all other cities (5 runs total)
- **Storage:** `unordered_map<string, unordered_map<string, int>>` - stores all-pairs distances
- **Benefit:** O(1) lookup when finding nearest hospital vs O(V²) on-demand computation
- **Trade-off:** O(V²) space for O(1) query time
- **Justification:** Since graph is static and never changes, pre-computation is worthwhile
- **When Used:** During `emergency` and `hospital close` commands to find nearest open hospital

### 4. Priority Queue (Max Heap) - AI ASSISTED
- **Implementation:** Array-based binary max heap using `vector<Patient>`
- **Operations:**
  - `insert()`: O(log n) - add to end, heapify up
  - `extractMax()`: O(log n) - swap with last, heapify down
  - `peekMax()`: O(1) - return root
  - `merge()`: O(n) - bulk heapify approach (see below)
- **Heap Property:** Parent severity ≥ children severity (max heap for highest severity first)

### 5. Priority Queue Merge Strategy
**IMPORTANT:** This is NOT the simple O(n log n) approach to avoid the 50% penalty.

- **Approach:** Bulk heapify method
- **Algorithm:**
  1. Append all elements from source queue to destination queue's vector
  2. Perform bottom-up heapify starting from last non-leaf node: `(size/2) - 1`
  3. Work backwards to index 0, calling heapifyDown on each node
  4. Clear the source queue
- **Complexity:** O(n) where n is total number of patients
- **Why O(n)?** Bottom-up heapify (Floyd's algorithm) builds a heap in linear time
- **Why NOT O(n log n)?** We're not inserting elements one-by-one (which would be n insertions × log n each)
- **Proof of Efficiency:** Building a heap from an array is mathematically proven to be O(n) because most nodes are near the leaves and require few swaps

**Alternative Considered:** Insert each patient one-by-one from closed hospital to open hospital would be O(n log n). My approach is better.

### 6. Edge Cases Handled

| Edge Case | How Handled |
|-----------|-------------|
| Closing the only open hospital | Warning message, patients remain queued |
| Emergency in city with closed hospital | Routes to nearest open hospital via Dijkstra lookup |
| Reopening a hospital | Status changes to open, previously transferred patients stay at current location |
| Treating from empty queue | "No patients waiting" message |
| Treating from closed hospital | Error message |
| Invalid severity (< 1 or > 10) | Error message, command rejected |
| Unknown city name | Error message |
| Hospital already closed/open | Appropriate message |

---

## AI Usage Declaration

### Components Using AI Assistance:
- Priority Queue implementation (`PriorityQueue.h`) - heap operations and merge logic
- Hospital class structure (`Hospital.h`) - encapsulation and methods
- Command parsing in `main.cpp` - string parsing for quoted names
- Code organization - file structure and function separation
- Helper functions - `findNearestOpenHospital()`

### Components WITHOUT AI (Student Implementation):
- **Dijkstra's Algorithm** (`Graph.h`, `dijkstra()` method)
  - This is MY implementation from MA3
  - Modified to support `excludedCities` parameter for closed hospitals
  - I understand the algorithm completely and can explain:
    - Why we initialize distances to infinity
    - How we select the minimum unvisited vertex
    - How edge relaxation works
    - Why it guarantees shortest paths
  - **NO AI tools were used for this component**

### Confirmation:
I confirm that my Dijkstra's algorithm implementation is from MA3 and was implemented without AI assistance. I understand how it works and can debug/explain it in the video walkthrough.

---

## Implementation Details

### Hospital Network Topology
```
Cities: Pullman, Moscow, Colfax, Lewiston, Spokane

Edges:
- Pullman ↔ Moscow: 8 miles
- Pullman ↔ Colfax: 17 miles  
- Pullman ↔ Lewiston: 30 miles
- Moscow ↔ Lewiston: 32 miles
- Moscow ↔ Spokane: 85 miles
- Colfax ↔ Spokane: 50 miles
```

### REPL Commands Implemented

1. **emergency "<name>" <severity> <city>**
   - Validates severity (1-10) and city
   - Finds nearest open hospital using pre-computed distances
   - Creates Patient object and inserts into priority queue
   - Prints confirmation with routed hospital

2. **hospital close <city>**
   - Marks hospital as closed
   - If patients exist, finds nearest open hospital
   - Merges priority queues using O(n) bulk heapify
   - Prints transfer confirmation

3. **hospital open <city>**
   - Changes hospital status to open
   - Prints confirmation

4. **treat <city>**
   - Validates hospital is open and has patients
   - Extracts max (highest severity) from heap
   - Prints patient details
   - Heap reorganizes via heapifyDown

5. **status**
   - Displays all 5 hospitals in order
   - Shows: name, status (OPEN/CLOSED), patient count
   - If patients waiting, shows next patient details

---

## Time and Space Complexity Analysis

### Initialization Phase
- **Time:** O(V³) = O(125) - Running Dijkstra V times, each taking O(V²)
- **Space:** O(V²) = O(25) - Storing all-pairs shortest paths

### Command Complexities

| Command | Time Complexity | Space Complexity | Explanation |
|---------|----------------|------------------|-------------|
| emergency | O(V) | O(1) | Loop through V cities to find min distance |
| hospital close | O(n) | O(n) | Merge operation where n = total patients |
| hospital open | O(1) | O(1) | Just flipping a boolean flag |
| treat | O(log n) | O(1) | Extract max + heapify down |
| status | O(H × k) | O(1) | H hospitals, k average patients per hospital |

Where:
- V = number of vertices/cities (5)
- H = number of hospitals (5)  
- n = number of patients in queue(s)

### Dijkstra's Algorithm in My Implementation
- **Time Complexity:** O(V²) - Using linear scan for min vertex
- **Space Complexity:** O(V) - Distance and visited arrays
- **Could be improved to:** O((V + E) log V) with priority queue, but unnecessary for 5 nodes
- **Modifications from MA3:** Added support for excluding nodes (closed hospitals)

---

## Testing

### Test Script from Appendix A
Successfully tested with all commands from the assignment appendix:
1. Initial status shows all 5 hospitals open with 0 patients
2. Adding 4 emergencies distributes patients correctly
3. closing Pullman transfers 2 patients to Moscow (8 miles - nearest)
4. New emergency in closed city routes to nearest open hospital
5. Treating patients extracts in correct priority order (severity 9 before 8 before 7)
6. Reopening hospital works, transferred patients remain at current location

### Additional Edge Cases Tested
- Closing hospital with no patients
- Adding emergency with invalid severity
- Treating from empty queue
- Multiple hospital closures in sequence

---

## Video Walkthrough Structure

My `walkthrough.mp4` covers all 5 required parts:

**Part 1 (10 pts):** Application demo following Appendix A script exactly  
**Part 2 (10 pts):** Emergency command - parsing, Dijkstra lookup, heap insertion  
**Part 3 (10 pts):** Hospital close - marking closed, finding nearest, queue merge  
**Part 4 (10 pts):** Treat command - extractMax, heapify down, heap structure  
**Part 5 (10 pts):** Graph structure and Dijkstra step-through from MA3  

Video length: ~18 minutes (under 20 minute limit)

---

## Challenges and Solutions

**Challenge 1:** Understanding merge operation complexity  
**Solution:** Researched Floyd's bottom-up heapify algorithm, implemented O(n) approach

**Challenge 2:** Handling quoted patient names in command parsing  
**Solution:** Check for opening quote, use `getline()` with quote delimiter

**Challenge 3:** Maintaining heap property during merge  
**Solution:** Start heapify from last non-leaf node, work upward to root

---

## Notes

- All hospitals start OPEN at program initialization
- Graph is static (never changes during execution)
- Pre-computation trades space for time (good decision for static graph)
- Dijkstra's algorithm excludes closed hospitals by marking them as visited
- Patients maintain original city information even after transfer
- Code follows good software engineering practices (modular, well-documented)

---

## Build Information

- **C++ Standard:** C++11
- **Compiler:** g++ with `-Wall -Wextra -g` flags
- **Debug Symbols:** Enabled for video walkthrough debugging
- **No external libraries** used (only STL)
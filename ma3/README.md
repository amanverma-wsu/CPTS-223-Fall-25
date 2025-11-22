# MA3: Dijkstra's Algorithm Implementation

**Course:** WSU CPTS 223  
**Assignment:** MA3 - Shortest Path Algorithms  
**Date:** November 21, 2025

## What I Built

For this assignment, I implemented Dijkstra's algorithm and compared it with a brute force approach for finding shortest paths between U.S. state capitals. The graph has 49 cities (the continental U.S. capitals) connected by edges representing distances between neighboring states.

I ran both algorithms 10 times each, computing shortest paths from every capital to every other capital, and measured their performance.

## My Results

### Brute Force Algorithm
- Min Time: 37.7207 ms
- Max Time: 63.7008 ms
- Average Time: 40.7374 ms
- Standard Deviation: 7.69899 ms

### Dijkstra's Algorithm
- Min Time: 8.86721 ms
- Max Time: 8.98354 ms
- Average Time: 8.9387 ms
- Standard Deviation: 0.0327776 ms

### What This Means

Dijkstra's algorithm ran about **4.6 times faster** than brute force (40.7374 ms vs 8.9387 ms). What really stood out to me was how consistent Dijkstra was - the standard deviation was only 0.033 ms compared to brute force's 7.7 ms. This means Dijkstra performs reliably no matter which city you start from.

## Why Dijkstra is So Much Faster

### The Big Picture

The brute force algorithm basically keeps checking every edge over and over until nothing changes anymore. It has a time complexity of O(V × E), which means for our 49 cities and ~148 edges, it's doing around 7,000+ operations per iteration and has to repeat this multiple times.

Dijkstra's algorithm is smarter - it uses a priority queue to always pick the closest unvisited city next. Its time complexity is O((V + E) log V), which works out to about 1,100 operations total. That's why it's faster.

### What Makes Dijkstra Better

**Smarter about which city to check next**  
The brute force method just goes through every edge blindly. Dijkstra uses a priority queue (min-heap) to always process the closest city first, which means it doesn't waste time on cities that are far away.

**No wasted work**  
Brute force keeps re-checking the same edges even when they won't improve anything. Dijkstra visits each city exactly once and checks each edge exactly once, so there's no redundant work.

**Knows when to stop**  
The brute force algorithm has to keep going through all edges until nothing changes. Dijkstra naturally finishes when all reachable cities have been processed.

**Better data structure**  
The priority queue does the heavy lifting for Dijkstra. It can insert and extract cities in O(log V) time, which keeps everything efficient.

## Problems I Ran Into

### Problem 1: Making a Min-Heap

The first issue I hit was that C++'s priority_queue is a max-heap by default, but Dijkstra needs a min-heap (we want the city with the smallest distance, not the largest).

I solved this by creating a struct called PQNode that holds a city name and distance, and I overloaded the > operator to reverse the comparison. Then I used `priority_queue<PQNode, vector<PQNode>, greater<PQNode>>` which turned it into a min-heap. It took me a bit to figure out the syntax but once I got it working, it made sense.

### Problem 2: Duplicate Entries in the Queue

This one was tricky. When you find a shorter path to a city, you add a new entry to the priority queue with the better distance. But the old entry with the worse distance is still sitting in there. So you could end up processing the same city multiple times, which would be wrong.

My solution was to use a set to track which cities I'd already visited. When I pop something from the queue, I check if it's already in the visited set. If it is, I just skip it and move on. This way each city only gets processed once even if it appears multiple times in the queue.

### Problem 3: Making Sure It's Correct

I was worried about bugs since this is a pretty complex algorithm. Luckily the assignment included verification code that compares results from both algorithms.

I uncommented that section and ran it - it computed paths from Olympia WA to a bunch of other capitals using both algorithms and checked that all 49 distances matched. When I saw "All shortest path distances match between both algorithms!" I knew my implementation was working correctly. That was a relief.

### Problem 4: Understanding the Graph

At first I wasn't sure how the graph was structured. I looked through the CSV file and realized it's just connections between neighboring states with their distances. Some states like Missouri have a lot of neighbors (8 connections) while others like Maine only have one. Alaska and Hawaii aren't included since they don't border any other states. The adjacency list representation works really well for this since the graph is pretty sparse.

## How I Implemented It

My Dijkstra implementation follows the standard algorithm we learned in class:

1. Set all distances to infinity except the start city (which is 0)
2. Add the start city to the priority queue
3. Keep going while the queue isn't empty:
   - Take out the city with the smallest distance
   - Skip it if we've already processed it
   - Mark it as visited
   - Look at all its neighbors
   - If we found a shorter path to a neighbor, update its distance and add it to the queue

I used a map for storing distances, a set for tracking visited cities, and the priority queue for picking which city to process next. I tried to keep my code clean with good variable names and comments explaining what each part does.

## How to Compile and Run

To compile and run the program on Mac/Linux:

```bash
# Navigate to the project directory
cd ~/code/WSU_CPTS223_MA3

# Compile the code
g++ -std=c++11 ma3.cpp -o ma3

# Run the program
./ma3
```

For Windows with MinGW:
```bash
g++ -std=c++11 ma3.cpp -o ma3.exe
ma3.exe
```

Make sure the `state_capitals.csv` file is in the same directory as `ma3.cpp` before running.

## Testing It Out

To verify everything worked, I tested paths from Olympia WA to several other capitals:

- Olympia WA → Salem OR: 180 miles
- Olympia WA → Boise ID: 508 miles
- Olympia WA → Sacramento CA: 766 miles
- Olympia WA → Phoenix AZ: 1330 miles
- Olympia WA → Austin TX: 2272 miles

Both algorithms gave the same answers for all cities, which confirmed my implementation was correct.

## Final Thoughts

This assignment really showed me why we spend so much time learning about different algorithms and data structures. Even on a relatively small graph with just 49 cities, Dijkstra was 4.6 times faster than brute force. On a bigger graph like Google Maps uses (millions of locations), the difference would be huge - maybe the difference between getting results instantly vs waiting minutes or even hours.

The most interesting thing to me was how much more consistent Dijkstra was. The brute force times were all over the place (37 ms to 63 ms) while Dijkstra was super stable (8.86 ms to 8.98 ms). That consistency matters in real applications where you want predictable performance.

Overall, this was a good assignment for understanding why algorithmic efficiency matters and how the right data structure (the priority queue) can make a huge difference.

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>

struct Edge {
    std::string destination;
    int weight;
    
    Edge(const std::string& dest, int w) : destination(dest), weight(w) {}
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;
    std::vector<std::string> cities;

public:
    void addCity(const std::string& city) {
        if (adjacencyList.find(city) == adjacencyList.end()) {
            adjacencyList[city] = std::vector<Edge>();
            cities.push_back(city);
        }
    }
    
    void addEdge(const std::string& from, const std::string& to, int weight) {
        addCity(from);
        addCity(to);
        
        // Undirected graph - add edge in both directions
        adjacencyList[from].push_back(Edge(to, weight));
        adjacencyList[to].push_back(Edge(from, weight));
    }
    
    const std::vector<Edge>& getNeighbors(const std::string& city) const {
        static std::vector<Edge> empty;
        auto it = adjacencyList.find(city);
        if (it != adjacencyList.end()) {
            return it->second;
        }
        return empty;
    }
    
    const std::vector<std::string>& getCities() const {
        return cities;
    }
    
    bool hasCity(const std::string& city) const {
        return adjacencyList.find(city) != adjacencyList.end();
    }
    
    // Dijkstra's algorithm - from MA3, implemented without AI assistance
    std::unordered_map<std::string, int> dijkstra(
        const std::string& source,
        const std::vector<std::string>& excludedCities = std::vector<std::string>()
    ) const {
        std::unordered_map<std::string, int> distances;
        std::unordered_map<std::string, bool> visited;
        
        // Initialize distances to infinity
        for (const auto& city : cities) {
            distances[city] = std::numeric_limits<int>::max();
            visited[city] = false;
        }
        distances[source] = 0;
        
        // Check if excluded
        for (const auto& excluded : excludedCities) {
            visited[excluded] = true;
        }
        
        // Process all vertices
        for (size_t i = 0; i < cities.size(); i++) {
            // Find minimum distance unvisited vertex
            int minDistance = std::numeric_limits<int>::max();
            std::string minCity;
            
            for (const auto& city : cities) {
                if (!visited[city] && distances[city] < minDistance) {
                    minDistance = distances[city];
                    minCity = city;
                }
            }
            
            if (minCity.empty()) break;
            
            visited[minCity] = true;
            
            // Update distances to neighbors
            const auto& neighbors = getNeighbors(minCity);
            for (const auto& edge : neighbors) {
                if (!visited[edge.destination]) {
                    int newDistance = distances[minCity] + edge.weight;
                    if (newDistance < distances[edge.destination]) {
                        distances[edge.destination] = newDistance;
                    }
                }
            }
        }
        
        return distances;
    }
};

#endif // GRAPH_H
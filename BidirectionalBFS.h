#ifndef BIDIRECTIONAL_BFS_H
#define BIDIRECTIONAL_BFS_H

#include <vector>
#include <unordered_map>

class BidirectionalBFS {
private:
    // Graph representation as adjacency list
    std::unordered_map<int, std::vector<int>> graph;
    
    // Helper method to reconstruct path from start to meeting point and meeting point to goal
    std::vector<int> reconstructPath(int start, int goal, 
                                     const std::unordered_map<int, int>& parentForward,
                                     const std::unordered_map<int, int>& parentBackward,
                                     int meetingNode);
    
public:
    // Add an edge to the graph (undirected)
    void addEdge(int from, int to);
    
    // Bidirectional BFS search
    std::vector<int> bidirectionalSearch(int start, int goal);
    
    // Print the graph (for debugging)
    void printGraph();
};

#endif // BIDIRECTIONAL_BFS_H


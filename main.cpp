#include "BidirectionalBFS.h"
#include <iostream>
#include <vector>

int main() {
    BidirectionalBFS bfs;
    
    // Example graph
    // Let's create a simple graph for demonstration
    // Graph structure:
    //     0 -- 1 -- 2
    //     |    |    |
    //     3 -- 4 -- 5
    //     |    |    |
    //     6 -- 7 -- 8
    
    // Add edges
    bfs.addEdge(0, 1);
    bfs.addEdge(1, 2);
    bfs.addEdge(0, 3);
    bfs.addEdge(1, 4);
    bfs.addEdge(2, 5);
    bfs.addEdge(3, 4);
    bfs.addEdge(4, 5);
    bfs.addEdge(3, 6);
    bfs.addEdge(4, 7);
    bfs.addEdge(5, 8);
    bfs.addEdge(6, 7);
    bfs.addEdge(7, 8);
    
    std::cout << "=== Bidirectional BFS Search ===" << std::endl;
    bfs.printGraph();
    std::cout << std::endl;
    
    // Test case 1: Find path from 0 to 8
    int start = 0;
    int goal = 8;
    std::cout << "Finding path from " << start << " to " << goal << ":" << std::endl;
    std::vector<int> path = bfs.bidirectionalSearch(start, goal);
    
    if (!path.empty()) {
        std::cout << "Path found: ";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
        std::cout << "Path length: " << path.size() - 1 << " edges" << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }
    std::cout << std::endl;
    
    // Test case 2: Find path from 2 to 6
    start = 2;
    goal = 6;
    std::cout << "Finding path from " << start << " to " << goal << ":" << std::endl;
    path = bfs.bidirectionalSearch(start, goal);
    
    if (!path.empty()) {
        std::cout << "Path found: ";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
        std::cout << "Path length: " << path.size() - 1 << " edges" << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }
    std::cout << std::endl;
    
    // Test case 3: Same start and goal
    start = 4;
    goal = 4;
    std::cout << "Finding path from " << start << " to " << goal << ":" << std::endl;
    path = bfs.bidirectionalSearch(start, goal);
    
    if (!path.empty()) {
        std::cout << "Path found: ";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found!" << std::endl;
    }
    
    return 0;
}


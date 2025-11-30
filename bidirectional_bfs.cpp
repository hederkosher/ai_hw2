#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class BidirectionalBFS {
private:
    // Graph representation as adjacency list
    unordered_map<int, vector<int>> graph;
    
public:
    // Add an edge to the graph (undirected)
    void addEdge(int from, int to) {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    
    // Reconstruct path from start to meeting point and meeting point to goal
    vector<int> reconstructPath(int start, int goal, 
                                 const unordered_map<int, int>& parentForward,
                                 const unordered_map<int, int>& parentBackward,
                                 int meetingNode) {
        vector<int> path;
        
        // Build path from start to meeting node
        vector<int> forwardPath;
        int current = meetingNode;
        while (current != start) {
            forwardPath.push_back(current);
            current = parentForward.at(current);
        }
        forwardPath.push_back(start);
        reverse(forwardPath.begin(), forwardPath.end());
        
        // Build path from meeting node to goal
        vector<int> backwardPath;
        current = meetingNode;
        while (current != goal) {
            backwardPath.push_back(current);
            current = parentBackward.at(current);
        }
        backwardPath.push_back(goal);
        
        // Combine paths (avoid duplicating meeting node)
        path = forwardPath;
        path.insert(path.end(), backwardPath.begin() + 1, backwardPath.end());
        
        return path;
    }
    
    // Bidirectional BFS search
    vector<int> bidirectionalSearch(int start, int goal) {
        // Check if start and goal are the same
        if (start == goal) {
            return {start};
        }
        
        // Forward search: from start to goal
        queue<int> queueForward;
        unordered_map<int, int> parentForward;
        unordered_set<int> visitedForward;
        
        // Backward search: from goal to start
        queue<int> queueBackward;
        unordered_map<int, int> parentBackward;
        unordered_set<int> visitedBackward;
        
        // Initialize forward search
        queueForward.push(start);
        visitedForward.insert(start);
        parentForward[start] = -1;
        
        // Initialize backward search
        queueBackward.push(goal);
        visitedBackward.insert(goal);
        parentBackward[goal] = -1;
        
        // Check if nodes exist in graph
        if (graph.find(start) == graph.end() || graph.find(goal) == graph.end()) {
            return {}; // Empty path - nodes don't exist
        }
        
        // Alternating BFS from both directions
        while (!queueForward.empty() || !queueBackward.empty()) {
            // Expand forward search
            if (!queueForward.empty()) {
                int current = queueForward.front();
                queueForward.pop();
                
                // Explore neighbors
                for (int neighbor : graph[current]) {
                    if (visitedForward.find(neighbor) == visitedForward.end()) {
                        visitedForward.insert(neighbor);
                        parentForward[neighbor] = current;
                        queueForward.push(neighbor);
                        
                        // Check if we've met the backward search
                        if (visitedBackward.find(neighbor) != visitedBackward.end()) {
                            return reconstructPath(start, goal, parentForward, 
                                                  parentBackward, neighbor);
                        }
                    }
                }
            }
            
            // Expand backward search
            if (!queueBackward.empty()) {
                int current = queueBackward.front();
                queueBackward.pop();
                
                // Explore neighbors
                for (int neighbor : graph[current]) {
                    if (visitedBackward.find(neighbor) == visitedBackward.end()) {
                        visitedBackward.insert(neighbor);
                        parentBackward[neighbor] = current;
                        queueBackward.push(neighbor);
                        
                        // Check if we've met the forward search
                        if (visitedForward.find(neighbor) != visitedForward.end()) {
                            return reconstructPath(start, goal, parentForward, 
                                                  parentBackward, neighbor);
                        }
                    }
                }
            }
        }
        
        // No path found
        return {};
    }
    
    // Print the graph (for debugging)
    void printGraph() {
        cout << "Graph representation:" << endl;
        for (const auto& pair : graph) {
            cout << pair.first << " -> ";
            for (int neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

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
    
    cout << "=== Bidirectional BFS Search ===" << endl;
    bfs.printGraph();
    cout << endl;
    
    // Test case 1: Find path from 0 to 8
    int start = 0;
    int goal = 8;
    cout << "Finding path from " << start << " to " << goal << ":" << endl;
    vector<int> path = bfs.bidirectionalSearch(start, goal);
    
    if (!path.empty()) {
        cout << "Path found: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Path length: " << path.size() - 1 << " edges" << endl;
    } else {
        cout << "No path found!" << endl;
    }
    cout << endl;
    
    // Test case 2: Find path from 2 to 6
    start = 2;
    goal = 6;
    cout << "Finding path from " << start << " to " << goal << ":" << endl;
    path = bfs.bidirectionalSearch(start, goal);
    
    if (!path.empty()) {
        cout << "Path found: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Path length: " << path.size() - 1 << " edges" << endl;
    } else {
        cout << "No path found!" << endl;
    }
    cout << endl;
    
    // Test case 3: Same start and goal
    start = 4;
    goal = 4;
    cout << "Finding path from " << start << " to " << goal << ":" << endl;
    path = bfs.bidirectionalSearch(start, goal);
    
    if (!path.empty()) {
        cout << "Path found: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }
    
    return 0;
}


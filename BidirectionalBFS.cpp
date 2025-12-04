#include "BidirectionalBFS.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>

// Add an edge to the graph (undirected)
void BidirectionalBFS::addEdge(int from, int to) {
  graph[from].push_back(to);
  graph[to].push_back(from);
}

// Reconstruct path from start to meeting point and meeting point to goal
std::vector<int> BidirectionalBFS::reconstructPath(
    int start, int goal, const std::unordered_map<int, int> &parentForward,
    const std::unordered_map<int, int> &parentBackward, int meetingNode) {
  std::vector<int> path;

  // Build path from start to meeting node
  std::vector<int> forwardPath;
  int current = meetingNode;
  while (current != start) {
    forwardPath.push_back(current);
    current = parentForward.at(current);
  }
  forwardPath.push_back(start);
  std::reverse(forwardPath.begin(), forwardPath.end());

  // Build path from meeting node to goal
  std::vector<int> backwardPath;
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
std::vector<int> BidirectionalBFS::bidirectionalSearch(int start, int goal) {
  // Check if start and goal are the same
  if (start == goal) {
    return {start};
  }

  // Forward search: from start to goal
  std::queue<int> queueForward;
  std::unordered_map<int, int> parentForward;
  std::unordered_set<int> visitedForward;

  // Backward search: from goal to start
  std::queue<int> queueBackward;
  std::unordered_map<int, int> parentBackward;
  std::unordered_set<int> visitedBackward;

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
            return reconstructPath(start, goal, parentForward, parentBackward,
                                   neighbor);
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
            return reconstructPath(start, goal, parentForward, parentBackward,
                                   neighbor);
          }
        }
      }
    }
  }

  // No path found
  return {};
}

// Print the graph (for debugging)
void BidirectionalBFS::printGraph() {
  std::cout << "Graph representation:" << std::endl;
  for (const auto &pair : graph) {
    std::cout << pair.first << " -> ";
    for (int neighbor : pair.second) {
      std::cout << neighbor << " ";
    }
    std::cout << std::endl;
  }
}

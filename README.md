# Bidirectional BFS Implementation

This project implements a Bidirectional Breadth-First Search (BFS) algorithm in C++.

## Overview

Bidirectional BFS is an optimization of the standard BFS algorithm that searches from both the start and goal nodes simultaneously. The search completes when the two search frontiers meet, which typically reduces the search space significantly compared to unidirectional BFS.

## Algorithm Description

1. **Initialization**: Start two BFS searches simultaneously:
   - Forward search: from the start node
   - Backward search: from the goal node

2. **Alternating Expansion**: Alternate between expanding the forward and backward search frontiers

3. **Meeting Point Detection**: Check if a node has been visited by both searches

4. **Path Reconstruction**: When the searches meet, reconstruct the complete path by:
   - Building the path from start to meeting point
   - Building the path from meeting point to goal
   - Combining both paths

## Complexity

- **Time Complexity**: O(b^(d/2)) where:
  - b = branching factor
  - d = depth of the shallowest solution
  - This is much better than unidirectional BFS which is O(b^d)

- **Space Complexity**: O(b^(d/2)) for storing the two search frontiers

## Compilation

```bash
make
```

Or manually:

```bash
g++ -std=c++11 -Wall -Wextra -O2 -o bidirectional_bfs bidirectional_bfs.cpp
```

## Usage

```bash
./bidirectional_bfs
```

Or use make:

```bash
make run
```

## Example Output

The program demonstrates bidirectional BFS on a sample graph and finds paths between various nodes.

## Graph Representation

The graph is represented as an undirected adjacency list, where each node has a list of its neighbors.

## Features

- Undirected graph support
- Path reconstruction
- Handles edge cases (same start/goal, disconnected nodes)
- Clean, modular code structure


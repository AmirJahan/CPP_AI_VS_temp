# Ai_cpp

# 🧭 Pathfinding Algorithms in C++

*A visual and modular implementation of DFS, BFS, Dijkstra, and A**

This project demonstrates four fundamental graph-search algorithms — **Depth-First Search**, **Breadth-First Search**, **Dijkstra’s Algorithm**, and **A* Search** — implemented in C++ and designed for grid-based pathfinding.
Each algorithm reveals a different strategy for exploring and navigating a grid, making this project a useful reference for understanding classical search techniques.

---

## 📌 Project Overview

The goal of this project is to:

* Provide clean, working implementations of **DFS, BFS, Dijkstra, and A***
* Visualize how each algorithm explores a grid
* Highlight their differences, strengths, and use cases
* Serve as an educational reference for learning search algorithms in C++

Each algorithm operates on a 2D grid of `Node` objects.
Nodes track information such as:

* `visited`
* `blocked`
* `parent` (for path reconstruction)
* `gCost`, `hCost`, and `fCost` (Dijkstra/A*)
* `step` (distance from start)

---

# 🔍 Implemented Algorithms

## 1. 🌲 Depth-First Search (DFS)

**Concept:** Explore as deeply as possible before backtracking.
**Data Structure:** `std::stack` (LIFO)

DFS behaves like an adventurer exploring one path fully before trying others.
It is simple and memory-efficient but does **not guarantee the shortest path**.

In this project, DFS:

* Uses a stack to always explore the newest discovered node
* Marks nodes as visited when popped
* Backtracks automatically when it reaches a dead end
* Stops once the goal is found

---

## 2. 🧭 Breadth-First Search (BFS)

**Concept:** Explore neighbors one level at a time (waves).
**Data Structure:** `std::queue` (FIFO)

BFS guarantees the **shortest path in terms of number of steps** when all edges have equal cost.
It expands outward evenly from the start node.

In this project, BFS:

* Tracks visited nodes to avoid re-adding them
* Uses parent pointers to reconstruct the shortest path
* Processes nodes in the order they were discovered
* Naturally generates “concentric rings” of exploration

---

## 3. 🧮 Dijkstra’s Algorithm

**Concept:** Always expand the node with the **lowest total travel cost so far**.
**Data Structure:** `std::priority_queue`

Dijkstra finds the shortest path in **weighted** graphs (or grids), even when some movements cost more than others.
Unlike BFS, it does not assume uniform cost.

In this project, Dijkstra:

* Initializes all nodes with `gCost = ∞`
* Updates (`relaxes`) neighbors when a cheaper path is found
* Uses a priority queue to always pick the lowest-cost node
* Reconstructs the optimal path using parent pointers

---

## 4. ⭐ A* Search

**Concept:** Combines Dijkstra’s cost-so-far with a heuristic estimating distance to the goal.
**Data Structure:** `std::priority_queue`

A* is typically the **fastest optimal pathfinding algorithm** on grids.
It uses:

* `gCost`: cost from start to current node
* `hCost`: estimated cost from current node to goal (Manhattan distance)
* `fCost = gCost + hCost`: priority value

In this project, A*:

* Uses Manhattan distance as the heuristic
* Prefers nodes that are both cheap *and* close to the goal
* Produces the same optimal path as Dijkstra but with far fewer explored nodes

---

# 🆚 Algorithm Comparison

| Algorithm    | Optimal Path?        | Uses Heuristic? | Memory Usage | Typical Behavior                   |
| ------------ | -------------------- | --------------- | ------------ | ---------------------------------- |
| **DFS**      | ❌ No                 | ❌ No            | Very Low     | Goes deep, backtracks at dead ends |
| **BFS**      | ✅ Yes (uniform cost) | ❌ No            | High         | Expands evenly outward             |
| **Dijkstra** | ✅ Yes                | ❌ No            | High         | Explores all low-cost paths        |
| **A***       | ✅ Yes                | ✅ Yes           | Medium       | Efficiently guided toward the goal |

---

# 📁 Project Structure

```
/src
    Ai.h / Ai.cpp          # Contains implementations of all 4 algorithms
    Node.h / Node.cpp      # Node structure, cost fields, state flags
    Grid.h / Grid.cpp      # Grid initialization and neighbor lookup
    main.cpp               # Entry point / visualization
```

---

# ▶️ How to Run

1. Clone the repository
2. Build with any C++17+ compatible compiler
3. Run the executable to visualize the four pathfinding methods
4. Toggle algorithms to compare their exploration patterns and resulting paths

Example (Linux/Mac):

```bash
g++ -std=c++17 -O2 -o Pathfinding main.cpp Ai.cpp Node.cpp Grid.cpp
./Pathfinding
```

---

# 📘 Educational Purpose

This project is ideal for:

* Students learning search algorithms
* Game developers implementing pathfinding AI
* Anyone interested in algorithm visualization
* Comparing search strategies directly on the same grid

---

# 📝 License

This project is open-source.
Use it freely for learning, teaching, or extending into your own projects.



![alt text](https://github.com/AmirJahan/Ai_cpp/blob/main/Pathfinding_sample.png?raw=true)

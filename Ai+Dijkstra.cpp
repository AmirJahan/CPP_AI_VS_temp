#include "Ai.h"
#include <queue>
#include <limits>
#include <algorithm> // For std::reverse
#include <iostream>  // For std::cout

/*
    Djikstra's ~ The careful planner
    You start from the entrance and keep track of the easiest way to get to each room, 
    one step at a time, until you find the best path to the exit.

    	•	Dijkstra: While guaranteed to find the least costly path, Dijkstra can be 
        inefficient in large grids because it explores every possible path without 
        regard for how close the nodes are to the goal. It can be slow in real-time 
        scenarios where speed matters.

	•	A*: Typically faster because it uses the heuristic to skip unpromising nodes 
    and focus on those that are likely to lead to the goal. This makes A* more efficient
     in many real-world scenarios, particularly when the heuristic is well-chosen.
*/


using namespace std;

// Dijkstra Algorithm
void Ai::Dijkstra(Node* start, Node* goal) 
{
    // Clear any previous path data to start fresh
    dijkstraTracedPath.clear();

    // Reset all nodes in the grid
    for (auto& row : grid) 
        for (auto& node : row) 
            node.Reset();  // Reset the node's state (e.g., visited, parent, groundCost)


    // Lambda ~ inline function
    // The node with the lowest gCost will have the highest priority
    auto Compare = [](Node* a, Node* b) {
        return a->gCost > b->gCost; // Nodes with lower gCost have higher priority
    };


    // storing nodes in a vector, with comparison type (lambda function)
    priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);
    // a priority_queue provides constant time lookup 
    // for the largest (by default) or smallest element


    // Initialize the starting node
    start->gCost = 0; // The cost to reach the start node from itself is 0
    openSet.push(start); // Add the start node to the priority queue


    // Main loop of Dijkstra's algorithm
    while (!openSet.empty()) 
    {
        // Get the node with the lowest gCost from the priority queue
        Node* current = openSet.top();
        openSet.pop(); // Remove the node from the queue as it's being processed

        // If the current node is the goal node, reconstruct the path
        
        
        // compare if current and the goal are the same

        if (current == goal)
        {
            // Start from the goal and follow the parent pointers back to the start
            while (current != nullptr) 
            {
                dijkstraTracedPath.push_back(current); // Add each node in the path to tracedPath
                current = current->parent; // Move to the parent node
            }

            cout << "Path found using Dijkstra's algorithm." << endl;
            return; // Exit the function as the path has been found
        }

        // Explore each neighbor of the current node
        for (Node* neighbor : GetNeighbors(current)) 
        {
            // Only consider neighbors that are not blocked and not visited
            if (neighbor->blocked || neighbor->visited) continue;
            

            // Calculate the tentative gCost for the neighbor (assuming uniform cost of 1)
            float tentative_gCost = current->gCost + 1; 
            
            // If this path to the neighbor is better, update its gCost and parent
            if (tentative_gCost < neighbor->gCost) // default gCost is FLT_MAX
            {
                neighbor->gCost = tentative_gCost; // Update the gCost to the lower value
                neighbor->parent = current; // Set the current node as the parent

                // Update the step count (how far the node is from the start)
                neighbor->step = current->step + 1; 
                
                // Mark the neighbor as visited
                neighbor->visited = true;
                
                openSet.push(neighbor); // Add the neighbor to the priority queue for further exploration
            }
        }
    }

    // If the priority queue is empty and the goal was not reached, print a failure message
    cout << "No path found using Dijkstra's algorithm." << endl;
}
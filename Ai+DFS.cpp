#include "Ai.h"
#include <iostream>
#include <stack>  // Include the stack header


/*
    DFS -> Depth First Search ~ The Adventurer
    At each fork, always take the same direction, always choose that unless not possible
    When you hit a dead end, you go back to the last fork and try a different path.
    Nighbors are added in North, South, East, West order.
    So, we first check for West
*/

// DFS -> Depth First Search
void Ai::DFS(Node* start, Node* goal) 
{
    // Clear the tracedPath 
    dfsTracedPath.clear();
    
    // Reset all nodes in the grid.
    for (auto& row : grid)
        for (auto& node : row)
            node.Reset();
    
    // Stack for managing the nodes to visit, starting with the initial node.
    std::stack<Node*> openSet; // last in first out
    openSet.push(start);

    // Flag to determine if a path was found
    bool pathFound = false;

    // While there are still nodes to explore
    while (!openSet.empty()) 
    {
        // Get the current node (the last one added to the stack).
        Node* current = openSet.top();
        openSet.pop(); // Remove the node from the stack

        // If the current node has already been visited, skip it.
        if (current->visited)
            continue;

        // Mark the current node as visited 
        current->visited = true;

        // Add the current node to the path being constructed.
        dfsTracedPath.push_back(current);

        // Check if the current node is the goal node
        if (current == goal) {
            cout << "Path found using DFS." << endl;
            pathFound = true;
            break;  // Exit the loop 
        }

        // Explore each neighbor of the current node.
        for (Node* neighbor : GetNeighbors(current)) 
        {
            // Only add neighbors that have not been visited and are not blocked.
            if (!neighbor->visited && !neighbor->blocked) 
            {
                // Set the current node as the parent of the neighbor
                neighbor->parent = current;

                // Keep track of how far the node is from the start.
                neighbor->step = current->step + 1;

                // Add the neighbor to the stack for further exploration.
                openSet.push(neighbor);
            }
        }
    }

    // If no path was found, clear the tracedPath to indicate failure.
    if (!pathFound) {
        dfsTracedPath.clear();
        cout << "No path found using DFS. Clearing tracedPath." << endl;
    }
}
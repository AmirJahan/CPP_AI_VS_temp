#include "Ai.h"
#include <queue>
#include <iostream>

/*
    BFS ~ The Organized Explorer
    Bexplores all the neighbors of a node before moving on to the next level.
*/

void Ai::BFS(Node* start, Node* goal) 
{
    // Clear the tracedPath vector
    bfsTracedPath.clear();

    // Reset the visited status and other related properties for all nodes in the grid.
    for (auto row : grid) 
        for (auto node : row)
            node.Reset();

    // Nodes that need to be explored
    queue<Node*> openSet;
    // queue first in first out ~ somehwat opposite of stack

    // Push the starting node onto the queue 
    openSet.push(start);

    // Mark the start node as visited
    start->visited = true;

    // BFS loop until no more nodes left to explore.
    while (!openSet.empty()) 
    {
        // Get the next node to explore from the front of the queue.
        Node* current = openSet.front();

        // Remove the node from the queue as it is now being processed.
        openSet.pop();

        if (current == goal)
        {
            // Path found, reconstruct and return
            while (current != start)
            {
                // Add the node to the tracedPath
                bfsTracedPath.push_back(current);
                
                // Move to the parent of the current node to continue
                current = current->parent;
            }
            bfsTracedPath.push_back(start);

            // Print a message indicating that a path was found using BFS.
            cout << "Path found using BFS." << endl;
            return;
        }


        // Explore all the neighbors of the current node.
        for (Node* neighbor : GetNeighbors(current)) 
        {
            // Check if the neighbor has not been visited and is not blocked.
            if (!neighbor->visited && !neighbor->blocked)
            {
                // Mark the neighbor as visited
                neighbor->visited = true;

                // keep track of how far the node is from the start.
                neighbor->step = current->step + 1;

                // or path reconstruction later.
                neighbor->parent = current;

                // Add the neighbor to the queue for further exploration.
                openSet.push(neighbor);
            }
        }
    }

    // If the loop ends without finding the goal, print a message indicating no path was found.
    cout << "No path found using BFS." << endl;
}
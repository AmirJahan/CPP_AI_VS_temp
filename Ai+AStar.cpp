#include "Ai.h"
#include <queue>
#include <unordered_map>
#include <vector>
#include <functional>

/*
    AStar Search ~ The Efficient Explorer ~ The Smart Navigator
    Not only do you explore the maze like Dijkstra, keeping track of the easiest paths,
    but also how close you are to target. Balancing between how far you’ve gone 
    and how close you think you are to the exit.

    Having a map and a compass, you can find the best path to the exit.


    Summary
        •	DFS is like diving deep into one path until you hit a dead end, then backtracking.
        •	BFS is like exploring all nearby paths step by step, making sure you find the shortest way.
        •	Dijkstra is like planning the easiest path, avoiding difficult spots.
        •	A* is like using both a map and a compass to find the quickest and easiest way to the exit.


    	A* is powerful and versatile when:
	•	You have a good heuristic.
	•	You want to balance cost and proximity to the goal.
	•	You need the optimal and most efficient solution.
	•	BFS is best when:
	•	You need the shortest path, and all moves have the same cost.
	•	You have a small grid or graph, and simplicity is key.
	•	DFS is useful when:
	•	You’re exploring deeply structured problems, like mazes, puzzles, or tree-like structures.
	•	Memory efficiency is a concern.
	•	Dijkstra is ideal when:
	•	You’re navigating weighted graphs and need to find the least costly path without needing a heuristic.
	•	A* is impractical because you can’t define a good heuristic.

*/


// this is all wrong. doesn't seem to be working
// camefrom servs o purpise. 

void Ai::AStarSearch(Node* start, Node* goal)
{
    // Clear the tracedPath vector
    astarTracedPath.clear();
    
    // Define the heuristic function inline using a lambda expression
    auto Heuristic = [](Node* a, Node* b) -> float
    {
        return abs(a->row - b->row) + abs(a->col - b->col); // Manhattan distance
    };

    // A lambda for comparing two Node* based on their fCost and, if those are equal, their hCost.
    auto Compare = [](Node* a, Node* b)
    {
        return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
    };

    // Priority queue to manage open nodes to explore
    priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);
    // a priority_queue provides constant time lookup 
    // for the largest (by default) or smallest element
    

    // Initialize gScore for all nodes
    for (auto& row : grid)
        for (auto& node : row)
            node.Reset();
            //gScore[&node] = INFINITY;

    start->gCost = 0;

    // gScore[start] = 0;


    start->hCost = Heuristic(start, goal); // Estimate heuristic from start to goal
    start->fCost = start->hCost; // Since gCost is 0, fCost is just the estimate heuristic initially
    // start->visited = true; // this will be handled in the loop

    openSet.push(start);

    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();
        current->visited = true; // Clear flag since it's being processed

        if (current == goal)
        {
            // Path found, reconstruct and return
            while (current != nullptr)
            {
                astarTracedPath.push_back(current);
                current = current->parent;
            }
            astarTracedPath.push_back(start);
            return;
        }

        for (Node* neighbor : GetNeighbors(current))
        {
            if (neighbor->blocked || neighbor->visited) // Skip blocked or visited nodes
                continue;

            float tentative_gScore = current->gCost + 1; // assuming a uniform cost of 1 for moving from the current node to the neighbor
            if (tentative_gScore < neighbor->gCost) // a cheaper path to this neighbor has been found
            {
                // cameFrom[neighbor] = current; // the best path to this neighbor (so far) comes through the current node
                neighbor->gCost = tentative_gScore;
                neighbor->hCost = Heuristic(neighbor, goal);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;


                neighbor->visited = true; // Set flag
                neighbor->step = current->step + 1; // Update the step count (how far the node is from the start)

                neighbor->parent = current; // Set the current node as the parent

                openSet.push(neighbor);
            }
        }
    }
}
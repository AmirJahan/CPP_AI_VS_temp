#include "Ai.h"
#include <vector>
#include <iostream>

using namespace std;

void Ai::Main()
{
    InitWindow(1000, 500, "AI in CPP");

    Start();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        UpdateAndDraw();

        EndDrawing();
    }

    CloseWindow();
}

Node* Ai::GetRandomNode ()
{
    int randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    int randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);

    while (grid[randRow][randCol].blocked || grid[randRow][randCol].selected)
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    }

    return &grid[randRow][randCol];
}

void Ai::Start()
{
    grid.clear();
    for (int row = 0; row < ROW_COUNT; row++)
    {
        float y = NODE_SIZE * row;
        vector<Node> rowNodes;
        for (int col = 0; col < COL_COUNT; col++)
        {
            float x = NODE_SIZE * col;
            Node node = { NODE_SIZE, row, col, Vector2{x, y}, DARKGRAY, LIGHTGRAY };
            rowNodes.push_back(node);
        }
        grid.push_back(rowNodes);
    }

    // Block Some
    int blockedCount = ROW_COUNT * COL_COUNT * 0.10; // 10%
    for (int i = 0; i < blockedCount; i++)
        GetRandomNode()->blocked = true;

    // choose a random home and dest from squares
    pointA = GetRandomNode();
    pointA->costText = "A";
    pointA->fillColor = GREEN;
    pointA->blocked = true;

    pointB = GetRandomNode();
    pointB->costText = "B";
    pointB->fillColor = BLUE;
    pointB->selected = true;

    
    
    // DFS(pointA, pointB);
    // BFS(pointA, pointB);
    // Dijkstra (pointA, pointB);
    AStarSearch(pointA, pointB);
}

void Ai::UpdateAndDraw()
{
    for (int i = 0; i < (int)(grid.size()); i++)
        for (int j = 0; j < (int)(grid[i].size()); j++)
            grid[i][j].Draw();

    // Draw DFS Traced Path
    for (Node* node : dfsTracedPath)
        node->DrawPath(dfsColor);
        
    // Draw BSF Traced Path
    for (Node* node : bfsTracedPath)
        node->DrawPath( bfsColor );

    // Draw Dijkstra Traced Path
    for (Node* node : dijkstraTracedPath)
        node->DrawPath(dijkstraColor);

    // Draw A* Traced Path
    for (Node* node : astarTracedPath)
        node->DrawPath(astarColor);

        // Check if the "R" key is pressed
    if (IsKeyPressed(KEY_R)) { Start(); } // RESTART

    // draw home and dest. Reset 
    pointA->step = -1; pointA->Draw();
    pointB->step = -1; pointB->Draw();
}
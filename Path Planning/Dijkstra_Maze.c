#include <stdio.h>
#include <stdlib.h> // Include this header for the abs function
#include <limits.h>

#define ROW 5
#define COL 5

// Structure to represent a cell in the maze
struct Cell {
    int row, col;
};

// Structure to represent a node in the graph
struct Node {
    struct Cell cell;
    int distance;
};

// Function to check if a cell is valid (within the maze bounds)
int isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Function to check if a cell is not blocked (obstacle-free)
int isUnBlocked(int maze[][COL], int row, int col) {
    return maze[row][col] == 1;
}

// Function to check if a cell is destination
int isDestination(struct Cell cell, struct Cell dest) {
    return cell.row == dest.row && cell.col == dest.col;
}

// Function to calculate the distance between two cells
int calculateDistance(struct Cell src, struct Cell dest) {
    return abs(src.row - dest.row) + abs(src.col - dest.col);
}

// Function to find the shortest path in the maze using Dijkstra's algorithm
void dijkstra(int maze[][COL], struct Cell src, struct Cell dest) {
    // Array to store shortest distance from source to all cells
    int dist[ROW][COL];

    // Boolean array to track visited cells
    int visited[ROW][COL];

    // Initialize dist and visited arrays
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            dist[i][j] = INT_MAX;
            visited[i][j] = 0;
        }
    }

    // Distance of source cell from itself is 0
    dist[src.row][src.col] = 0;

    // Array to store previous cell in the shortest path
    struct Cell parent[ROW][COL];

    // Set parent of source cell to (-1, -1)
    parent[src.row][src.col].row = -1;
    parent[src.row][src.col].col = -1;

    // Find shortest path
    for (int count = 0; count < ROW*COL-1; count++) {
        int minDistance = INT_MAX;
        struct Cell currentCell;

        // Find the cell with minimum distance
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (!visited[i][j] && dist[i][j] < minDistance) {
                    minDistance = dist[i][j];
                    currentCell.row = i;
                    currentCell.col = j;
                }
            }
        }

        // Mark the selected cell as visited
        visited[currentCell.row][currentCell.col] = 1;

        // Update distances of adjacent cells
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (isValid(currentCell.row + i, currentCell.col + j) &&
                    isUnBlocked(maze, currentCell.row + i, currentCell.col + j)) {
                    int newDist = dist[currentCell.row][currentCell.col] + 1;
                    if (newDist < dist[currentCell.row + i][currentCell.col + j]) {
                        dist[currentCell.row + i][currentCell.col + j] = newDist;
                        parent[currentCell.row + i][currentCell.col + j] = currentCell;
                    }
                }
            }
        }
    }

    // Print the shortest path
    if (dist[dest.row][dest.col] != INT_MAX) {
        printf("Shortest Path Length: %d\n", dist[dest.row][dest.col]);

        // Print path from destination to source
        printf("Path: ");
        struct Cell current = dest;
        while (!(current.row == src.row && current.col == src.col)) {
            printf("(%d,%d) <- ", current.row, current.col);
            current = parent[current.row][current.col];
        }
        printf("(%d,%d)\n", src.row, src.col);
    } else {
        printf("Destination not reachable!\n");
    }
}

int main() {
    int maze[ROW][COL] = {
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 1},
        {1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}
    };

    struct Cell src = {0, 0};
    struct Cell dest = {4, 4};

    dijkstra(maze, src, dest);

    return 0;
}

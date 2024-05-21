#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ROWS 5
#define COLS 5

// Structure to represent a node in the graph
typedef struct Node {
    int x, y;               // Coordinates of the node
    struct Node* next;      // Pointer to the next node in the adjacency list
} Node;

// Structure to represent the graph
typedef struct Graph {
    Node* vertices[ROWS][COLS]; // Adjacency list for each vertex in the grid
} Graph;

// Structure to represent a cell in the grid
typedef struct Cell {
    int x, y;               // Coordinates of the cell
    struct Cell* parent;    // Pointer to the parent cell
    double g;               // Cost from the start node to this cell
    double h;               // Heuristic cost from this cell to the goal node
    double f;               // Total cost (g + h)
    bool closed;            // Flag to indicate if the cell is closed (visited)
} Cell;

// Function to initialize the graph
Graph* initializeGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    // Initialize all vertices with NULL adjacency lists
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            graph->vertices[i][j] = NULL;
        }
    }
    return graph;
}

// Function to add an edge between two nodes (representing movements)
void addEdge(Graph* graph, int x1, int y1, int x2, int y2) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x2;
    newNode->y = y2;
    newNode->next = graph->vertices[x1][y1];
    graph->vertices[x1][y1] = newNode;
}

// Function to add obstacles to the graph
void addObstacle(Graph* graph, int x, int y) {
    // Simply remove the vertex from the adjacency list
    Node* temp = graph->vertices[x][y];
    while (temp != NULL) {
        Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    graph->vertices[x][y] = NULL;
}

// Function to set the start and goal nodes
void setStartAndGoal(Graph* graph, int startX, int startY, int goalX, int goalY) {
    // We don't need to modify the graph for this, just store the coordinates
    printf("Start node: (%d, %d)\n", startX, startY);
    printf("Goal node: (%d, %d)\n", goalX, goalY);
}

// Function to print the graph for visualization
void printGraph(Graph* graph) {
    printf("Graph:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("(%d, %d): ", i, j);
            Node* temp = graph->vertices[i][j];
            while (temp != NULL) {
                printf("(%d, %d) -> ", temp->x, temp->y);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

// Function to print the grid with markers including path
void printGridWithMarkers(int startX, int startY, int goalX, int goalY, int obstacles[ROWS][COLS], Cell* path) {
    printf("Grid with Markers:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            bool isPath = false;
            Cell* current = path;
            while (current != NULL) {
                if (current->x == i && current->y == j) {
                    isPath = true;
                    break;
                }
                current = current->parent;
            }
            if (isPath) {
                printf("P "); // Path marker
            } else if (i == startX && j == startY) {
                printf("S "); // Start node marker
            } else if (i == goalX && j == goalY) {
                printf("G "); // Goal node marker
            } else if (obstacles[i][j] == 1) {
                printf("# "); // Obstacle marker
            } else {
                printf(". "); // Empty space
            }
        }
        printf("\n");
    }
}

// Function to calculate the Manhattan distance heuristic
double manhattanDistance(int x1, int y1, int x2, int y2) {
    return fabs(x1 - x2) + fabs(y1 - y2);
}








int main() {
    // Initialize the graph
    Graph* graph = initializeGraph();

    // Add edges representing possible movements (up, down, left, right)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i > 0) addEdge(graph, i, j, i - 1, j); // Up
            if (i < ROWS - 1) addEdge(graph, i, j, i + 1, j); // Down
            if (j > 0) addEdge(graph, i, j, i, j - 1); // Left
            if (j < COLS - 1) addEdge(graph, i, j, i, j + 1); // Right
        }
    }

    // Add obstacles
    int obstacles[ROWS][COLS] = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    addObstacle(graph, 1, 2);
    addObstacle(graph, 3, 3);

    // Set start and goal nodes
    int startX = 0, startY = 0;
    int goalX = 4, goalY = 4;

    // Print the grid with markers
    printGridWithMarkers(startX, startY, goalX, goalY, obstacles, NULL);

    // Find and visualize the shortest path using A* algorithm
   //mory for the graph
    // ...

    // Print the graph for visualization
    printGraph(graph);

    // Free memory for the graph
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            Node* temp = graph->vertices[i][j];
            while (temp != NULL) {
                Node* nextNode = temp->next;
                free(temp);
                temp = nextNode;
            }
        }
    }
    free(graph);

    return 0;
}



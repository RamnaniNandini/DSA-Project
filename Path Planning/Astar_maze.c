#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ARENA_WIDTH 800
#define ARENA_HEIGHT 600

typedef struct {
    int x;
    int y;
} Point;

typedef struct Node {
    struct Node* parent;
    int x, y;
    int g, f;
} Node;

// Function to calculate Manhattan distance heuristic
int heuristic(Point current, Point goal) {
    return abs(current.x - goal.x) + abs(current.y - goal.y);
}

// Function to check if a point is within the bounds of the arena
bool is_within_bounds(Point point) {
    return (point.x >= 0 && point.x < ARENA_WIDTH && point.y >= 0 && point.y < ARENA_HEIGHT);
}

// Function to check if a point is an obstacle
bool is_obstacle(Point point) {
    return (point.x >= 100 && point.x <= 200 && point.y >= 100 && point.y <= 200);
}

// Function to print path
void print_path(Node* goal_node) {
    if (goal_node == NULL) {
        printf("No path found.\n");
        return;
    }
    Node* current = goal_node;
    while (current != NULL) {
        printf("(%d, %d) -> ", current->x, current->y);
        current = current->parent;
    }
    printf("Start\n");
}

Node* astar(int m[5][5], int sx, int sy, int ex, int ey) {
    int w = 10, h = 10;
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = NULL;
    node->x = sx;
    node->y = sy;
    node->g = 0;
    node->f = abs(ex - sx) + abs(ey - sy);
    
    Node* closeList = node;
    Node* createdList[w * h];
    for (int i = 0; i < w * h; i++) {
        createdList[i] = NULL;
    }
    createdList[sy * w + sx] = node;
    
    while (closeList != NULL) {
        node = closeList;
        closeList = closeList->parent;
        int x = node->x;
        int y = node->y;
        int l = node->g + 1;
        
        Node* neighbours[4];
        neighbours[0] = (Node*)malloc(sizeof(Node));
        neighbours[0]->x = x;
        neighbours[0]->y = y + 1;
        neighbours[1] = (Node*)malloc(sizeof(Node));
        neighbours[1]->x = x;
        neighbours[1]->y = y - 1;
        neighbours[2] = (Node*)malloc(sizeof(Node));
        neighbours[2]->x = x + 1;
        neighbours[2]->y = y;
        neighbours[3] = (Node*)malloc(sizeof(Node));
        neighbours[3]->x = x - 1;
        neighbours[3]->y = y;
        
        for (int i = 0; i < 4; i++) {
            int nx = neighbours[i]->x;
            int ny = neighbours[i]->y;
            
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && m[ny][nx] == 0) {
                if (createdList[ny * w + nx] == NULL) {
                    Node* nn = (Node*)malloc(sizeof(Node));
                    nn->parent = node;
                    nn->x = nx;
                    nn->y = ny;
                    nn->g = l;
                    nn->f = l + abs(nx - ex) + abs(ny - ey);
                    createdList[ny * w + nx] = nn;
                    
                    if (nx == ex && ny == ey) {
                        return nn;
                    }
                    
                    // Add to closeList if not already there
                    nn->parent = closeList;
                    closeList = nn;
                } else {
                    // Update existing node if this path is shorter
                    Node* existingNode = createdList[ny * w + nx];
                    if (l < existingNode->g) {
                        existingNode->g = l;
                        existingNode->f = l + abs(nx - ex) + abs(ny - ey);
                        existingNode->parent = node;
                    }
                }
            }
            free(neighbours[i]);
        }
    }
    return NULL;
}

int main() {
    Point start = {0, 0}; // Starting point
    Point goal = {4, 4}; // Goal point

    printf("Start: (%d, %d)\n", start.x, start.y);
    printf("Goal: (%d, %d)\n", goal.x, goal.y);

    // Create a map (0 for unblocked, 1 for blocked)
    int map[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };

    Node* goal_node = astar(map, start.x, start.y, goal.x, goal.y);
    printf("Path: ");
    print_path(goal_node);

    return 0;
}

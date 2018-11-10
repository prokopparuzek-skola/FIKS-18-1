#include <stdio.h>
#include <stdlib.h>
#include "bludiste.h"
#define ROUTE 'X'

blud storeBlud(void);
int kroky(blud);
void printBlud(blud);
bod *availableSteps(bod);
bod storeStep(int x, int y);
bod *noWalls(blud *maze, bod *steps);
int makeStep(blud *maze, queue* stack);
int solve(blud maze);
bod *findRoute(queue *stack);
int drawRoute(int length, blud *maze, bod *route);

int main() {
    blud maze = storeBlud();
    printBlud(maze);
    solve(maze);
}

int solve(blud maze) {
   int sizeQ = 128;
   queue stack = {0, 0, sizeQ, NULL};
   stack.stepQueue = calloc(sizeQ, sizeof(step));
   stack.stepQueue[0].where.x = 0;
   stack.stepQueue[0].where.y = 0;
   stack.stepQueue[0].depth = 0;
   stack.stepQueue[0].parent = 0;
   int count;
   while ((count = makeStep(&maze, &stack)) == -1);
   printf("%d\n",count);
   drawRoute(stack.stepQueue[count].depth, &maze, findRoute(&stack));
   printBlud(maze);
}

int makeStep(blud *maze, queue* stack) {
    int i, j, r = stack->right;
    bod *steps;
    for (i = stack->left; i <= stack->right; i++) {
        steps = noWalls(maze, availableSteps(stack->stepQueue[i].where));
        for (j = 0; j < 4; j++) {
            if (steps[j].x == -1) continue;
            else {
                r++;
                if (r >= stack->size){
                    stack->stepQueue = realloc(stack->stepQueue, stack->size * 2 * sizeof(step));
                    stack->size *= 2;
                }
                stack->stepQueue[r].where.x = steps[j].x;
                stack->stepQueue[r].where.y = steps[j].y;
                stack->stepQueue[r].depth = stack->stepQueue[stack->left].depth ? stack->stepQueue[stack->left].depth + 1 : 1;
                stack->stepQueue[r].parent = i;
                if (steps[j].x == (maze->x - 1) && steps[j].y == (maze-> y - 1)){
                    stack->left = stack->right + 1;
                    stack->right = r;
                    free(steps);
                    return r;
                }
            }
        }
    }
    stack->left = stack->right + 1;
    stack->right = r;
    free(steps);
    return -1;
}

bod *findRoute(queue *stack) {
    int r = stack->right;
    int d = stack->stepQueue[r].depth + 1;
    int i = d - 1;
    bod *steps = malloc(d * sizeof(bod));
    for (; i >= 0; i--) {
        steps[i] = storeStep(stack->stepQueue[r].where.x, stack->stepQueue[r].where.y);
        r = stack->stepQueue[r].parent;
    }
    return steps;
}

int drawRoute(int length, blud *maze, bod *route) {
    int i;
    for (i = 0; i <= length; i++) {
        maze->bludiste[route[i].x * maze->x + route[i].y] = ROUTE;
    }
    free(route);
    return length + 1;
}

blud storeBlud() {
    int i, j;
    blud maze = {NULL, 0, 0};
    scanf("%d %d\n", &maze.x, &maze.y);
    maze.bludiste = malloc(maze.x * maze.y);
    for (i = 0; i < maze.y; i++) {
        for (j = 0; j < maze.x; j++) {
            scanf(" %c", maze.bludiste + (i * maze.y + j));
        }
    }
    return maze;
}

void printBlud(blud maze) {
    int i, j;
    for (i = 0; i < maze.y; i++) {
        for (j = 0; j < maze.x; j++) {
            putchar(*(maze.bludiste + (i * maze.y + j)));
        }
        putchar('\n');
    }
}

bod *availableSteps(bod where) {
    bod *steps = malloc(sizeof(bod) * 4);
    steps[0] = storeStep(where.x, where.y - 1);
    steps[1] = storeStep(where.x + 1, where.y);
    steps[2] = storeStep(where.x, where.y + 1);
    steps[3] = storeStep(where.x - 1, where.y);
    return steps;
}

bod *noWalls(blud *maze, bod *steps) {
    int i;
    for (i = 0; i < 4; i++) {
        if (steps[i].x < 0 || steps[i].y < 0 || steps[i].x >= maze->x || steps[i].y >= maze-> y) {
            (steps + i)->x = -1;
            (steps + i)->y = -1;
            continue;
        }
        if (*(maze->bludiste + steps[i].y + steps[i].x * maze->x) == WALL) {
            (steps + i)->x = -1;
            (steps + i)->y = -1;
        }
    }
    return steps;
}

bod storeStep(int x, int y) {
    bod s;
    s.x = x;
    s.y = y;
    return s;
}

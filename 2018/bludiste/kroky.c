#include <stdio.h>
#include <stdlib.h>
#include "bludiste.h"
#include "bludiste.h"

blud storeBlud(void);
int kroky(blud);
void printBlud(blud);
bod *availableSteps(bod);
bod storeStep(int x, int y);

int main() {
//   printf("%d\n", kroky(storeBlud()));
    printBlud(storeBlud());
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

int kroky(blud maze) {
    queue steps = {0, 0, 128, NULL};
    steps.stepQueue = malloc(sizeof(step) * steps.size);

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
    steps[0] = storeStep(where.x, where.y -1);
    steps[1] = storeStep(where.x + where.x, where.y);
    steps[2] = storeStep(where.x, where.y +1);
    steps[3] = storeStep(where.x -1, where.y);
    return steps;
}

bod *noWalls(blud *maze, bod *steps) {
    int i;
    for (i = 0; i < 4; i++) {
        if (steps[i].x < 0 || steps[i].y < 0) {
            (steps + i)->x = -1;
            (steps + i)->y = -1;
            continue;
        }
        if (*(maze->bludiste + steps[i].y * maze->y + steps[i].x) == WALL) {
            (steps + i)->x = -1;
            (steps + i)->y = -1;
        }
    }
}

bod storeStep(int x, int y) {
    bod s;
    s.x = x;
    s.y = y;
    return s;
}

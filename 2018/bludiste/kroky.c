#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bludiste.h"

int solve(blud *maze) {
    buffer_t queue = {maze->size_x, maze->size_y, NULL};
    step* buffer = malloc(sizeof(step) * maze->size_x * maze->size_y);

    if (buffer == NULL) {
        puts("Málo paměti");
        exit(1);
    }
    initBuff(&queue);

    while (queue.buff[(queue.size_x - 1) * (queue.size_y - 1)].depth == -1) {
        makeStep(&queue);
    }
    printBlud(*maze);
    free(buffer);

    return queue.buff[(queue.size_x - 1) * (queue.size_y - 1)].depth + 1;
}

void initBuff(buffer_t *buff) {
    int i, j;

    for (i = 0; i < buff->size_y; i++) {
        for (j = 0; j < buff->size_x; j++) {
            buff->buff[i * buff->size_x + j].depth = -1;
            buff->buff[i * buff->size_x + j].parent = -1;
        }
    }
}

void makeStep(buffer_t *queue) {

}

blud storeBlud(void) {
    int i, j;
    blud maze = {NULL, 0, 0};

    scanf("%d %d\n", &maze.size_y, &maze.size_x);
    maze.bludiste = malloc(maze.size_x * maze.size_y);

    for (i = 0; i < maze.size_y; i++) {
        for (j = 0; j < maze.size_x; j++) {
            scanf(" %c", (maze.bludiste + (i * maze.size_x + j)));
        }
    }

    return maze;
}

void printBlud(blud maze) {
    int i, j;

    for (i = 0; i < maze.size_y; i++) {
        for (j = 0; j < maze.size_x; j++) {
            putchar(*(maze.bludiste + (i * maze.size_x + j)));
        }
        putchar('\n');
    }
}

int main() {
    blud maze = storeBlud();

    printBlud(maze);
    solve(&maze);
    free(maze.bludiste);

    return 0;
}

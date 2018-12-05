#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bludiste.h"

int solve(blud *maze) {
    buffer_t queue = {maze->size_x, maze->size_y, 0, 0, NULL, NULL, NULL};
    queue.buff = malloc(sizeof(step) * maze->size_x * maze->size_y);
    queue.stackAc = malloc(sizeof(unsigned) * maze->size_x * maze->size_y);
    queue.stackFu = malloc(sizeof(unsigned) * maze->size_x * maze->size_y);

    if (queue.buff == NULL || queue.stackAc == NULL || queue.stackFu == NULL) {
        puts("Málo paměti");
        exit(1);
    }
    initBuff(&queue);
    initStack(&queue);
    queue.stackAc[0] = 0;

    while (queue.buff[(queue.size_x * queue.size_y) - 1].depth == -1) {
        makeStep(&queue, maze);
    }
    printBlud(maze);

    free(queue.buff);
    free(queue.stackAc);
    free(queue.stackFu);

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

void initStack (buffer_t *buff) {
    int i;

    for (i = 0; i < buff->size_x * buff->size_y; i++) {
        buff->stackAc[i] = -1;
        buff->stackFu[i] = -1;
    }
}

void initStackFu (buffer_t *buff) {
    int i;

    for (i = 0; i < buff->size_x * buff->size_y; i++) {
        buff->stackFu[i] = -1;
    }
}

void makeSteps(buffer_t *queue, blud *maze) {
    int i, *swap;

    for (i = 0; i <= queue->indexAc; i++) {
        solveStep(queue, maze, i);
    }
    swap = queue->stackAc;
    queue->stackAc = queue->stackFu;
    queue->stackAc = swap;
    initStackFu(queue);
}

void solveStep(buffer_t *queue, blud *maze, int index) {
    int steps[4] = {0, 0, 0, 0};
    int i;

    steps[0] = queue->stackAc[index] - queue->size_x;
    steps[1] = queue->stackAc[index] + 1;
    steps[2] = queue->stackAc[index] + queue->size_x;
    steps[3] = queue->stackAc[index] - 1;
    for (i = 0; i < 4; i++) { // Vyhození nepotřebných dat
        if (steps[i] < 0 || steps[i] >= queue->size_x * queue->size_y){ //Kontrola mezí pole
            DISCARD;
        }
        if (maze->bludiste[i] == WALL) { // Kontrola zdí
            DISCARD;
        }
        if ((queue->buff[queue->stackAc[index]].depth + 1) >= queue->buff[steps[i]].depth && queue->buff[steps[i]].depth != -1) { // Už jsem tam byl
            DISCARD;
        }
    }
    for (i = 0; i < 4; i++) {
        if (steps[i] == -1) {
            continue;
        }
        queue->indexFu++; // zvyš index příštích budů o 1
        queue->stackFu[queue->indexFu] = steps[i]; // ulož tam aktuální bod
        queue->buff[steps[i]].depth = queue->buff[queue->stackAc[index]].depth + 1; // ulož do něj hloubku
        queue->buff[steps[i]].parent = queue->stackAc[index]; // a rodiče
    }
}

blud storeBlud(void) {
    int i;
    blud maze = {NULL, 0, 0};

    scanf("%d %d\n", &maze.size_y, &maze.size_x);
    maze.bludiste = malloc(maze.size_x * maze.size_y);

    for (i = 0; i < maze.size_y * maze.size_x; i++) {
        scanf(" %c", &maze.bludiste[i]);
    }

    return maze;
}

void printBlud(blud *maze) {
    int i, j;

    for (i = 0; i < maze->size_y; i++) {
        for (j = 0; j < maze->size_x; j++) {
            putchar(*(maze->bludiste + (i * maze->size_x + j)));
        }
        putchar('\n');
    }
}

int main() {
    blud maze = storeBlud();

    printBlud(&maze);
    solve(&maze);

    free(maze.bludiste);

    return 0;
}

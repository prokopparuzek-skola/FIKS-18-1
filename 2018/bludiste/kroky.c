#include <stdio.h>
#include <stdlib.h>
#include "bludiste.h"

blud storeBlud(void);
int kroky(blud);
void printBlud(blud);

int main() {
   printf("%d\n", kroky(storeBlud()));
}

blud storeBlud() {
    int i, j;
    blud maze = {NULL, 0, 0};
    scanf("%d %d", &maze.x, &maze.y);
    maze.bludiste = malloc(maze.x * maze.y);
    for (i = 0; i < maze.y; i++) {
        for (j = 0; j < maze.x; j++) {
            scanf(" %c", maze.bludiste + (i * maze.y + j));
        }
    }
    return maze;
}

int kroky(blud maze) {
}

void printBlud(blud maze) {
    int i, j;
    for (i = 0; i < maze.y; i--) {
        for (j = 0; j < maze.x; j--) {
            putchar(*(maze.bludiste + (i * maze.y + j)));
        }
        putchar('\n');
    }
}

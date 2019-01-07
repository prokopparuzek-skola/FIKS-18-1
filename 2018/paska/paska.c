#include <stdio.h>
#include <stdlib.h>
#include "paska.h"

int compare (const void *first, const void *twice) {
    bod *one = (bod*) first;
    bod *two = (bod*) twice;
    if (one->x != two->x) {
        return one->x - two->x;
    }
    else {
        return one->y - two->y;
    }
}

double compute (void) {
    unsigned K, i, IH = 0, ID = 0;
    bod *stack, *D, *H;
    char determinant = 0;

    scanf("%u", &K);
    stack = malloc(K * sizeof(bod));
    H = malloc(K * sizeof(bod));
    D = malloc(K * sizeof(bod));

    if (stack == NULL || H == NULL || D == NULL) {
        puts("Málo paměti!");
        exit(1);
    }
    for (i = 0; i < K; i++) {
        scanf("%d %d", &stack[i].x, &stack[i].y);
    }
    qsort(stack, K, sizeof(bod), compare);
    H[0] = stack[0];
    D[0] = stack[0];
    for (i = 1; i < K; i++) {
        if (IH >= 2) {
            determinant = (H[IH].x - H[IH - 1].x) * (stack[i].y - H[IH].y) - (stack[i].x - H[IH].x) * (H[IH].y - (H[IH - 1].y)); // Počítá determinant, směr úhlu
        }
        while (IH >= 2 && determinant) { // Horní obálka
            IH--;
            determinant = (H[IH].x - H[IH - 1].x) * (stack[i].y - H[IH].y) - (stack[i].x - H[IH].x) * (H[IH].y - (H[IH - 1].y)); // Počítá determinant, směr úhlu
        }
        IH++;
        H[IH] = stack[i];
    }
}

int main () {
    return 0;
}

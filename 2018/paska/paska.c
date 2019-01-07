#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "paska.h"

static int compare (const void *first, const void *twice) {
    bod *one = (bod*) first;
    bod *two = (bod*) twice;
    if (one->x != two->x) {
        return one->x - two->x;
    }
    else {
        return one->y - two->y;
    }
}

double compute (bod *stack, unsigned IndexStack) {
    double sum = 0;
    for (; IndexStack != 0; IndexStack--) {
       sum += sqrt(pow(abs(stack[IndexStack].x - stack[IndexStack - 1].x), 2) + pow(abs(stack[IndexStack].y - stack[IndexStack - 1].y), 2));  // Pythagoras
    }
    return sum;
}

bod* set (envelop *obalky) {
    bod *stack;
    int i, IndexStack = 0;

    stack = malloc(sizeof(bod) * (obalky->IndexDolni + obalky->IndexHorni + 1));
    if (stack == NULL) {
        puts("Málo paměti!");
        exit(1);
    }
    for (i = 0; i <= obalky->IndexHorni; i++) {
        stack[IndexStack] = obalky->Horni[i];
        IndexStack++;
    }
    for (i = obalky->IndexDolni - 1; i >= 0; i--) {
        stack[IndexStack] = obalky->Dolni[i];
        IndexStack++;
    }
    free(obalky->Horni);
    free(obalky->Dolni);
    return stack;
}

magazine points (bod *stack, unsigned K) {
    unsigned i, IndexHorni = 0, IndexDolni = 0;
    bod *Dolni, *Horni;
    int determinant = 0;
    envelop obalky;
    magazine Stack;

    Horni =  malloc(K * sizeof(bod));
    Dolni = malloc(K * sizeof(bod));

    if (Horni == NULL || Dolni == NULL) {
        puts("Málo paměti!");
        exit(1);
    }

    qsort(stack, K, sizeof(bod), compare);
    Horni[0] = stack[0];
    Dolni[0] = stack[0];

    for (i = 1; i < K; i++) {
        if (IndexHorni >= 1) { // Horní obálka
            determinant = (Horni[IndexHorni].x - Horni[IndexHorni - 1].x) * (stack[i].y - Horni[IndexHorni].y) - (stack[i].x - Horni[IndexHorni].x) * (Horni[IndexHorni].y - (Horni[IndexHorni - 1].y)); // Počítá determinant, směr úhlu
        }
        while (IndexHorni >= 1 && determinant >= 0) {
            IndexHorni--;
            if (IndexHorni >= 1) {
                determinant = (Horni[IndexHorni].x - Horni[IndexHorni - 1].x) * (stack[i].y - Horni[IndexHorni].y) - (stack[i].x - Horni[IndexHorni].x) * (Horni[IndexHorni].y - (Horni[IndexHorni - 1].y)); // Počítá determinant, směr úhlu
            }
        }
        IndexHorni++;
        Horni[IndexHorni] = stack[i];

        if (IndexDolni >= 1) { // Dolní obálka
            determinant = (Dolni[IndexDolni].x - Dolni[IndexDolni - 1].x) * (stack[i].y - Dolni[IndexDolni].y) - (stack[i].x - Dolni[IndexDolni].x) * (Dolni[IndexDolni].y - (Dolni[IndexDolni - 1].y)); // Počítá determinant, směr úhlu
        }
        while (IndexDolni >= 1 && determinant <= 0) {
            IndexDolni--;
            if (IndexDolni >= 1) {
                determinant = (Dolni[IndexDolni].x - Dolni[IndexDolni - 1].x) * (stack[i].y - Dolni[IndexDolni].y) - (stack[i].x - Dolni[IndexDolni].x) * (Dolni[IndexDolni].y - (Dolni[IndexDolni - 1].y)); // Počítá determinant, směr úhlu
            }
        }
        IndexDolni++;
        Dolni[IndexDolni] = stack[i];
    }

//    puts("Horni");
//    for (i = 0; i <= IndexHorni; i++)
//        printf("%d %d\n", Horni[i].x, Horni[i].y);
//    puts("Dolni");
//    for (i = 0; i <= IndexDolni; i++)
//        printf("%d %d\n", Dolni[i].x, Dolni[i].y);
    obalky.IndexHorni = IndexHorni;
    obalky.IndexDolni = IndexDolni;
    obalky.Horni = Horni;
    obalky.Dolni = Dolni;
    stack = set(&obalky);
    Stack.stack = stack;
    Stack.Index = IndexDolni +  IndexHorni;
    return Stack;
}

int main () {
    unsigned i, j, N, K, SizeStack = 32, IndexStack = 0;
    bod *stack;
    magazine Stack;

    stack = malloc(sizeof(bod) * BLOCK);
    if (stack == NULL) {
        puts("Málo paměti!");
        exit(1);
    }

    scanf("%u", &N);
    for (i = 0; i < N; i++) {
        scanf("%u", &K);
        if ((IndexStack + K) > SizeStack) {
            stack = realloc(stack, sizeof(bod) * SizeStack + BLOCK);
            SizeStack += BLOCK;
            if (stack == NULL) {
                puts("Málo paměti!");
                exit(1);
            }
        }
        for (j = 0; j < K; j++) {
            scanf("%d %d", &stack[IndexStack + j].x, &stack[IndexStack + j].y);
        }
        IndexStack += K;
    }
    Stack = points(stack, IndexStack);
    printf("%.2lf\n", compute (Stack.stack, Stack.Index));
    free(stack);
    free(Stack.stack);
    return 0;
}

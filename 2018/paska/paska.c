#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "paska.h"

static int compare (const void *first, const void *twice) { // Porovnává body
    bod *one = (bod*) first;
    bod *two = (bod*) twice;
    if (one->x != two->x) {
        return one->x - two->x;
    }
    else {
        return one->y - two->y;
    }
}

double compute (bod *stack, unsigned IndexStack) { // Počítá vzdálenost mezi body pomocí pythagorovy věty
    double sum = 0;
    for (; IndexStack != 0; IndexStack--) {
       sum += sqrt(pow(abs(stack[IndexStack].x - stack[IndexStack - 1].x), 2) + pow(abs(stack[IndexStack].y - stack[IndexStack - 1].y), 2));  // Pythagoras
    }
    return sum;
}

bod* set (envelop *obalky) { // Každý bod pouze jednou v pořadí jak jsou za sebou, 1 bod je 2 krát; Ze dvou obálk udělá jednu výslednou
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
    bod *Dolni, *Horni; // Ukazatele na body v dolní a horní obálce
    int determinant = 0; // sem přijde determinant (orientace úhlu)
    envelop obalky; // Obalky, parametr set()
    magazine Stack; // Návratová struktura

    Horni =  malloc(K * sizeof(bod));
    Dolni = malloc(K * sizeof(bod));

    if (Horni == NULL || Dolni == NULL) {
        puts("Málo paměti!");
        exit(1);
    }

    qsort(stack, K, sizeof(bod), compare); // Seřadí body dle velikosti, podle x, pak dle y
    Horni[0] = stack[0]; // Vloží 1. bod do obou obálek
    Dolni[0] = stack[0];

    for (i = 1; i < K; i++) { // Prochází postupně body
        if (IndexHorni >= 1) { // Horní obálka
            determinant = (Horni[IndexHorni].x - Horni[IndexHorni - 1].x) * (stack[i].y - Horni[IndexHorni].y) - (stack[i].x - Horni[IndexHorni].x) * (Horni[IndexHorni].y - (Horni[IndexHorni - 1].y)); // Počítá determinant, směr úhlu
        }
        while (IndexHorni >= 1 && determinant >= 0) { // Když je dost bodů a zárověn je úhel orientován doleva => odstraníme poslední bod co kazí obal
            IndexHorni--;
            if (IndexHorni >= 1) {
                determinant = (Horni[IndexHorni].x - Horni[IndexHorni - 1].x) * (stack[i].y - Horni[IndexHorni].y) - (stack[i].x - Horni[IndexHorni].x) * (Horni[IndexHorni].y - (Horni[IndexHorni - 1].y)); // Počítá determinant, směr úhlu
            }
        }
        IndexHorni++; // Přídám bod do horní obálky
        Horni[IndexHorni] = stack[i];

        if (IndexDolni >= 1) { // Dolní obálka
            determinant = (Dolni[IndexDolni].x - Dolni[IndexDolni - 1].x) * (stack[i].y - Dolni[IndexDolni].y) - (stack[i].x - Dolni[IndexDolni].x) * (Dolni[IndexDolni].y - (Dolni[IndexDolni - 1].y)); // Počítá determinant, směr úhlu
        }
        while (IndexDolni >= 1 && determinant <= 0) { // Když je dost bodů a zárověn je úhel orientován doleva => odstraníme poslední bod co kazí obal
            IndexDolni--;
            if (IndexDolni >= 1) {
                determinant = (Dolni[IndexDolni].x - Dolni[IndexDolni - 1].x) * (stack[i].y - Dolni[IndexDolni].y) - (stack[i].x - Dolni[IndexDolni].x) * (Dolni[IndexDolni].y - (Dolni[IndexDolni - 1].y)); // Počítá determinant, směr úhlu
            }
        }
        IndexDolni++; // Přidám bod do dolní obálky
        Dolni[IndexDolni] = stack[i];
    }

    obalky.IndexHorni = IndexHorni; // Načtu obálky do struktury
    obalky.IndexDolni = IndexDolni;
    obalky.Horni = Horni;
    obalky.Dolni = Dolni;
    stack = set(&obalky); // Odstraním přebytečné body
    Stack.stack = stack;
    Stack.Index = IndexDolni +  IndexHorni;
    return Stack; // Vrátím body na obalu
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
    for (i = 0; i < N; i++) { // Načítání bodů, nezajímají mě obrazce, pouze body
        scanf("%u", &K);
        if ((IndexStack + K) > SizeStack) { // alokace místa na body
            stack = realloc(stack, sizeof(bod) * SizeStack + BLOCK);
            SizeStack += BLOCK;
            if (stack == NULL) {
                puts("Málo paměti!");
                exit(1);
            }
        }
        for (j = 0; j < K; j++) {
            scanf("%d %d", &stack[IndexStack + j].x, &stack[IndexStack + j].y); // Načítá body
        }
        IndexStack += K;
    }
    Stack = points(stack, IndexStack); // Získání bodů na obalu
    printf("%.2lf\n", compute (Stack.stack, Stack.Index)); // Spočítání vzdálenosti a její vytištění s přesností na 2 desetiná místa
    free(stack);
    free(Stack.stack);
    return 0;
}

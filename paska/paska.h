#ifndef __PASKA
#define __PASKA
#define BLOCK 32

typedef struct {
    int x;
    int y;
} bod;
typedef struct { // Obsahuje obě obálky i s indexy
    unsigned IndexHorni;
    unsigned IndexDolni;
    bod *Horni;
    bod *Dolni;
} envelop;

typedef struct { // pouze 1 obálka
    unsigned Index;
    bod *stack;
} magazine;
static int compare (const void *first, const void *twice);
magazine points (bod*, unsigned); // Vrací body na obaly, 1 dvakrát
double compute (bod *stack, unsigned IndexStack); // Spočítá vzdálenosti mezi body, vrací výsledek
#endif /*__PASKA*/

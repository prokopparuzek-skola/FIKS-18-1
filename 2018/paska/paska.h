#ifndef __PASKA
#define __PASKA
#define BLOCK 32

typedef struct {
    int x;
    int y;
} bod;
typedef struct {
    unsigned IndexHorni;
    unsigned IndexDolni;
    bod *Horni;
    bod *Dolni;
} envelop;

typedef struct {
    unsigned Index;
    bod *stack;
} magazine;
static int compare (const void *first, const void *twice);
magazine points (bod*, unsigned);
double compute (bod *stack, unsigned IndexStack);
#endif /*__PASKA*/

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

static int compare (const void *first, const void *twice);
bod* points (bod*, unsigned);
double compute (bod *stack, unsigned IndexStack);
#endif /*__PASKA*/

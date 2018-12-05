#ifndef __BLUDISTE
#define __BLUDISTE

#define WALL '#'
#define CORIDOR '.'
#define ROUTE 'X'

#define DISCARD steps[i] = -1; continue

typedef struct {
    int depth;
    int parent;
} step;

typedef struct {
    int size_x;
    int size_y;
    int indexAc;
    int indexFu;
    step *buff;
    unsigned *stackAc;
    unsigned *stackFu;
} buffer_t;

typedef struct {
    char *bludiste;
    int size_x;
    int size_y;
} blud;

blud storeBlud(void);
void printBlud(blud*);
int solve(blud *maze);
void initBuff(buffer_t *buff);
void makeSteps(buffer_t *queue, blud*);
void solveStep(buffer_t *queue, blud *maze, int index);
unsigned findRoute(buffer_t *queue, blud *maze);
#endif /* __BLUDISTE */

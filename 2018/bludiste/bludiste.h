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
    int size_x;
    int size_y;
    char *bludiste;
} blud;

blud storeBlud(void);
void printBlud(blud*);
int solve(blud *maze);
void initBuff(buffer_t *buff);
void makeSteps(buffer_t *queue, blud*);
void solveStep(buffer_t *queue, blud *maze, int index);
unsigned findRoute(buffer_t *queue, blud *maze);
int addWall(blud *maze, unsigned*);
void makeMaze(unsigned size_x, unsigned size_y, unsigned lenght);
int addWallVertical(blud *maze, unsigned*);
void makeWall(blud *maze, unsigned*, int);
void makeWallVertical(blud *maze, unsigned *last, int);
#endif /* __BLUDISTE */

#ifndef __BLUDISTE
#define __BLUDISTE

#define WALL '#'
#define CORIDOR '.'
#define ROUTE 'X'

typedef struct {
    int x;
    int y;
} bod;

typedef struct {
    int depth;
    int parent;
} step;

typedef struct {
    int size_x;
    int size_y;
    step *buff;
    bod *stack;
} buffer_t;

typedef struct {
    char *bludiste;
    int size_x;
    int size_y;
} blud;

blud storeBlud(void);
void printBlud(blud*);
bod storeStep(int x, int y);
int solve(blud *maze);
void initBuff(buffer_t *buff);
void makeStep(buffer_t *queue);
void initStack (buffer_t *buff) {
#endif /* __BLUDISTE */

#ifndef BLUDISTE
#define BLUDISTE
#define WALL '#'
#define CORIDOR '.'
#define ROUTE 'X'

typedef struct {
    int x;
    int y;
} bod;
typedef struct {
    bod where;
    int depth;
    int parent;
} step;
typedef struct {
    int right;
    int left;
    int size;
    step *stepQueue;
} queue;
typedef struct {
    char *bludiste;
    int x;
    int y;
} blud;
#endif

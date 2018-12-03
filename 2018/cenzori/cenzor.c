#include<stdio.h>
#include<stdlib.h>

void spocti(unsigned int *ID, unsigned int B, unsigned int E);

 int main() {
    unsigned int T, N, Q, B, E, i;
    scanf("%d", &T);
    for (; T > 0; T--) {
        scanf("%d %d", &N, &Q);
        unsigned int *ID = malloc(sizeof(unsigned int) * N);
        for (i = 0; i < N; i++) {
            scanf("%u",ID + i);
        }
        for (; Q > 0; Q--) {
            scanf("%d %d", &B, &E);
            spocti(ID, B, E);
        }
        free(ID);
    }
    return 0;
 }

void spocti(unsigned int *ID, unsigned int B, unsigned int E) {
    int i;
    unsigned int min = ID[B], maxID = 0, maxI = B, XOR = ID[B];
    for (i = B; i <= E; i++) {
        if (ID[i] < min) {
            min = ID[i];
        }
    }
    printf("%u\n", min);
    for (i = B; i <= E; i++) {
        if (ID[i] > maxID) {
            maxID = ID[i];
            maxI = i;
        }
    }
    printf("%u\n", maxI);
    for (i = B + 1; i <= E; i++) {
        XOR ^= ID[i];
    }
    printf("%u\n", XOR);
}

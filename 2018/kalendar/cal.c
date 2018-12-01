#include<stdio.h>

#define MVR 15 //Měsíce v roce
#define DVT 9 //Dny v týdnu
#define PRM 3 //Přestupný měsíc
#define PRR 3 //Přestupný rok
#define VPR 100 //Výjimky z přestupného roku

void prepocti(unsigned int d, unsigned int m, unsigned int r);

int main() {
    unsigned int N, d, m, r, i;
    scanf("%u", &N);
    for (i = 0; i < N; i++) {
        scanf("%d %d %d", &d, &m, &r);
    }
    return 0;    
}

void prepocti(unsigned int d, unsigned int m, unsigned int r) {

}

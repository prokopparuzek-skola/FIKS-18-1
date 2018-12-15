#include<stdio.h>

#define MVR 15 //Měsíce v roce
#define DVT 9 //Dny v týdnu
#define PRM 3 //Přestupný měsíc
#define PRR 3 //Přestupný rok
#define VPR 100 //Výjimky z přestupného roku
#define DVR 350 // Dny v roce

#define PMGK 2 // Přestupný měsíc gregoriánský kalendář
#define PRGK 4 // Přestupný rok gregoriánský kalendář
#define VPRGK 100 // Výjimka z přestupného roku gregoriánský kalendář
#define DVRGK 365 // Dny v roce gregoriánský kalendář

static int DVMGK[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int DVMVK[] = {-1, 25, 21, 21, 24, 24, 25, 25, 21, 25, 24, 21, 24, 21, 24, 25};

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

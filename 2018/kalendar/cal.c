#include<stdio.h>

#define MVR 15 //Měsíce v roce
#define DVT 9 //Dny v týdnu
#define PRM 3 //Přestupný měsíc
#define PRR 3 //Přestupný rok
#define VPR 100 //Výjimky z přestupného roku
#define DVR 350 // Dny v roce
enum {SD = 20, SM = 8, SY = 1984};

#define MVRGK 12
#define PMGK 2 // Přestupný měsíc gregoriánský kalendář
#define PRGK 4 // Přestupný rok gregoriánský kalendář
#define VPRGK 100 // Výjimka z přestupného roku gregoriánský kalendář
#define VZVPRGK 400 // Výjimka z výjimky přestupného roku gregoriánský kalendář
#define DVRGK 365 // Dny v roce gregoriánský kalendář

static int DVMGK[] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Měsíce v roce 1 a poslední je prosinec
static int DVMVK[] = {-1, 25, 21, 21, 24, 24, 25, 25, 21, 25, 24, 21, 24, 21, 24, 25};

typedef struct {
    int day;
    int dayOfWeek;
    int month;
    int year;
} date;

void prepocti(date*);
int spoctiDny (date* from);

int main() {
    unsigned int N, i;
    date from;

    scanf("%u", &N);
    for (i = 0; i < N; i++) {
        scanf("%d %d %d", &from.day, &from.month, &from.year);
        prepocti(&from);
    }
    return 0;
}

void prepocti(date *from) {
    date to = {1, 1, 1, 1};
    printf("%d\n", spoctiDny(from));
}

int spoctiDny (date* from) {
    date buff = {from->day - SD, -1, from->month - SM, from->year - SY};
    int years, months, days = 0;
    unsigned i;

    for (; buff.year > 0; buff.year--) {
        years = buff.year + SY;
        if (!(years % PRGK) && (years % VPRGK) || !(years % VZVPRGK)) {
            days += DVRGK + 1;
        }
        else {
            days += DVRGK;
        }
    }
    for (; buff.month > 0; buff.month--) {
        months = buff.month + SM;
        days += DVMGK[months - 1];
    }
    if (buff.month < 0) {
        for (; buff.month < 0; buff.month++) {
            months = buff.month + SM;
            days -= DVMGK[months];
        }
    }
    days += buff.day;
    return days;
}

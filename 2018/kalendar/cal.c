#include <stdio.h>
#include "cal.h"

void prepocti(date *from) {
    date to = {1, 1, 1, 1};
    printf("%d\n", spoctiDny(from));
}

int spoctiDny (date* from) {
    date buff = {from->day - SD, -1, from->month - SM, from->year - SY};
    int years, months, days = 0;
    char prestupI = (!(from->year % PRGK) && (from->year % VPRGK) || !(from->year % VZVPRGK));
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
            if (prestupI && months == PMGK) days--;
        }
    }
    days += buff.day;
    prestupI = 0;
    return days;
}

int main() {
    unsigned int N, i;
    date from;

    //scanf("%u", &N);
    //for (i = 0; i < N; i++) {
    while (1) {
        scanf("%d %d %d", &from.day, &from.month, &from.year);
        prepocti(&from);
    }
    return 0;
}

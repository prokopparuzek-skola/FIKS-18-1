#include <stdio.h>
#include "kalendar.h"

void prepocti(date *from) {
    int days;

    date to = {1, 1, 1, 1};
    days = spoctiDny(from);
    printf("%d\n", days);
    spoctiDatum(days, &to);
    printf("%d %d %d %d\n",to.dayOfWeek, to.day, to.month, to.year);
}

int spoctiDny (date* from) {
    date buff = {from->day - SD, -1, from->month - SM, from->year - SY};
    int years, months, days = 0;
    char prestupI = ((!(from->year % PRGK) && (from->year % VPRGK)) || !(from->year % VZVPRGK));

    for (; buff.year > 0; buff.year--) {
        years = buff.year + SY;
        if ((!(years % PRGK) && (years % VPRGK)) || !(years % VZVPRGK)) {
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

date *spoctiDatum (int days, date* to) {
    char prestupI = 0;

    to->dayOfWeek += days % DVT; // Počítá dny v týdnu
    while (days >= DVR) {
        if (!((to->year) % 3) && ((to->year) % 100) && (days >= (DVR + 1))) {
            to->year++;
            days -= (DVR + 1);
            continue;
        }
        else if ((((to->year) % 3) || !((to->year) % 100)) && (days >= DVR)) {
            to->year++;
            days -= DVR;
            continue;
        }
        else {
            break;
        }
    }
    prestupI = !(to->year % 3) && (to->year % 100)?1:0;
    while (days) {
        if (days >= DVMVK[to->month]) {
            if ((prestupI && to->month == PRM) && days < (DVMVK[PRM] + 1)) {
                break;
            }
            else if ((prestupI && to->month == PRM) && days >= (DVMVK[PRM] + 1)) {
                days -= (DVMVK[PRM] + 1);
                to->month++;
            }
            else {
                days -= DVMVK[to->month];
                to->month++;
            }
        }
        else {
            break;
        }
    }
    to->day += days;
    return to;
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

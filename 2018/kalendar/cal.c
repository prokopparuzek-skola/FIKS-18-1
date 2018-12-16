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

int spoctiDny (date* from) { // Z gregoriánského data udělá počet dní od 20.8.1948
    date buff = {from->day - SD, -1, from->month - SM, from->year - SY}; // Inicializuje buffer zadané datum - počáteční
    int years, months, days = 0;
    char prestupI = ((!(from->year % PRGK) && (from->year % VPRGK)) || !(from->year % VZVPRGK)); // Je přestupný rok?

    for (; buff.year > 0; buff.year--) { // Přičte dny za roky
        years = buff.year + SY; // Vyrobí znovu zadané datum, nutné kvůli přestupným rokům
        if ((!(years % PRGK) && (years % VPRGK)) || !(years % VZVPRGK)) { // Je tento rok přestupný?
            days += DVRGK + 1;
        }
        else { // Není přestupný
            days += DVRGK;
        }
    }
    for (; buff.month > 0; buff.month--) { // Přičte, nebo odečte dny za měsíce
        months = buff.month + SM; // Znovu vyrobení původního měsíce, index do tabulky dní
        days += DVMGK[months - 1]; // Přičte počet dní v měsíci, za předchozí, ten již uběhl aktuální ještě ne
    }
    if (buff.month < 0) { // měsíce před srpnem
        for (; buff.month < 0; buff.month++) {
            months = buff.month + SM;
            days -= DVMGK[months];
            if (prestupI && months == PMGK) days--; // Pokud přestupný odečte den, rok se přidal celý i přestupným dnem
        }
    }
    days += buff.day; // přičte počet dní, může být záporný
    return days;
}

date *spoctiDatum (int days, date* to) { // Ze dní spočítá datum nového kalendáře
    char prestupI = 0;

    to->dayOfWeek += days % DVT; // Počítá dny v týdnu
    while (days >= DVR) { // Počítá roky
        if (!((to->year) % 3) && ((to->year) % 100) && (days >= (DVR + 1))) { //Pokud přestupný odečti den navíc
            to->year++;
            days -= (DVR + 1);
            continue;
        }
        else if ((((to->year) % 3) || !((to->year) % 100)) && (days >= DVR)) { // Jinak normálně
            to->year++;
            days -= DVR;
            continue;
        }
        else { // Pokud je málo dní, skonči
            break;
        }
    }
    prestupI = !(to->year % 3) && (to->year % 100)?1:0; // Byl poslední rok přestupný?
    while (days >= 0) { // Počítá měsíce
        if (days >= DVMVK[to->month]) { // Vejde se tam měsíc?
            if ((prestupI && to->month == PRM) && days < (DVMVK[PRM] + 1)) { // Pokud je přestupný, vejde se stále?
                break;
            }
            else if ((prestupI && to->month == PRM) && days >= (DVMVK[PRM] + 1)) { // U přestupného odečti den navíc
                days -= (DVMVK[PRM] + 1);
                to->month++;
            }
            else { // Jinak normálně
                days -= DVMVK[to->month];
                to->month++;
            }
        }
        else { // Pokud je málo dní, skonči
            break;
        }
    }
    to->day += days; // Přičti zbylé dny
    return to;
}

int main() {
    unsigned int N, i;
    date from;

    scanf("%u", &N);
    for (i = 0; i < N; i++) {
    //while (1) { // Na testování, není potřeba zadávat počet
        scanf("%d %d %d", &from.day, &from.month, &from.year);
        prepocti(&from);
    }
    return 0;
}

/*
 * Nefunguje pro data před 20.8. 1984
 */
#include <stdio.h>

#define MVR 15 //Měsíce v roce
#define DVT 9 //Dny v týdnu
#define PRM 3 //Přestupný měsíc
#define PRR 3 //Přestupný rok
#define VPR 100 //Výjimky z přestupného roku
#define DVR 350 // Dny v roce
enum {SD = 20, SM = 8, SY = 1984}; // Určuje počáteční datum; SD:den, SM:měsíc, SY:rok

#define MVRGK 12
#define PMGK 2 // Přestupný měsíc gregoriánský kalendář
#define PRGK 4 // Přestupný rok gregoriánský kalendář
#define VPRGK 100 // Výjimka z přestupného roku gregoriánský kalendář
#define VZVPRGK 400 // Výjimka z výjimky přestupného roku gregoriánský kalendář
#define DVRGK 365 // Dny v roce gregoriánský kalendář

static int DVMGK[] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Měsíce v roce 1 a poslední je prosinec
static int DVMVK[] = {-1, 25, 21, 21, 24, 24, 25, 25, 21, 25, 24, 21, 24, 21, 24, 25}; // Měsíce v roce, nový kalendář

typedef struct { // Uložení datumu
    int day;
    int dayOfWeek;
    int month;
    int year;
} date;

void prepocti(date*);
int spoctiDny (date* from);
date *spoctiDatum (int days, date* to);

void prepocti(date *from) { // Přepočítá datum
    int days;

    date to = {1, 1, 1, 1}; // 1. den v novém kalendáři, přičítá se k němu
    days = spoctiDny(from);
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
            if (prestupI && months == PMGK) days--; // Pokud přestupný rok odečtu den, rok se přidal celý i přestupným dnem
        }
    }
    days += buff.day; // přičte počet dní, může být záporný; pokud je datup před začátkem kalendáře, vyjde záporný počet dní
    return days;
}

date *spoctiDatum (int days, date* to) { // Ze dní spočítá datum nového kalendáře
    char prestupI = 0;

    to->dayOfWeek += days % DVT; // Spočítá dny v týdnu
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
        scanf("%d %d %d", &from.day, &from.month, &from.year);
        prepocti(&from);
    }
    return 0;
}

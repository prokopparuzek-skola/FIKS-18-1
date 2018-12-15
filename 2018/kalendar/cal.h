#ifndef __CAL
#define __CAL
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
#endif /* __CAL */

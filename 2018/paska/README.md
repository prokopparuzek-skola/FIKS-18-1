---
header-includes:
	\usepackage{a4wide}
	\usepackage[czech]{babel}
---
# Páska
## Řešení
### Popis
Při řešení jsem vycházel z Průvodce labyrintem algoritmů kapitoly 16.1 (Materiály ke studiu), kde je řešení zcela 
popsáno, tak jsem ho pouze přepsal do programovacího jazyka C. Pokusím se alespoň algoritmus popsat vlastními slovy 
Úloha je v podstatě o tom nalézt co nejkratší obal všech zadaných bodů bez ohledu na další členění, tedy nalezení 
konvexního obalu.

### Algoritmus
Začnu tím že si body seřadím, abych je následně mohl rozumně projít. Jelikož je budu procházet zleva, seřadím si je 
podle x. Pokud je x stejné u více bodů řadím dle y, mohu plochu ,,pootočit", body na obalu se tím nezmění. K řazení 
používám quicksort, který má průměrou složitost řazení `O(N log N)`. Jakmile mám body seřazeny, mohu si je zleva projít 
a zařazovat je do obalu, aby zůstal konvenxní, už bodle názvu, v něm musí být jen úhly pod 180°. To řeším takto. 
Rozdělím si plochu na dvě poloviny, mezi nejlevějším a nejpravějším bodem, horní a dolní. Pak přidám do každe poloviny 
bod a kontroluji zda je polovina pořád konvexní. To dělám pomocí směru zatáčení úhlu, v horní polovině obal pořád zatáčí 
doprava,jakoby do kružnice, pokud je však úhel orientován vlevo, vznikne jakýsi zub a obal přestává být konvexní 
a nejkratší možný a jelikož úhel se zkládá z aktuálního a dvou bodů zpět, musím odstranit předchozí bod a zkontrolovat 
to znovu, dokud mi nedojdou body, nebo nebudu zatáčet doprava. To samé dělám z dolní polovinou, kde pouze zatáčím 
doleva. Když mi dojdou body mám hotovo. A mohu spočítat délku, na to použiji Pythagorovu větu, jelikož mi řekne z délek 
dvou stran (rozdíl souřadnic), jak dlouhá je přepona (Spojnice dvou daných bodů). Takto spočítám celý obal, pouze 
poslední bod použiji dvakrát, poprvé od prvního na druhý bod, podruhé z posledního na první. 

### Složitost
U složitosti, prvně spočítám složitost řadícího algoritmu (quicksort), kterou znám a je průměrně `O(N log N)`. Pokud jde 
o zbytek, složitost přidání bodu je úměrná počtu odebraných bodů a jelikož mohu každý bod odebrat jen jednou, je 
složitost `O(N)`, kdy N je počet bodů.  Celková složitost je tedy: 
```
O(N + N log N)
```
Odstraníme přičítací konstanty a vyjde nám:
```
O(N log N)
```
To je celková složitost algoritmu.

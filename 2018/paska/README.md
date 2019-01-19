# Páska
## Řešení
### Popis
Při řešení jsem vycházel z Průvodce labyrintem algoritmů kapitoly 16.1 (Materiály ke studiu), kde je řešení zcela popsáno,
tak jsem ho pouze přepsal do programovacího jazyka C. Pokusím se alespoň algoritmus popsat vlastními slovy.
Úloha je v podstatě o tom nalézt co nejkratší obal všech zadaných bodů bez ohledu na další členění, tedy nalezení konvexního obalu.

### Algoritmus
Začnu tím že si body seřadím, abych je následně mohl rozumně projít. Jelikož je budu procházet zleva, seřadím si je podle x.
Pokud je x stejné u více bodů řadím dle y, mohu plochu "pootočit". K řazení používám quicksort, který má průměrou složitost
řazení `O(N log N)`. Jakmile mám body seřazeny, mohu si je zleva projít a zařazovat je do obalu, aby zůstal konvenxní, už bodle názvu,
v něm musí být jen úhly pod 180°. To řeším takto.
Rozdělím si plochu na dvě poloviny, mezi nejlevějším a nejpravějším bodem, horní a dolní. Pak přidám do každe poloviny bod a kontroluji

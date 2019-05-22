---
header-includes:
	\usepackage[czech]{babel}
	\usepackage{a4wide}
---
# Inverze
## Řešení
### Algoritmus
Začneme tím, že si vytvoříme posloupnost N čísel od 1 do N, s tím že pokud je K menší než N, přidáme 1 a ubíráme místo 
nich čísla od N. Tím nám vznikne posloupnost ve které nejsou žádné inverze. Poté postupně od nejmenšího čísla porovnáme 
aktuální počet inverzí, na začátku 0, s tím co získáme, když je přesuneme na konec. Jestliže je přesuneme získáme `K 
- dané číslo` inverzí. Pokud získáme méně než potřebujeme, pokračujeme dalším číslem, pokud více začneme postupně 
  prohazovat číslo s čísly napravo od něj. Pokud prohazujeme s číslem větším, přičteme k inverzím 1, jinak ne. Jakmile 
  narazíme na menší číslo a stále máme málo inverzí, ukončíme program a vypíšeme že to nejde. Pokud u první části, 
  prohození na konec zjistíme, že jsme na čísle rovném K,též ukončíme program a vypíšeme, že to nejde.

### Složitost
Pokud vezmeme ten nejhorší případ, přesuneme každé číslo nakonec, tedy N čísel, v případě prohazování v druhé fázi, 
můžeme též provést až N prohození. Výsledná složitost je tedy `O(2N)`.
Pokud to maximálně zkrátím vyjde mi tato složitost.
`O(N)`

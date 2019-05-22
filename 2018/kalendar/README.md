---
header-includes:
	\usepackage{a4wide}
	\usepackage[czech]{babel}
---
# Nový Kalednář
## Řešení 
### Popis
Pro řešení jsem zvolil tento postup: Nejprve z data Gregoriánského kalendáře vypočtu dny od začátku kalendáře Velkého Vůdce (20.8.1984). Poté zpět z počtu dnů udělám datum v kalendáři Velkého Vůdce.  Algoritmus převodu na dny funguje asi takto: Projdu cyklem roky a přičtu za ně dny, poté to samé udělám z měsíci, a nakonec přičtu dny. U přepočtu na dny je třeba pouze dát pozor na přestupné roky a jejich výjimky a na měsíce před srpnem, u nich je potřeba dny odečíst, ne přičíst. Pokud je přestupný rok je potřeba odečíst den navíc.  Algoritmus převodu zpět funguje obdobně: vezme dny, a v cyklu je podělí roky, měsíci a pak je přičte. Musí dát pouze pozor na přestupné roky. Zbytek jsem doufám dostatečně okomentoval ve zdrojovém kódu. 

### Složitost
Podle mého odhadu, jelikož každý den použji jednou je složitost `O(N)`, kdy N je počet dní od 20.8.1984.

### Modifikatelnost
Pokud se u jiného kalendáře nezmění počet výjimek z přestupných let je algoritmus modifikovatelný pouze zmněnou konstant ve zdrojovém kódu. Pokud se zmnění počet výjimek, je třeba program přepsat.

### Poznámky
Funguje pouze pro data od 20.8.1984 a dále, před začátkem Kalendáře nejsem spočítat datum.

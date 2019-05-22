#!/bin/bash

if [ -e o.sav ]; then rm o.sav ; fi
read t
for i in $( seq $t )
    do read m n k
    echo "1 $m $n $k" | ./a.out > $i.sav
done
for i in $( seq $t )
    do  check=$(head -n 1 "$i.sav")
        if [ "$check" = "Nejde to." ]; then  continue; fi
        wc $i.sav | sed -e "s/ \+/ /g" -e "s/^ \+//" | cut -d " " -f 1,3 > tmp
        y=$(cut -d " " -f 1 tmp)
        chars=$(cut -d " " -f 2 tmp)
        chars=$(dc -e "$chars $y-p")
        x=$(dc -e "$chars $y/p")
        sed -i'' -e "1i$y $x" $i.sav
        echo -n "$y $x " >> o.sav
        ./check <$i.sav >>o.sav
done
for i in $(seq $t)
    do rm $i.sav;done
rm tmp

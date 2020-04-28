#!/bin/bash

uniq $1 > tmp1
cut -d " " -f 2 tmp1 > tmp2
wc tmp2
uniq tmp2 > tmp1
wc tmp1
rm tmp[12]

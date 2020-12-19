#/bin/bash

sort_py/sort.py $1 sample.bin
sort_rs/sort $1 sample.bin
sort_c/sort $1 sample.bin
sort_asm/sort $1 sample.bin

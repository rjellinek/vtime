#!/usr/bin/gnuplot

reset
set terminal png

set xlabel "Bytes Away from Initial Read"
set ylabel "Time (micro seconds)"
set title "Ideal Buffer Size for Random Reads Within a File"

set grid
unset key

plot "results/run54" using 1:2 w lines title 'run20' 

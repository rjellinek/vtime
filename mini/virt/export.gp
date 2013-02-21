#!/usr/bin/gnuplot

reset
set terminal png

set xlabel "Bytes Read"
set ylabel "Cycles"

set style data line

set grid

plot "run1" using 1:2

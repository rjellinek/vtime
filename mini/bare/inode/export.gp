#!/usr/bin/gnuplot

reset
set terminal png

set xlabel "Blocks Written"
set ylabel "Time (milli seconds)"
set title "Measuring What File Size Causes Indirection"

set grid
unset key

plot "results/combined" using 1:2

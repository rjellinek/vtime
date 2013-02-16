#!/usr/bin/gnuplot

reset
set terminal png

set xlabel "Blocks Written"
set ylabel "Time (micro seconds)"
set title "Measuring What File Size Causes Indirection"

set style data line

set grid
unset key

plot "run7" using 1:3

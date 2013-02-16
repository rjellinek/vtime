#!/usr/bin/gnuplot

reset
set terminal png

set xlabel "Blocks Read"
set ylabel "Time (micro seconds)"
set title "Measuring Amount of Data Prefetched by the File System"

set style data line
set grid

unset key

plot "run10" using 1:2 w lines title 'Run 10'
#	"g3" using 1:2 w lines title 'Run 2'

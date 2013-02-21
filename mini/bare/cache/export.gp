#!/usr/bin/gnuplot

reset
set terminal png

set xlabel "Bytes Read (MB)"
set ylabel "Time (micro seconds)"
set title "Measuring Cache Size"

set style data line
unset key

set grid

plot "results/run12" using 1:2 title '64 MB Step' w lines
#	"g2" using 1:3 title '50 MB Step' w lines, \
#	"g3" using 1:3 title '32 MB Step' w lines

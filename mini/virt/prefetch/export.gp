#!/usr/bin/gnuplot

# Plot averages
reset
set terminal png
set output 'avg_runs.png'

set xlabel "Bytes Read"
set ylabel "Time (usec)"
#set yrange [0:400]
set title "Average Read Times For Various Byte Amounts on Bare Metal (n=30)"
set xtics 32

set grid

plot "avg_runs.dat" using 1:2 w lines title 'Read times, bare metal'


# Plot combined scatter plot
reset
set terminal png
set output 'combined_runs.png'
set logscale y
set autoscale x

set xlabel "Bytes Read"
set ylabel "Read Time (logscale)"
set title "Read Times For Various Byte Amounts on Bare Metal (n=30)"

set grid
plot "combined_runs.dat" using 1:2 w points title 'Read times, bare metal'

#!/usr/bin/gnuplot

# Plot averages
reset
set terminal png
set output 'avg_runs.png'

set xlabel "Bytes Read"
set ylabel "Time (usec)"
set yrange [0:400]
set title "Average Read Times For Various Byte Amounts on Bare Metal (n=18)"

set grid
unset key

plot "avg_runs.dat" using 1:2 w lines title 'avg_runs'


# Plot combined scatter plot
reset
set terminal png
set output 'combined_runs.png'
set logscale y
set autoscale x

set xlabel "Bytes Read"
set ylabel "Read Time (logscale)"
set title "Combined Read Times For Various Byte Amounts on Bare Metal (n=18)"

set grid
unset key
plot "combined_runs.dat" using 1:2 w points title 'combined_runs'

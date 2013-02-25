#!/usr/bin/gnuplot

# Plot averages
reset
set terminal png
set output 'avg_runs.png'

set xlabel "Bytes Read"
set ylabel "Time (usec)"
set title "Measuring File Buffer Cache on Bare Metal: Average Read Times (n=5)"

#set yrange [0:400]
#set xtics 32

unset key
set grid

plot "avg_runs.dat" using 1:2 w lines title 'avg_runs'


# Plot combined scatter plot
reset
set terminal png
set output 'combined_runs.png'
#set logscale y
set autoscale x

set xlabel "Bytes Read"
set ylabel "Read Time (usec)"
set title "Measuring File Buffer Cache on Bare Metal: Combined Read Times (n=5)"

unset key
set grid
plot "combined_runs.dat" using 1:2 w points title 'combined_runs'

#!/usr/bin/gnuplot

# Plot averages
set terminal png
set output 'random_avg.png'

set xlabel "Bytes Read"
set ylabel "Read Time (usec)"
set yrange [0:400]
set title "Measuring Ideal Random Read Buffer Size: Average Read Times (n=18)"

set grid
set style line 1 lt 2 lc rgb "blue" lw 3
set style line 2 lt 2 lc rgb "orange" lw 2
plot "../bare/random/avg_runs.dat" using 1:2 w lines ls 1 title 'Bare Metal', \
     "../virt/random/avg_runs.dat" using 1:2 w lines ls 2 title 'QEMU-KVM'


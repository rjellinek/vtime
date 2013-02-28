#!/usr/bin/gnuplot

# Plot averages
set terminal png
set output 'prefetch_avg.png'

set xlabel "Number of 4k Blocks Read"
set ylabel "Read Time (usec)"
set yrange [0:800]
set title "Measuring Prefetch Data Size: Average Read Times (n=30)"

set grid
set style line 1 lt 2 lc rgb "blue" lw 1
set style line 2 lt 3 lc rgb "orange" lw 2
plot "../bare/prefetch/avg_runs.dat" using 1:2 w lines ls 1 title 'Bare Metal', \
     "../virt/prefetch/avg_runs.dat" using 1:2 w lines ls 2 title 'QEMU-KVM'


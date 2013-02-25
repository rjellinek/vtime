#!/usr/bin/gnuplot

# Plot averages
set terminal png
set output 'cache_avg.png'

set xlabel "Bytes Read"
set ylabel "Read Time (usec)"
#set yrange [0:400]
set title "Measuring File Cache Size: Average Read Times (n=5)"

set grid
set style line 1 lt 2 lc rgb "blue" lw 1
set style line 2 lt 3 lc rgb "orange" lw 2
plot "../bare/cache/avg_runs.dat" using 1:2 w lines ls 1 title 'Bare Metal', \
     "../virt/cache/avg_runs.dat" using 1:2 w lines ls 2 title 'QEMU-KVM'


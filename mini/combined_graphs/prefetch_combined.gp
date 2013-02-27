#!/usr/bin/gnuplot

# Plot averages
set terminal png
set output 'prefetch_combined.png'

#set logscale y
set autoscale x
set yrange[0:1000]

set xlabel "Number of 4k Blocks Read"
set ylabel "Read Time (usec)"
set title "Measuring Prefetch Data Size: Combined Read Times (n=30)"

set grid
plot "../bare/prefetch/combined_runs.dat" using 1:2 w points pt 2 lc rgb 'blue' title 'Bare Metal', \
     "../virt/prefetch/combined_runs.dat" using 1:2 w points pt 4 lc rgb 'orange' title 'QEMU-KVM'


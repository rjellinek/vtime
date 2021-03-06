#!/usr/bin/gnuplot

# Plot averages
set terminal png
set output 'cache_combined.png'

#set logscale y
#set autoscale x
#set yrange[0:1000]

set xlabel "Bytes Read"
set ylabel "Read Time (usec)"
set title "Measuring File Cache Size: Combined Read Times (n=5)"

set grid
plot "../bare/cache/combined_runs.dat" using 1:2 w points pt 2 lc rgb 'blue' title 'Bare Metal', \
     "../virt/cache/combined_runs.dat" using 1:2 w points pt 4 lc rgb 'orange' title 'QEMU-KVM'


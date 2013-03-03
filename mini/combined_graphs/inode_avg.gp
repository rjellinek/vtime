#!/usr/bin/gnuplot

# Plot averages
set terminal png
set output 'inode_avg.png'

set xlabel "Blocks Written"
set ylabel "Written Time (usec)"
set title "Measuring Inode Indirection: Average Write Times (n=5)"

#set yrange [0:400]

set grid
set style line 1 lt 2 lc rgb "blue" lw 1
set style line 2 lt 3 lc rgb "orange" lw 2
plot "../bare/inode/avg_runs.dat" using 1:2 w lines ls 1 title 'Bare Metal', \
     "../virt/inode/avg_runs.dat" using 1:2 w lines ls 2 title 'QEMU-KVM'


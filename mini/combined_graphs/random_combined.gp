#!/usr/bin/gnuplot

# Plot averages
set terminal png
set output 'random_combined.png'

#set logscale y
set autoscale x
set yrange[0:600]

set xlabel "Bytes Read"
set ylabel "Read Time (logscale)"
set title "Read Times For Various Byte Amounts on Bare Metal (n=18)"

set grid
plot "../bare/random/combined_runs.dat" using 1:2 w points pt 2 lc rgb 'blue' title 'Bare Metal', \
     "../virt/random/combined_runs.dat" using 1:2 w points pt 4 lc rgb 'orange' title 'QEMU-KVM'


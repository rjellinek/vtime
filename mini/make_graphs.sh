#!/bin/bash

## Run this from the test directory, like from
## vtime/mini/bare/random/make_graphs.sh as a symbolic link

dir=`pwd`
../../average_runs.py "$dir/results" $dir
gnuplot export.gp
eog avg_runs.png

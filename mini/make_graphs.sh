#!/bin/bash

## 

## A symbolic link to this file should be made in the test directory,
## e.g.: vtime/mini/bare/random/make_graphs.sh
## Then run it from the test directory, assuming the test directory
## also containts the correct export.gp file to make the correct
## gnuplot graphs.

dir=`pwd`
../../average_runs.py "$dir/results_iostat" $dir
gnuplot export.gp
eog avg_runs.png

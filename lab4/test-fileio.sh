#!/bin/bash

# iterate over the program parameters using nested for loops
# program usage: ./fileio <workload> <block_size> <num_procs>
#     - workload: WS (write-sequential), WR (write-random), RS (read sequential), RR (read random)
#     - block_size: 4KB, 64KB, 1MB, 64MB
#     - num_procs: 1 2 4 8

workload="WS"
block_size="1MB"
num_procs="1"

# right now the bash script calls the program with only one configuration
./fileio $workload $block_size $num_procs

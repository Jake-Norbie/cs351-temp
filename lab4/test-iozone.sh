#!/bin/bash

# iterate over the program parameters using nested for loops
# program usage: ./fileio <workload> <block_size> <num_procs>
#     - workload: WS (write-sequential), WR (write-random), RS (read sequential), RR (read random)
#     - block_size: 1KB, 10KB, 1000KB, 1MB
#     - num_procs: 1 2 4

# right now the bash script calls the program with only one configuration
iozone -i0

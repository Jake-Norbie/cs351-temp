#!/bin/bash

# iterate over the program parameters using nested for loops
# program usage: ./fileio <workload> <block_size> <num_procs>
#     - workload: WS (write-sequential), WR (write-random), RS (read sequential), RR (read random)
#     - block_size: 1KB, 10KB, 1000KB, 1MB
#     - num_procs: 1 2 4

# right now the bash script calls the program with only one configuration


for WORKLOAD in 1 0 2
do
	for  BLOCK_SIZE in 64k 1m 16m
	do
		./iozone3_394/src/current/iozone -I -+n -i 0 -i $WORKLOAD -r $BLOCK_SIZE -t 1 -s 1g
		./iozone3_394/src/current/iozone -I -+n -i 0 -i $WORKLOAD -r $BLOCK_SIZE -t 2 -s 500m 
		./iozone3_394/src/current/iozone -I -+n -i 0 -i $WORKLOAD -r $BLOCK_SIZE -t 4 -s 250m  
                ./iozone3_394/src/current/iozone -I -+n -i 0 -i $WORKLOAD -r $BLOCK_SIZE -t 8 -s 125m
	done
done

./iozone3_394/src/current/iozone -I -+n -i 0 -i 2 -r 4k -t 1 -s 4m -O
./iozone3_394/src/current/iozone -I -+n -i 0 -i 2 -r 4k -t 2 -s 2m -O
./iozone3_394/src/current/iozone -I -+n -i 0 -i 2 -r 4k -t 4 -s 1m -O
./iozone3_394/src/current/iozone -I -+n -i 0 -i 2 -r 4k -t 8 -s 512k -O

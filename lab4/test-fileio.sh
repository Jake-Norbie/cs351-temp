#!/bin/bash

# iterate over the program parameters using nested for loops
# program usage: ./fileio <workload> <block_size> <num_procs>
#     - workload: WS (write-sequential), WR (write-random), RS (read sequential), RR (read random)
#     - block_size: 4KB, 64KB, 1MB, 64MB
#     - num_procs: 1 2 4 8
echo Creating dummy files

head -c 500KB /dev/urandom > testfiles/halfmb1.txt
head -c 500KB /dev/urandom > testfiles/halfmb2.txt
head -c 500KB /dev/urandom > testfiles/halfmb3.txt
head -c 500KB /dev/urandom > testfiles/halfmb4.txt
head -c 500KB /dev/urandom > testfiles/halfmb5.txt
head -c 500KB /dev/urandom > testfiles/halfmb6.txt
head -c 500KB /dev/urandom > testfiles/halfmb7.txt
head -c 500KB /dev/urandom > testfiles/halfmb8.txt

head -c 1MB /dev/urandom > testfiles/onemb1.txt
head -c 1MB /dev/urandom > testfiles/onemb2.txt
head -c 1MB /dev/urandom > testfiles/onemb3.txt
head -c 1MB /dev/urandom > testfiles/onemb4.txt

head -c 2MB /dev/urandom > testfiles/twomb1.txt
head -c 2MB /dev/urandom > testfiles/twomb2.txt

head -c 4MB /dev/urandom > testfiles/fourmb1.txt

head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive1.txt
head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive2.txt
head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive3.txt
head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive4.txt
head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive5.txt
head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive6.txt
head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive7.txt
head -c 125MB /dev/urandom > testfiles/onehundredtwentyfive8.txt

head -c 250MB /dev/urandom > testfiles/twohundredfifty1.txt
head -c 250MB /dev/urandom > testfiles/twohundredfifty2.txt
head -c 250MB /dev/urandom > testfiles/twohundredfifty3.txt
head -c 250MB /dev/urandom > testfiles/twohundredfifty4.txt

head -c 500MB /dev/urandom > testfiles/fivehundred1.txt
head -c 500MB /dev/urandom > testfiles/fivehundred2.txt

head -c 1GB /dev/urandom > testfiles/onethousand1.txt

echo Done with dummy file
echo ---

for WORKLOAD in WS WR RS RR
do
	for BLOCK_SIZE in 64KB 1MB 16MB
	do
		echo ---
		echo $WORKLOAD workload with $BLOCK_SIZE block size
		echo ---
		for NUM_PROCS in 1 2 4 8
		do
			./fileio $WORKLOAD $BLOCK_SIZE $NUM_PROCS THROUGHPUT
	        done
	done
done

echo ---
echo IOPS testing
echo ---

for WORKLOAD in WR RR
do
	for NUM_PROCS in 1 2 4 8
	do
		./fileio $WORKLOAD 4KB $NUM_PROCS IOPS
	done
done

CC=gcc
CFLAGS=-Wall -O3

build: hash bsort para

test: hash bsort
	./hash cs351
	./hash awesome
	./bsort < pp2.txt
	

hash: hash.c
	$(CC) $(CFLAGS) -o hash $<

bsort: bubblesort.c
	$(CC) $(CFLAGS) -o bsort $<

para: parallel.c
	$(CC) $(CFLAGS) -o para $<

clean:
	rm -rf hash bsort para

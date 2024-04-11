CC = gcc
CFLAGS = -Wall -O2

OBJ_DIR = ../../data-structure/obj

SEARCHINGS += binary-search
SEARCHINGS += interpolation-search
SEARCHINGS += lower-bound
SEARCHINGS += upper-bound
SEARCHINGS += partition
SEARCHINGS += randomized-select


all: $(SEARCHINGS)


binary-search: binary-search.c
	$(CC) $(CFLAGS) -o binary-search binary-search.c

interpolation-search:
	$(CC) $(CFLAGS) -o interpolation-search interpolation-search.c

lower-bound:
	$(CC) $(CFLAGS) -o lower-bound lower-bound.c

upper-bound:
	$(CC) $(CFLAGS) -o upper-bound upper-bound.c

partition:
	$(CC) $(CFLAGS) -o partition partition.c
	
randomized-select:
	$(CC) $(CFLAGS) -o randomized-select randomized-select.c

clean:
	rm -rf $(SEARCHINGS)
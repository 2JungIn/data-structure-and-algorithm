CC = gcc
CFLAGS = -Wall -O2

OBJ_DIR = ../../data-structure/obj

SORTINGS += bubble-sort
SORTINGS += insertion-sort
SORTINGS += selection-sort
SORTINGS += partial-selection-sort
SORTINGS += shell-sort
SORTINGS += merge-sort
SORTINGS += quick-sort
SORTINGS += randomized-quick-sort
SORTINGS += quick-sort-3way
SORTINGS += radix-sort
SORTINGS += bucket-sort

all: $(SORTINGS)


bubble-sort: bubble-sort.c
	$(CC) $(CFLAGS) -o bubble-sort bubble-sort.c


insertion-sort: insertion-sort.c
	$(CC) $(CFLAGS) -o insertion-sort insertion-sort.c


selection-sort: selection-sort.c
	$(CC) $(CFLAGS) -o selection-sort selection-sort.c

partial-selection-sort: partial-selection-sort.c
	$(CC) $(CFLAGS) -o partial-selection-sort partial-selection-sort.c


shell-sort: shell-sort.c
	$(CC) $(CFLAGS) -o shell-sort shell-sort.c


merge-sort: merge-sort.c
	$(CC) $(CFLAGS) -o merge-sort merge-sort.c


quick-sort: quick-sort.c
	$(CC) $(CLFAGS) -o quick-sort quick-sort.c

randomized-quick-sort:
	$(CC) $(CFLAGS) -o randomized-quick-sort randomized-quick-sort.c

quick-sort-3way:
	$(CC) $(CFLAGS) -o quick-sort-3way quick-sort-3way.c
	

radix-sort: radix-sort.c
	$(CC) $(CLFAGS) -o radix-sort radix-sort.c $(OBJ_DIR)/single-linked-list.o $(OBJ_DIR)/queue.o


bucket-sort: bucket-sort.c
	$(CC) $(CLFAGS) -o bucket-sort bucket-sort.c $(OBJ_DIR)/vector.o

clean:
	rm -rf $(SORTINGS)
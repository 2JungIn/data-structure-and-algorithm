CC = gcc
CFLAGS = -Wall -O2 -g

SRC_DIR = ./src
OBJ_DIR = ./obj

OBJS += $(OBJ_DIR)/pair.o 
OBJS += $(OBJ_DIR)/single-linked-list.o 
OBJS += $(OBJ_DIR)/double-linked-list.o 
OBJS += $(OBJ_DIR)/stack.o 
OBJS += $(OBJ_DIR)/array-stack.o
OBJS += $(OBJ_DIR)/queue.o
OBJS += $(OBJ_DIR)/array-queue.o
OBJS += $(OBJ_DIR)/deque.o 
OBJS += $(OBJ_DIR)/array-deque.o
OBJS += $(OBJ_DIR)/vector.o 
OBJS += $(OBJ_DIR)/heap.o 
OBJS += $(OBJ_DIR)/priority-queue.o
OBJS += $(OBJ_DIR)/binary-tree.o 
OBJS += $(OBJ_DIR)/avl-tree.o 
OBJS += $(OBJ_DIR)/red-black-tree.o
OBJS += $(OBJ_DIR)/hash-table.o
OBJS += $(OBJ_DIR)/map.o
OBJS += $(OBJ_DIR)/graph.o

all: $(OBJS)
	cd test; make all

# pair
$(OBJ_DIR)/pair.o: $(SRC_DIR)/pair.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pair.c -o $(OBJ_DIR)/pair.o

# single linked list
$(OBJ_DIR)/single-linked-list.o: $(SRC_DIR)/single-linked-list.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/single-linked-list.c -o $(OBJ_DIR)/single-linked-list.o

# double linked list
$(OBJ_DIR)/double-linked-list.o: $(SRC_DIR)/double-linked-list.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/double-linked-list.c -o $(OBJ_DIR)/double-linked-list.o

# stack
$(OBJ_DIR)/stack.o: $(SRC_DIR)/stack.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/stack.c -o $(OBJ_DIR)/stack.o

# array stack
$(OBJ_DIR)/array-stack.o: $(SRC_DIR)/array-stack.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/array-stack.c -o $(OBJ_DIR)/array-stack.o

# queue
$(OBJ_DIR)/queue.o: $(SRC_DIR)/queue.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/queue.c -o $(OBJ_DIR)/queue.o

# array queue
$(OBJ_DIR)/array-queue.o: $(SRC_DIR)/array-queue.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/array-queue.c -o $(OBJ_DIR)/array-queue.o

# deque
$(OBJ_DIR)/deque.o: $(SRC_DIR)/deque.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/deque.c -o $(OBJ_DIR)/deque.o

# array deque
$(OBJ_DIR)/array-deque.o: $(SRC_DIR)/array-deque.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/array-deque.c -o $(OBJ_DIR)/array-deque.o

# vector
$(OBJ_DIR)/vector.o: $(SRC_DIR)/vector.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/vector.c -o $(OBJ_DIR)/vector.o

# heap
$(OBJ_DIR)/heap.o: $(SRC_DIR)/heap.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/heap.c -o $(OBJ_DIR)/heap.o

# priority queue
$(OBJ_DIR)/priority-queue.o: $(SRC_DIR)/priority-queue.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/priority-queue.c -o $(OBJ_DIR)/priority-queue.o

# binary tree
$(OBJ_DIR)/binary-tree.o: $(SRC_DIR)/binary-tree.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/binary-tree.c -o $(OBJ_DIR)/binary-tree.o

# avl tree
$(OBJ_DIR)/avl-tree.o: $(SRC_DIR)/avl-tree.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/avl-tree.c -o $(OBJ_DIR)/avl-tree.o

# red-black-tree
$(OBJ_DIR)/red-black-tree.o: $(SRC_DIR)/red-black-tree.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/red-black-tree.c -o $(OBJ_DIR)/red-black-tree.o

# hash table
$(OBJ_DIR)/hash-table.o: $(SRC_DIR)/hash-table.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/hash-table.c -o $(OBJ_DIR)/hash-table.o

# map
$(OBJ_DIR)/map.o: $(SRC_DIR)/map.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/map.c -o $(OBJ_DIR)/map.o
	
# graph
$(OBJ_DIR)/graph.o: $(SRC_DIR)/graph.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/graph.c -o $(OBJ_DIR)/graph.o

clean:
	rm -rf $(OBJS)
	cd test; make clean
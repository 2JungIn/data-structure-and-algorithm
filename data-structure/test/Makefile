CC = gcc 
CFLAGS = -Wall -O2 -g

OBJ_DIR = ../obj

TESTS += pair-test 
TESTS += single-linked-list-test 
TESTS += double-linked-list-test 
TESTS += stack-test 
TESTS += array-stack-test
TESTS += queue-test 
TESTS += array-queue-test
TESTS += deque-test 
TESTS += array-deque-test
TESTS += vector-test 
TESTS += heap-test
TESTS += priority-queue-test
TESTS += binary-tree-test 
TESTS += avl-tree-test 
TESTS += red-black-tree-test
TESTS += hash-table-test
TESTS += graph-test

all: $(TESTS)

pair-test: pair-test.c
	$(CC) $(CFLAGS) -o pair-test pair-test.c $(OBJ_DIR)/pair.o


single-linked-list-test: single-linked-list-test.c
	$(CC) $(CFLAGS) -o single-linked-list-test single-linked-list-test.c $(OBJ_DIR)/single-linked-list.o

double-linked-list-test: double-linked-list-test.c
	$(CC) $(CFLAGS) -o double-linked-list-test double-linked-list-test.c $(OBJ_DIR)/double-linked-list.o


stack-test: 
	$(CC) $(CFLAGS) -o stack-test stack-test.c $(OBJ_DIR)/stack.o $(OBJ_DIR)/single-linked-list.o

array-stack-test: 
	$(CC) $(CFLAGS) -o array-stack-test array-stack-test.c $(OBJ_DIR)/array-stack.o


queue-test: 
	$(CC) $(CFLAGS) -o queue-test queue-test.c $(OBJ_DIR)/queue.o $(OBJ_DIR)/single-linked-list.o

array-queue-test:
	$(CC) $(CFLAGS) -o array-queue-test array-queue-test.c $(OBJ_DIR)/array-queue.o


deque-test: 
	$(CC) $(CFLAGS) -o deque-test deque-test.c $(OBJ_DIR)/deque.o $(OBJ_DIR)/double-linked-list.o

array-deque-test:
	$(CC) $(CFLAGS) -o array-deque-test array-deque-test.c $(OBJ_DIR)/array-deque.o


vector-test:
	$(CC) $(CFLAGS) -o vector-test vector-test.c $(OBJ_DIR)/vector.o

heap-test:
	$(CC) $(CFLAGS) -o heap-test heap-test.c $(OBJ_DIR)/vector.o $(OBJ_DIR)/heap.o

priority-queue-test:
	$(CC) $(CFLAGS) -o priority-queue-test priority-queue-test.c $(OBJ_DIR)/vector.o $(OBJ_DIR)/heap.o $(OBJ_DIR)/priority-queue.o 


binary-tree-test:
	$(CC) $(CFLAGS) -o binary-tree-test binary-tree-test.c $(OBJ_DIR)/binary-tree.o


avl-tree-test:
	$(CC) $(CFLAGS) -o avl-tree-test avl-tree-test.c $(OBJ_DIR)/avl-tree.o


red-black-tree-test:
	$(CC) $(CFLAGS) -o red-black-tree-test red-black-tree-test.c $(OBJ_DIR)/red-black-tree.o


hash-table-test:
	$(CC) $(CFLAGS) -o hash-table-test hash-table-test.c $(OBJ_DIR)/pair.o $(OBJ_DIR)/single-linked-list.o $(OBJ_DIR)/hash-table.o


graph-test:
	$(CC) -o graph-test graph-test.c $(OBJ_DIR)/pair.o $(OBJ_DIR)/single-linked-list.o $(OBJ_DIR)/stack.o $(OBJ_DIR)/queue.o $(OBJ_DIR)/avl-tree.o $(OBJ_DIR)/red-black-tree.o $(OBJ_DIR)/map.o $(OBJ_DIR)/graph.o


clean:
	rm -rf $(TESTS)
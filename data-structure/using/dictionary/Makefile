CC = gcc
CFLAGS = -Wall -O2 -g

OBJ_DIR = ../../obj

OBJS += $(OBJ_DIR)/pair.o
OBJS += $(OBJ_DIR)/hash-table.o
OBJS += $(OBJ_DIR)/avl-tree.o
OBJS += $(OBJ_DIR)/single-linked-list.o
OBJS += md5.o

all: dictionary

dictionary: dictionary.c
	$(CC) $(CFLAGS) -o dictionary dictionary.c $(OBJS)

clean:
	rm -rf dictionary
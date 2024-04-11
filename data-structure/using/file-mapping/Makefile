CC = gcc
CFLAGS = -Wall -O2 -g

OBJ_DIR = ../../obj

OBJS += $(OBJ_DIR)/pair.o
OBJS += $(OBJ_DIR)/red-black-tree.o
OBJS += $(OBJ_DIR)/map.o

all: file-mapping

file-mapping: file-mapping.c
	$(CC) $(CFLAGS) -o file-mapping file-mapping.c $(OBJS)

clean:
	rm -rf file-mapping
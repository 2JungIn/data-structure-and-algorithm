CC = gcc
CFLAGS = -Wall -O2 -g

OBJ_DIR = ../../obj

OBJS += $(OBJ_DIR)/single-linked-list.o 
OBJS += $(OBJ_DIR)/stack.o 
OBJS += $(OBJ_DIR)/queue.o

all: calculate

calculate: calculate.c
	$(CC) $(CFLAGS) -o calculate calculate.c $(OBJS)

clean:
	rm -rf calculate
.PHONY: clean

CC = gcc
CFLAGS = -Wall -g

OBJ = parser.o filemaker.o extractor.o main.o
BIN = prog

all : prog

prog: $(OBJ)
				$(CC) $(CFLAGS) -o prog $(OBJ)

%.o : %.c
				$(CC) $(CFLAGS) -c $<

clean:
				rm -rf $(OBJ) $(BIN)

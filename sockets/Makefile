CC = gcc 
CFLAGS = -Wall -Wextra -pedantic -Wno-unused-parameter

all: comm
comm: comm.o
comm.o: comm.c comm.h 

clean:
    rm -f comm comm.o
run: comm
    ./comm
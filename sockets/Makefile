<<<<<<< HEAD
CC = gcc 
CFLAGS = -Wall -Wextra -pedantic -Wno-unused-parameter

all: comm
comm: comm.o
comm.o: comm.c comm.h 

clean:
    rm -f comm comm.o
run: comm
    ./comm
=======
all: client server

client:
	cd client; make all

server:
	cd server; make all

clean:
	cd client; make clean
	cd server; make clean

.PHONY: client server
>>>>>>> 18768f1995adf0603ee14bff828305734b57d31c

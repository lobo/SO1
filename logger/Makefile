SOURCES = $(wildcard *.c)
EXE = logger.bin
GCC = gcc
GCCFLAGS = -Wall

all:
	$(GCC) $(GCCFLAGS) $(SOURCES) -o $(EXE)

clean:
	rm -rf $(EXE)
	rm -rf "logs.txt"

.PHONY: clean 

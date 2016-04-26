EXE = server.bin
GCC = gcc
GCCFLAGS = -Wall -I./../includes -lpthread
SOURCES_C = $(wildcard ../objects/*.c)
MAIN_C = $(wildcard *.c)
OBJECTS = $(SOURCES_C:.c=.o)

all: $(EXE)

$(EXE): $(OBJECTS)
	$(GCC) $(GCCFLAGS) $(MAIN_C) -o $(EXE) $(OBJECTS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@


clean:
	rm -rf ../objects/*.o *.o *.bin
	rm -rf server.bin

.PHONY: clean

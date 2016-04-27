SOURCES_NP = $(wildcard ../libraries/libnamedpipe/objects/*.c)
SOURCES_S = $(wildcard ../libraries/libsocket/objects/*.c)

ifeq  ($(imp), sockets)
	SOURCES_C = $(SOURCES_S)
else
	SOURCES_C = $(SOURCES_NP)
endif

EXE = client.bin
GCC = gcc
GCCFLAGS = -Wall -I./../libraries/includes
MAIN_C = $(wildcard *.c)
OBJECTS = $(SOURCES_C:.c=.o)

all: $(EXE)

$(EXE): $(OBJECTS)
	$(GCC) $(GCCFLAGS) $(MAIN_C) -o $(EXE) $(OBJECTS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJECTS)
	rm -rf $(EXE)

.PHONY: clean 

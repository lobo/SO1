#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <types.h>
#include <unistd.h>
#include <signal.h>

// pipes, sockets, files, signals
// ADT address

typedef struct {
	char * origin;
	char * dest;
} address_t;

typedef struct {
	
} message;

int open();

int close(address_t );

int sendMessage(address_t dest, data);

int receiveMessage(address_t origin);


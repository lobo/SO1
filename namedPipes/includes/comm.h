#ifndef COMM_H
#define COMM_H

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MYFIFO "/tmp/myfifo"

typedef struct
{
	char * ip;
	int port;
} socket_connection_info;

typedef char* fifo_t;

typedef void (* main_handler) (int new_connection_descriptor);

int connect_to(void * address);

int disconnect(int connection_descriptor);

int send_data(int connection_descriptor, void * message);

int receive_data(int connection_descriptor, void *ret_buffer);

int listen_connections(void * address, main_handler handler);


#endif

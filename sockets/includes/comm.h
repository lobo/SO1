#ifndef COM_H
#define COM_H


typedef struct
{
	char * ip;
	int port;
}socket_connection_info;

typedef void (* main_handler) (int listener_descriptor, int new_connection_descriptor);

int connect_to(void * address);

int disconnect(int connection_descriptor);

int send_data(int connection_descriptor, void * message);

int receive_data(int connection_descriptor, void *ret_buffer);

int listen_connections(void * address, main_handler handler);


#endif
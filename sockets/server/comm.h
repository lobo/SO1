#ifndef COM_H
#define COM_H


// this is what will be sent
//typedef struct 
//{
//	char * message;
//	int client_id;
//} ComData;

typedef struct
{
	char * ip;
	int port;
}socket_connection_info;

// recibe la data del request y la convierte en un response
// en vez de bloquearme, me quita el flujo de ejecucion, no retorna data, simplemente no retorna
// cada vez que hay un request, deveulve un requesthandler que lo que tiene que retornar es un requestdata.

typedef void (* main_handler) (int new_connection_descriptor);

int connect_to(void * address);

int disconnect(int connection_descriptor);

int send_data(int connection_descriptor, void * message);

int receive_data(int connection_descriptor, void *ret_buffer);

int listen_connections(void * address, main_handler handler);


// * Sockets: te conectas a un socket
// * Pipe: abris un pipe

// generate a uuid per connection

// * Sockets: te desconectas de ese socket
// * Pipe: cerras el pipe


//int accept(void * connection);





#endif
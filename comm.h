#ifndef COM_H
#define COM_H


// this is what will be sent
typedef struct 
{
	char * data;
	int size;
} ComData;

// information of the client
//typedef struct 
//{
//	int client_id;	// for internal use only
//	void * fd;		// depends on the implementation
//}ClientInfo;

// recibe la data del request y la convierte en un response
// en vez de bloquearme, me quita el flujo de ejecucion, no retorna data, simplemente no retorna
// cada vez que hay un request, deveulve un requesthandler que lo que tiene que retornar es un requestdata.
typedef ComData * (* RequestHandler) (ComData * req);



ComData * SendData(void * connection, ComData * req);

// old ListenToRequest
void Listen(
	void * connection, 
	ComData requestHandler
);


// * Sockets: te conectas a un socket
// * Pipe: abris un pipe
int Connect(void * connection);
// generate a uuid per connection

// * Sockets: te desconectas de ese socket
// * Pipe: cerras el pipe
int Disconnect(void * connection);

int Accept(void * connection);





#endif
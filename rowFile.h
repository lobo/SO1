#ifndef COM_H
#define COM_H

//void * data;
//int size;

// ambos bloqueantes
//ResponseData * Request(Connection * connection, RequestData * req);

// le voy a encodear en el request a quien es el chabon al que le mando la informacion
//int Response(RequestData * req, ResponseData * data);
// Opcion 1) listen se desbloquea cuando le llega un mensaje (desbloquearme con un request pointer)
// Opcion 2) llama un callback
// esto cambia si el main loop esta en la capa de comunicacion
// seguramente lo voy a estar comentando como un request
// RequestData * ListenToRequest(Connection * connection);



// -------- Otra forma de implementar esto es:

typedef struct
{
	char * address;
} Connection;

typedef struct 
{
	char * data;
	int size;
} RequestData;

typedef struct 
{
	char * data;
	int size;
} ResponseData;

// recibe la data del request y la convierte en un response
// en vez de bloquearme, me quita el flujo de ejecucion, no retorna data, simplemente no retorna
// cada vez que hay un request, deveulve un requesthandler que lo que tiene que retornar es un requestdata.
typedef ResponseData * (*RequestHandler) (RequestData * req);

ResponseData * Request(Connection * connection, RequestData * req);

void ListenToRequest(
	Connection * connection, 
	ResponseData requestHandler
);




#endif
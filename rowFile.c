#include "rowFile.h"
#include <unistd.h>

typedef ResponseData * (*RequestHandler) (RequestData * req);

ResponseData * Request(Connection * connection, RequestData * req){
	int wfd = *((int*)(connection->address))[0];
	int rfd = *((int*)(connection->address))[1];

	ResponseData * res = malloc(sizeof(ResponseData));
	res->data = malloc(1024); // hard-coded: depende del tamaña del response. // voy a ir haciendo un realloc de data segun lo que llegue.
	res->size = 1024;

	// manejar el buffer:
	// do while buffer not full...
	write(wfd, req->data, req->size);
	read(rfd, res->data, res->size);
	return res;
}

void ListenToRequest(Connection * connection, RequestHandler requestHandler){
	int wfd = *((int*)(connection->address))[0];
	int rfd = *((int*)(connection->address))[1];

	while(1){
		RequestData * req = malloc(sizeof(RequestData));
		// seguramente dentro del while(1) o del requestHanlder de mas abajo
		// haga un fork
		req->data = malloc(1024);
		req->size = 1024;

		read(rfd, req->data, req->size);
		// se desbloqueo y anduvo todo bien
		ResponseData * res = requestHandler(req);

		write(wfd, res->data, res->size);

		free(req->data);
		free(req);
		free(res->data);
		free(res);
	}
}


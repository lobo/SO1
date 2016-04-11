typedef ResponseData * (*RequestHandler) (RequestData * req);

ComData * SendData(Connection * connection, ComData * req){
	int wfd = *((int*)(connection->address))[0];
	int rfd = *((int*)(connection->address))[1];

	ComData * res = malloc(sizeof(ComData));
	res->data = malloc(1024); // hard-coded: depende del tamaña del response. // voy a ir haciendo un realloc de data segun lo que llegue.
	res->size = 1024;

	// manejar el buffer:
	// do while buffer not full...
	write(wfd, req->data, req->size);
	read(rfd, res->data, res->size);
	return res;
}

// * El select va aca
void Listen(Connection * connection, RequestHandler requestHandler){
	int wfd = *((int*)(connection->address))[0];
	int rfd = *((int*)(connection->address))[1];

	while(1){
		ComData * req = malloc(sizeof(ComData));
		// seguramente dentro del while(1) o del requestHanlder de mas abajo
		// haga un fork
		req->data = malloc(1024);
		req->size = 1024;

		read(rfd, req->data, req->size);
		// se desbloqueo y anduvo todo bien
		ComData * res = requestHandler(req);

		write(wfd, res->data, res->size);

		free(req->data);
		free(req);
		free(res->data);
		free(res);
	}
}

// abre socket/pipe
int Connect(Connection * connection) { 

}

int Disconnect(Connection * connection) {

}

int Accept(Connection * connection) {
	
}
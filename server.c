struct fds {
	int wfd;
	int rfd;
}FDs

// hardocdeadn file descriptors
// should og on separate config files
int server(int wfd, int rfd) {
	// Config
	FDs * fds = malloc(sizeof(FDs));
	fds->wfd = wfd;
	fds->rfd = rfd

	Connection * conn = malloc(sizeof(Connection));
	conn->address = (char*)fds; // negrada, no es prolijo


	// App
	ListenToRequest(Connection * connection, RequestHandler requesthandler)
}

// mi servidor recibe un numero
ResponseData * Handler(RequestData * req){
	ResponseData * res = malloc(sizeof(ResponseData));
	res->data = malloc(sizeof(int));
	res->size = sizeof(int);

	// right side of equal: la capara de marshalling mas villera del universo :)
	// un servidor perfecto: suma 1
	*(int*)&res->data = ((int)(req->data) + 1);
	return res;
}
void client(){
	/ Config
	FDs * fds = malloc(sizeof(FDs));
	fds->wfd = wfd;
	fds->rfd = rfd

	Connection * conn = malloc(sizeof(Connection));
	conn->address = (char*)fds; // negrada, no es prolijo

	RequestData * req = malloc(sizeof(RequestData));
	req->data = malloc(sizeof(Connection));
	req->size = sizeof(int);
	*((int*)&(req->data)) = inc;

	while(1){
		printf("res> %d", (int)(res->data));
		ResponseData * res = Request(conn, req);
		printf("res> %d", (int)(res->data));
		*((int*)&(req->data)) = ++inc;
	}
}
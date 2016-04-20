#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "../comm.h"

int Accept(void * connection){
    char * myfifo = (char *) connection;
    // create the FIFO (named pipe)
    //char * myfifo = "../fifos/myfifo";
    return mkfifo(myfifo, 0666) ? -1 : 0; 
}

ComData * SendData(void * connection, ComData * request){
	write(connection, request->message, sizeof(request->message));
	return request;
}

// incorrect: should not be doing all these actions 
// but don't know where to put them
void Listen(void * connection, ComData requestHandler){
	int fd = Connect(connection);

	SendData((void *) &fd, "Hi, brother!");
	Disconnect((void *) &fd);
}


// opens a pipe:
// idealmente pasarle un char * con el nombre de la connection
// deberia ser algo asi: "../fifos/myfifo"
// to-do? generate a uuid per connection
int Connect(void * connection){
    // check if the connection can be created
    if(Accept(connection)){
    	perror("The connection was not accepted.");
    	return -1;
    }
    
    // opens the pipe for writing only
    return open(connection, O_WRONLY); 
}

// cerras el pipe
int Disconnect(void * connection){
	close((int)connection);
	/* remove the FIFO */
	unlink(connection);
}



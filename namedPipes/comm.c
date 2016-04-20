#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "../comm.h"

int Accept(void * connection){
    char * namedPipe = (char *) connection;
    // create the FIFO (named pipe)
    //char * namedPipe = "../fifos/namedPipe";
    return mkfifo(namedPipe, 0666) ? -1 : 0; 
}

ComData * SendData(void * connection, ComData * request){
	write(connection, request->message, sizeof(request->message));
	return request;
}

void Listen(void * connection, ComData requestHandler){
	if(open(connection, O_RDWR) == -1){
		perror("Error opening the file");
		exit(1);
	}
}

// opens a pipe:
// idealmente pasarle un char * con el nombre de la connection
// deberia ser algo asi: "../fifos/namedPipe"
// to-do? generate a uuid per connection
int Connect(void * connection){
    // check if the connection can be created
    if(Accept(connection)){
    	perror("The connection was not accepted.");
    	return -1;
    }
    
    return 0; // todo bien
}

// cerras el pipe
int Disconnect(void * connection){
	close((int)connection);
	/* remove the FIFO */
	unlink(connection);
}



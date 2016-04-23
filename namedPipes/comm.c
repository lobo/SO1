#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "../comm.h"


typedef void (* main_handler) (int new_connection_descriptor);

int connect_to(void * address);


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

int disconnect(int connection_descriptor){
    if (close(connection_descriptor) == 0){
        printf("Pipe closed successfully.\n");
    }
    else {
        printf("Pipe could not be closed. Aborting.\n");
        exit(1);
    }
    return (_disconnect(connection_descriptor) == 0) ? 0 : 1;
}


int _disconnect(int connection_descriptor){
    // busca el connection_descriptor y lo guarda en un string
    // FALTA IMPLEMENTAR
    char * pipeName; // buscarlo y asignarlo aca
    if (unlink(pipeName) == 0) {
        printf("Unlinking was successful.\n");
        return 0;
    }
    else {
        printf("There was an error doing the unlinking. Aborting.\n");
        exit(1);
    }
}

int send_data(int connection_descriptor, void * message){
    int written_bytes;
    if((written_bytes = write(connection_descriptor, (char *) message, strlen(message))) == -1){
        printf("Could not send information to this pipe: %d\n", connection_descriptor);
        return -1;
    }
    return written_bytes; // will be 0 if no bytes are written
}

int receive_data(int connection_descriptor, void * ret_buffer){
    int read_bytes;
    if ((read_bytes = read(connection_descriptor, (char *) ret_buffer, strlen(ret_buffer))) == -1)
    {
        printf("There was an error reading information from this pipe: %d\n", connection_descriptor);
        return -1;
    }
    return read_bytes;
}

int listen_connections(void * address, main_handler handler){
    pipe = open("server_client_pipeline", O_RDONLY);     //Open for reading only. 
    if(pipe >= 0)                       //Upon successful completion, open function return a non-negative integer
        fprintf(stderr, "SERVER READY\n");
    else{
        fprintf(stderr, "ERROR, CANNOT OPEN FIFO PIPE\nABORT EXECUTION\n");  
        exit(1);
    }

    while(1){
        message = readClient(pipe,message);
        if(strcmp(message,"logout") == 0){
            closeConnection(pipe);
            break;
        }
        serverWrite(message);
    }
}






// Old below:



void Listen(void * connection, ComData requestHandler){
	if(open(connection, O_RDWR) == -1){
		perror("Error opening the file");
		exit(1);
	}
    printf("> Listening to connection: %s\n", (char *) connection);
}






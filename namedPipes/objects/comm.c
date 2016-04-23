#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "comm.h"
#include <stdlib.h>
#include <string.h>


typedef void (* main_handler) (int new_connection_descriptor);

int connect_to(void * address);

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

// falta usar el handler
int listen_connections(void * address, main_handler handler){
    int pipe;   
    char * message;

    if((pipe = open((char *) address, O_RDONLY)) == -1){
        printf("There was an error opening the pipeline. Aborting.\n");
        exit(1);
    }
    printf("Server ready, listening: %s\n", (char *) address);

    while(1){
        //message = receive_data(pipe, message);
        
        //if(strcmp(message,"logout") == 0){
        //   disconnect(pipe);
        //    return 0;
        //}
        //send_data(pipe, message);
    }
}
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <string.h>

#define MESSAGE_SIZE 60

int send_data(int connection_descriptor, void * message);
int receive_data(int connection_descriptor, void *ret_buffer);
int disconnect(int connection_descriptor);


void main(int argc, char **argv){

	char * message;
	int pipe;

	message = (char *)malloc(MESSAGE_SIZE * sizeof(char));
	pipeline = mkfifo("server_pipeline", 0666);  

	if(pipeline == -1){
		printf("There was an error creating the pipeline.\n");
		exit(1);
	}
	else{
		printf("Pipeline created...\n");
	}

	/*Now that we have created the fifo pipe, we have also to open it from the server's end*/
    fprintf(stderr, "OPENING FIFO PIPE\nWaiting for client to connect...\n");
    pipe = open("server_client_pipeline", O_RDONLY);     //Open for reading only. 
    if(pipe >= 0)						//Upon successful completion, open function return a non-negative integer
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


void main(int argc, char **argv){
	
	char * message;
	int pipe;

	message = (char *)malloc(MESSAGE_SIZE*sizeof(char));
	pipe = mkfifo("server",0666);  

	if(pipe == -1){
		printf("Hubo un error creando el pipe.\n");
		exit(1);
	}
	else{
		printf("Se creo el pipe...\n");
	}

	listen_connections();

}


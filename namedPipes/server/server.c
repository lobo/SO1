#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <string.h>
#include "comm.h"

#define MESSAGE_SIZE 60

void server_main(int listener_descriptor, int new_connection_descriptor){
// IMPLEMENTAR ALGO SIMILAR AL DE SOCKETS
}	

int
main(int argc, char **argv){
	
	char * message;
	int pipe;

	char * server_pipeline = "server_pipeline";

	message = (char *) malloc(MESSAGE_SIZE * sizeof(char));
	pipe = mkfifo(server_pipeline, 0666);  

	if(pipe == -1){
		printf("Error opening the pipeline. Aborting.\n");
		exit(1);
	}
	else{
		printf("Pipeline created...\n");
	}

	listen_connections((void *) &server_pipeline, server_main);

	return 0;
}


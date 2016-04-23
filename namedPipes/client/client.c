#include "comm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char *argv[]){
	
	int pipe;
	char * message;

	pipe = open("server_pipeline",O_WRONLY); 

	if(pipe == -1){
		printf("Error opening the pipeline. Aborting.\n");
		exit(1);
	}
	else{
		printf("Pipeline created...\n");
	}

	printf("Please write your message to send to the server\n");
	while(1){
    	if (receive_data(pipe, message)) printf("Recibí: %s\n",message);
	}

	return 0;
}
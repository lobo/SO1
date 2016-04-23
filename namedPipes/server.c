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

void readMessage(char * message);
void sendMessage(int pipe, char * message);
void closeConnection(int pipe);

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


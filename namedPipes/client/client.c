#include "comm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char *argv[]){
	
	FILE* fd;
	char a[40];
	char readbuf[80];
	
	while (1) {
		if((fp = connect_to((void*)MYFIFO)) == NULL){
			perror("Couldn't get file pointer");
			exit(1);
		}
		printf("Me (client): ");
		read(stdin, a, 40);
		printf("%s\n", a);
		send_data(fd, (void*)a);
		disconnect(fd);
		sleep(1);
		if((fp = connect_to((void*)MYFIFO)) == NULL){
			perror("Couldn't get file pointer");
			exit(1);
		}
		receive_data(fd, (void*)readbuf);
		disconnect(fd);
		printf("HIM: %s\n", readbuf);
		sleep(1);
	}
	return 0;
}
	
	/*int pipe;
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

	return 0;*/
}

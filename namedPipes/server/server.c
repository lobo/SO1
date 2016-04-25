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
#include <pthread.h>

void * connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int client_socket_fd = * (int*) socket_desc;
    char * message;
    char buffer[2000];
     
    //Send some messages to the client
    message = "Hola cliente!\n";
    send_data(client_socket_fd , message);

    if (receive_data(client_socket_fd, buffer)) printf("Recibí: %s\n",buffer);
    
	disconnect(client_socket_fd);  
    free(socket_desc);

    printf("Thread terminado. Socket cerrado.\n");
   
   	return NULL;
     
}

void server_main(int listener_descriptor, int new_connection_descriptor){

    	pthread_t sniffer_thread;
        int * new_sock = malloc(sizeof(int));

        * new_sock = new_connection_descriptor;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("No se pudo crear un thread.");
          	return;
        }

        printf("Se conectó al servidor un nuevo cliente con el socket_fd: %d\n", new_connection_descriptor);

}
 
int main(int argc , char *argv[])
{

    char * server_address = "/tmp/fifo_server";

    listen_connections((void*)server_address, server_main);

    return 0;

}


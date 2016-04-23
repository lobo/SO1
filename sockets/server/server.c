// SEMAFOROS DE THREADS: http://www.csc.villanova.edu/~mdamian/threads/posixsem.html

#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
//#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include "comm.h"

void* connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int client_socket_fd = * (int*) socket_desc;
    char *message;
     
    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    send_data(client_socket_fd , message);
    
       
	disconnect(client_socket_fd);  
    free(socket_desc);
   
   	return NULL;
     
}

void server_main (int listener_descriptor, int new_connection_descriptor){

    	pthread_t sniffer_thread;
        int * new_sock = malloc(sizeof(int));

        *new_sock = new_connection_descriptor;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
          	return;
        }

        puts("Se creo un thread nuevo para una nueva conexion.");

}
 
int main(int argc , char *argv[])
{
    socket_connection_info server_info;

    server_info.ip = strdup("0");
    server_info.port = 8888;

    listen_connections((void*)&server_info, server_main);

    return 0;
}
 


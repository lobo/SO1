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
#include "error.h"
#include <pthread.h>

void * connection_handler(void *socket_desc)
{

    int connection_fd = * (int*) socket_desc;
    char read_buffer[2000];
     
    send_data(connection_fd , "Hola cliente!\n");

    if (receive_data(connection_fd, read_buffer)) printf("Recibí: %s\n",read_buffer);
    
    disconnect(connection_fd);  
    free(socket_desc);

   	return NULL;
     
}

void server_main(int listener_descriptor, int new_connection_descriptor){

    	pthread_t sniffer_thread;
        int * new_con = malloc(sizeof(int));

        * new_con = new_connection_descriptor;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_con) < 0)
            return;
        

        printf("Se conectó al servidor un nuevo cliente con el socket_fd: %d\n", new_connection_descriptor);

}
 
int main(int argc , char *argv[])
{

    socket_connection_info server_info;

    strcpy(server_info.ip, "127.0.0.1");
    server_info.port = 8888;
    int run = 1;
   
    listen_connections((void*)&server_info, server_main, run);

    return 0;

}


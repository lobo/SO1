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

#define WELCOME_MSG "Bienvenido al chatroom, "


void * connection_handler(void *context) //STRUCT DE CONTEXTO = socket_desc
{

    context_info * my_context = (context_info*) context;
    int connection_fd = my_context->new_connection_descriptor;

    printf("Se conectó al servidor un nuevo cliente con el socket_fd: %d\n", connection_fd); //LOG

    //Send bienvenida la cliente
    //Leer 
    //Handle tcp packet

    char read_buffer[2000];
     
    send_data(connection_fd , "Hola cliente!\n", 15);

    if (receive_data(connection_fd, read_buffer, 16)) printf("Recibí: %s\n",read_buffer);
    
    disconnect(connection_fd);  

   	return NULL;
     
}

void server_main(context_info * context){

    	pthread_t sniffer_thread;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) context) < 0) //pasar contexto, que contenga new_con y run
            return;

}
 
int main(int argc , char *argv[])
{

    connection_info server_info;

    strcpy(server_info.ip, "127.0.0.1");
    server_info.port = 8888;
    int run = 1; 
   
    listen_connections((void*)&server_info, server_main, &run); //manejo de errores

    return 0;

}


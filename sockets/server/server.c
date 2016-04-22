// SEMAFOROS DE THREADS: http://www.csc.villanova.edu/~mdamian/threads/posixsem.html

#include <stdio.h>
#include <string.h>    //strlen
//#include <stdlib.h>    //strlen
//#include <unistd.h>    //write
//#include <pthread.h> //for threading , link with lpthread
#include "comm.h"


void *connection_handler(void *);

void funcion_prueba (int new_connection_descriptor){

    printf("Hola, acepte la conexion %d\n",new_connection_descriptor);

    disconnect(new_connection_descriptor);

}
 
int main(int argc , char *argv[])
{
    socket_connection_info server_info;

    server_info.ip = strdup("0");
    server_info.port = 8888;

    listen_connections((void*)&server_info, funcion_prueba);

    return 0;
}
 


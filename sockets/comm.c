#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include "comm.h"

typedef struct{

    int socketfd;
    struct * sockaddr_un s_address;

}socket_t;

socket_t * _create_socket(void * address){

    socket_t * ret_socket = (socket_t * ) malloc(sizeof(socket_t));

    if (ret_socket->socketfd = socket(AF_INET , SOCK_STREAM , 0) == -1){
        free(ret_socket);
        return -1;
    }

    (struct * sockaddr_un) ret_socket->s_address = (struct * sockaddr_un) malloc (sizeof((struct sockaddr_un)));

    if (s_address == NULL){
        free(ret_socket->s_address);
        free(ret_socket);
        return - 1;
    }

    socket_connection_info * socket_info = (* socket_connection_info) address;


    if (strcmp(socket_info->ip, "0")){
        ret_socket->s_address->s_addr = inet_addr(strdup(socket_info->ip));
    }else{
        ret_socket->s_address->s_addr = INADDR_ANY;
    }

    ret_socket->s_address->sin_family = AF_INET;
    ret_socket->s_address->sin_port = htons(socket_info->port);


    return ret_socket;
}

void _delete_socket(socket_t * socket){

    free(socket->s_address);
    free(socket);

}


int connect(void * address){

    struct sockaddr_un remote;
    socket_t * my_socket;

    if ( my_socket = _create_socket(address) == -1){
        perror("No se pudo crear el socket."); //hacer funcion propia y no imprimir en pantalla.
        return -1;
    }

    if (connect(my_socket->socketfd, (struct sockaddr *)&my_socket->s_address, sizeof(my_socket->s_address)) == -1) {
        perror("No se pudo conectar con el servidor.");
        return -1;
    }

    return my_socket->socketfd;

}

int send_data(int connection_descriptor, void * message){

    int bytes_to_write = strlen((char *) message) + 1;

    while ( int written_bytes = write(sockfd, message, bytes_to_write) < bytes_to_write){}

    return written_bytes;
}

int receive_data(int connection_descriptor, void * ret_buffer){



}

void listen(void * address, main_handler handler){

    socket_t * my_socket;
    struct sockaddr_in client;
    int new_socket_fd;

    if ( my_socket = _create_socket(address) == -1){
        perror("No se pudo crear el socket."); //hacer funcion propia y no imprimir en pantalla.
        return -1;
    }

    if( bind(my_socket->socketfd,(struct sockaddr *)&my_socket->s_address , sizeof(my_socket->s_address)) < 0)
    {
        perror("No se pudo bindear el socket del servidor.");
        return -1;
    }
     
    listen(my_socket->socketfd , 3);

    c = sizeof(struct sockaddr_in);

    while( (new_socket_fd = accept(my_socket->socketfd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        
        handler(new_socket_fd);
    }

     if (new_socket_fd < 0)
    {
        perror("No se pudo aceptar la conexion entrante.");
        return -1;
    }
     
    return 0;

}

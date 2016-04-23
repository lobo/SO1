#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include "comm.h"
   

int _build_socket(void * address, struct sockaddr_in * s_address){

    socket_connection_info * socket_info = (socket_connection_info *) address;

    if (strcmp(socket_info->ip, "0")){
        s_address->sin_addr.s_addr = inet_addr(strdup(socket_info->ip));
    }else{
        s_address->sin_addr.s_addr = INADDR_ANY;

    }

    s_address->sin_family = AF_INET;
    s_address->sin_port = htons(socket_info->port);

    return 0;

}


int connect_to(void * address){

    int socket_fd;
    struct sockaddr_in sock;

    if ( (socket_fd = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        perror("No se pudo crear el socket.");        
        return -1;
    } 

    _build_socket(address, &sock);

    if (connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock)) == -1) {
        perror("No se pudo conectar con el servidor.");
        return -1;
    }

    return socket_fd;

}

int disconnect(int connection_descriptor){

    close(connection_descriptor);

    return 0;

}


int send_data(int connection_descriptor, void * message){

    int bytes_to_write = strlen((char *) message) + 1;
    int written_bytes;

    while ( (written_bytes = send(connection_descriptor, message, bytes_to_write, 0)) < bytes_to_write){}

    return written_bytes;
}

int receive_data(int connection_descriptor, void * ret_buffer){


    if( recv(connection_descriptor , ret_buffer , 2000 , 0) < 0)  //cambiar magic number 2000
        {
            puts("No se pudo recibir data.");
            return -1;
        }

    return 0;

}
    
int listen_connections(void * address, main_handler handler){

    int listener_socket;
    int new_socket_fd;
    struct sockaddr_in sock;
    struct sockaddr_in client;

    if ( (listener_socket = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        perror("No se pudo crear el socket que escucha.");        
        return -1;
    } 

     _build_socket(address, &sock);


    if( bind(listener_socket,(struct sockaddr *)&sock , sizeof(sock)) < 0)
    {
        perror("No se pudo bindear el socket del servidor.");
        return -1;
    }
     
    listen(listener_socket , 3);

    int c = sizeof(struct sockaddr_in);

    while( (new_socket_fd = accept(listener_socket, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {

        handler(listener_socket, new_socket_fd);
    }

     if (new_socket_fd < 0)
    {
        perror("No se pudo aceptar la conexion entrante.");
        return -1;
    }

    disconnect(listener_socket);
     
    return 0;

}

#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include "comm.h"

#define MAX_SOCKETS 150

typedef struct{

    int socketfd;
    struct sockaddr_in * s_address;

}socket_t;

socket_t * socket_list[MAX_SOCKETS];
int CANTIDAD_SOCKETS = 0;

void _add_socket(socket_t * socket){

    for (int i = 0; i <= CANTIDAD_SOCKETS; i++){

        if (socket_list[i] == 0) {
            printf("Agrego el socket fd %d en el lugar %d\n", socket->socketfd,i);
            socket_list[i] = socket;
        }
    
    }

    CANTIDAD_SOCKETS++;
}

socket_t * _create_socket(){

    socket_t * ret_socket = (socket_t * ) malloc(sizeof(socket_t));

    if (ret_socket == NULL) return NULL;


    ret_socket->s_address = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));

    if (ret_socket->s_address == NULL){
        free(ret_socket->s_address);
        free(ret_socket);
        return NULL;
    }

    return ret_socket;
}

void _assign_socket_info(socket_t * empty_socket, void * address){

    if ( (empty_socket->socketfd = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        free(empty_socket);
        return;
    }

    socket_connection_info * socket_info = (socket_connection_info *) address;

    if (strcmp(socket_info->ip, "0")){
        empty_socket->s_address->sin_addr.s_addr = inet_addr(strdup(socket_info->ip));
    }else{
        empty_socket->s_address->sin_addr.s_addr = INADDR_ANY;
    }

    empty_socket->s_address->sin_family = AF_INET;
    empty_socket->s_address->sin_port = htons(socket_info->port);

}

int _socket_id_from_fd(int connection_descriptor){

    for (int i = 0; i <= CANTIDAD_SOCKETS; i++){
        printf("Voy en el indice %d de %d sockets y busco %d, pero esta el %d\n",i,CANTIDAD_SOCKETS,connection_descriptor, socket_list[i]->socketfd);
        if (socket_list[i]->socketfd == connection_descriptor) {
            puts("Entro");
            return i;
        }
    }

    return -1;
}

void _delete_socket(int connection_descriptor){

    int sockid = _socket_id_from_fd(connection_descriptor);
    socket_t * socket = socket_list[sockid];
    socket_list[sockid] = 0;
    CANTIDAD_SOCKETS--;
    free(socket->s_address);
    free(socket);

}


int connect_to(void * address){

    socket_t * my_socket;

    if ( (my_socket = _create_socket()) == NULL){
        perror("No se pudo crear el socket."); //hacer funcion propia y no imprimir en pantalla.
        return -1;
    }

     _assign_socket_info(my_socket, address); //manejo de errores, que devuelva int.
     _add_socket(my_socket);

    if (connect(my_socket->socketfd, (struct sockaddr *)&my_socket->s_address, sizeof(my_socket->s_address)) == -1) {
        perror("No se pudo conectar con el servidor.");
        return -1;
    }

    return my_socket->socketfd;

}

int disconnect(int connection_descriptor){

    close(connection_descriptor);
    _delete_socket(connection_descriptor);

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

    socket_t * my_socket;
    struct sockaddr_in client;
    int new_socket_fd;

    if ( (my_socket = _create_socket()) == NULL){
        perror("No se pudo crear el socket."); //hacer funcion propia y no imprimir en pantalla.
        return -1;
    }

     _assign_socket_info(my_socket, address);
     _add_socket(my_socket);

    if( bind(my_socket->socketfd,(struct sockaddr *)my_socket->s_address , sizeof(*(my_socket->s_address))) < 0)
    {
        perror("No se pudo bindear el socket del servidor.");
        return -1;
    }
     
    listen(my_socket->socketfd , 3);

    int c = sizeof(struct sockaddr_in);

  
    
    while( (new_socket_fd = accept(my_socket->socketfd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        socket_t * new_socket = _create_socket();
        new_socket->socketfd = new_socket_fd;
        new_socket->s_address->sin_addr.s_addr = client.sin_addr.s_addr; //encapsular
        new_socket->s_address->sin_port = client.sin_port;
        new_socket->s_address->sin_family = client.sin_family;
        _add_socket(new_socket);

        handler(new_socket_fd);
    }

     if (new_socket_fd < 0)
    {
        perror("No se pudo aceptar la conexion entrante.");
        return -1;
    }

    disconnect(my_socket->socketfd);
     
    return 0;

}

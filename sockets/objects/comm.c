#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include "comm.h"
#include "error.h"

//separar todo y dejar un cliente y un servidor solo que impleemnte el .h

int _build_socket(void * address, struct sockaddr_in * s_address){

    //poner todo en un char * y aca adentro separar los dos puntos
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
        return raise_error(ERR_RES_CREATION);
    } 

    _build_socket(address, &sock);

    if (connect(socket_fd, (struct sockaddr *)&sock, sizeof(sock)) == -1) {
        return raise_error(ERR_CON_REFUSED);
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

    int read_bytes;
    read_bytes = recv(connection_descriptor , ret_buffer , 2000 , 0);  //cambiar MN 2000. MSG_WAITALL en flag?
       

    return read_bytes;

}
    
int listen_connections(void * address, main_handler handler){

    int listener_socket;
    int new_socket_fd;
    struct sockaddr_in sock;
    struct sockaddr_in client;

    if ( (listener_socket = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        return raise_error(ERR_ADDRESS_IN_USE);        
    } 

     _build_socket(address, &sock);


    if( bind(listener_socket,(struct sockaddr *)&sock , sizeof(sock)) < 0)
       return raise_error(ERR_RES_CREATION);
    
     
    listen(listener_socket , 3);

    int c = sizeof(struct sockaddr_in);

    while (1)
    {
        new_socket_fd = accept(listener_socket, (struct sockaddr *)&client, (socklen_t*)&c);
        
        if (new_socket_fd < 0) {
            return raise_error(ERR_CON_REJECTED);
        }

        handler(listener_socket, new_socket_fd);
    }

    disconnect(listener_socket);
     
    return 0;

}

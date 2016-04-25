#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "comm.h"
#include <stdlib.h>
#include <string.h>

#define MAX_CONNECTIONS 128

typedef struct _fifo_connection_data{

    int pipe_fd;
    char * pipe_address;

} fifo_handler;

fifo_handler * connections_list[MAX_CONNECTIONS];
int connections_number;


int _fd_to_index(int fd){

    for (int i = 0; i <= MAX_CONNECTIONS; i++){

        if (connections_list[i]->pipe_fd == fd) return i;

    }

    return -1;

}

int _get_free_index(){

    for(int i = 0; i <= connections_number; i++){ 

        if (connections_list[i] == NULL) return i;

    }

    return -1;

}

void _create_fifo(char * address){

    if (mkfifo(address, 0666) == -1) {
        perror("Error while creating the fifo");
        return;
    }

}

void _add_fifo(fifo_handler * fh){

    connections_list[fh->pipe_fd] = fh;
    connections_number++;

}

fifo_handler * _create_fifo_handler(char * address){

    fifo_handler * ret_fh = (fifo_handler *) malloc(sizeof(fifo_handler));

    ret_fh->pipe_fd = _get_free_index();
    ret_fh->pipe_address = strdup(address);

    printf("Buildie un fh con address %s\n",ret_fh->pipe_address);

    if (ret_fh->pipe_address == NULL){
        perror("Error while creating the fifo");
        free(ret_fh);
        unlink(address); //address con _r y _w hay que borrar aca
        return NULL;
    }

    _add_fifo(ret_fh);

    return ret_fh;

}

void _delete_fifo(int pipe_fd){ //que le paso? el pipefd, el pipe, el address?

    fifo_handler * del_fh = connections_list[_fd_to_index(pipe_fd)];

    unlink(del_fh->pipe_address);
    free(del_fh->pipe_address);
    free(del_fh);
    connections_list[pipe_fd] = NULL;
    connections_number--;

    puts("Borre todo");

}

int _accept_connection(char *client_id){

    char aux_buffer[20];
    fifo_handler * accepted_fifo;

    //estructura en el servidor
    //fifo real
    //enviar al cliente el index de esta estructura
    sprintf(aux_buffer, "/tmp/fifo_%s", client_id);
    accepted_fifo = _create_fifo_handler(aux_buffer);
    _create_fifo(aux_buffer);

    send_data(accepted_fifo->pipe_fd, "OK");

    return accepted_fifo->pipe_fd;

}

int connect_to(void * address){ //no tiene timeout...

    char connection_string[20], receive_buffer[20], aux_buffer[20];
    int fd, pid;

    if ( (fd = open( (char *) address, O_WRONLY)) < 0) {    //si no funciona, poner fopen.
        perror("Error while trying to connect 1");  
        return -1;
    }  

    pid = getpid();
    sprintf(aux_buffer, "/tmp/fifo_%d", pid); 
    fifo_handler * fh = _create_fifo_handler(aux_buffer); //abrir en lectura y escritura.
    
    sprintf(connection_string, "%d", pid); 
    write(fd, connection_string, strlen((char *) connection_string) + 1);

    close(fd);

    sleep(2);

    if ( (fd = open(fh->pipe_address, O_RDONLY)) < 0) {    //si no funciona, poner fopen.
        perror("Error while trying to connect 2");  
        return -1;
    }  
            
    read(fd , receive_buffer , 20);
    
    close(fd);

    return fh->pipe_fd;

}

int disconnect(int connection_descriptor){

    close(connection_descriptor); //por si quedo abierto, aunque no deberia...
    _delete_fifo(connection_descriptor);

    return 0;
}

int send_data(int connection_descriptor, void * message){ //deberia ir el real connection descriptor, el del open. Una funcion que te haga open, otra close.

    int fd, written_bytes;
    int bytes_to_write = strlen((char *) message) + 1;

    printf("Paso 1 con el mensaje: %s\n", message);
   
    if ( (fd = open( connections_list[connection_descriptor]->pipe_address, O_WRONLY)) < 0) {    
        perror("Error while trying to send data");  
        return -1;
    }  

     printf("Paso 2 con el mensaje: %s\n", message);
    
    while ( (written_bytes = write(fd, message, bytes_to_write)) < bytes_to_write){}

         printf("Paso 3 con el mensaje: %s\n", message);

    close(fd);

     printf("Paso 4 con el mensaje: %s\n", message);

    return written_bytes; // will be 0 if no bytes are written
}

int receive_data(int connection_descriptor, void * ret_buffer){

    int fd, read_bytes;

    if ( (fd = open( connections_list[connection_descriptor]->pipe_address, O_RDONLY)) < 0) {    
        perror("Error while trying to read");  
        return -1;
    }  

    if( (read_bytes = read(fd , ret_buffer , 2000)) < 0){  //cambiar MN 2000. MSG_WAITALL en flag?
            perror("Error while reading");
            return -1;
    }

    close(fd);

    return read_bytes;
}

// falta usar el handler
int listen_connections(void * address, main_handler handler){
    
    fifo_handler * listener_fifo;
    int new_connection_descriptor;
    char aux_buffer[20];

    listener_fifo = _create_fifo_handler(address);
    _create_fifo(address);
    _add_fifo(listener_fifo);

    while (1){ //read, create, write accept, handler.

        if (receive_data(listener_fifo->pipe_fd, aux_buffer) > 0){
           new_connection_descriptor = _accept_connection(aux_buffer);
        }

        handler(listener_fifo->pipe_fd, new_connection_descriptor); 

    }

    //todo esto no se ejecuta de abajo con control c, asi que hay que borrar y unlinkear los archivos.

    if (new_connection_descriptor < 0){
        perror("Error while trying to accept incoming connection");
        return -1;
    }

    disconnect(listener_fifo->pipe_fd);
     
    return 0;
}
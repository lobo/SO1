#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "comm.h"
#include <stdlib.h>
#include <string.h>

//en sockets meter el accept dentro del while para que no lo puedan tirar
//Usar la misma estructura para todos, ip y port y que el archivo se llame asi...
//IP:PUERTO asi meto en el struct un char * y nada mas
//abstraer lo del sprintf a una funcion

#define MAX_CONNECTIONS 128

typedef struct _fifo_connection_data{

    int pipe_fd;
    int file_desc_r;
    int file_desc_w;
    char * pipe_address;
    char listening;

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

void _create_fifos(char * address){

    char aux_buffer[20];


    sprintf(aux_buffer, "%s_%s", address, "w");
    if (mkfifo(aux_buffer, 0666) == -1) {
        perror("Error while creating the fifo");
        return;
    }


    sprintf(aux_buffer, "%s_%s", address, "r");
     if (mkfifo(aux_buffer, 0666) == -1) {
        perror("Error while creating the fifo");
        return;
    }


}

void _add_fifo(fifo_handler * fh){

    connections_list[fh->pipe_fd] = fh;
    connections_number++;

}


int _open_fifos(fifo_handler * fh, char * address, char listening){

    char aux_buffer[20];
    int fdr, fdw;

    if (listening == 0){


        sprintf(aux_buffer, "%s_%s", address, "r");
        if ( (fdw = open( aux_buffer, O_WRONLY)) < 0) {    
            perror("Error while opening fifo W");  
            return -1;
        }  

        sprintf(aux_buffer, "%s_%s", address, "w");
        if ( (fdr = open( aux_buffer, O_RDONLY)) < 0) {    
            perror("Error while opening fifo R");  
            return -1;
        } 


    }else{

        sprintf(aux_buffer, "%s_%s", address, "r");
        if ( (fdr = open( aux_buffer, O_RDONLY)) < 0) {    
            perror("Error while opening fifo R");  
            return -1;
        }  

        sprintf(aux_buffer, "%s_%s", address, "w");
        if ( (fdw = open( aux_buffer, O_WRONLY)) < 0) {    
            perror("Error while opening fifo W");  
            return -1;
        }  

        
    }

    fh->file_desc_w = fdw;
    fh->file_desc_r = fdr;

    return 0;

}

fifo_handler * _create_fifo_handler(char * address){

    fifo_handler * ret_fh = (fifo_handler *) malloc(sizeof(fifo_handler));
    

    ret_fh->pipe_fd = _get_free_index();
    ret_fh->pipe_address = strdup(address); //chequeo de errores
    

    _add_fifo(ret_fh);

    return ret_fh;

}

void _delete_fifo(int pipe_fd){ //que le paso? el pipefd, el pipe, el address?

    fifo_handler * del_fh = connections_list[_fd_to_index(pipe_fd)];
    char aux_buffer[20];

    close(del_fh->file_desc_r);
    close(del_fh->file_desc_w);

    sprintf(aux_buffer, "%s_%s", del_fh->pipe_address, "r"); 
    unlink(aux_buffer);
    sprintf(aux_buffer, "%s_%s", del_fh->pipe_address, "w"); 
    unlink(aux_buffer);

    free(del_fh->pipe_address);
    free(del_fh);
    connections_list[pipe_fd] = NULL;
    connections_number--;

}


int connect_to(void * address){ //no tiene timeout...

    char connection_string[20], receive_buffer[20], aux_buffer[20];
    int fd;
    int pid = getpid();

    sprintf(aux_buffer, "%s_%s", (char*) address, "r"); 

    if ( (fd = open( (char *) aux_buffer, O_WRONLY)) < 0) {  
        perror("Error while trying to connect 1");  
        return -1;
    }  
    
    sprintf(connection_string, "%d", pid); 
    
    write(fd, connection_string, strlen((char *) connection_string) + 1);
    close(fd);

    sprintf(aux_buffer, "%s_%s", (char*) address, "w"); 
    
    if ( (fd = open(aux_buffer, O_RDONLY)) < 0) {    //si no funciona, poner fopen.
        perror("Error while trying to connect 2");  
        return -1;
    }  
           
    read(fd , receive_buffer , 20);

    sprintf(aux_buffer, "/tmp/fifo_%d", pid); 
    fifo_handler * fh = _create_fifo_handler(aux_buffer); //abrir en lectura y escritura.
    _open_fifos(fh, aux_buffer, 0);

    close(fd);

    return fh->pipe_fd;

}

int disconnect(int connection_descriptor){

    _delete_fifo(connection_descriptor);

    return 0;
}

int send_data(int connection_descriptor, void * message){ //deberia ir el real connection descriptor, el del open. Una funcion que te haga open, otra close.

    int written_bytes;
    int bytes_to_write = strlen((char *) message) + 1;
   

    while ( (written_bytes = write(connections_list[connection_descriptor]->file_desc_w, message, bytes_to_write)) < bytes_to_write){}


    return written_bytes; // will be 0 if no bytes are written
}

int receive_data(int connection_descriptor, void * ret_buffer){

    int read_bytes;

    if( (read_bytes = read(connections_list[connection_descriptor]->file_desc_r , ret_buffer , 2000)) < 0){  //cambiar MN 2000. MSG_WAITALL en flag?
            perror("Error while reading");
            return -1;
    }

    return read_bytes;
}


int _accept_connection(fifo_handler *listener, char *client_id){

    char aux_buffer[20];
    fifo_handler * accepted_fifo;

    sprintf(aux_buffer, "/tmp/fifo_%s", client_id);
    accepted_fifo = _create_fifo_handler(aux_buffer);
    _create_fifos(aux_buffer);
    send_data(listener->pipe_fd, "OK");
    _open_fifos(accepted_fifo, aux_buffer, 1);
    

    return accepted_fifo->pipe_fd;

}

// falta usar el handler
int listen_connections(void * address, main_handler handler){
    
    fifo_handler * listener_fifo;
    int new_connection_descriptor;
    char aux_buffer[20];

    listener_fifo = _create_fifo_handler(address);
    _create_fifos(address);
    _open_fifos(listener_fifo, address, 1);
    _add_fifo(listener_fifo);

    while (1){ //read, create, write accept, handler.

        if (receive_data(listener_fifo->pipe_fd, aux_buffer) > 0){
           
           flock(listener_fifo->file_desc_w, LOCK_SH);
           new_connection_descriptor = _accept_connection(listener_fifo, aux_buffer);
           flock(listener_fifo->file_desc_w, LOCK_UN);
           
           handler(listener_fifo->pipe_fd, new_connection_descriptor); 
        }

    }

    if (new_connection_descriptor < 0){
        perror("Error while trying to accept incoming connection");
        return -1;
    }

    disconnect(listener_fifo->pipe_fd);
     
    return 0;
}

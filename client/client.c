#include "comm.h"
#include "error.h"
#include "serialize.h"
#include "tcp_client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>


int client_connection_id;
int run;
t_buffer * client_send_buffer;
t_buffer * client_recv_buffer;
connection_info server_info;

//select en cliente.

void init_client(char * ip, int port){

    strcpy(server_info.ip, ip);
    server_info.port = port;

    client_connection_id = -1;

    client_send_buffer = create_buffer();
    client_recv_buffer = create_buffer();

    run = 1;

}

void deinit_client(){

    delete_buffer(client_send_buffer);
    delete_buffer(client_recv_buffer);

    run = 0;
    
}


int main(int argc , char *argv[])
{

    fd_set fds;
    int maxfd, r_bytes;
    char stdin_buffer[20];

    init_client("127.0.0.1", 8888);

    write_login("martin", "martin123", 5); //debe devolver valor asi hago si es -1, return;

    write_talk("hola que tal");

    maxfd = client_connection_id;
    FD_ZERO(&fds);
    FD_SET(client_connection_id, &fds); 
    FD_SET(0, &fds); 


    while (1){

        select(maxfd+1, &fds, NULL, NULL, NULL); 

        if (FD_ISSET(0, &fds)){
            fgets(stdin_buffer, 20, stdin);
        }
        
        if (FD_ISSET(client_connection_id, &fds)){

            r_bytes = load_buffer(client_connection_id, client_recv_buffer);

    
            while (client_recv_buffer->pos + 1 < r_bytes){
                handle_tcp_packets();
                client_recv_buffer->pos+=1;
            }

            clean_buffer(client_recv_buffer);
        }
        

    }

    deinit_client();
     
    //send_disc_message
    //disconnect

    return 0;
}

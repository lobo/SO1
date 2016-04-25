#include "comm.h"
#include <string.h>
#include <stdio.h>

int main(int argc , char *argv[])
{
    socket_connection_info server_info;

    strcpy(server_info.ip, "127.0.0.1");
    server_info.port = 8888;

    int sock;
    char buffer[1000];
    
    sock = connect_to((void*)&server_info);

    
    while(1){
    	
    	if (receive_data(sock, buffer)) printf("Recibí: %s\n",buffer);
    }


    return 0;
}
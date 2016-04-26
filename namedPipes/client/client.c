#include "comm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc , char *argv[])
{

    char * server_address = "/tmp/fifo_server";
    int sock;
    char buffer[2000];

    char * message;
    message = "Hola servidor!\n";

    sock = connect_to((void*)server_address);

    send_data(sock , message);

    if (receive_data(sock, buffer)) printf("Recibí: %s\n",buffer);

    


    return 0;
}

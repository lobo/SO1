#include "comm.h"
#include "error.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\033[0m"

int main(int argc , char *argv[])
{
    socket_connection_info server_info;

    strcpy(server_info.ip, "fifo_server");

    int sock;
    char buffer[2000];

    char * message;
    message = "Hola servidor!\n";

    sock = connect_to((void*)&server_info);

    if (sock < 0){
        print_error();
        return -1;
    }else
        printf( GREEN "Conectado.\n" RESET);

    send_data(sock , message);

    if (receive_data(sock, buffer)) printf("Recibí: %s\n",buffer);

    


    return 0;
}

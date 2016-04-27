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
    int connection_fd;
    char read_buffer[2000];

    strcpy(server_info.ip, "127.0.0.1");
    server_info.port = 8888;

    connection_fd = connect_to((void*)&server_info);

    if (connection_fd < 0){
        print_error();
        return -1;
    }else
        printf( GREEN "Conectado.\n" RESET);

    send_data(connection_fd , "Hola servidor!\n");

    if (receive_data(connection_fd, read_buffer)) printf("Recibí: %s\n",read_buffer);


    return 0;
}

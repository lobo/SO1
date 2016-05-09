#include "comm.h"
#include "error.h"
#include "serialize.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\033[0m"


//select en cliente.

int main(int argc , char *argv[])
{
    connection_info server_info;
    int connection_fd;
    int run = 1;

    strcpy(server_info.ip, "127.0.0.1");
    server_info.port = 8888;
    
    connection_fd = connect_to((void*)&server_info);

    if (connection_fd < 0){
        print_error();
        return -1;
    }else
        printf( GREEN "Conectado.\n" RESET);

    //send_data(connection_fd , "Hola servidor!\n", 16);

    t_buffer * buffer = create_buffer();
    int x,y;
    char z[20];
        
    while(run){
            
            printf("Lei %d bytes\n", load_buffer(connection_fd, buffer));
  
            read_int(buffer, &x);
            read_int(buffer, &y);
            read_string(buffer, z);
            printf("Recibí: %d, %d y %s\n",x, y, z); //parche
            printf( RED "Desconectado.\n" RESET);
            run = 0;
            delete_buffer(buffer);
            break;
     

    }


    //send_disc_message
    //disconnect

    return 0;
}

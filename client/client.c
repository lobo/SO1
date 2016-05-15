#include "comm.h"
#include "error.h"
#include "serialize.h"
#include "parser.h"
#include "tcp_client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>

int client_connection_id;
int run;
fd_set fds;
int maxfd;
t_buffer * client_send_buffer;
t_buffer * client_recv_buffer;
connection_info server_info;

//select en cliente.
//sacar los gccextras para que no tire warnings el clang. Del o:c
//errpres con rojo.

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
    //destruir arg1 y arg2? free
}


int main(int argc , char *argv[])
{


    int r_bytes;
    char user_input[256];
    char* arg1 = NULL;
    char* arg2 = NULL;
	char username[30]; //IDEALMENTE NO TIENE QUE ESTAR ESTO
	char password[30]; //IDEALMENTE NO TIENE QUE ESTAR ESTO
	int cmd;

	
    init_client("127.0.0.1", 8888);

    //write_login("pedrito", "pedrito123", 5);

    maxfd = 0;
     
    while (run){


        FD_ZERO(&fds);
        //FD_SET(client_connection_id, &fds); //al establecer conexion tengo que hacerlo.
        FD_SET(0, &fds); //stdin

        select(maxfd+1, &fds, NULL, NULL, NULL);

        if (FD_ISSET(0, &fds)){

   			fgets(user_input, 256, stdin); 
			cmd = parse_cmd(user_input, &arg1, &arg2);
			
            switch(cmd) {
				
				case CMD_CHAT:
					write_talk(user_input);
					break;
				case CMD_LOGIN:
					write_login(arg1, arg2, 5);
					strcpy(username, arg1);	//ESTO NO DEBERIA GUARDARSE ACA
					strcpy(password, arg2); //ESTO NO DEBERIA GUARDARSE ACA
					break;
				case CMD_REGISTER:
					write_register(arg1, arg2);
					break;
				case CMD_LOGOUT:
					write_disconnect();
					break;
				case CMD_CH_PW:
					write_change_pw(username, arg1, arg2);
					break;
				case CMD_CH_PRIVS:
					//write_change_privileges(arg1, arg2); IMPLEMENTAR (usuario, privilegio)
					break;
				case CMD_CH_COLOR:
					write_change_color((int) *arg1);
					break;
				case CMD_DELETE_USER:
					write_delete(arg1, password); 	//ver de no pasar la pass
					break;
				case CMD_KICK:
					write_kick(arg1, arg2);
					break;
				case CMD_BAN:
					write_ban(arg1, arg2);
					break;
				case CMD_ERROR:
					fprintf(stderr, "Algo se rompió vieja...\n");
					break;				
			}
			
			if (arg1 != NULL)
				free(arg1);
			if (arg2 != NULL)
				free(arg2);
				
			arg1 = arg2 = NULL;
			
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
     
    return 0;
}

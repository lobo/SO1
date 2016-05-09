#include "tcp_client.h"
#include "serialize.h"
#include "comm.h"
#include "error.h"

/*

typedef enum _packet_id{ 
	LOGIN,               
	REGISTER_USER,
	DELETE_USER,
	TALK,
	CHANGE_COLOR,
	CHANGE_PW,
	KICK,
	BAN,
	DISCONNECT,
	CHECK_LOGS
} packet_id;

int client_socket_id;
connection_info server_info;

void init_client(char * ip, int port){

	strcpy(server_info.ip, ip);
    server_info.port = port;

    client_socket_id = -1;

}

void write_login(char * username, char * password, char color){

	if (client_socket_id > 0){
		printf("Ya estás logeado.\n");
		return;
	}

	client_socket_id = connect_to((void*)&server_info);

	if (client_socket_id < 0){
    	print_error();
        return;
    }

    write_int(client_socket_id, packet_id.LOGIN);
    write_string(client_socket_id, username);
    write_string(cl)



}

void write_register(char * username, char * password);

void write_delete(char * username, char * password);

void write_talk(char * mensaje);
void handle_talk();

void write_change_color(char color);

void write_change_pw(char * username, char * old_password, char * new_password);

void write_kick(char * username, char * reason);

void write_ban(char * username, char * reason);

void write_disconnect();
void handle_disconnect();

void write_check_logs();

*/
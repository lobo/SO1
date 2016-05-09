#include "tcp_server.h"
#include "user.h"
#include <string.h>
#include <stdio.h>

#define MAX_USERS 100
#define WELCOME_MSG "Servidor>> Bienvenido al chatroom."
#define SERVER_COLOR 1


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

extern t_user * user_list[MAX_USERS];
extern int connected_users;


void handle_tcp_packets(int user_index){

    int p_id;

    read_int(user_list[user_index]->recv_buffer, &p_id);

    switch (p_id){

        case LOGIN:
            handle_login(user_index);
            break;

        case TALK:
        	handle_talk(user_index);
        	break;

    }




}

void handle_login(int user_index){

	char username [20], password [20];
	int color, privileges;

	read_string(user_list[user_index]->recv_buffer, username); 
	read_string(user_list[user_index]->recv_buffer, password); 
	read_int(user_list[user_index]->recv_buffer, &color);

	//check user y pw

	//check privileges
	privileges = 0;

	user_list[user_index]->name = strdup(username); //ponerlo con un (MOD)o(ADMIN) segun priv.
	user_list[user_index]->color = color;
	user_list[user_index]->privileges = privileges;


	write_talk(user_index, WELCOME_MSG, SERVER_COLOR);

	//delete_user(user_list, user_index);

}

void handle_register();

void handle_delete();

void handle_talk(int user_index){ //user index es el ejecutante. target a quien se lo mando.

	char message[40], data[40];
	int color = user_list[user_index]->color;

	read_string(user_list[user_index]->recv_buffer, data);

	sprintf(message, "%s>> %s", user_list[user_index]->name, data);

	write_talk(user_index, message, color);

	//for(int i = 0; i < connected_users; i++ )
	//	write_talk(i, message, color);
}

void write_talk(int target_index, char * message, int color){

	write_int(user_list[target_index]->send_buffer, TALK);
	write_string(user_list[target_index]->send_buffer, message);
	write_int(user_list[target_index]->send_buffer, color); //server color

	flush_buffer(user_list[target_index]->connection_descriptor, user_list[target_index]->send_buffer);


}

void handle_change_color();

void handle_change_pw();

void handle_kick();

void handle_ban();

void handle_disconnect();
void write_disconnect();

void handle_check_logs();
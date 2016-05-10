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

void check_command(char * command, char * arguments){

    int n_of_arguments = 1;
    //printf("Los arguments son: %s\n", arguments);
    //printf("long de los args: %d\n", strlen(arguments));

    if (strlen(arguments) != 0)
    {
        arguments = strtok(arguments, " ");

        while ((arguments = strtok(NULL, " ")) != NULL){
            n_of_arguments++;
            //printf("Next: %s\n", arguments);
        }

        //printf("La cantidad de arguments fue: %d\n", n_of_arguments);
    } else {
        n_of_arguments = 0;
    }

    if (strcmp(command, "/login") == 0) {
        if (n_of_arguments == 3) {
            printf("Your login works\n");
        } else {
            printf("%s\n", FAILED_LOGIN_MSG);
        }
    } else if (strcmp(command, "/create") == 0){
        if (n_of_arguments == 2) {
            printf("Your create works\n");
        } else {
            printf("%s\n", FAILED_CREATE_MSG);
        }
    } else if (strcmp(command, "/delete") == 0){
        if (n_of_arguments == 2) {
            printf("Your delete works\n");
        } else {
            printf("%s\n", FAILED_DELETE_MSG);
        }
    } else if (strcmp(command, "/change_color") == 0){
        if (n_of_arguments == 1) {
            printf("Your change_color works\n");
        } else {
            printf("%s\n", FAILED_CHANGE_COLOR_MSG);
        }
    } else if (strcmp(command, "/change_password") == 0){
        if (n_of_arguments == 3) {
            printf("Your change_password works\n");
        } else {
            printf("%s\n", FAILED_CHANGE_PASSWORD_MSG);
        }
    } else if (strcmp(command, "/kick") == 0){
        if (n_of_arguments == 2) {
            printf("Your kick works\n");
        } else {
            printf("%s\n", FAILED_KICK_MSG);
        }
    } else if (strcmp(command, "/ban") == 0){
        if (n_of_arguments == 2) {
            printf("Your ban works\n");
        } else {
            printf("%s\n", FAILED_BAN_MSG);
        }
    } else if (strcmp(command, "/disconnect") == 0){
        if (n_of_arguments == 0) {
            printf("Your disconnect works\n");
        } else {
            printf("%s\n", FAILED_DISCONNECT_MSG);
        }
    }
}

void read_user_input(char * user_input){

    char * command;
    char * arguments;

    scanf (" %[^\n]%*c", user_input);
    //printf("El texto ingresado fue: %s\n", user_input);

    printf("%s\n", user_input);

    command = strtok(user_input, " ");
    //printf("Command is: %s\n", command);

    arguments = strtok(NULL, "");
    //printf("Arguments are: %s\n", arguments);

    if (arguments != NULL) check_command(command, arguments);
    else check_command(command, "");
    
}



int main(int argc , char *argv[])
{

    fd_set fds;
    int maxfd, r_bytes;
    char stdin_buffer[20];

    // wolf
    char user_input[100];


    init_client("127.0.0.1", 8888);

    //write_login("admin", "admin", 5); //debe devolver valor asi hago si es -1, return;
    write_register("pedrito", "pedrito123");
    //write_talk("hola que tal");

    maxfd = client_connection_id;
     
    while (1){

        FD_ZERO(&fds);
        FD_SET(client_connection_id, &fds); 
        FD_SET(0, &fds);

        select(maxfd+1, &fds, NULL, NULL, NULL);

        if (FD_ISSET(0, &fds)){
            //fgets(stdin_buffer, 20, stdin); 
            read_user_input(user_input);
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

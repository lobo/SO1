#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void check_command(char * command, char * arguments){

    int n_of_arguments = 1;
    char saved_args[100];
    char arg1[100], arg2[100], arg3[100];
    //printf("Los arguments son: %s\n", arguments);
    //printf("long de los args: %d\n", strlen(arguments));

    strcpy(saved_args,arguments);

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

    //printf("ylos saved args son: %s\n", saved_args);

    if (n_of_arguments == 3) {
        sscanf(saved_args,"%s %s %s", arg1, arg2, arg3);
    } else if (n_of_arguments == 2) {
        sscanf(saved_args,"%s %s", arg1, arg2);
    } else if (n_of_arguments == 1) {
        sscanf(saved_args,"%s", arg1);
    } else {
        // just chatting
    }
    //printf("ACA ESTAN LOS PIBES: %s %s %s\n", arg1, arg2, arg3);
    //printf("And n_of_arguments is: %d\n", n_of_arguments);
    if (strcmp(command, "/login") == 0) {
        if (n_of_arguments == 3) {
            printf("Your login works, and the arguments are: %s %s %s\n", arg1, arg2, arg3);
        } else {
            printf("%s\n", FAILED_LOGIN_MSG);
        }
    } else if (strcmp(command, "/create") == 0){
        if (n_of_arguments == 2) {
            printf("Your create works, and the arguments are: %s %s\n", arg1, arg2);
        } else {
            printf("%s\n", FAILED_CREATE_MSG);
        }
    } else if (strcmp(command, "/delete") == 0){
        if (n_of_arguments == 2) {
            printf("Your delete works, and the arguments are: %s %s\n", arg1, arg2);
        } else {
            printf("%s\n", FAILED_DELETE_MSG);
        }
    } else if (strcmp(command, "/change_color") == 0){
        if (n_of_arguments == 1) {
            printf("Your change_color works, and the arguments are: %s\n", arg1);
        } else {
            printf("%s\n", FAILED_CHANGE_COLOR_MSG);
        }
    } else if (strcmp(command, "/change_password") == 0){
        if (n_of_arguments == 3) {
            printf("Your change_password works, and the arguments are: %s %s %s\n", arg1, arg2, arg3);
        } else {
            printf("%s\n", FAILED_CHANGE_PASSWORD_MSG);
        }
    } else if (strcmp(command, "/kick") == 0){
        if (n_of_arguments == 2) {
            printf("Your kick works, and the arguments are: %s %s\n", arg1, arg2);
        } else {
            printf("%s\n", FAILED_KICK_MSG);
        }
    } else if (strcmp(command, "/ban") == 0){
        if (n_of_arguments == 2) {
            printf("Your ban works, and the arguments are: %s %s\n", arg1, arg2);
        } else {
            printf("%s\n", FAILED_BAN_MSG);
        }
    } else if (strcmp(command, "/disconnect") == 0){
        if (n_of_arguments == 0) {
            printf("Your disconnect works, and the arguments are: \n");
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




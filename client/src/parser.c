#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void static check_errors(int argsNumber, int parameters, char * errorMessage) {
	if (strcmp(errorMessage, FAILED_LOGIN_MSG) == 0)
	{
		if (argsNumber == 3) {
    		printf("Succcess!\n");
    	} else {
    		printf("%s\n", FAILED_LOGIN_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_CREATE_MSG) == 0) {
		if(argsNumber == 3)
    	{
    		printf("Succcess!\n");
    	} else {
    		printf("%s\n", FAILED_CREATE_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_DELETE_MSG) == 0) {
		if (argsNumber == 2)
    	{
    		printf("Succcess!\n");
    	} else {
    		printf("%s\n", FAILED_DELETE_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_CHANGE_COLOR_MSG) == 0) {
		if (argsNumber == 1)
    	{
    		printf("Succcess!\n");
    	} else {
    		printf("%s\n", FAILED_CHANGE_COLOR_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_CHANGE_PASSWORD_MSG) == 0) {
		if (argsNumber == 3){
    		printf("Succcess!\n");
    	} else {
    		printf("%s\n", FAILED_CHANGE_PASSWORD_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_KICK_MSG) == 0) {
		if (argsNumber == 2) {
    		printf("Succcess!\n");
    	} else {
    		printf("%s\n", FAILED_KICK_MSG);
    	}

	} else if (strcmp(errorMessage, FAILED_BAN_MSG) == 0) {
	   	if (argsNumber == 2) {
    		printf("Succcess!\n");
    	} else {
    		printf("%s\n", FAILED_BAN_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_DISCONNECT_MSG) == 0){
		if (argsNumber == 0) {
    		printf("Goodbye!\n");
    	} else {
    		printf("%s\n", FAILED_DISCONNECT_MSG);
    	}
	} else {
		printf("There was some error.\n");
	}
}

/*
int
main()     
{
    char * line = malloc(128); 
    while (1) {

	    
	    fgets(line, 128, stdin);

   		char command[20];
    	sscanf(line, "%20s ", command);

	    line = strchr(line, ' ');

	    printf("The Command is: %s\n", command);
        //printf("%s\n", line);

        char space[2] = " ";
        char * token;
        token = strtok(line, space);
        int argumentsCount = 0;

        while( token != NULL ) 
        {
            //printf( "Token is: %s\n", token);
            token = strtok(NULL, space);
            argumentsCount++;
        }

        printf("El comando tenia args: %d\n", argumentsCount);

        if (strcmp(command, "/login") == 0) {
	    	check_errors(argumentsCount, 3, FAILED_LOGIN_MSG);
	    } else if (strcmp(command, "/create") == 0){
	    	check_errors(argumentsCount, 3, FAILED_CREATE_MSG);
	    } else if (strcmp(command, "/delete") == 0){
	    	check_errors(argumentsCount, 2, FAILED_DELETE_MSG);
	    } else if (strcmp(command, "/change_color") == 0){
	    	check_errors(argumentsCount, 1, FAILED_CHANGE_COLOR_MSG);
	    } else if (strcmp(command, "/change_password") == 0){
	    	check_errors(argumentsCount, 3, FAILED_CHANGE_PASSWORD_MSG);
	    } else if (strcmp(command, "/kick") == 0){
	    	check_errors(argumentsCount, 2, FAILED_KICK_MSG);
	    } else if (strcmp(command, "/ban") == 0){
	    	check_errors(argumentsCount, 2, FAILED_BAN_MSG);
	    } else if (strcmp(command, "/disconnect") == 0){
	    	check_errors(argumentsCount, 0, FAILED_DISCONNECT_MSG);
	    } else {
	    	//printf("I don't know that command, bro.\n");
            break;
	    }
	}

    free(line);

	return 0;
}
*/


void parse(){
     char * line = malloc(128); 
        
    fgets(line, 128, 0);

    char command[20];
    sscanf(line, "%20s ", command);

    line = strchr(line, ' ');

    printf("The Command is: %s\n", command);
    //printf("%s\n", line);

    char space[2] = " ";
    char * token;
    token = strtok(line, space);
    int argumentsCount = 0;

    while( token != NULL ) 
    {
        //printf( "Token is: %s\n", token);
        token = strtok(NULL, space);
        argumentsCount++;
    }

    printf("El comando tenia args: %d\n", argumentsCount);

    if (strcmp(command, "/login") == 0) {
        check_errors(argumentsCount, 3, FAILED_LOGIN_MSG);
    } else if (strcmp(command, "/create") == 0){
        check_errors(argumentsCount, 3, FAILED_CREATE_MSG);
    } else if (strcmp(command, "/delete") == 0){
        check_errors(argumentsCount, 2, FAILED_DELETE_MSG);
    } else if (strcmp(command, "/change_color") == 0){
        check_errors(argumentsCount, 1, FAILED_CHANGE_COLOR_MSG);
    } else if (strcmp(command, "/change_password") == 0){
        check_errors(argumentsCount, 3, FAILED_CHANGE_PASSWORD_MSG);
    } else if (strcmp(command, "/kick") == 0){
        check_errors(argumentsCount, 2, FAILED_KICK_MSG);
    } else if (strcmp(command, "/ban") == 0){
        check_errors(argumentsCount, 2, FAILED_BAN_MSG);
    } else if (strcmp(command, "/disconnect") == 0){
        check_errors(argumentsCount, 0, FAILED_DISCONNECT_MSG);
    } else {
        //printf("I don't know that command, bro.\n");
    }
    free(line);
    
}
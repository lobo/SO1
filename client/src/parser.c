#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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



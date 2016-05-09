#include <stdio.h>

#define FAILED_LOGIN_MSG "Command syntax error. Correct format is: /login username password color"
#define FAILED_CREATE_MSG "Command syntax error. Correct format is: /create username password"
#define FAILED_DELETE_MSG "Command syntax error. Correct format is: /delete username password"
#define FAILED_CHANGE_COLOR_MSG "Command syntax error. Correct format is: /change_color color"
#define FAILED_CHANGE_PASSWORD_MSG "Command syntax error. Correct format is: /change_password username old_password new_password"
#define FAILED_KICK_MSG "Command syntax error. Correct format is: /login username reason"
#define FAILED_BAN_MSG "Command syntax error. Correct format is: /login username reason"
#define FAILED_DISCONNECT_MSG "Command syntax error. Correct format is: /disconnect"

void static check_errors(int argsNumber, char * arguments[], int parameters, char * errorMessage) {
	if (strcmp(errorMessage, FAILED_LOGIN_MSG) == 0)
	{
		if (argsNumber == 3) {
    		for (int i = 0; i < argsNumber; i++) {
        		printf("Argument %i is: %s\n", i, arguments[i]);
    		}
    	} else {
    		printf("%s\n", FAILED_LOGIN_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_CREATE_MSG) == 0) {
		if(argsNumber == 3)
    	{
    		for (int i = 0; i < argsNumber; i++) {
        		printf("Argument %i is: %s\n", i, arguments[i]);
    		}
    	} else {
    		printf("%s\n", FAILED_CREATE_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_DELETE_MSG) == 0) {
		if (argsNumber == 2)
    	{
    		for (int i = 0; i < argsNumber; i++) {
        		printf("Argument %i is: %s\n", i, arguments[i]);
    		}
    	} else {
    		printf("%s\n", FAILED_DELETE_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_CHANGE_COLOR_MSG) == 0) {
		if (argsNumber == 1)
    	{
    		for (int i = 0; i < argsNumber; i++) {
        		printf("Argument %i is: %s\n", i, arguments[i]);
    		}
    	} else {
    		printf("%s\n", FAILED_CHANGE_COLOR_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_CHANGE_PASSWORD_MSG) == 0) {
		if (argsNumber == 3){
    		for (int i = 0; i < argsNumber; i++) {
        		printf("Argument %i is: %s\n", i, arguments[i]);
    		}
    	} else {
    		printf("%s\n", FAILED_CHANGE_PASSWORD_MSG);
    	}
	} else if (strcmp(errorMessage, FAILED_KICK_MSG) == 0) {
		if (argsNumber == 2) {
    		for (int i = 0; i < argsNumber; i++) {
        		printf("Argument %i is: %s\n", i, arguments[i]);
    		}
    	} else {
    		printf("%s\n", FAILED_KICK_MSG);
    	}

	} else if (strcmp(errorMessage, FAILED_BAN_MSG) == 0) {
	   	if (argsNumber == 2) {
    		for (int i = 0; i < argsNumber; i++) {
        		printf("Argument %i is: %s\n", i, arguments[i]);
    		}
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


int
main()     
{

    while (1) {
	    char * line = malloc(128); 
	    char * origLine = line;
	    fgets(line, 128, stdin);

   		char command[20];
    	sscanf(line, "%20s ", command);

	    line = strchr(line, ' ');

	    printf("The Command is: %s\n", command);

	    unsigned argumentsCount = 0;
	    char **arguments = malloc(sizeof(char *));

   		while (1) {
        	
        	char arg[20];

        	if (line && (sscanf(++line, "%20s", arg) == 1)) {
            	arguments[argumentsCount] = malloc(sizeof(char) * 20);
            	strncpy(arguments[argumentsCount], arg, 20);
	            argumentsCount++;
	            arguments = realloc(arguments, sizeof(char *) * argumentsCount + 1);
    	        line = strchr(line, ' ');
        	}
        	else {
            	break;
        	}
    	}

	    if (strcmp(command, "/login") == 0) {
	    	check_errors(argumentsCount, arguments, 3, FAILED_LOGIN_MSG);
	    } else if (strcmp(command, "/create") == 0){
	    	check_errors(argumentsCount, arguments, 3, FAILED_CREATE_MSG);
	    } else if (strcmp(command, "/delete") == 0){
	    	check_errors(argumentsCount, arguments, 2, FAILED_DELETE_MSG);
	    } else if (strcmp(command, "/change_color") == 0){
	    	check_errors(argumentsCount, arguments, 1, FAILED_CHANGE_COLOR_MSG);
	    } else if (strcmp(command, "/change_password") == 0){
	    	check_errors(argumentsCount, arguments, 3, FAILED_CHANGE_PASSWORD_MSG);
	    } else if (strcmp(command, "/kick") == 0){
	    	check_errors(argumentsCount, arguments, 2, FAILED_KICK_MSG);
	    } else if (strcmp(command, "/ban") == 0){
	    	check_errors(argumentsCount, arguments, 2, FAILED_BAN_MSG);
	    } else if (strcmp(command, "/disconnect") == 0){
	    	check_errors(argumentsCount, arguments, 0, FAILED_DISCONNECT_MSG);
	    } else {
	    	printf("I don't know that command, bro.\n");
	    }

	   	for (int i = 0; i < argumentsCount; i++) {
	    	free(arguments[i]);
	    }

	    free(arguments);
	    free(origLine);
	}

	return 0;
}
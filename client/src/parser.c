#include "parser.h"

static char* all_cmds[] = {"login", "register", "logout", "change_password", "change_privileges", "change_color", "delete", "kick", "ban"};
static int cmds_amount = 9;

void del_spaces(char* str);
void replace_char(char* str, char c1, char c2);

/*
int check_command(char * command, char * arguments){

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
        if (n_of_arguments == 2) {
            printf("Your login works, and the arguments are: %s %s\n", arg1, arg2);
            return CMD_LOGIN;
        } else {
            printf("%s\n", FAILED_LOGIN_MSG);
            return CMD_ERROR;
        }
    } else if (strcmp(command, "/register") == 0){
        if (n_of_arguments == 2) {
            printf("Your create works, and the arguments are: %s %s\n", arg1, arg2);
            return CMD_REGISTER;
        } else {
            printf("%s\n", FAILED_REGISTER_MSG);
            return CMD_ERROR;
        }
    } else if (strcmp(command, "/delete") == 0){
        if (n_of_arguments == 2) {
            printf("Your delete works, and the arguments are: %s %s\n", arg1, arg2);
            return CMD_DELETE_USER;
        } else {
            printf("%s\n", FAILED_DELETE_MSG);
            return CMD_ERROR;
        }
    } else if (strcmp(command, "/change_color") == 0){
        if (n_of_arguments == 1) {
            printf("Your change_color works, and the arguments are: %s\n", arg1);
            return CMD_CH_COLOR;
        } else {
            printf("%s\n", FAILED_CHANGE_COLOR_MSG);
            return CMD_ERROR;
        }
    } else if (strcmp(command, "/change_password") == 0){
        if (n_of_arguments == 3) {
            printf("Your change_password works, and the arguments are: %s %s %s\n", arg1, arg2, arg3);
            return CMD_CH_PW;
        } else {
            printf("%s\n", FAILED_CHANGE_PASSWORD_MSG);
            return CMD_ERROR;
        }
    } else if (strcmp(command, "/kick") == 0){
        if (n_of_arguments == 2) {
            printf("Your kick works, and the arguments are: %s %s\n", arg1, arg2);
            return CMD_KICK;
        } else {
            printf("%s\n", FAILED_KICK_MSG);
            return CMD_ERROR;
        }
    } else if (strcmp(command, "/ban") == 0){
        if (n_of_arguments == 2) {
            printf("Your ban works, and the arguments are: %s %s\n", arg1, arg2);
            return CMD_BAN;
        } else {
            printf("%s\n", FAILED_BAN_MSG);
            return CMD_ERROR;
        }
    } else if (strcmp(command, "/logout") == 0){
        if (n_of_arguments == 0) {
            printf("Your logout works, and the arguments are: \n");
            return CMD_LOGOUT;
        } else {
            printf("%s\n", FAILED_LOGOUT_MSG);
            return CMD_ERROR;
        }
    }
    return CMD_ERROR;
}*/

/*int read_user_input(char * user_input){

    char * command;
    char * arguments;

	printf("EMPEZAMOS...\n");
	printf("Argumento recibido: %s\n", user_input);

    //scanf (" %[^\n]%*c", user_input);
    //printf("El texto ingresado fue: %s\n", user_input);

    printf("%s\n", user_input);

    command = strtok(user_input, " ");
    //printf("Command is: %s\n", command);

    arguments = strtok(NULL, "");
    //printf("Arguments are: %s\n", arguments);

    if (arguments != NULL)
		return check_command(command, arguments);
    else
		return check_command(command, "");
    
}*/

/**
 * Returns de command code and the arguments 1 and 2 initialized if needed
 */
int parse_cmd(char* msg, char* arg1, char* arg2) {
	
	int i = 0;
	int msg_length;
	int cmd_length;
	int arg1_length = 0;
	int arg2_length = 0;
	
	del_spaces(msg);
	
	if(*msg != '/') {	//Si no empieza con una barra es que estan chateando (no es comando)
		printf("Recibi un simple chat: %s\n", msg);
		return CMD_CHAT;
	}

	printf("Recibi un comando: %s\n", msg);
	
	while(msg[i] != ' ' && msg[i] != '\0')
		i++;
	
	msg_length = strlen(msg);
	
	replace_char(msg, ' ', '\0');
	cmd_length = strlen(msg);
		
	if (msg_length - cmd_length - 1 > 0) {	//Si queda algo despues del comando
		arg1_length = strlen(msg + cmd_length + 1);
		strcpy(arg1, msg + cmd_length + 1);
		if (msg_length - cmd_length - arg1_length - 2 > 0) { 	//Si hay un 2do arg
			arg2_length = strlen(msg + arg1_length + 2);
			strcpy(arg2, msg + cmd_length + arg1_length + 2);
		}
	}
	
	for (int j = 0; j < cmds_amount; j++)
		if (strcmp(all_cmds[j], msg+1) == 0){
			msg_length = msg_length - cmd_length - 1;
			switch (j) {
				case 0: 	//login username password
					if (arg2_length == 0) {
						fprintf(stderr, FAILED_LOGIN_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_LOGIN;
					
				case 1:		//register username password
					if (arg2_length == 0) {
						fprintf(stderr, FAILED_REGISTER_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_REGISTER;
					
				case 2:		//logout
					if (arg1_length != 0) {
						fprintf(stderr, FAILED_LOGOUT_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_LOGOUT;
					
				case 3:		//change_password old_pass new_pass
					if (arg2_length == 0) {
						fprintf(stderr, FAILED_CHANGE_PASSWORD_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_CH_PW;
					
				case 4:		//change_privileges username new_priv
					if (arg2_length == 0) {
						fprintf(stderr, FAILED_CHANGE_PRIVILEGES_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_CH_PRIVS;
					
				case 5:		//change_color color
					if (arg1_length == 0 || arg2_length != 0) {
						fprintf(stderr, FAILED_CHANGE_COLOR_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_CH_COLOR;
					
				case 6:		//delete username
					if (arg1_length == 0 || arg2_length != 0) {
						fprintf(stderr, FAILED_DELETE_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_DELETE_USER;
					
				case 7:		//kick username reason
					if (arg2_length == 0) {
						fprintf(stderr, FAILED_CHANGE_PRIVILEGES_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_KICK;
					
				case 8:		//ban username reason
					if (arg2_length == 0) {
						fprintf(stderr, FAILED_CHANGE_PRIVILEGES_MSG);
						j = cmds_amount;
						break;
					}
					return CMD_BAN;
			}
		}
		
	return CMD_ERROR;
}

/**
 * Borra espacios extra que pueda haber en un string (y todos los primeros)
 */
void del_spaces(char* str){
	
	char* str2 = str;
	
	while (*str == ' ')	//hago que str apunte al primer char que no sea un espacio
		str++;

	str--; //fix porque despues lo aumento en el while. #AhListoQueVillero
	
	while (*str++ != 0){
		if (*str != ' ')
			*str2++ = *str;
		else{
			if (*(str+1) == ' ')
				continue;
			else
				*str2++ = *str;
			}
	}
}

/**
 * Reemplaza el char c1 por c2 en todo un string.
 */
 void replace_char(char* str, char c1, char c2) {
	 while (*str != '\0') {
		if (*str == c1)
			*str = c2;
		str++;
	}
 }




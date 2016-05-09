#ifndef PARSER_H
#define PARSER_H

#define FAILED_LOGIN_MSG "Command syntax error. Correct format is: /login username password color"
#define FAILED_CREATE_MSG "Command syntax error. Correct format is: /create username password"
#define FAILED_DELETE_MSG "Command syntax error. Correct format is: /delete username password"
#define FAILED_CHANGE_COLOR_MSG "Command syntax error. Correct format is: /change_color color"
#define FAILED_CHANGE_PASSWORD_MSG "Command syntax error. Correct format is: /change_password username old_password new_password"
#define FAILED_KICK_MSG "Command syntax error. Correct format is: /login username reason"
#define FAILED_BAN_MSG "Command syntax error. Correct format is: /login username reason"
#define FAILED_DISCONNECT_MSG "Command syntax error. Correct format is: /disconnect"

void static check_errors(int argsNumber, int parameters, char * errorMessage);
void parse();


#endif
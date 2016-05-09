#ifndef TCPCLIENT_H
#define TCPCLIENT_H

void init_client();

void write_login(char * username, char * password, char color);

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


#endif
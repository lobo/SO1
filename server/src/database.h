#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3/sqlite3.h"

#define LOGIN_STATUS_SUCCESS 0
#define LOGIN_STATUS_FAIL 1
#define LOGIN_STATUS_BANNED 2

#define QUERY_OK 0
#define ERROR_GENERIC 100
#define ERROR_USER_ALREADY_REGISTERED 101

#define USER_NORMAL 0
#define USER_MOD 1
#define USER_ADMIN 2

typedef struct {
    char username[30];
    char password[30];
    char privileges;
    int login_status;
} Login_info;

int register_user(char* username, char* password);
int update_privileges(char* username, char privilege);
int login(char* username, char* password, Login_info* login_info);
int insert_chatlog(char * username, char * message);
int get_chatlog(char* from, char* to, char** chatlog);
int delete_username(char * username);
int db_create();
int is_db_initiated();

#endif
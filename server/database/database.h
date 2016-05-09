#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sqlite3.h>
#include "sqlite3/sqlite3.h"

#define LOGIN_STATUS_SUCCESS  0
#define LOGIN_STATUS_FAIL 1
#define LOGIN_STATUS_BANNED 2

#define USER_NORMAL 0
#define USER_MOD 1
#define USER_ADMIN 2

typedef struct {
    char username[20];
    char password[20];
    int login_status;
} Login_info;

static int register_user(char* username, char* password);
static int login(char* username, char* password);
static int insert_chatlog(char * username, char * message);
static int get_chatlog(char* from, char* to);
static int delete_username(char * username);


#endif
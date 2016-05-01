#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sqlite3.h>
#include "sqlite3/sqlite3.h"

#define LOGIN_SUCCESS  0
#define LOGIN_FAIL  !LOGIN_SUCCESS

typedef struct {
    char username[30];
    char password[30];
    int login_status;
} Login_info;

static int callback(void* NotUsed, int argc, char** argv, char** column_name);
static int register_user(char* username, char* password);
static int login(char* username, char* password);
static int login_callback(void* user_login_info, int argc, char** argv, char** column_name);

/*void db_close();
int db_open(const char* path);
static void db_create();*/

#endif
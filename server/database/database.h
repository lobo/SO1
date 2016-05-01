#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sqlite3.h>
#include "sqlite3/sqlite3.h"

static int callback(void* NotUsed, int argc, char** argv, char** column_name);
static int register_user(char* username, char* password);

/*void db_close();
int db_open(const char* path);
static void db_create();*/

#endif
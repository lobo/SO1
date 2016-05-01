#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "./sqlite3/sqlite3.h"

#define DB_PREPARE_V2(db, query, statement) {\
    int rc = sqlite3_prepare_v2(db, query, -1, &statement, NULL);\
    if (rc != SQLITE_OK) {\
        printf("Failed to fetch data: %s\n", sqlite3_errmsg(db));\
        sqlite3_close(db);\
        exit(1);\
    }\
}

#define DB_FINALIZE(db) {\
    int rc = sqlite3_finalize(statement);\
    if (rc != SQLITE_OK) {\
        printf("Couldn't finalize the db: %s\n", sqlite3_errmsg(db));\
        sqlite3_close(db);\
        exit(1);\
    }\
}

#define DB_QUERY(db, query) {\
    int rc;\
    char * err_msg;\
    rc = sqlite3_exec(db, query, 0, 0, &err_msg);\
    if (rc != SQLITE_OK ) {\
        printf("SQL error: %s\n", err_msg);\
        sqlite3_free(err_msg);\
        sqlite3_close(db);\
        exit(1);\
    }\
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

const char* db_file = "DB/chatroom.db";

static int callback(void* NotUsed, int argc, char** argv, char** column_name) {
    int i;
    for (i = 0 ; i < argc ; i++) {
        printf("%s = %s\n", column_name[i], argv[i] ? argv[i] : "NULL");
    }
    putchar('\n');
    return 0;
}

static int register_user (char* username, char* password) {
    sqlite3* db;
    int rc;
    char* sql;
    char* errMsg = 0;

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "INSERT INTO USERNAME(USER, PASSWORD) VALUES ('%s', '%s');", username, password);

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't register your username. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Username %s registered successfully\n", username);
    }

    sqlite3_close(db);

    return rc;
}

void db_close() {
    sqlite3_close(db);
}

int db_open(const char* path) {
    int has_to_populate = 0;
    int rc;

    if (!file_exist(path)) {
        has_to_populate = 1;
    }

    rc = sqlite3_open(path, &db);

    if (rc != SQLITE_OK) {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {

        if (has_to_populate) {
            printf("%s\n", "Database does not exist. Creating...");
            db_create();
        }

        printf("%s\n", "Opened database successfully");
    }

    return 0;
}

static void db_create() {
    char * sql;
    char * err_msg;
    int rc;

    // sql = poner tablas aca;

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        printf("SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        exit(1);
    }
}

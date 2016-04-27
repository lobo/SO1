#include <sqlite3.h>
#include <stdio.h>
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
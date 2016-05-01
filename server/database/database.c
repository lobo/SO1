#include "database.h"

/*#define DB_PREPARE_V2(db, query, statement) {\
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
}*/

const char* db_file = "chatroom.db";

int main(int argc, char const *argv[])
{
    /*sqlite3* db;
    int rc;
    char sql[256];
    char* errMsg = 0;

    printf("DB path: %s\n", db_file);
    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "CREATE TABLE USERNAME(" \
        "ID INTEGER PRIMARY KEY," \
        "USER CHAR(30) UNIQUE NOT NULL," \
        "PASSWORD CHAR (30) NOT NULL);");

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't create your table. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    sqlite3_close(db);*/

    if (argc == 2) { //hago que registre y se logee con el mismo usuario y contraseña, paja escribir las 2 por separado.
        char* user_pass = malloc(sizeof(char) * strlen(argv[1]));
        strcpy(user_pass, argv[1]);
        register_user(user_pass, user_pass);
        login(user_pass, user_pass);
    }
    else
        fprintf(stderr, "Just 1 argument expected\n");

    return 0;
}

static int callback(void* NotUsed, int argc, char** argv, char** column_name) {
    int i;
    for (i = 0 ; i < argc ; i++) {
        printf("%s = %s\n", column_name[i], argv[i] ? argv[i] : "NULL");
    }
    putchar('\n');
    return 0;
}

static int register_user(char* username, char* password) {
    sqlite3* db;
    int rc;
    char sql[128];
    char* errMsg = 0;

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "INSERT INTO USERNAME(USER, PASSWORD) VALUES ('%s', '%s');", username, password);
    printf("Comando SQL: %s\n", sql);

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

static int login(char* username, char* password) {
    sqlite3* db;
    int rc;
    char sql[128];
    char* errMsg = 0;
    Login_info login_info;

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "SELECT USER, PASSWORD " \
        "FROM USERNAME " \
        "WHERE USER='%s' AND PASSWORD='%s';", username, password);
    printf("Comando SQL: %s\n", sql);

    strcpy(login_info.username, username);
    strcpy(login_info.password, password);
    login_info.login_status = LOGIN_FAIL;

    rc = sqlite3_exec(db, sql, login_callback, (void*)(&login_info), &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't make your request. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else if (login_info.login_status){
        fprintf(stdout, "Login successful!!!\n");
    }

    sqlite3_close(db);

    return login_info.login_status;
}

/*
* Callback ejecutado al intentar logear. Si retorna distinto a 0 sqlite3_exec devuelve error.
*/
static int login_callback(void* user_login_info, int argc, char** argv, char** column_name) {
    int i;
    Login_info* login_info = (Login_info*) user_login_info;

    if (!strcmp(login_info->username, argv[0]) || !strcmp(login_info->password, argv[1])) {
        login_info->login_status = LOGIN_SUCCESS;
        printf("User login successfull.\n");
    } else {
        fprintf(stderr, "User login failed. (Datos no coinciden)\n");
        return 1;
    }

    return 0;
}

/*void db_close() {
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
}*/

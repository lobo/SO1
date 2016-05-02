#include "database.h"

const char* db_file = "chatroom.db";
static int callback(void* NotUsed, int argc, char** argv, char** column_name);
static int login_callback(void* user_login_info, int argc, char** argv, char** column_name);

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
        "PASSWORD CHAR (30) NOT NULL," \
        "PRIVILEGES INT DEFAULT 0," \
        "DATE_CREATED DATETIME NOT NULL," \
        "LAST_LOGIN DATETIME);");

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
        //register_user(user_pass, user_pass);
        if (login(user_pass, user_pass) == LOGIN_SUCCESS)
            printf("Loguie bien.\n");
        else 
            printf("Loguie mal.\n");
    }
    else
        fprintf(stderr, "Just 1 argument expected\n");

    return 0;
}

/*
* Callback generico para la ejecucion de comandos SQL
*/
static int callback(void* NotUsed, int argc, char** argv, char** column_name) {
    int i;
    for (i = 0 ; i < argc ; i++) {
        printf("%s = %s\n", column_name[i], argv[i] ? argv[i] : "NULL");
    }
    putchar('\n');
    return 0;
}

/*
* Registro un nuevo usuario en mi base de datos si no esta ya registrado
*/
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

    sprintf(sql, "INSERT INTO USERNAME(USER, PASSWORD, PRIVILEGES, DATE_CREATED) VALUES ('%s', '%s', 0, datetime('now', 'localtime'));", username, password);
    printf("Comando SQL: %s\n", sql);

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't register your username. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Username %s registered successfully\n", username);
    }

    sqlite3_close(db);

    return rc;
}

/*
* Funcion de login
*/
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
    }

    sprintf(sql, "UPDATE USERNAME SET LAST_LOGIN = datetime('now', 'localtime') WHERE USER = '%s';", login_info.username);
    printf("Comando SQL: %s\n", sql);
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't make your request. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
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

    printf("Me llega la siguiente data: %s / %s\n", argv[0], argv[1]);

    login_info->login_status = LOGIN_SUCCESS;
       
    return 0;
}

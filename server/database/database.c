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

// creation of both tables: users and chatlogs
static void db_create() {
    sqlite3* db;
    char * sql;
    char * err_msg;
    int rc;

    sql = "CREATE TABLE USERS(" \
          "ID INTEGER PRIMARY KEY" \
          "username         CHAR(20) NOT NULL UNIQUE," \
          "password         CHAR(20) NOT NULL," \
          "privileges       INT DEFAULT 0," \
          "date_created     DATETIME NOT NULL datetime('now', 'localtime')," \
          "last_login       DATETIME," \
          "banned_flag      INTEGER DEFAULT 0);" \

          "CREATE TABLE CHATLOG(" \
          "ID INTEGER PRIMARY KEY," \
          "DATE_TIME    DATETIME NOT NULL DEFAULT datetime('now', 'localtime'),", \
          "USER_ID     INTEGER NOT NULL," \
          "MESSAGE      TEXT NOT NULL)," \
          "FOREIGN KEY (USER_ID) REFERENCES USERS(ID);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        printf("SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        exit(1);
    }

}

/*
* Registro un nuevo usuario indicando privilegios en mi base de datos si no esta ya registrado
* Los privilegios estan definidos en database.h
*/
static int register_user(char* username, char* password, int privileges) {
    sqlite3* db;
    int rc;
    char sql[160];
    char* errMsg = 0;

    if (privileges != USER_NORMAL && privileges != USER_MOD && privileges != USER_ADMIN) {
        fprintf(stderr, "User privileges not correct. Please check for correct privileges to register user\n");
        exit(1);
    }

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(1);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "INSERT INTO USERS(USER, PASSWORD, PRIVILEGES, DATE_CREATED) VALUES ('%s', '%s', %d, datetime('now', 'localtime'));", username, password, privileges);
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


// Elimino un usuario por su username... utilidad???
static int delete_username(char * username) {
    sqlite3* db;
    int rc;
    char sql[64];
    char* errMsg = 0;

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(1);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "DELETE FROM USERS WHERE USERNAME = '%s';", username);
    printf("Comando SQL: %s\n", sql);

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't delete the username. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Username %s deleted successfully.\n", username);
    }

    sqlite3_close(db);

    return rc;
}

/*
* Busca chatlogs entre tales fechas
* Las fechas tienen el formato YYYY-MM-DD HH:MM:SS
* Si el formato es incorrecto SQLite me tira error y lo handleo
*/
static int get_chatlog(char* from, char* to, char** chatlog) {
    sqlite3* db;
    int rc;
    char sql[256];
    char* errMsg = 0;

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "SELECT DATE_TIME, USERNAME, MESSAGE " \
        "FROM USERS, CHATLOG " \
        "WHERE USERS.ID = CHATLOG.USER_ID AND DATE_TIME >= datetime('%s') AND DATE_TIME <= datetime('%s');", from, to);
    printf("Comando SQL: %s\n", sql);

    rc = sqlite3_exec(db, sql, get_chatlog_callback, (void*) chatlog, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't get the chatlog. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);

    return rc;
}

/*
* Voy poniendo el resultado en el puntero a char que me pasaron y lo voy reallocando con cada tupla que devuelve.
*/
static int get_chatlog_callback(void* chatlog_ptr, int argc, char** argv, char** column_name) {
    char** chatlog = (char**) chatlog_ptr;
    int current_size = strlen(*chatlog);

    *chatlog = realloc(*chatlog, (current_size + strlen(argv[2]) + 1) * sizeof(char));
    if (*chatlog == 0) {
        fprintf(stderr, "No pudo alocarse la memoria necesaria para el chatlog. Cancelando...\n");
        return 1;
    }

    strcat(*chatlog, argv[2]);
    strcat(*chatlog, "\n");

    return 0;
}

/*
* Inserto nuevo mensaje en el chatlog. Esto puede ser tanto un mensaje de usuario como de sistema.
*/
static int insert_chatlog(char * username, char * message) {

    sqlite3* db;
    int rc;
    char sql[160];
    char* errMsg = 0;

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(1);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    sprintf(sql, "INSERT INTO CHATLOG(USER_ID, MESSAGE) VALUES ((SELECT ID FROM USERS WHERE USERNAME = '%s'), %s);", username, message);
    printf("Comando SQL: %s\n", sql);

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Couldn't log the current chatlog. Error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Log logged successfully.\n", username);
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
    char sql[160];
    char* errMsg = 0;
    Login_info login_info;

    rc = sqlite3_open(db_file, &db);

    if (rc) {
        fprintf(stderr, "Can't open DB file: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stdout, "Opened DB successfully\n");
    }

    //Search for the user and pw in the DB
    sprintf(sql, "SELECT USER, PASSWORD, PRIVILEGES, BANNED_FLAG " \
        "FROM USERS " \
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

    //Update the last time the user logged in in the DB
    sprintf(sql, "UPDATE USERS SET LAST_LOGIN = datetime('now', 'localtime') WHERE USER = '%s';", login_info.username);
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

    printf("Me llega la siguiente data: %s / %s / %s / %s\n", argv[0], argv[1], argv[2], argv[3]);

    if (atoi(argv[3]) == 1) {
        login_info -> login_status = LOGIN_STATUS_BANNED;
        return LOGIN_STATUS_BANNED;
    }

    login_info->login_status = LOGIN_STATUS_SUCCESS;

    return 0;
}

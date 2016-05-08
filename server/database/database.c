#include "database.h"
#include <time.h>

const char* db_file = "chatroom.db";
static int callback(void* NotUsed, int argc, char** argv, char** column_name);
static int login_callback(void* user_login_info, int argc, char** argv, char** column_name);

static sqlite3 * db;

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


// =========================
// Operations on the tables:
// =========================

static void execute_query(sqlite3 * db, char * query){
    
    int rc;
    char * err_msg;
    rc = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

}

// creation of both tables: users and chatlogs
static void db_create() {

    char * sql;
    char * err_msg;
    int rc;

    sql = "CREATE TABLE user("
          "username         CHAR(20) NOT NULL UNIQUE,"
          "password         CHAR(20) NOT NULL",
          "privileges       INTEGER NOT NULL DEFAULT 0",
          "date_created     DATE NOT NULL",
          "last_login       DATE NOT NULL",
          "banned_flag      INTEGER NOT NULL);"

          "CREATE TABLE chatlog("
          "date_time    DATE NOT NULL",
          "username     CHAR(20) NOT NULL",
          "message      CHAR(255) NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        printf("SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        exit(1);
    }

}

// Registro un nuevo usuario en mi base de datos si no esta ya registrado
static int insert_user(char* username, char* password) {
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


// Elimino un usuario por su username
static int delete_username(char * username) {

    char query[128];

    sprintf(query, "DELETE FROM user where username = %s;", username);

    execute_query(db, query);

    return 0;
}

// Busca chatlogs entre tales fechas
// TODO: Corregir el formato de las dates
static int get_chatlog(Date from, Date to) {

    char query[128];

    sprintf(query, "SELECT * FROM chatlog where date_time BETWEEN %s AND %s;", from, to);

    execute_query(db, query);

    return 0;
}

// Inserto un nuevo chatlog
static int insert_chatlog(char * username, char * message) {

    char query[128];

    // variables for time
    time_t rawtime;
    struct tm *info;
    char date_time[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(date_time,80,"%x - %I:%M%p", info); // La fecha tiene la forma: 08/23/12 - 12:40AM (quizas hay una manera mejor)

    sprintf(query, "INSERT INTO chatlog (date_time, username, message) VALUES (%s,%s,%s);", date_time, username, message);

    execute_query(db, query);

    return sqlite3_last_insert_rowid(db);
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

#include "logging.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct my_msgbuf {
    long mtype;
    char mtext[256];
};

char * errors_str[3] = {"INFO", "WARNING", "ERROR"};

void log_error(error_t error_type, char * error_description) {

    struct my_msgbuf buf;
    int msqid;
    key_t key;
    time_t timer;
    char formatted_date[26];
    char aux_buff[256];
    struct tm* tm_info;

    key = 123;

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget fallo");
        exit(1);
    }

    buf.mtype = 1; // works like this

    time(&timer);
    tm_info = localtime(&timer);
    strftime(formatted_date, 26, "%Y:%m:%d %H:%M:%S", tm_info);

    //printf("El tipo de error es: %s\n", errors_str[error_type]);
    //printf("La fecha es: %s\n", formatted_date);
    //printf("El error_description fue: %s\n", error_description);
    
    sprintf(aux_buff, "%s - %s: %s", errors_str[error_type], formatted_date, error_description);


    if (msgsnd(msqid, aux_buff, strlen(aux_buff)+1, 0) == -1) {
        perror("msgsnd failed!");
    }

}
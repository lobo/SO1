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
    char mtext[200];
};

char * errors_str[3] = {"INFO", "WARNING", "ERROR"};

void log_error(error_t error_type, char * error_description) {

    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // con esto me conecto al receiver
    /*if ((key = ftok("../server-logs.txt", 'B')) == -1) {
        perror("ftok fallo");
        exit(1);
    }*/

    key = 123;

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget fallo");
        exit(1);
    }

    //printf("Ya podes escribir...:\n");

    buf.mtype = 1; // works like this

    // aca falta ver de donde toma los logs
    // y poner la condicion segun el error que se le pase
    // para ver donde mandar esa informacion

    // aca stdin deberia ser input_stream
    /*
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    */


    time_t timer;
    char formatted_date[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(formatted_date, 26, "%Y:%m:%d %H:%M:%S", tm_info);

    char aux_buff[256];
    sprintf(aux_buff, "%s - %s: %s", errors_str[error_type], formatted_date, error_description);
    printf("aux_buff: %s\n", aux_buff);


    if (msgsnd(msqid, aux_buff, strlen(aux_buff)+1, 0) == -1) {
        perror("msgsnd failed!");
    }

}
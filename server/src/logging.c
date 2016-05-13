#include "logging.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

void logging_daemon(error_t error_type, FILE * input_stream) {
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // con esto me conecto al receiver
    if ((key = ftok("../msgq.c", 'B')) == -1) {
        perror("ftok fallo");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget fallo");
        exit(1);
    }

    printf("Ya podes escribir...:\n");

    buf.mtype = 1; // works like this

    // aca falta ver de donde toma los logs
    // y poner la condicion segun el error que se le pase
    // para ver donde mandar esa informacion

    // aca stdin deberia ser input_stream
    while(fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL) {
        int len = strlen(buf.mtext);

        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, len+1, 0) == -1) 
            perror("msgsnd");
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }  
}
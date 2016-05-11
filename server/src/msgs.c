#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

typedef enum {INFO, WARNING, ERROR} error_t;


/* Probarlo con el main, no probe el metodo aun.
int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    if ((key = ftok("msgs.c", 'B')) == -1) {
        perror("ftok fallo");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget fallo");
        exit(1);
    }
    
    printf("Ya podes escribir...:\n");

    buf.mtype = 1; // works like this

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

    return 0;
}*/


void logging_daemon(error_t error_type, FILE * input_stream) {
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    // con esto me conecto al receiver
    if ((key = ftok("msgs.c", 'B')) == -1) {
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

    while(fgets(buf.mtext, sizeof(buf.mtext), input_stream) != NULL) {
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




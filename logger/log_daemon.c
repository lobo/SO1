#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 200
#define LOGFILE_PATH "../logger/logs.txt"

struct msgbuf {
	long mtype;
	char message[MAX_SIZE];
};


int main(void)
{
    struct msgbuf buf;
    int msqid;
    key_t key = 123;

    if ((msqid = msgget(key, 0644)) == -1) { 
        perror("msgget error: fallo conectarse a la cola.");
        exit(1);
    }
    
    //printf("Listo para recibir mensajes.\n");

    while(1) { // corre siempre
        if (msgrcv(msqid, &buf, sizeof(buf.message), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("El mensaje es: \"%s\"\n", buf.message);
        FILE * fp = fopen(LOGFILE_PATH, "ab");
	    if (fp != NULL)
	    {
	        fputs(buf.message, fp);
	        fprintf(fp, "\n");
	        fclose(fp);
	    }

    }

    return 0;
}
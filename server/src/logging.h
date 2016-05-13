#ifndef LOGGING_H
#define LOGGING_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {INFO, WARNING, ERROR} error_t;

void logging_daemon(error_t error_type, FILE * input_stream);

#endif
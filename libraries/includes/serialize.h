#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "comm.h"


int send_int(int connection_descriptor, int message);
int send_string(int connection_descriptor, char * message);

int read_int(int connection_descriptor, int * message);
int read_string(int connection_descriptor, char * message);


#endif




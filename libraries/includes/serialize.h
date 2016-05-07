#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "comm.h"


int write_int(int connection_descriptor, int message);
int write_string(int connection_descriptor, char * message);
//int write_message(int connection_descriptor, t_msg * msg);

int read_int(int connection_descriptor);
int read_string(int connection_descriptor, char * read_buffer);
//int read_message(int connection_descriptor, t_msg * msg);




#endif




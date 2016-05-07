#include "serialize.h"
#include "comm.h"
#include <stdint.h>
#include <string.h>


int write_int(int connection_descriptor, int message){

	return send_data(connection_descriptor, (void*) &message, sizeof(int32_t));

}

int write_string(int connection_descriptor, char * message){

	int len = strlen(message) + 1;

	write_int(connection_descriptor, len);

	return send_data(connection_descriptor, message, len);

}

//int write_message(int connection_descriptor, t_msg * msg);

int read_int(int connection_descriptor){

	int message;
	receive_data(connection_descriptor, &message, sizeof(int32_t));

	return message;
}

int read_string(int connection_descriptor, char * read_buffer){

	int len = read_int(connection_descriptor);

	return receive_data(connection_descriptor, read_buffer, len);

}

//int read_message(int connection_descriptor, t_msg * msg);
#include "serialize.h"
#include "comm.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

/*
int write_int(int connection_descriptor, int message){

	return send_data(connection_descriptor, (void*) &message, sizeof(int32_t));

}

int write_string(int connection_descriptor, char * message){

	int len = strlen(message) + 1;

	write_int(connection_descriptor, len);

	return send_data(connection_descriptor, message, len);

}

int read_int(int connection_descriptor){

	int message;
	receive_data(connection_descriptor, &message, sizeof(int32_t));

	return message;
}

int read_string(int connection_descriptor, char * read_buffer){

	int len = read_int(connection_descriptor);

	return receive_data(connection_descriptor, read_buffer, len);

}

*/

t_buffer * create_buffer(){

	t_buffer * ret_buffer = (t_buffer *) malloc(sizeof(t_buffer));

	if (ret_buffer == NULL)
		return NULL;

	ret_buffer->pos = 0;
	ret_buffer->data = (BYTE *) malloc(sizeof(BYTE) * BUFFER_SIZE);

	if (ret_buffer->data == NULL){
		free(ret_buffer);
		return NULL;
	}

	return ret_buffer;

}
void delete_buffer(t_buffer * buffer){

	free(buffer->data);
	free(buffer);

}


void write_int(t_buffer * buffer , int number){

	memcpy(buffer->data + buffer->pos, (char *) &number, sizeof(int32_t));
	buffer->pos += sizeof(int32_t);
	
}

void write_string(t_buffer * buffer, char * string){

	int string_len = strlen(string) + 1;

	write_int(buffer, string_len);

	memcpy(buffer->data + buffer->pos, string, string_len);
	buffer->pos+= string_len;

}

void read_int(t_buffer * buffer, int * number){

	memcpy(number, buffer->data + buffer->pos, sizeof(int32_t));
	buffer->pos+= sizeof(int32_t);

}

void read_string(t_buffer * buffer, char * string){

	int string_len;

	read_int(buffer, &string_len);
	memcpy(string, buffer->data + buffer->pos, string_len);
	buffer->pos+= string_len;

}

int flush_buffer(int connection_descriptor, t_buffer * buffer){

	buffer->data[buffer->pos] = END_MESSAGE_SENTINEL;
	buffer->pos+=1;
	int w_bytes = send_data(connection_descriptor, (void *) buffer->data, buffer->pos);
	clean_buffer(buffer);

	return w_bytes;

}

void clean_buffer(t_buffer * buffer){

	bzero(buffer->data, buffer->pos);
	buffer->pos = 0;

}

int load_buffer(int connection_descriptor, t_buffer * buffer){

	return receive_data(connection_descriptor, buffer->data);

}





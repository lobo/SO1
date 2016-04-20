#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread

typedef struct
{
    int socket_fd;
    int client_id;

}Connection;


ComData * SendData(Connection * connection, ComData * request){
    if(write(connection->socket_fd, request-> message, sizeof(request->message)) < 0){
        perror("ERROR writing to socket");
        exit(1);
    }
    return request->message;
}

void Listen(Connection * connection, ComData requestHandler){
    listen(socket_desc , 3);
}

int Connect(Connection * connection){
    int socket_desc;
    struct sockaddr_in server;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        perror("Could not create socket");
        exit(1);
    }
    
    //server.sin_addr.s_addr = inet_addr("74.125.235.20");
    server.sin_addr.s_addr = inet_addr((char *) connection));
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
 
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
        puts("bind failed");
    }

    puts("bind done");
}

int Disconnect(Connection * connection){
    close(connection->socket_fd);
}

int Accept(Connection * connection){
    struct sockaddr_in client;
    int c;


    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    new_socket = accept(connection->socket_fd, (struct sockaddr *)&client, (socklen_t*)&c);

    if (new_socket < 0)
    {
        perror("Connection to that socket not accepted.\n");
        return 1;
    }
     
    puts("Connection accepted.\n");
     
    //Reply to the client
    message = "Hello Client , I have received your connection.\n";
    write(new_socket, message , strlen(message));
}


// ---> Martin <----

Connection *_create_connection(char * ip, int port){

    Connection *Con = (Connection*) malloc(sizeof(Connection));

    if (Con == NULL) free(Con);

    Con->clientid = 1; //Generar client id con funcion.
    Con->sockfd = socket(AF_INET , SOCK_STREAM , 0);
    
    if (Con->sockfd == -1){
        free(Con);
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    return Con;
}


// Old script below: 
int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c , *new_sock;
    struct sockaddr_in server , client;
    char *message;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept an incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        //Reply to the client
        message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
        write(new_socket , message , strlen(message));
         
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }
     
    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}
 
/*
 * This will handle connection for each client
 * 
 */
void * connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
     
    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock , message , strlen(message));
     
    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        write(sock , client_message , strlen(client_message));
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    //Free the socket pointer
    free(socket_desc);
     
    return 0;
}
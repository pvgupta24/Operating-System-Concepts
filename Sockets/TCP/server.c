/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int socketDescriptor, newsocketDescriptor, port, client_len, n;
    //socketDescriptor, port on which server accepts connections,size of client address, characters read/written
    char buffer[256];
    //server reads from the socket connection to this buffer.
    
    //Contains an internet address
    struct sockaddr_in serv_addr, cli_addr;
    /*
    struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
    };
    */
    printf("Server\n========\n");
    if (argc < 2) {
        fprintf(stderr,"Usage: %s <Port No>\n",argv[0]);
        exit(1);
    }
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);//create socket
    //AF_UNIX if process share common file system & AF_INET for internet domain
    //stream socket in which characters are read in a continuous stream as if from a file or pipe,
    //datagram socket, in which messages are read in chunks
    // 0: OS schooses appropriate protocol

    //returns -1 on error
    if (socketDescriptor < 0)
        error("ERROR opening socket");

    //Initialize buffer to 0 to prevent unwanted stuff
    bzero((char *) &serv_addr, sizeof(serv_addr));

    //Port number on which the server will listen for connections
    port = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;//address family
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);//covert port to network byte order i.e bigendian

    //Bind  : binds a socket to a particular address and port combination
    if (bind(socketDescriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
            error("Binding Error");

    //Listen : max 5 connections     
    listen(socketDescriptor,5);
    printf("Listening for connections....\n");

    client_len = sizeof(cli_addr);
    newsocketDescriptor = accept(socketDescriptor, (struct sockaddr *) &cli_addr, &client_len);

    if (newsocketDescriptor < 0)
        error("Error on accept");

    //Clear the buffer
    bzero(buffer,256);
    while(1){
        n = recv(newsocketDescriptor,buffer,255,0);
        if (n < 0) 
            error("ERROR reading from socket");

        printf("Received Message: %s",buffer);
        printf("Enter reply:");
        fgets(buffer,255,stdin);
        n = send(newsocketDescriptor, buffer, strlen(buffer),0);
        if (n < 0) 
            error("ERROR writing to socket");
    }
    return 0;
}

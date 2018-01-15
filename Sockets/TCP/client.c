#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int socketDescriptor, port, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"Usage : %s <Host><Port>\n", argv[0]);
       exit(0);
    }
    port = atoi(argv[2]);
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor < 0) 
        error("Error opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Error, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(socketDescriptor,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("Connection Error");

    while(1){
        printf("Enter message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        n = send(socketDescriptor,buffer,strlen(buffer),0);

        if (n < 0) 
            error("Error: writing to socket");

        bzero(buffer,256);
        n = recv(socketDescriptor,buffer,255,0);

        if (n < 0) 
            error("Error: reading from socket");
        printf("%s\n",buffer);
    }


    return 0;
}

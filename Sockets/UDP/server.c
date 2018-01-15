#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){

    printf("Server\n========\n");
    if (argc < 2) {
        fprintf(stderr,"Usage: %s <Port No>\n",argv[0]);
        exit(1);
    }

    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    
    //returns -1 on error
    if (socketDescriptor < 0)
        error("Error opening socket");

    struct sockaddr_in serveraddr,clientaddr;
    //memset( &serveraddr, 0, sizeof(serveraddr) );

    //Initialize buffer to 0 to prevent unwanted stuff
    bzero((char *) &serveraddr, sizeof(serveraddr));
    int port = atoi(argv[1]);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    /*bind() of INADDR_ANY doesn't generate a random IP i.e binds the socket to all available interfaces.
     For a server,we usually bind to all interfaces not just localhost. */
    
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(socketDescriptor, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
        error( "Bind error" );
    }

    char buffer[256];
    bzero(buffer,256);
    int n;
    int clientLen = sizeof(clientaddr);
    while(1){
        // n = recvfrom( socketDescriptor, buffer, sizeof(buffer) - 1, 0, NULL, 0 );
        // if ( n < 0 ) {
        //     perror( "recvfrom Error" );
        //     break;
        // }
        // buffer[n] = '\0';
        // printf( "Message received:\n%s", buffer);
        n = recvfrom(socketDescriptor,buffer,255,0,(struct sockaddr *) &clientaddr, &clientLen);
        if (n < 0) 
            error("Error reading from socket");

        printf("Received Message: %s",buffer);
        printf("Enter reply:");
        fgets(buffer,255,stdin);printf("\n");
        n = sendto(socketDescriptor, buffer, 256, 0, (struct sockaddr*) &clientaddr, clientLen);
        //n = sendto(socketDescriptor, buffer, 256, 0, NULL, 0);
        if (n < 0) 
            error("ERROR writing to socket");
    }

    close( socketDescriptor );
  return 0;
}

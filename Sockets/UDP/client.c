#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){

    printf("Client\n========\n");
    if (argc < 2) {
        fprintf(stderr,"Usage: %s <Port No>\n",argv[0]);
        exit(1);
    }

    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if ( socketDescriptor < 0 ) 
        error("Error opening socket");
    

    struct sockaddr_in serveraddr;
    //memset( &serveraddr, 0, sizeof(serveraddr) );
    bzero((char *) &serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    int port = atoi(argv[2]);
    serveraddr.sin_port = htons(port);     
    struct hostent *server;
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Error, no such host\n");
        exit(0);
    }
    // serveraddr.sin_addr.s_addr = htonl( 0x7f000001 );  
    bcopy(server->h_addr, (char *) &serveraddr.sin_addr, server->h_length);
    char buff[256];
    int n;

    while(1) {
        printf("Enter message: ");
        //scanf("%s",buff);        
        fgets(buff,255,stdin);
        if (sendto( socketDescriptor, buff, 256, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 )
            error( "sendto failed" );

        n = recvfrom(socketDescriptor,buff,255,0,NULL,0);
        if (n < 0) 
            error("Error: reading from socket");
        printf("%s\n",buff);
    }

    close( socketDescriptor );

  return 0;
}

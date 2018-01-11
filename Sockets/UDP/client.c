#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
    int fd;
    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket failed");
        return 1;
    }

    struct sockaddr_in serveraddr;
    memset( &serveraddr, 0, sizeof(serveraddr) );

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8000);     

    /*


     struct sockaddr_in {
        short   sin_family;
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
    };


    */         
    serveraddr.sin_addr.s_addr = htonl( 0x7f000001 );  
        
    char buff[256];
    for ( int i = 0; i < 4; i++ ) {
        printf("Enter message: ");
        //scanf("%s",buff);        
        fgets(buff,255,stdin);
        if (sendto( fd, buff, strlen(buff), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
            perror( "sendto failed" );
            break;
        }
        printf( "Message sent\n" );
    }

    close( fd );

  return 0;
}

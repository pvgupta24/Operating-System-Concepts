#include <stdio.h>
#include <sys/socket.h>

int main(){
    //int socket(int __domain, int __type, int __protocol)
    int socketDescriptor = socket(AF_INET , SOCK_STREAM , 0);
    int udpSocket = socket(AF_INET , SOCK_DGRAM , 0);    

    /*
    Address Family - AF_INET (IPv4)
    Type - SOCK_STREAM (Connection oriented TCP protocol - Hand-Shake Connection, then start sending)
         - SOCK_DGRAM  (Connection less UDP protocol - Each data unit is individually addressed and route)
    Protocol - 0 (IP protocol)
    */

    if(socketDescriptor == -1)
        printf("Could not create TCP Socket\n");
    else
        printf("Created TCP Socket successfully\n");

    if(udpSocket == -1)
        printf("Could not create UDP Socket\n");
    else
        printf("Created UDP Socket successfully\n");
        
    return 0;
}

/*
    Sockets are the "virtual" endpoints of any kind of network communications done 
    between 2 hosts over in a network. When we open google.com, it opens
    a socket and connects to google.com to fetch the page & show. Any network 
    communication goes through a socket.
*/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <string.h>
#include <netdb.h> 


#define PORT 80
/*
// IPv4 AF_INET sockets:
struct sockaddr_in {
    short            sin_family;   e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     e.g. htons(3490)
    struct in_addr   sin_addr;     see struct in_addr, below
    char             sin_zero[8];  zero this if you want to
};
 
struct in_addr {
    unsigned long s_addr;          load with inet_pton()
};
 
struct sockaddr {
    unsigned short    sa_family;    address family, AF_xxx
    char              sa_data[14];  14 bytes of protocol address
};

/* Description of data base entry for a single host.  
struct hostent
{
  char *h_name;         Official name of host.  
  char **h_aliases;     Alias list of Host.  
  int h_addrtype;       Host address type.  
  int h_length;         Length of address.  
  char **h_addr_list;   List of addresses from name server.  
};
*/
 
 
int main(int argc , char *argv[])
{

    //Create socket for connection
    int socketDescriptor = socket(AF_INET , SOCK_STREAM , 0);
    if (socketDescriptor == -1)
        printf("Could not create socket\n");
    else{

        printf("Domain Name resolution\n============================\nEnter Host Domain:  ");
        struct sockaddr_in server;
        char host[100], ip[100];
        scanf("%s",host);
        struct hostent *he;

        if ((he = gethostbyname(host)) == NULL){
            //gethostbyname failed
            herror("gethostbyname");
            return 1;
        }
        //Get list of IP address's for the given host
        struct in_addr **addr_list = (struct in_addr **) he->h_addr_list;
        printf("IP addresses for %s :\n",host);

        int i;
        for(i = 0; addr_list[i] != NULL; i++) 
            printf("%s\n",inet_ntoa(*addr_list[i]));
    
        strcpy(ip, inet_ntoa(*addr_list[0]));
        printf("\nTrying to connect to %s (%s)....\n\n",host,ip);
        //Google's IP to long format        
        server.sin_addr.s_addr = inet_addr(ip);
        //IPv4
        server.sin_family = AF_INET;
        //PORT 80
        server.sin_port = htons(PORT);
    
        //Try connecting to server with the given sd
        if (connect(socketDescriptor , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
            printf("Connection Error\n");
            return 1;
        }
        else
            printf("Connected Successfully\n");

    return 0;
}

}

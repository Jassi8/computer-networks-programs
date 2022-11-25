#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define    SRV_TCP_PORT   5556
#define    MAX_MSG       100
void  errExit( char *str )
{
   puts(str);
   exit(0);
}
int main( )
{
     int  sockFd,newSockFd;
    struct  sockaddr_in   srvAdr,cliAdr;
    int  cliLen,n;
    char  mesg[MAX_MSG];
    if ( ( sockFd= socket(AF_INET, SOCK_STREAM ,0) ) < 0 )
    {
        errExit ("can.t open stream socket \n");
    }
    memset(&srvAdr ,0,sizeof(srvAdr));  //initializes the srvAdr structure to zero
   // Initialize the structure members to Family name, port no. and ip address    
   srvAdr.sin_family = AF_INET;
    srvAdr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvAdr.sin_port = htons(SRV_TCP_PORT);
    if (bind (sockFd,(struct sockaddr *)&srvAdr, sizeof (srvAdr )) < 0)
    {
        errExit ("Can.t bind local address \n");
    }
    listen(sockFd,5);    // Waiting for the clients, max. 5 clients can be in waiting state
    while (1)
    {
        printf("server waiting for new connection :\n");
        cliLen = sizeof(cliAdr);
        newSockFd = accept(sockFd,( struct sockaddr *) &cliAdr, &cliLen );
        if(newSockFd < 0)
        {
            errExit ("accept error \n");
        }
        printf("connected to client :%s \n", inet_ntoa (cliAdr.sin_addr ));
        while(1)
        {
            n =recv(newSockFd, mesg,MAX_MSG,0);
            if ( n < 0)
            {
                 errExit ("recv error \n");
            }
            if(n== 0)
            {
                close (newSockFd);
                break;
            }
            mesg [n] =0;
    if(send (newSockFd,mesg,n,0) !=n)
           {
                errExit("send error \n");
            }
            printf("Received following message :\n %s \n ",mesg);
        }
    }
}

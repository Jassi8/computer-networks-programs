#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
struct hostent*h;
if(argc!=2)
{
printf(stderr,"usage:getpid address \n");
exit(1);
}
if((h=gethostbyname(argv[1]))==NULL)
{
perror("gethostbyname");
exit(1);
}
printf("hostname: %s \n",h->h_name);
printf("IP address: %s \n",inet_ntoa(*((struct in_addr*)h->h_addr)));
return 0;
}

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080
#define N 1024

void main(){
   int clnsock_fd;
   char message[N];
   char buffer[N];
   struct sockaddr_in svraddr;
   socklen_t svraddrlen = sizeof(struct sockaddr_in);
   clnsock_fd = socket(AF_INET, SOCK_STREAM, 0);
   svraddr.sin_family = AF_INET;
   svraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   svraddr.sin_port = htons(PORT);
   connect(clnsock_fd, (struct sockaddr *)&svraddr, svraddrlen);
   
   while(1){
      memset(message, 0, sizeof(message));
      printf("Enter data for server: ");
      gets(message);
      send(clnsock_fd, message, sizeof(message), 0);
      if (strcmp(message, "exit")==0) break;
      memset(buffer, 0, sizeof(buffer));
      read(clnsock_fd, buffer, sizeof(buffer));
      printf("Recieved data from server: %s\n", buffer);
      if(strcmp(buffer, "exit")==0) break;
      }
}

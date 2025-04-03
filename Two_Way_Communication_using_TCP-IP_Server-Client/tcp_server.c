#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080
#define N 1024

void main(){
   int svrsock_fd, new_conn;
   int opt=1;
   char message[N];
   char buffer[N];
   struct sockaddr_in address;
   socklen_t addrlen = sizeof(struct sockaddr_in);
   svrsock_fd = socket(AF_INET, SOCK_STREAM, 0);
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);
   setsockopt(svrsock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
   bind(svrsock_fd, (struct sockaddr *)&address, addrlen);
   printf("WAITING FOR CLIENT \n");
   listen(svrsock_fd, 3);
   new_conn = accept(svrsock_fd, (struct sockaddr *)&address, &addrlen);
   
   while(1){
      memset(buffer, 0, sizeof(buffer));
      read(new_conn, buffer, sizeof(buffer));
      printf("Recieved data from client  %s\n", buffer);
      if(strcmp(buffer, "exit")==0) break;
      memset(message, 0, sizeof(message)); 
      printf("Enter data for client: ");
      gets(message);
      send(new_conn, message, sizeof(message), 0);
      if(strcmp(message, "exit")==0) break;
      }
}

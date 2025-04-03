#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#define N 1024

void main(){
int fd;
char *myfifo = "fifo";
char message[N];
char buffer[N];
mkfifo(myfifo, 0666);
while(1){
fd = open(myfifo, O_WRONLY);
memset(message, 0, sizeof(message));
printf("Enter the message for 2nd program: ");
gets(message);
write(fd, message, N);
close(fd);
if (strcmp(message, "exit")==0) break;
memset(buffer, 0, sizeof(buffer));
fd = open(myfifo, O_RDONLY);
read(fd, buffer, N);
printf("Recieve data from 2nd program %s \n", buffer);
close(fd);
if (strcmp(buffer, "exit")==0) break;
}
}




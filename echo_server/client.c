#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 4096

char buf[BUFFER_SIZE];

int main(){

  int fd = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in server_addr,client_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  int rv = connect(fd,(const struct sockaddr*)&server_addr,sizeof(server_addr));
  printf("Connected to server\n");

  char *msg = "Hello from client!";
  ssize_t byte_written = write(fd,msg,strlen(msg));

  ssize_t read_bytes = read(fd,buf,BUFFER_SIZE-1);

  printf("From Server : %s\n",buf) ;
  


}

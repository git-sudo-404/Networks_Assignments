#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>


#define PORT 8081
#define BUFFER_SIZE 4096

char rbuf[BUFFER_SIZE] = {0};
char wbuf[BUFFER_SIZE] = {0};

int main(){

  int fd = socket(AF_INET,SOCK_STREAM,0) ;

  struct sockaddr_in server_addr = {};

  server_addr.sin_family = AF_INET ;
  server_addr.sin_port = htons(PORT) ;
  server_addr.sin_addr.s_addr = INADDR_ANY ;

  int rv = bind(fd,(const struct sockaddr*)&server_addr,sizeof(server_addr)) ;

  rv = listen(fd,SOMAXCONN) ;

  printf("Server listening on PORT : %d\n",PORT) ;

  struct sockaddr_in client_addr = {};
  socklen_t client_addr_len = sizeof(client_addr) ;

  int client_fd = accept(fd,(struct sockaddr*)&client_addr,&client_addr_len);

  printf("Connected to Client!\n") ;

  while(1){
    
    size_t bytes_read ,bytes_written ;

    bytes_read = read(client_fd,rbuf,BUFFER_SIZE-1);

    rbuf[bytes_read] = '\0';

    printf("Client : %s\n",rbuf);

    printf("Type a msg to Client : \n");

    scanf("%s",wbuf);

    int len = strlen(wbuf);

    bytes_written = write(client_fd,wbuf,len) ; 

    char bye[] = "BYE" ;

    if(strcmp(rbuf,bye)==0 || strcmp(wbuf,bye)==0){
      close(client_fd);
      close(fd);
      exit(0);
    }

  }

}

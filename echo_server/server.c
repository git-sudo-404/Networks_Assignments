#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>


#define PORT 8080
#define BUFFER_SIZE 4096

char buf[BUFFER_SIZE] ;

void echo(int client_fd){

  ssize_t rv = read(client_fd,buf,BUFFER_SIZE-1);
  if(rv<=0)
    return;

  printf("%s",buf);

  write(client_fd,buf,rv) ;

  return;

}

int main(){

  int fd = socket(AF_INET,SOCK_STREAM,0);
  
  struct sockaddr_in server_adr = {} ;
  server_adr.sin_family = AF_INET ;
  server_adr.sin_port = htons(PORT) ;
  server_adr.sin_addr.s_addr = INADDR_ANY ;

  int rv = bind(fd,(const struct sockaddr*) &server_adr,sizeof(server_adr));
  if(rv<0){
    printf("\nError : binding\n");
    exit(1);
  }

  rv = listen(fd,SOMAXCONN);

  if(rv<0){
    printf("Error : listen()\n");
    exit(1);
  }
 
  printf("Server listening on PORT : %d\n",PORT);

  /* while(1){ */

    struct sockaddr_in client_addr = {} ;

    socklen_t client_addr_len = sizeof(client_addr) ;

    int client_fd = accept(fd,(struct sockaddr*)&client_addr,&client_addr_len) ;

    echo(client_fd) ;

    close(client_fd) ;

  /* } */

  close(fd) ;

}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include<sys/select.h>
#include<sys/wait.h>

#define BUFFER_SIZE 4096
#define PORT 8080


int main(){

  int fd = socket(AF_INET,SOCK_STREAM,0) ;

  struct sockaddr_in server_addr = {};

  server_addr.sin_family = AF_INET ;
  server_addr.sin_port = htons(PORT) ;
  server_addr.sin_addr.s_addr = INADDR_ANY ;

  int rv = bind(fd,(const struct sockaddr*)&server_addr,sizeof(server_addr)) ;

  rv = listen(fd,SOMAXCONN) ;
  printf("Server listening on PORT : %d\n",PORT) ;

  
  while(1){

    struct sockaddr_in client_addr = {};
    socklen_t client_addr_len = sizeof(client_addr) ;
    int client_fd = accept(fd,(struct sockaddr*)&client_addr,&client_addr_len) ;
    printf("New Connection Accepted!\n") ;

    pid_t pid = fork();

    if(pid==0){ // Child Process -- Client 
      
      close(fd); // don't need this in client side.

      char rbuf[BUFFER_SIZE] = {0};
      char wbuf[BUFFER_SIZE] = {0};

      while(1){

        size_t bytes_read,bytes_written;

        bytes_read = read(client_fd,rbuf,BUFFER_SIZE-1);
        rbuf[bytes_read] = '\0' ;

        printf("Client : %s\n",rbuf) ;

        printf("Enter a msg to Client : \n");

        scanf("%s",wbuf);

        int len = strlen(wbuf) ;

        bytes_written = write(client_fd,wbuf,len) ;

        char bye[] = "BYE" ;

        if(strcmp(bye,rbuf)==0 || strcmp(bye,wbuf)==0){
          printf("Convo Ended!");
          close(client_fd);
          exit(0) ;
        }

      }

    } else { // Parent Process -- Server 
      close(client_fd) ;
      waitpid(-1,NULL,WNOHANG) ;
    }

  }

  close(fd) ;


}

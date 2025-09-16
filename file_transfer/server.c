#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>


#define PORT 8080
#define BUFFER_SIZE 4096

char buf[4096] = {0};

void send_file(FILE *fp,int client_fd){

  size_t bytes_read;

  while((bytes_read=fread(buf,1,BUFFER_SIZE,fp))>0){
    if(write(client_fd,buf,bytes_read)<0){
      perror("Error : send_file()");
      return;
    }
  }

}

int main(){

  int fd = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in server_addr = {};

  server_addr.sin_family = AF_INET ;
  server_addr.sin_port = htons(PORT) ;
  server_addr.sin_addr.s_addr = INADDR_ANY ;
 
  int rv = bind(fd,(const struct sockaddr*)&server_addr,sizeof(server_addr));

  listen(fd,SOMAXCONN) ;

  printf("Listening on PORT : %d\n",PORT);

  struct sockaddr_in client_addr = {} ;
  socklen_t client_addr_len = sizeof(client_addr) ;

  int client_fd = accept(fd,(struct sockaddr*)&client_addr,&client_addr_len) ;

  char fileName[256] = {0} ;

  size_t bytes_read = read(client_fd,fileName,sizeof(fileName)-1) ;
  if(bytes_read>0){
    fileName[bytes_read] = '\0' ;
  } else {
    perror("Error : fileName read()") ;
    exit(1);
  }

  printf("Request file : %s\n",fileName) ;

  FILE *fp = fopen(fileName,"rb");
  
  send_file(fp,client_fd);

  fclose(fp);
  close(client_fd);
  close(fd);

}

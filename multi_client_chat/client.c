#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main(){

  int fd = socket(AF_INET,SOCK_STREAM,0) ;

  char wbuf[BUFFER_SIZE] = {0};
  char rbuf[BUFFER_SIZE] = {0};
  
  struct sockaddr_in server_addr = {} ;
  
  server_addr.sin_family = AF_INET ;
  server_addr.sin_port = htons(PORT) ;
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK) ;

  int rv = connect(fd,(const struct sockaddr*)&server_addr,sizeof(server_addr)) ;
  printf("Connected to Server!\n");

  while(1){
  
    size_t read_bytes,bytes_written ;

    printf("Enter a msg to Server : \n");

    scanf("%s",wbuf);

    int len = strlen(wbuf) ;

    bytes_written = write(fd,wbuf,len);

    read_bytes = read(fd,rbuf,BUFFER_SIZE-1) ;

    rbuf[read_bytes] = '\0' ;

    printf("Server : %s\n",rbuf) ;

    char bye[] = "BYE" ;

    if(strcmp(bye,rbuf)==0 || strcmp(wbuf,bye)==0){
      close(fd);
      exit(0);
    }


  }

  close(fd);


}

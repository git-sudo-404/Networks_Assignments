#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>


#define PORT 8080
#define BUFFER_SIZE 4096

int main(){

  int fd = socket(AF_INET,SOCK_DGRAM,0);
  
  struct sockaddr_in server_adr = {} ;
  server_adr.sin_family = AF_INET ;
  server_adr.sin_port = htons(PORT) ;
  server_adr.sin_addr.s_addr = INADDR_ANY ;

  int rv = bind(fd,(const struct sockaddr*) &server_adr,sizeof(server_adr));
  if(rv<0){
    printf("\nError in binding\n");
    exit(1);
  }

  

}

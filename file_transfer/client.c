#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 4096
#define PORT 8080

char buf[BUFFER_SIZE] ;


void recieve_file(int fd){

  FILE *fp = fopen("got_file.txt","wb");

  size_t bytes_recieved;

  while((bytes_recieved = read(fd,buf,BUFFER_SIZE))>0){
    fwrite(buf,1,bytes_recieved,fp);
  }

  fclose(fp);

}


int main(){

  int fd = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in server_addr = {};
  server_addr.sin_family = AF_INET ;
  server_addr.sin_port = htons(PORT) ;
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK) ;

  char fileName[] = "file_2.txt";

  connect(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));

  printf("Connected to server");

  // Send the fileName requesting for that file 

  write(fd,fileName,strlen(fileName));

  recieve_file(fd) ;

  printf("File transfer Complete") ;

  close(fd) ;

}

#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>

#include "client.h"

#define MAX 80
//#define PORT 8080 
#define SA struct sockaddr 

// ./hello -server 8080
int main(int argc, char *argv[]){ 
	int i = 1;
	int port;
	
	while(argv[i] != NULL){
		if(strcmp(argv[i], "-server") == 0){
			port = atoi(argv[i+1]);
		}
		i++;
	}

    int sockfd; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
        printf("Socket successfully created..\n"); 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(port); 
  
    connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
        printf("connected to the server..\n"); 
  	
    func(sockfd); 
    close(sockfd); 
    
   /*
   
   structs
   åpne socket
   bzero?
   
   sette client settings
   
   connect
   
   
   */ 
} 

void func(int sockfd) 
{ 
    char buff[MAX]; 				// MAX = 80
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("Client: "); 
        n = 0; 
        
        while ((buff[n++] = getchar()) != '\n');
         
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit..\n"); 
            break; 
        } 
    } 
} 
  


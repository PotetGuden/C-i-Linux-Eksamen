#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define SA struct sockaddr

#include "server.h"

// ./main -port 8080 -id etNavn
int main(int argc, char *argv[]) 
{ 
	int i = 1;													// For å hoppe over argument 0
	int port;
	char *id = malloc(sizeof(char*));

	while(argv[i] != NULL){
		if(strcmp(argv[i], "-port") == 0){
			port = atoi(argv[i+1]);
			//printf("%s\n", argv[i+1]);
		} else if(strcmp(argv[i], "-id") == 0){
			id = argv[i+1];
			//printf("%s\n", id);
		}
		i++;
	}
	printf("Trying to connect with userid: %s\n", id);
	
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 					// Socket
    if(sockfd == -1){
    	printf("failed to create socket..\n");
    	exit(0);
    } else{
    	printf("Successfully created a socket..\n");
    }
    
    bzero(&servaddr, sizeof(servaddr)); 
  	
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 				// Tar imot hvem som helst
    servaddr.sin_port = htons(port); 							// Kunne hardkodet port, #define port 8080
 
    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){	// Bind
   		printf("Failed to bind socket..\n");
   		exit(0);	 	
   	} else{
   		printf("Successfully binded socket..\n");
   	}
  
    if((listen(sockfd, 5)) != 0){								// Listen
    	printf("Listening failed...\n");
    	exit(0);	
    } else{
    	printf("Server listening..\n");
    }

    len = sizeof(cli); 
  
    connfd = accept(sockfd, (SA*)&cli, &len); 					// Accept
    if(connfd < 0){
    	printf("Server failed to accept...\n");
    	exit(0);
    } else{
    	printf("Server accepted the client\n");
    }
  
    func(connfd); 
  	
  
    close(sockfd); 
    
   /*
   structs
   åpne socket
   bzero?
   
   sette client settings
   
   bind
   listen
   accept
   */ 
    
} 

void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    printf("connected..\n");
    for (;;) { 
        bzero(buff, MAX); 
  
        read(sockfd, buff, sizeof(buff)); 
        
        printf("Server: %s\t Client : ", buff); 
        
        bzero(buff, MAX); 
        n = 0; 
 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
 
        write(sockfd, buff, sizeof(buff)); 

        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 


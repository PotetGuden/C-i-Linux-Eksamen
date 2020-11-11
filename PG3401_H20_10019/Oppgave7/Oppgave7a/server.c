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
	printf("Trying to connect with userid : %s\n", id);
	
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
  
    func(connfd, id); 
  	
  
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

void func(int sockfd, char *id) 
{ 
    char buff[MAX]; 
    int n = 0; 
  	int numberOfMsg = 0;
    printf("connected..\n\n");
	char *handshake = malloc(sizeof(char*)); 
    //char startMsg[] = "Trying to connect to ID, do you wish to continue? Y/N\n";
    //write(sockfd, startMsg, 100);			// Harkodet input og "100"!
    for (;;) { 
        bzero(buff, MAX); 
  
        
        
        //printf("number: %i id: %s \n",numberOfMsg, id);

       	read(sockfd, buff, sizeof(buff)); 
       	
       	if(numberOfMsg == 0){						// Mottar ingenting, skal bare sende id til klient
       		bzero(buff,MAX);
       		write(sockfd, id, sizeof(id));
       		numberOfMsg++;
       		continue;
       	}
       	
       	if(numberOfMsg == 1 && buff[0] == 'Y'){		// Om bruker svarer 'Y', Sammenligner ascii verdiene
        	handshake = "200 OK\n";
        	printf("Server: %s", buff); 
        	bzero(buff, MAX); 
        	
        	while(handshake[n] != '\n'){
        		buff[n] = handshake[n];
        		n++;
        	} 
        	
        	write(sockfd, buff, sizeof(buff));
    		
    		numberOfMsg++;
    		
    		continue;
        		
        } else if(numberOfMsg == 1) {				// Aka hvis brukeren ikke svarer 'Y'
        	printf("Server shutting down..");
        	handshake = "403 Forbidden\n";
        	
        	bzero(buff, MAX);
        	while(handshake[n] != '\n'){
        		buff[n] = handshake[n];
        		n++;
        	}
        	write(sockfd, buff, sizeof(buff));
        	
        	read(sockfd, buff, sizeof(buff));   	 // Venter på at client har stoppet
        	numberOfMsg++;
        	
        	break;
        } 
        
        printf("From Client: %s\nTo Client : ", buff); 
        
        bzero(buff, MAX); 
        n = 0; 
 	
        while ((buff[n++] = getchar()) != '\n');
 
        write(sockfd, buff, sizeof(buff)); 

        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server shutting down..\n"); 
            break; 
        } 
        numberOfMsg++;
    } 
    free(handshake);
} 


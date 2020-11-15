#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "server.h"

// ./main -port 8000 -id etNavn
int main(int argc, char *argv[]) 
{ 
	int i = 1;													// For å hoppe over argument 0
	int port;
	char *id = malloc(sizeof(char*));

	while(argv[i] != NULL){
		if(strcmp(argv[i], "-port") == 0){
			port = atoi(argv[i+1]);
		} else if(strcmp(argv[i], "-id") == 0){
			id = argv[i+1];
		}
		i++;
	}
	printf("Trying to connect with userid : %s\n", id);
	
    int sockfd, connfd, len; 
    struct sockaddr_in serveraddress, client; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 					// Socket
    if(sockfd == -1){
    	printf("Failed to create socket..\n");
    	exit(1);
    }
    
    bzero(&serveraddress, sizeof(serveraddress)); 
  	
    serveraddress.sin_family = AF_INET; 
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY); 				// Tar imot hvem som helst
    serveraddress.sin_port = htons(port); 							
 
    if((bind(sockfd, (SA*)&serveraddress, sizeof(serveraddress))) != 0){	// Bind
   		printf("Failed to bind socket, use another port\n");
   		exit(1);	 	
   	} 
  
    listen(sockfd, 5); 		// Listen    "5" - annbefalte nummer for ventende connections
    printf("Waiting for client to connect..\n");
    

    len = sizeof(client); 
  
    connfd = accept(sockfd, (SA*)&client, &len); 					// Accept
    if(connfd < 0){
    	printf("Failed to accept\n");
    	exit(1);
    } else{
    	printf("Accepted the client\n");
    }
  
    func(connfd, id); 
  
    close(sockfd); 
    
   /*
   structs
   åpne socket
   bzero
   
   sette client settings
   
   bind
   listen
   accept
   */ 

} 

void func(int sockfd, char *id){ 
    char buff[MAX_BUFF_SIZE]; 
    int n = 0; 
  	int numberOfMsg = 0;
    printf("Connected.\n\n");
	char *handshake = malloc(sizeof(char*)); 
	memset(handshake,0,sizeof(char*));
   
    while(1){ 
        bzero(buff, MAX_BUFF_SIZE); 

       	read(sockfd, buff, sizeof(buff)); 
       	
       	if(numberOfMsg == 0){						// Mottar ingenting, skal bare sende id til klient
       		bzero(buff,MAX_BUFF_SIZE);
       		write(sockfd, id, sizeof(id));
       		numberOfMsg++;
       		continue;
       	}
       	
       	if(numberOfMsg == 1 && buff[0] == 'Y'){		// Om bruker svarer 'Y', Sammenligner ascii verdiene
        	handshake = "200 OK\n";
        	printf("Server: %s", buff); 
        	bzero(buff, MAX_BUFF_SIZE); 
        	
        	while(handshake[n] != '\n'){
        		buff[n] = handshake[n];
        		n++;
        	} 
        	
        	write(sockfd, buff, sizeof(buff));

    		numberOfMsg++;
    		
    		continue;
        		
        } else if(numberOfMsg == 1) {				// Aka hvis brukeren ikke svarer 'Y'
        	printf("Closing server..\n");
        	handshake = "403 Forbidden\n";
        	
        	bzero(buff, MAX_BUFF_SIZE);
        	
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
        
        bzero(buff, MAX_BUFF_SIZE); 
        n = 0; 
 	
        while ((buff[n++] = getchar()) != '\n');
 
        write(sockfd, buff, sizeof(buff)); 

        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server shutting down..\n"); 
            break; 
        } 
        numberOfMsg++;
    } 
    //free(handshake);
} 


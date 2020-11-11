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

// ./main -server 8080
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
        printf("Socket successfully created..\n\n"); 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(port); 
  
    connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
        //printf("Trying to connect to server ASD, do you wish to continue? Y/N...\n"); 
  	
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

void func(int sockfd) { 
	int numberOfMsg = 0;
    char buff[MAX]; 				// MAX = 80
    int n; 
    char *id = malloc(sizeof(char*));
    //read(sockfd, buff, sizeof(buff));
    for (;;) { 
    	
        bzero(buff, sizeof(buff)); 
        
        if(numberOfMsg == 0){							// Sender en tom melding, bare for at jeg skal få id tilbake
     		write(sockfd, buff, sizeof(buff));
         	//printf("Sender ingenting\n");
         	numberOfMsg++;
         	continue;
    	}
        if(numberOfMsg == 1){							// Har fått tak i id, spør klient om de vil fortsettte
        	read(sockfd, buff, sizeof(buff));
        	printf("Trying to connect to server %s, do you wish to continue? Y/N...\n", buff); 
        	printf("To Server: ");
        	bzero(buff, sizeof(buff));        	
	        while ((buff[n++] = getchar()) != '\n');
        	write(sockfd, buff, sizeof(buff));
        	
        	read(sockfd, buff, sizeof(buff));
        	if(buff[0] == '4'){
        		break;
        	}
        	numberOfMsg++;
        	continue;
        }
		if(numberOfMsg == 2){							// Hvis man kommer hit så har man gjort ferdig "handshaken"
			printf("Handshake was sucessful, continue to write if you want to.\n");
        }
        printf("To Server: "); 
        n = 0; 
        //read(sockfd, buff, sizeof(buff));       
        
        while ((buff[n++] = getchar()) != '\n');
         
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        
        printf("\nFrom Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Shutting down..\n"); 
            break; 
        } 
        numberOfMsg++;
    } 
    free(id);
} 
  


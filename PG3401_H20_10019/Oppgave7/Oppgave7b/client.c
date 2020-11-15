#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>

#include "client.h"

// ./main -server 8000
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
        
    memset(&servaddr, 0, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 		
    servaddr.sin_port = htons(port); 
  
    connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
  	
    func(sockfd); 
    close(sockfd); 
    
} 

void func(int sockfd) { 
	int numberOfMsg = 0;
    char buff[MAX_BUFF_SIZE]; 				// MAX = 80
    int n; 
    char *id = malloc(sizeof(char*));
    
    while(1) { 
    	
        bzero(buff, MAX_BUFF_SIZE); 
        
        if(numberOfMsg == 0){							// Sender en tom melding, bare for at jeg skal få id tilbake
     		write(sockfd, buff, MAX_BUFF_SIZE);
         	//printf("Sender ingenting\n");
         	numberOfMsg++;
         	continue;
    	}
        if(numberOfMsg == 1){							// Har fått tak i id, spør klient om de vil fortsettte
        	read(sockfd, buff, MAX_BUFF_SIZE);
        	printf("Trying to connect to server %s, do you wish to continue? Y/N...\n", buff); 
        	printf("To Server: ");
        	bzero(buff, MAX_BUFF_SIZE);        	
	        while ((buff[n++] = getchar()) != '\n');
        	write(sockfd, buff, MAX_BUFF_SIZE);
        	
        	read(sockfd, buff, MAX_BUFF_SIZE);
        	
        	if(strcmp(buff,"403 Forbidden") == 0){
        		printf("\n%s, permission denied, closing both applications..\n", buff);
        		write(sockfd, buff, MAX_BUFF_SIZE);
        		break;
        	}
        	bzero(buff, MAX_BUFF_SIZE);
        	numberOfMsg++;
        	continue;
        }
		if(numberOfMsg == 2){							// Hvis man kommer hit så har man gjort ferdig "handshaken"
			printf("Handshake was successful, continue to write if you want to.\n");
        }
        printf("To Server: "); 
        n = 0;       
        
        while ((buff[n++] = getchar()) != '\n');
         
        write(sockfd, buff, MAX_BUFF_SIZE); 
        bzero(buff, MAX_BUFF_SIZE); 
        read(sockfd, buff, MAX_BUFF_SIZE); 
        
        printf("\nFrom Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Shutting down..\n"); 
            break; 
        } 
        numberOfMsg++;
    } 
    free(id);
} 
  


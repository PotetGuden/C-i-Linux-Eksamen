#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h> // for mode constants
#include <fcntl.h>	  // for 0_constants

#include <time.h>
#include "Oppgave6.h"

#define SEM_PRODUCER_NAME "semproducer"
#define SEM_RECEIVER_NAME "semreceiver"
#define TRUE 1
#define FALSE 0

// Lage en define MAX_BUFF_SIZE 11? og ta -1 på forloops
#pragma (1)			// Fjerne padding 
typedef struct MyStruct {
	char buff[11];	// [11] brukes som 0-terminering
	int totalLetters;
	char *fileName;
	int endOfFile;
} MyStruct;
#pragma()

void *PrintMessage (void *ms){
	
 	MyStruct *ms2 = malloc(sizeof(MyStruct));
 	ms2 = (MyStruct*) ms;
 
   	FILE *fp;
	
   	fp = fopen(ms2->fileName, "r");
	if(fp == NULL){
		printf("Ugyldig filnavn\n"); 
		
		exit(1);
	}
   	// Prøv å bruk sem_init istedenfor sem_open..
   	sem_t *sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, 0644 , 0);		// Lager semaphore 1
	if(sem_prod == SEM_FAILED){
		printf("EROOR1");
		exit(1);
	}
	
	sem_t *sem_receiv = sem_open(SEM_RECEIVER_NAME, O_CREAT, 0644, 0);		// Lager semaphore 2
	if(sem_receiv == SEM_FAILED){
		printf("EROOR2");
		exit(1);
	}

	printf("Reading 10 and 10 characters from the file: %s\n\n", ms2->fileName);
		
   	while(1){	
		sem_wait(sem_receiv);			// Venter på at main skal gi klar signal
		fread(ms2->buff,sizeof(char), sizeof(ms2->buff)-1, (FILE*)fp);	
		if(feof(fp)){									
			ms2->totalLetters += strlen(ms2->buff)-1;		// -1 for 0-termineringen
			//printf("Working thread gives signal.\n");
			ms2->endOfFile = TRUE;
			break;
		}
		ms2->buff[11] = '\0';
		ms2->totalLetters += 10;
		//printf("Working thread gives signal.\n");
		sem_post(sem_prod);				// Gir main klar signal
   	}
   	
   	fclose(fp); 
	sem_post(sem_prod);					// Valgte å sette den her istedenfor siste gang inni loopen, og jeg trengte å close fp, mest for ordensskyld.			
   	
   	return NULL;
}

void main (int argc, char *argv[]){
	if(argc < 2){
		printf("Remember to add the filename after the %s, please try again\n", argv[0]);
		exit(1);
	}

	MyStruct *ms = malloc(sizeof(MyStruct));
	if(ms == NULL){
		memset(ms,0,sizeof(MyStruct));
	}
	
	ms->totalLetters = 0;
 	ms->fileName = argv[1];				// Navn på tekstfil
 	ms->endOfFile = FALSE;
 	
	sem_unlink(SEM_PRODUCER_NAME);		// Fjerner aktive semaphores hvis de finnes.
   	sem_unlink(SEM_RECEIVER_NAME);

	
	sem_t *sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, 0644, 0);		// Åpner semaphore 1
	if(sem_prod == SEM_FAILED){
		printf("Could not open S1");
		exit(1);
	}

	sem_t *sem_receiv = sem_open(SEM_RECEIVER_NAME, O_CREAT, 0644, 1);		// Åpner semaphore 2   
	if(sem_receiv == SEM_FAILED){
		printf("Could not open S2");
		exit(1);
	}

	pthread_t pThread1;
	pthread_create (&pThread1, NULL, PrintMessage, (void *) ms);
	
	int t = 0;
	while(1){
		sem_wait(sem_prod);
		if(strlen(ms->buff) <= 1) break; 		// 0-termineringen som henger igjen fra arbeidstråden, om lengden på bufferet er mindre enn dette.
		
		printf("From main thread:\n%s\n\n", ms->buff);
		
		memset(ms->buff,0,sizeof(ms->buff));
		
		if(ms->endOfFile == TRUE){	
			printf("THIS IS END\n");
			break;
		}
		
		sem_post(sem_receiv);
	}
	
	printf("Number of letters in the file is: %d\n", ms->totalLetters);
	
   	pthread_join(pThread1, NULL);  			// Venter på at arbeidstråd skal bli ferdig
   	
   	sem_close(sem_prod);
   	sem_close(sem_receiv);   
	
	free(ms);
   	//printf("After thread finished.\n");
}

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>	  // for O_constants

#include "Oppgave6.h"

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
	
	sem_t *sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, MODE, 0);		// Åpner semaphore 1 - SEM_PROD_NAME/MODE er defines fra headerfil
	if(sem_prod == SEM_FAILED){
		printf("Could not open S1");
		exit(1);
	}

	sem_t *sem_receiv = sem_open(SEM_RECEIVER_NAME, O_CREAT, MODE, 1);		// Åpner semaphore 2   
	if(sem_receiv == SEM_FAILED){
		printf("Could not open S2");
		exit(1);
	}

	pthread_t pThread1;
	pthread_create (&pThread1, NULL, WorkThread, (void *) ms);
	
	while(1){
		sem_wait(sem_prod);										// Venter på arbeidstråd signal
		
		if(strlen(ms->buff) <= 1 && ms->buff[0] == '\0'){		// 0-termineringen som henger igjen fra arbeidstråden, om lengden på bufferet er mindre enn dette.
			break; 					
		}
		printf("From main thread:\n%s\n\n", ms->buff);
		
		memset(ms->buff,0,sizeof(ms->buff));
		
		if(ms->endOfFile == TRUE){	
			break;
		}
		
		sem_post(sem_receiv);									// Gir arbeidstråd signal
	}
	
	printf("Number of letters in the file is: %d\n", ms->totalLetters);
	
   	pthread_join(pThread1, NULL);  								// Venter på at arbeidstråd skal bli ferdig
   	
   	sem_close(sem_prod);
   	sem_close(sem_receiv);
	free(ms);
}

void *WorkThread (void *ms){
	
 	MyStruct *ms2 = (MyStruct*) ms;
 
   	FILE *fp;
	
   	fp = fopen(ms2->fileName, "r");
	if(fp == NULL){
		printf("You gave a non-valid filename\n"); 
		exit(1);
	}

   	sem_t *sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, MODE , 0);		// Lager semaphore 1
	if(sem_prod == SEM_FAILED){
		printf("Failed to open Sempahore!");
		exit(1);
	}
	
	sem_t *sem_receiv = sem_open(SEM_RECEIVER_NAME, O_CREAT, MODE, 0);		// Lager semaphore 2
	if(sem_receiv == SEM_FAILED){
		printf("Failed to open Semaphore!");
		exit(1);
	}

	printf("Reading 10 and 10 characters from the file: %s\n\n", ms2->fileName);
		
   	while(1){	
		sem_wait(sem_receiv);			// Venter på at main skal gi klar signal
		fread(ms2->buff,sizeof(char), sizeof(ms2->buff)-1, (FILE*)fp);	
		if(feof(fp)){									
			ms2->buff[strlen(ms2->buff)] = '\0';		// 0-terminerer manuelt på slutten av buff 
			ms2->totalLetters += strlen(ms2->buff)-1; 	
			ms2->endOfFile = TRUE;
			break;
		}
		ms2->buff[11] = '\0';
		ms2->totalLetters += 10;
		sem_post(sem_prod);				// Gir main klar signal
   	}
   	
   	fclose(fp); 
	sem_post(sem_prod);					// Valgte å sette den her istedenfor siste gang inni loopen, siden jeg trengte å close fp, mest for ordensskyld.			
   	sem_close(sem_prod);
   	sem_close(sem_receiv);
   	return NULL;
}

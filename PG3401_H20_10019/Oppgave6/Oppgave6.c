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

// Lage en define MAX_BUFF_SIZE 11? og ta -1 på forloops
#pragma (1)			// Fjerne padding 
typedef struct MyStruct {
	char buff[11];	// [11] brukes som 0-terminering
	int totalLetters;
	char *fileName;
} MyStruct;
#pragma()

int iCounter = 0;

// HUSK Å FJERNE *2 fra mallocs om det funker!!!!!!! free() etter mallocs?   memset(hvis det trengs);

void *PrintMessage (void *ms){
	MyStruct *pp =  ms;
	
 	MyStruct *ms2 = malloc(sizeof(MyStruct)*2);
 	ms2 = (MyStruct*) ms;
 
   	char *fileName = malloc(sizeof(char*)*2);
   	memset(fileName,0,sizeof(char*));
   	fileName = ms2->fileName;
   	FILE *fp;
	
   	fp = fopen((char*)fileName, "r");
	//if(fp == NULL) printf("Ugyldig filnavn\n"); exit(1);

	printf("Reading 10 and 10 characters from the file: %s\n\n", (char*)fileName);
   	
   	sem_t *sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, 0644 , 0);
	if(sem_prod == SEM_FAILED){
		printf("EROOR1");
		exit(1);
	}
	
	sem_t *sem_receiv = sem_open(SEM_RECEIVER_NAME, O_CREAT, 0644, 0);
	if(sem_receiv == SEM_FAILED){
		printf("EROOR2");
		exit(1);
	}
	
   	int i = 0;												// Bare for linjenummer - er ikke nødvendig
   	while(fgets(ms2->buff, sizeof(ms2->buff), (FILE*)fp)){	// Utfører fgets og printer ut, husk \0 terminering
		sem_wait(sem_prod);
		
		if(strlen(ms2->buff) < 10){							// Hvis lengden på bufferet er mindre enn 10, bufferet er egt 11 pga \0
			ms2->totalLetters += strlen(ms2->buff);
			//printf("%d: %s\n", i, ms2->buff);
			for(int y = 0; y < (ms2->totalLetters)%10; y++){ // Kunne brukt strlen(ms2->buff) istedenfor %10  (skulle ikke ha noe å si)
				pp->buff[y] = ms2->buff[y];
			}
			printf("Arbeidstråd gir klar signal.\n");
			sem_post(sem_receiv);
			break;
		}
		for(int y = 0; y < 10; y++){					// TEST
			pp->buff[y] = ms2->buff[y];
			//printf("%c\n", ms2->buff[y]);
		}
		//printf("%d: %s\n", i, ms2->buff );
		i++;
		ms2->totalLetters += 10;
		printf("Arbeidstråd gir klar signal.\n");
		
		sem_post(sem_receiv);
   	}
   
   	printf("Antall Bokstaver i filen er: %d\n", ms2->totalLetters);
   	
   	fclose(fp); 
   	sem_close(sem_prod);
   	sem_close(sem_receiv);

	free(ms2);
   	return NULL;
}

void main (int argc, char *argv[]){
	if(argc < 2){
		printf("Remember to add the filename after the %s, please try again\n", argv[0]);
		exit(1);
	}

	MyStruct *ms = malloc(sizeof(MyStruct)*3);
	if(ms == NULL){
		memset(ms,0,sizeof(MyStruct));
	}
	
	ms->totalLetters = 0;
 	ms->fileName = argv[1];			// Navn på tekstfil
 	
	sem_unlink(SEM_PRODUCER_NAME);
   	sem_unlink(SEM_RECEIVER_NAME);

	sem_t *sem_prod;
	sem_t *sem_receiv;
	
	sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, 0644, 0);		// Åpner semaphore 1
	if(sem_prod == SEM_FAILED){
		printf("EROOR1");
		exit(1);
	}

	sleep(0.5);	// Da funker det..

	sem_receiv = sem_open(SEM_RECEIVER_NAME, O_CREAT, 0644, 1);		// Åpner semaphore 2   --  Legg til comment for "value"
	if(sem_receiv == SEM_FAILED){
		printf("EROOR2");
		exit(1);
	}
		
	pthread_t pThread1;	
	
	
 	pthread_create (&pThread1, NULL, PrintMessage, (void *) ms);

	int t = 0;
	while(1){
		sem_wait(sem_receiv);
		
		//printf("Strlen: %li\n", strlen(ms->buff));
		if((ms->totalLetters) % 10 != 0 && strlen(ms->buff) > 0){		// Kan være midtlertidig løsning, usikker hva som skjer hvis siste er 10 bokstaver
			printf("Fra main: %s\n", ms->buff);			// Skjønner feilen hvis man ser på denne i console, flere ganger
			sem_post(sem_prod);
			break;
		}	
		if(strlen(ms->buff) > 0){
			printf("Fra main: %s", ms->buff);
			
			printf("\n\n");
			//memset(ms->buff,'0',sizeof(MyStruct));
			//sem_post(sem_prod);
		}
		sem_post(sem_prod);
	}
	
	
   	pthread_join(pThread1, NULL);  // Wait for thread 1 to finish.
   	
   	sem_close(sem_prod);
   	sem_close(sem_receiv);   

	free(ms);
   	//printf("After thread finished.\n");
}
